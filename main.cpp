#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include "Menu.h"
#include "Handler.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/src/icon.ico"));

//  DANG KI TYPE VOI QML
    qmlRegisterType<MyMenu>("MyMenu",1,0,"MyMenu");
    qmlRegisterType<Handler>("Handler",1,0,"Handler");


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
