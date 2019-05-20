#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include "ExampleQmlObject.h"
#include "ChildQmlObject.h"
#include "QmlSharedPointer.h"
#include <QDebug>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    qmlRegisterType<ExampleQmlObject>("com.example.qsp", 1, 0, "ExampleQmlObject");
    qmlRegisterType<QmlSharedPointer<ExampleQmlObject>>("com.example.qsp", 1, 0, "ExampleQmlObjectSP");
    qmlRegisterType<QmlSharedPointer<ChildQmlObject>>("com.example.qsp", 1, 0, "ChildQmlObjectSP");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QString("../src/main.qml")));
    if (engine.rootObjects().isEmpty()) return 1;
    return app.exec();
}
