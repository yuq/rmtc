#include <QCoreApplication>
#include <Server>
#include <ServerProtocolListenerTcp>
#include "rmtc_services.h"
#include <unistd.h>

int server_main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);
	QtRpc::Server srv;
	QtRpc::ServerProtocolListenerTcp tcp(&srv);
	if(!tcp.listen(QHostAddress::Any, 6768)) {
		qCritical() << "Failed to listen on port 6768!";
		sleep(10);
		return 1;
	}
	srv.registerService<RMTCServices>("RMTC");
    return a.exec();
}
