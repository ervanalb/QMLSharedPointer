#pragma once

#include <QObject>
#include "QmlSharedPointer.h"

class ExampleQmlObject;
typedef QmlSharedPointer<ExampleQmlObject>ExampleQmlObjectSP;

class ExampleQmlObject : public QObject {
    Q_OBJECT

    Q_PROPERTY(int integer MEMBER m_integer NOTIFY integerChanged);
    Q_PROPERTY(QString string MEMBER m_string NOTIFY stringChanged);
    Q_PROPERTY(int five READ getFive WRITE setFive);

signals:
    void integerChanged(int integer);
    void stringChanged(QString string);
    void signalFired();

public:
    ExampleQmlObject();
    ~ExampleQmlObject();

public slots:
    int addToInteger(int number1, int number2);
    QString addToString(QString str1, QString str2);
    void fireSignal();
    int getFive();
    void setFive(int five);
    ExampleQmlObjectSP *frobObject(ExampleQmlObjectSP *object);

private:
    int m_integer{};
    QString m_string{};
};

//typedef QmlSharedPointer<ExampleQmlObject>ExampleQmlObjectSP;
Q_DECLARE_METATYPE(ExampleQmlObjectSP*);
