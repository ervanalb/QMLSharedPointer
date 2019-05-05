import QtQuick 2.0
import com.example.qsp 1.0

Item {
    ExampleQmlObject {
        id: o;

        onIntegerChanged: {
            console.log("Integer set to " + integer);
        }

        onStringChanged: {
            console.log("String set to " + string);
        }

        onSignalFired: {
            console.log("Signal fired!");
        }
    }

    Component.onCompleted: {
        console.log("Created a QML object!");

        o.string = "a";
        console.log(o.addToString("b", "c"));

        o.integer = 1;
        console.log(o.addToInteger(2, 3));

        o.fireSignal();

        Qt.callLater(Qt.quit);
    }
}
