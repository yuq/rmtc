#ifndef RMTC_SERVICES_H
#define RMTC_SERVICES_H

#include <ClientProxy>

class RMTCServices : public QtRpc::ClientProxy
{
	Q_OBJECT
	QTRPC_CLIENTPROXY(RMTCServices)
public:
	RMTCServices(QObject *parent = 0);

	Q_INVOKABLE bool doSetChannel(int ch, bool high);

private:

signals:
	ReturnValue setChannel(int ch, bool high);
};

#endif // RMTC_SERVICES_H
