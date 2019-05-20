#pragma once

#include "ExampleQmlObject.h"

class ChildQmlObject : public ExampleQmlObject {
    Q_OBJECT

    Q_PROPERTY(int four READ getFour WRITE setFour);

public:
    ChildQmlObject();

public slots:
    int getFour();
    void setFour(int four);
};
