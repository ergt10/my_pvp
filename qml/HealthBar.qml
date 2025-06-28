import QtQuick 2.15

Rectangle {
    id: healthBar
    
    property var playerViewModel: null
    property color barColor: "#E74C3C"
    property real healthPercentage: playerViewModel ? playerViewModel.healthPercentage : 1.0
    
    color: "#34495E"
    border.color: "#ECF0F1"
    border.width: 1
    radius: 3
    
    Rectangle {
        id: healthFill
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 2
        width: (parent.width - 4) * healthPercentage
        radius: 2
        
        Behavior on width {
            NumberAnimation { duration: 200 }
        }
        
        // 血条颜色根据血量变化
        color: {
            if (healthPercentage > 0.6) return "#2ECC71"
            else if (healthPercentage > 0.3) return "#F39C12"
            else return "#E74C3C"
        }
    }
    
    Text {
        anchors.centerIn: parent
        text: playerViewModel ? playerViewModel.health + " / " + playerViewModel.maxHealth : "100 / 100"
        color: "#ECF0F1"
        font.pixelSize: 10
        font.bold: true
    }
} 