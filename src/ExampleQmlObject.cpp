#include "ExampleQmlObject.h"
#include <QDebug>
#include <QQmlEngine>

ExampleQmlObject::ExampleQmlObject() {
    qDebug() << "Constructed!" << this;
}

int ExampleQmlObject::addToInteger(int number1, int number2) {
    return m_integer + number1 + number2;
}

QString ExampleQmlObject::addToString(QString string1, QString string2) {
    return m_string + string1 + string2;
}

void ExampleQmlObject::fireSignal() {
    emit signalFired();
}

int ExampleQmlObject::getFive() {
    qDebug() << "in getFive: this is" << this;
    qDebug() << "in getFive: integer is" << m_integer;
    qDebug() << "in getFive: string is" << m_string;
    return 5;
}

void ExampleQmlObject::setFive(int five) {
    qDebug() << "You can't change five!";
}

ExampleQmlObject::~ExampleQmlObject() {
    qDebug() << "Destructed!" << this;
}
