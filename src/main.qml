import QtQuick 2.0
import com.example.qsp 1.0

QtObject {
    Component.onCompleted: {
        var o = Factory.makeExampleQmlObject();

        o.stringChanged.connect(function(v) {
            console.log("String changed to " + v);
        })
        o.integerChanged.connect(function(v) {
            console.log("Integer changed to " + v);
        })
        o.signalFired.connect(function() {
            console.log("Signal fired!");
        })

        console.log("Created a QML object!");

        o.string = "a";
        console.log(o.addToString("b", "c"));

        o.integer = 1;
        console.log(o.addToInteger(2, 3));

        o.fireSignal();

        Qt.callLater(Qt.quit);
    }
}
