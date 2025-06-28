import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: gameUI
    
    // Top UI container
    Rectangle {
        id: topUI
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 80
        color: "#2C3E50"
        opacity: 0.9
        
        Row {
            anchors.fill: parent
            anchors.margins: 10
            
            // Player 1 UI
            Column {
                width: parent.width * 0.4
                height: parent.height
                
                Text {
                    text: "Player 1"
                    color: "#ECF0F1"
                    font.pixelSize: 16
                    font.bold: true
                }
                
                HealthBar {
                    id: player1HealthBar
                    width: parent.width
                    height: 20
                    playerViewModel: gameViewModel.player1
                    barColor: "#E74C3C"
                }
                
                EnergyBar {
                    id: player1EnergyBar
                    width: parent.width
                    height: 15
                    playerViewModel: gameViewModel.player1
                    barColor: "#3498DB"
                }
            }
            
            // Center time display
            Column {
                width: parent.width * 0.2
                height: parent.height
                
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Time"
                    color: "#ECF0F1"
                    font.pixelSize: 14
                }
                
                Rectangle {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 80
                    height: 40
                    color: "#34495E"
                    radius: 5
                    border.color: "#ECF0F1"
                    border.width: 2
                    
                    Text {
                        anchors.centerIn: parent
                        text: gameViewModel.timeRemaining
                        color: gameViewModel.timeRemaining <= 10 ? "#E74C3C" : "#ECF0F1"
                        font.pixelSize: 24
                        font.bold: true
                    }
                }
            }
            
            // Player 2 UI
            Column {
                width: parent.width * 0.4
                height: parent.height
                
                Text {
                    anchors.right: parent.right
                    text: "Player 2"
                    color: "#ECF0F1"
                    font.pixelSize: 16
                    font.bold: true
                }
                
                HealthBar {
                    id: player2HealthBar
                    anchors.right: parent.right
                    width: parent.width
                    height: 20
                    playerViewModel: gameViewModel.player2
                    barColor: "#E74C3C"
                }
                
                EnergyBar {
                    id: player2EnergyBar
                    anchors.right: parent.right
                    width: parent.width
                    height: 15
                    playerViewModel: gameViewModel.player2
                    barColor: "#3498DB"
                }
            }
        }
    }
    
    // Game state indicator
    Rectangle {
        id: stateIndicator
        anchors.centerIn: parent
        width: 200
        height: 50
        color: "#2C3E50"
        opacity: gameViewModel.gameState !== "fighting" ? 0.9 : 0
        radius: 10
        
        Behavior on opacity {
            NumberAnimation { duration: 300 }
        }
        
        Text {
            anchors.centerIn: parent
            text: getStateText()
            color: "#ECF0F1"
            font.pixelSize: 18
            font.bold: true
        }
        
        function getStateText() {
            switch (gameViewModel.gameState) {
                case "menu": return "Menu"
                case "fighting": return ""
                case "paused": return "Paused"
                case "gameOver": return "Game Over"
                default: return ""
            }
        }
    }
    
    // Bottom control hints
    Rectangle {
        id: controlHints
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 10
        width: 600
        height: 60
        color: "#2C3E50"
        opacity: 0.8
        radius: 5
        
        Row {
            anchors.centerIn: parent
            spacing: 40
            
            Column {
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Player 1 Controls"
                    color: "#3498DB"
                    font.pixelSize: 12
                    font.bold: true
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "WASD Move, J/K/L Attack, U Block"
                    color: "#ECF0F1"
                    font.pixelSize: 10
                }
            }
            
            Column {
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Player 2 Controls"
                    color: "#E74C3C"
                    font.pixelSize: 12
                    font.bold: true
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Arrows Move, 1/2/3 Attack, 0 Block"
                    color: "#ECF0F1"
                    font.pixelSize: 10
                }
            }
        }
    }
} 