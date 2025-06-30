import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: gameScreen
    objectName: "gameScreen"
    color: "#87CEEB" // 备用颜色，如果图片加载失败则显示
    focus: true
    
    signal backToMenu()
    
    // 背景图片
    Image {
        id: backgroundImage
        anchors.fill: parent
        source: "image://sprites/background_default"
        fillMode: Image.PreserveAspectCrop
        
        // 如果图片加载失败，显示纯色背景
        onStatusChanged: {
            if (status === Image.Error) {
                visible = false
                console.log("背景图片加载失败，使用纯色背景")
            }
        }
    }
    
    // Ground
    Rectangle {
        id: ground
        anchors.bottom: parent.bottom
        width: parent.width
        height: 150
        color: "#228B22"
        
        Rectangle {
            anchors.top: parent.top
            width: parent.width
            height: 5
            color: "#32CD32"
        }
    }
    
    // Game UI
    GameUI {
        id: gameUI
        anchors.fill: parent
    }
    
    // Player characters
    PlayerCharacter {
        id: player1Character
        playerId: 1
        playerViewModel: gameViewModel.player1
        
        x: playerViewModel ? playerViewModel.position.x - width/2 : 200
        y: playerViewModel ? playerViewModel.position.y - height : 350
        
        Behavior on x {
            NumberAnimation { duration: 50 }
        }
        
        Behavior on y {
            NumberAnimation { duration: 50 }
        }
    }
    
    PlayerCharacter {
        id: player2Character
        playerId: 2
        playerViewModel: gameViewModel.player2
        
        x: playerViewModel ? playerViewModel.position.x - width/2 : 600
        y: playerViewModel ? playerViewModel.position.y - height : 350
        
        Behavior on x {
            NumberAnimation { duration: 50 }
        }
        
        Behavior on y {
            NumberAnimation { duration: 50 }
        }
    }
    
    // Pause menu
    Dialog {
        id: pauseDialog
        anchors.centerIn: parent
        title: "Game Paused"
        modal: true
        
        contentItem: Column {
            spacing: 20
            
            Button {
                text: "Continue Game"
                onClicked: {
                    pauseDialog.close()
                    gameViewModel.resumeGame()
                }
            }
            
            Button {
                text: "Back to Menu"
                onClicked: {
                    pauseDialog.close()
                    backToMenu()
                }
            }
        }
    }
    
    // ESC key pause
    Keys.onPressed: function(event) {
        if (event.key === Qt.Key_Escape) {
            if (gameViewModel.gameState === "fighting") {
                gameViewModel.pauseGame()
                pauseDialog.open()
            } else if (gameViewModel.gameState === "paused") {
                pauseDialog.close()
                gameViewModel.resumeGame()
            }
            event.accepted = true
        }
    }
} 