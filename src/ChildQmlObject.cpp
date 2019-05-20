#include "ChildQmlObject.h"
#include <QDebug>

ChildQmlObject::ChildQmlObject() {
    qDebug() << "Constructed!" << this;
}

int ChildQmlObject::getFour() {
    qDebug() << "in getFour: this is" << this;
    qDebug() << "in getFour: five is" << getFive();
    return 4;
}

void ChildQmlObject::setFour(int four) {
    qDebug() << "You can't change four!";
}
