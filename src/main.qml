import QtQuick 2.0
import com.example.qsp 1.0

Item {
    ChildQmlObjectSP {
    //ExampleQmlObjectSP {
        id: o

        onStringChanged: {
            console.log("String changed to " + string);
        }
        onIntegerChanged: {
            console.log("Integer changed to " + integer);
        }
        onSignalFired: {
            console.log("Signal fired!");
        }
    }

    Component.onCompleted: {
        console.log("Got " + o);

        console.log("Created a QML object!");

        o.string = "a";
        console.log(o.addToString("b", "c"));

        o.integer = 1;
        console.log(o.addToInteger(2, 3));

        o.fireSignal();

        o.five = 6;
        console.log(o.five);

        Qt.callLater(Qt.quit);
    }
}
