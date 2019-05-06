#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include "ExampleQmlObject.h"
#include "QmlSharedPointer.h"
#include <QDebug>

//Q_DECLARE_METATYPE(QmlSharedPointer<ExampleQmlObject>*)
//Q_DECLARE_METATYPE_TEMPLATE_1ARG(QmlSharedPointer<ExampleQmlObject>*)

class Factory : public QObject {
    Q_OBJECT

public slots:
    ExampleQmlObject *makeExampleQmlObject() {
        auto o = new ExampleQmlObject();
        QQmlEngine::setObjectOwnership(o, QQmlEngine::JavaScriptOwnership);
        return o;
    }

    QmlSharedPointer<ExampleQmlObject> *makeExampleQmlObjectSP() {
        auto o = new QmlSharedPointer<ExampleQmlObject>(new ExampleQmlObject());
        qDebug() << "Factory made" << o;
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

    //qRegisterMetaType<QmlSharedPointer<ExampleQmlObject>*>();
    qmlRegisterSingletonType<Factory>("com.example.qsp", 1, 0, "Factory", &provider);
    qmlRegisterType<ExampleQmlObject>("com.example.qsp", 1, 0, "ExampleQmlObject");

    qDebug() << QmlSharedPointer<ExampleQmlObject>::staticMetaObject.className();

    //auto mo = QmlSharedPointer<ExampleQmlObject>::staticMetaObject;
    //qDebug() << mo.className();

    //qmlRegisterUncreatableType<QmlSharedPointer<ExampleQmlObject>>("com.example.qsp", 1, 0, "ExampleQmlObjectSP", "Can't create shared pointers from within QML");
    qmlRegisterType<QmlSharedPointer<ExampleQmlObject>>("com.example.qsp", 1, 0, "ExampleQmlObjectSP");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QString("../src/main.qml")));
    if (engine.rootObjects().isEmpty()) return 1;
    return app.exec();
}

#include "main.moc"
