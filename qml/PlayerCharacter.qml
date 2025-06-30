import QtQuick 2.15

Item {
    id: playerCharacter
    width: 80
    height: 80
    
    property int playerId: 1
    property var playerViewModel: null
    property string currentAnimation: playerViewModel ? playerViewModel.currentAnimation : "idle"
    property bool facingRight: playerViewModel ? playerViewModel.facingRight : true
    
    Image {
        id: characterSprite
        anchors.fill: parent
        source: {
            var spriteId = "player" + playerId + "_" + currentAnimation;
            return "image://sprites/" + spriteId;
        }
    }
    
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
    
    Rectangle {
        anchors.right: facingRight ? parent.right : undefined
        anchors.left: facingRight ? undefined : parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: -10
        width: getWeaponLength()
        height: 4
        color: getWeaponColor()
        radius: 2
        
        // 武器光芒
        Rectangle {
            anchors.centerIn: parent
            width: parent.width * 0.7
            height: 2
            color: "#FFFFFF"
            opacity: currentAnimation.includes("attack") ? 0.8 : 0.2
            radius: 1
            
            Behavior on opacity {
                NumberAnimation { duration: 150 }
            }
        }
        
        // 根据动画状态调整武器长度
        function getWeaponLength() {
            switch (currentAnimation) {
                case "light_attack": return 18
                case "heavy_attack": return 22
                case "special_attack": return 26
                case "block": return 12
                default: return 15
            }
        }
        
        // 根据动画状态调整武器颜色
        function getWeaponColor() {
            switch (currentAnimation) {
                case "light_attack": return "#FFA500"  // 橙色
                case "heavy_attack": return "#FF4500"  // 红橙色
                case "special_attack": return "#FF0000" // 红色
                case "block": return "#4169E1"         // 蓝色
                default: return "#C0C0C0"              // 银色
            }
        }
        
        // 平滑过渡动画
        Behavior on width {
            NumberAnimation { duration: 200 }
        }
        
        Behavior on color {
            ColorAnimation { duration: 200 }
        }
    }
    
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
    
    onCurrentAnimationChanged: {
        if (currentAnimation.includes("attack")) {
            attackAnimation.start()
        }
    }
    
    transform: Scale {
        xScale: facingRight ? 1 : -1
        origin.x: playerCharacter.width / 2
    }
} 