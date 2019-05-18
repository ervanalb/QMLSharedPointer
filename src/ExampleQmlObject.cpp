#include "ExampleQmlObject.h"
#include <QDebug>
#include <QQmlEngine>

ExampleQmlObject::ExampleQmlObject() {
    qDebug() << "Constructed!" << this;
}

int ExampleQmlObject::addToInteger(int number1, int number2) {
    qDebug() << this << "object's QML context:" << QQmlEngine::contextForObject(this);
    return m_integer + number1 + number2;
}

QString ExampleQmlObject::addToString(QString string1, QString string2) {
    return m_string + string1 + string2;
}

void ExampleQmlObject::fireSignal() {
    emit signalFired();
}

int ExampleQmlObject::getFive() {
    qDebug() << "this is" << this;
    qDebug() << "integer" << m_integer;
    qDebug() << "string" << m_string;
    return 5;
}

void ExampleQmlObject::setFive(int five) {
    qDebug() << "this is" << this;
    qDebug() << "You can't change five!";
}

ExampleQmlObject::~ExampleQmlObject() {
    qDebug() << "Destructed!" << this;
}
