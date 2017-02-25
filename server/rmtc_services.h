#ifndef RMTC_SERVICES_H
#define RMTC_SERVICES_H

#include <ServiceProxy>
#include "gpio.h"

class RMTCServices : public QtRpc::ServiceProxy
{
    Q_OBJECT
public:
	RMTCServices(QObject *parent = 0);

	virtual ReturnValue auth(QString user, QString passwd);

public slots:
	ReturnValue setChannel(int ch, bool high);

private:
	const static int NUM_GPIO = 4;
	GPIO *mGPIOs[NUM_GPIO];
};

#endif // RMTC_SERVICES_H
