#include "rmtc_services.h"
#include <QDebug>


RMTCServices::RMTCServices(QObject *parent)
	: ServiceProxy(parent)
{
	for (int i = 0; i < NUM_GPIO; i++) {
		mGPIOs[i] = new GPIO(this);
		mGPIOs[i]->setDirection(false);
		mGPIOs[i]->setValue(false);
	}

	// IO-0 PA1 CH1
	mGPIOs[0]->setNumber(32 * 0 + 1);
	// IO-1 PD14 CH2
	mGPIOs[1]->setNumber(32 * 3 + 14);
	// IO-2 PA0 CH3
	mGPIOs[2]->setNumber(32 * 0 + 0);
	// IO-3 PA3 CH4
	mGPIOs[3]->setNumber(32 * 0 + 3);
}

ReturnValue RMTCServices::auth(QString user, QString passwd)
{
	(void)user;
	(void)passwd;
	qDebug() << "auth";
	return true;
}

ReturnValue RMTCServices::setChannel(int ch, bool high)
{
	if (ch < 0 || ch >= NUM_GPIO)
		return false;
	mGPIOs[ch]->setValue(high);
	return true;
}
