import QtQuick 2.15

Rectangle {
    id: playerCharacter
    width: 80
    height: 80
    
    property int playerId: 1
    property var playerViewModel: null
    property string currentAnimation: playerViewModel ? playerViewModel.currentAnimation : "idle"
    property bool facingRight: playerViewModel ? playerViewModel.facingRight : true
    
    color: playerId === 1 ? "#3498DB" : "#E74C3C"
    border.color: "#ECF0F1"
    border.width: 2
    radius: 5
    
    // Character ID display
    Text {
        anchors.centerIn: parent
        text: "P" + playerId
        font.pixelSize: 20
        font.bold: true
        color: "white"
    }
    
    // Animation state indicator
    Rectangle {
        anchors.top: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 5
        width: parent.width
        height: 20
        color: getAnimationColor()
        radius: 3
        
        Text {
            anchors.centerIn: parent
            text: currentAnimation
            font.pixelSize: 10
            color: "white"
        }
        
        function getAnimationColor() {
            switch (currentAnimation) {
                case "idle": return "#7F8C8D"
                case "walk": return "#3498DB"
                case "jump": return "#9B59B6"
                case "light_attack": return "#F39C12"
                case "heavy_attack": return "#E67E22"
                case "special_attack": return "#E74C3C"
                case "block": return "#27AE60"
                case "crouch": return "#8E44AD"
                default: return "#95A5A6"
            }
        }
    }
    
    // Facing direction indicator
    Rectangle {
        anchors.right: facingRight ? parent.right : undefined
        anchors.left: facingRight ? undefined : parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: -10
        width: 15
        height: 5
        color: "#F1C40F"
        radius: 2
    }
    
    // Attack effect
    Rectangle {
        id: attackEffect
        anchors.centerIn: parent
        width: parent.width + 20
        height: parent.height + 20
        color: "transparent"
        border.color: "#F39C12"
        border.width: 3
        radius: 10
        opacity: 0
        
        PropertyAnimation {
            id: attackAnimation
            target: attackEffect
            property: "opacity"
            from: 0.8
            to: 0
            duration: 200
        }
    }
    
    // Listen for attack animations
    onCurrentAnimationChanged: {
        if (currentAnimation.includes("attack")) {
            attackAnimation.start()
        }
    }
    
    // Transform effect
    transform: Scale {
        xScale: facingRight ? 1 : -1
        origin.x: playerCharacter.width / 2
    }
} 