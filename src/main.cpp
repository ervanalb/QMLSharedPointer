#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include "ExampleQmlObject.h"

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    qmlRegisterType<ExampleQmlObject>("com.example.qsp", 1, 0, "ExampleQmlObject");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QString("../src/main.qml")));
    if (engine.rootObjects().isEmpty()) return 1;
    return app.exec();
}
