import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: mainWindow
    width: 800
    height: 600
    visible: true
    title: "PvP Fighting Game - Death vs Naruto Style"
    
    // Game state management
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: menuScreen
        focus: true
        
        Component {
            id: menuScreen
            MenuScreen {
                onStartGame: {
                    stackView.push(gameScreen)
                    gameViewModel.startGame()
                }
            }
        }
        
        Component {
            id: gameScreen
            GameScreen {
                onBackToMenu: {
                    stackView.pop()
                    gameViewModel.resetGame()
                }
            }
        }
        
        // Global key handling
        Keys.onPressed: function(event) {
            if (stackView.currentItem && stackView.currentItem.objectName === "gameScreen") {
                gameViewModel.handleKeyPress(event.key)
                event.accepted = true
            }
        }
        
        Keys.onReleased: function(event) {
            if (stackView.currentItem && stackView.currentItem.objectName === "gameScreen") {
                gameViewModel.handleKeyRelease(event.key)
                event.accepted = true
            }
        }
    }
    
    // Game end handling
    Connections {
        target: gameViewModel
        function onGameEnded(winnerId) {
            gameEndDialog.winnerId = winnerId
            gameEndDialog.open()
        }
    }
    
    // Game end dialog
    Dialog {
        id: gameEndDialog
        anchors.centerIn: parent
        width: 450
        height: 350
        title: "Game Over"
        modal: true
        
        property int winnerId: 0
        
        contentItem: Item {
            width: parent.width
            height: parent.height
            
            Column {
                anchors.centerIn: parent
                spacing: 40
                width: parent.width - 40
                
                Text {
                    width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Player " + gameEndDialog.winnerId + " Wins!"
                    font.pixelSize: 32
                    font.bold: true
                    color: "#2C3E50"
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap
                    
                    Rectangle {
                        anchors.centerIn: parent
                        width: parent.contentWidth + 30
                        height: parent.contentHeight + 15
                        color: "#F8F9FA"
                        radius: 10
                        z: -1
                        border.color: "#E9ECEF"
                        border.width: 2
                    }
                }
                
                Column {
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    
                    Button {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Play Again"
                        width: 150
                        height: 50
                        font.pixelSize: 16
                        font.bold: true
                        
                        background: Rectangle {
                            color: parent.pressed ? "#27AE60" : "#2ECC71"
                            radius: 10
                            border.color: "#229954"
                            border.width: 2
                        }
                        
                        contentItem: Text {
                            text: parent.text
                            font: parent.font
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        
                        onClicked: {
                            gameEndDialog.close()
                            gameViewModel.resetGame()
                            gameViewModel.startGame()
                        }
                    }
                    
                    Button {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Back to Menu"
                        width: 150
                        height: 50
                        font.pixelSize: 16
                        font.bold: true
                        
                        background: Rectangle {
                            color: parent.pressed ? "#2980B9" : "#3498DB"
                            radius: 10
                            border.color: "#2471A3"
                            border.width: 2
                        }
                        
                        contentItem: Text {
                            text: parent.text
                            font: parent.font
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        
                        onClicked: {
                            gameEndDialog.close()
                            stackView.pop()
                            gameViewModel.resetGame()
                        }
                    }
                }
            }
        }
        
        // 添加背景样式
        background: Rectangle {
            color: "#FFFFFF"
            radius: 15
            border.color: "#BDC3C7"
            border.width: 3
            
            // 添加阴影效果
            Rectangle {
                anchors.fill: parent
                anchors.margins: -8
                color: "transparent"
                border.color: "#34495E"
                border.width: 1
                radius: 18
                opacity: 0.2
                z: -1
            }
        }
    }
} 