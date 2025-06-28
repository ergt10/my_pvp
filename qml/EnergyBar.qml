import QtQuick 2.15

Rectangle {
    id: energyBar
    
    property var playerViewModel: null
    property color barColor: "#3498DB"
    property real energyPercentage: playerViewModel ? playerViewModel.energyPercentage : 1.0
    
    color: "#34495E"
    border.color: "#ECF0F1"
    border.width: 1
    radius: 3
    
    Rectangle {
        id: energyFill
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 1
        width: (parent.width - 2) * energyPercentage
        color: barColor
        radius: 2
        
        Behavior on width {
            NumberAnimation { duration: 150 }
        }
    }
    
    Text {
        anchors.centerIn: parent
        text: playerViewModel ? playerViewModel.energy + " / " + playerViewModel.maxEnergy : "100 / 100"
        color: "#ECF0F1"
        font.pixelSize: 8
    }
} 