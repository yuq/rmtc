#ifndef _GPIO_H_
#define _GPIO_H_

#include <QTimer>
#include <QSocketNotifier>

class GPIO : public QObject
{
	Q_OBJECT

public:
	explicit GPIO(QObject *parent = 0);
	~GPIO();

	bool value();
	int number() { return mNumber; }
	// true for input
	bool direction() { return mDirection; }

	void setNumber(int);
	void setValue(bool);
	void setDirection(bool);

signals:
	void valueChanged(bool);

private:
	int mNumber;
	bool mDirection;
	int mFd;

	void enable();
	void disable();

	void echo(const std::string &file, const std::string &value);

#ifdef CONFIG_ASYNC_GPIO
	QSocketNotifier *mNotifier;

private slots:
	void onValueChanged(int fd);
#else
	static const int mInterval = 500;
	bool mValue;
	QTimer mTimer;

private slots:
	void onTimeout();
#endif

};

#endif // _GPIO_H
