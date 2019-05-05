import QtQuick 2.0

QtObject {
    Component.onCompleted: {
        console.log("Created a QML object!");
        Qt.callLater(Qt.quit);
    }
}
