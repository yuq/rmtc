#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include "rmtc_services.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

	RMTCServices srv;
	ReturnValue ret = srv.connect("tcp://orangepi.local:6768/RMTC");
	if(ret.isError()) {
		qCritical() << "Failed to connect:" << ret;
		return 1;
	}

	QQuickView view;
	view.rootContext()->setContextProperty("rmtc", &srv);
	view.setSource(QUrl("main.qml"));
	view.show();

    return app.exec();
}
