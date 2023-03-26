import QtQuick 2.12
import QtGraphicalEffects 1.0
Image {
//    property string cSource: "/svg/right.svg"
    property string cColor: 'red'
//    source: cSource
    ColorOverlay {
        anchors.fill: parent
        source: parent
        color: cColor
    }
}
