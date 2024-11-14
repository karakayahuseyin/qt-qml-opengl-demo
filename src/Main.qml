import QtQuick 2.15
import QtQuick.Controls 2.15
import QmlOpenGL 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "OpenGL Test"

    Rectangle {
        anchors.fill: parent
        color: "#222222"

        OpenGLItem {
            width: parent.width
            height: parent.height
            anchors.centerIn: parent
        }
    }
}
