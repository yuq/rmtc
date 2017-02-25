#include <QDebug>
#include <QDir>

#include <fcntl.h>
#include <unistd.h>

#include "gpio.h"


GPIO::GPIO(QObject *parent)
	: QObject(parent), mNumber(-1), mDirection(true), mFd(-1)
{
#ifdef CONFIG_ASYNC_GPIO
	mNotifier = NULL;
#else
	mValue = true;
	mTimer.setInterval(mInterval);
	mTimer.setSingleShot(false);
	connect(&mTimer, SIGNAL(timeout()), SLOT(onTimeout()));
#endif
}

GPIO::~GPIO()
{
	disable();
}

bool GPIO::value()
{
	char v;
	int ret = lseek(mFd, 0, SEEK_SET);
	if (ret != 0) {
		qCritical() << "seek gpio port fail: " << mNumber;
		return false;
	}

	ret = read(mFd, &v, 1);
	if (ret < 1) {
		qCritical() << "get gpio port fail: " << mNumber << ret << mFd;
		return false;
	}

	if (v == '0')
		return false;
	else
		return true;
}

void GPIO::setNumber(int n)
{
	if (mNumber == n)
		return;

	disable();
	mNumber = n;
	enable();
}

void GPIO::setValue(bool high)
{
	if (mDirection)
		return;

	int ret = lseek(mFd, 0, SEEK_SET);
	if (ret != 0) {
		qCritical() << "seek gpio port fail: " << mNumber;
		return;
	}

	std::string v;
	if (high)
		v = "1";
	else
		v = "0";

	ret = write(mFd, v.c_str(), v.size());
	if (ret < (int)v.size()) {
		qCritical() << "set gpio port fail: " << mNumber << ret << v.size();
		return;
	}
}

void GPIO::setDirection(bool input)
{
	if (mDirection == input)
		return;

	disable();
	mDirection = input;
	enable();
}

#ifdef CONFIG_ASYNC_GPIO
void GPIO::onValueChanged(int fd)
{
	(void)fd;
	emit valueChanged(value());
}
#else
void GPIO::onTimeout()
{
	if (mValue != value()) {
		mValue = !mValue;
		emit valueChanged(mValue);
	}
}
#endif

void GPIO::echo(const std::string &file, const std::string &value)
{
	int fd = open(file.c_str(), O_WRONLY);
	if (fd < 0) {
		qCritical() << "echo open gpio file fail: " << mNumber;
		return;
	}

	int ret = write(fd, value.c_str(), value.size());
	if (ret < (int)value.size())
		qCritical() << "echo write gpio file fail: " << mNumber;

	close(fd);
}

void GPIO::enable()
{
	if (mNumber < 0)
		return;

	QString gpiodir = "/sys/class/gpio/gpio" + QString::number(mNumber);

	if (!QDir(gpiodir).exists())
		echo("/sys/class/gpio/export", QString::number(mNumber).toStdString());

	if (!QDir(gpiodir).exists()) {
		qCritical() << "fail to create gpio dir: " << gpiodir;
		return;
	}

	int flags;
	std::string dir = gpiodir.toStdString();
	if (mDirection) {
		echo(dir + "/direction", "in");
		echo(dir + "/edge", "both");
		flags = O_RDONLY;
	}
	else {
		echo(dir + "/direction", "out");
		flags = O_RDWR;
	}

	int fd = open((dir + "/value").c_str(), flags);
	if (fd < 0) {
		qCritical() << "open gpio value fail: " << mNumber;
		return;
	}
	mFd = fd;

	if (mDirection) {
#ifdef CONFIG_ASYNC_GPIO
		mNotifier = new QSocketNotifier(mFd, QSocketNotifier::Exception, this);
		connect(mNotifier, SIGNAL(activated(int)), SLOT(onValueChanged(int)));
#else
		mValue = value();
		mTimer.start();
#endif
	}

	qCritical() << "gpio enabled: " << mNumber;
}

void GPIO::disable()
{
#ifdef CONFIG_ASYNC_GPIO
	if (mNotifier) {
		delete mNotifier;
		mNotifier = NULL;
	}
#else
	mTimer.stop();
#endif
	if (mFd > 0) {
		close(mFd);
		mFd = -1;
	}
}
