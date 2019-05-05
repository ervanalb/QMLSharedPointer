#include "ExampleQmlObject.h"

ExampleQmlObject::ExampleQmlObject() {
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
