#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "includes/uicontroller.h"
#include "includes/backendlogic.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QCoreApplication::setOrganizationName("Four Directions");
    QCoreApplication::setApplicationName("ExamOop");

    qmlRegisterUncreatableType<DataTypesEnums>("SortVisualizer",1,0,"DataTypes",
                                               QStringLiteral("This object should not be created in qml"));
    qmlRegisterUncreatableType<SortsEnums>("SortVisualizer",1,0,"SortChoice",
                                           QStringLiteral("This object should not be created in qml"));

    UiController controller;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(QStringLiteral("UiController"), &controller);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
