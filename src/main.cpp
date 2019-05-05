#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include "ExampleQmlObject.h"
#include "QmlSharedPointer.h"
#include <QDebug>

class Factory : public QObject {
    Q_OBJECT

public slots:
    ExampleQmlObject *makeExampleQmlObject() {
        auto o = new ExampleQmlObject();
        QQmlEngine::setObjectOwnership(o, QQmlEngine::JavaScriptOwnership);
        return o;
    }

    QmlSharedPointer<ExampleQmlObject> makeExampleQmlObjectSP() {
        QmlSharedPointer<ExampleQmlObject> o(new ExampleQmlObject());
        return o;
    }
};

static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new Factory(); 
}

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    qmlRegisterSingletonType<Factory>("com.example.qsp", 1, 0, "Factory", &provider);
    qmlRegisterType<ExampleQmlObject>("com.example.qsp", 1, 0, "ExampleQmlObject");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QString("../src/main.qml")));
    if (engine.rootObjects().isEmpty()) return 1;
    return app.exec();
}

#include "main.moc"
