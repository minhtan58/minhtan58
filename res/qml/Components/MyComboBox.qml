import QtQuick 2.12
import QtQuick.Controls 2.12
import "Global.js" as Global
ComboBox {
    property int cWidth: 100
    property int cHeight: 40
    signal selected()
    background: Rectangle {
        implicitWidth: cWidth
        implicitHeight: cHeight
        color: enabled ? "transparent" : "lightgray"
        border {width: 1; color: '#bbbbbb'}
    }
    onActivated: {
        selected();
    }
}
