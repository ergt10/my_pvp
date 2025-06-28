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
        width: 300
        height: 200
        title: "Game Over"
        modal: true
        
        property int winnerId: 0
        
        contentItem: Column {
            spacing: 20
            width: parent.width - 40
            anchors.centerIn: parent
            
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Player " + gameEndDialog.winnerId + " Wins!"
                font.pixelSize: 24
                color: "#333333"
            }
            
            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 20
                
                Button {
                    text: "Play Again"
                    width: 100
                    height: 40
                    onClicked: {
                        gameEndDialog.close()
                        gameViewModel.resetGame()
                        gameViewModel.startGame()
                    }
                }
                
                Button {
                    text: "Back to Menu"
                    width: 100
                    height: 40
                    onClicked: {
                        gameEndDialog.close()
                        stackView.pop()
                        gameViewModel.resetGame()
                    }
                }
            }
        }
    }
} 