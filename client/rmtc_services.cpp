#include "rmtc_services.h"

RMTCServices::RMTCServices(QObject *parent)
	: ClientProxy(parent)
{

}

bool RMTCServices::doSetChannel(int ch, bool high)
{
	ReturnValue ret = setChannel(ch, high);
	if(ret.isError()) {
		qCritical() << "Failed to call setChannel():" << ret;
		return false;
	}
	return ret.toBool();
}
