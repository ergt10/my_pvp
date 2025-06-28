import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: menuScreen
    color: "#2C3E50"
    
    signal startGame()
    
    Column {
        anchors.centerIn: parent
        spacing: 30
        
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "PvP Fighting Game"
            font.pixelSize: 48
            font.bold: true
            color: "#ECF0F1"
        }
        
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Death vs Naruto Style"
            font.pixelSize: 24
            color: "#BDC3C7"
        }
        
        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 15
            
            Button {
                text: "Start Game"
                font.pixelSize: 18
                width: 200
                height: 50
                
                background: Rectangle {
                    color: parent.pressed ? "#27AE60" : "#2ECC71"
                    radius: 5
                }
                
                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                
                onClicked: startGame()
            }
            
            Button {
                text: "Instructions"
                font.pixelSize: 18
                width: 200
                height: 50
                
                background: Rectangle {
                    color: parent.pressed ? "#2980B9" : "#3498DB"
                    radius: 5
                }
                
                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                
                onClicked: instructionDialog.open()
            }
            
            Button {
                text: "Exit Game"
                font.pixelSize: 18
                width: 200
                height: 50
                
                background: Rectangle {
                    color: parent.pressed ? "#C0392B" : "#E74C3C"
                    radius: 5
                }
                
                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                
                onClicked: Qt.quit()
            }
        }
    }
    
    // Game instructions dialog
    Dialog {
        id: instructionDialog
        anchors.centerIn: parent
        title: "Game Instructions"
        modal: true
        width: 500
        height: 400
        
        ScrollView {
            anchors.fill: parent
            anchors.margins: 20
            
            Text {
                width: instructionDialog.width - 40
                wrapMode: Text.WordWrap
                color: "#2C3E50"
                font.pixelSize: 14
                text: `
Game Controls:

Player 1 Controls (Left):
• WASD: Move and jump
• J: Light attack (costs 10 energy)
• K: Heavy attack (costs 25 energy)
• L: Special attack (costs 50 energy)
• U: Block

Player 2 Controls (Right):
• Arrow keys: Move and jump
• 1: Light attack (costs 10 energy)
• 2: Heavy attack (costs 25 energy)
• 3: Special attack (costs 50 energy)
• 0: Block

Game Rules:
• Each round lasts 99 seconds
• Defeat opponent or player with more health wins
• Blocking reduces 70% damage
• Energy regenerates automatically
• Successful attacks cause knockback

Enjoy the game!
                `
            }
        }
        
        standardButtons: Dialog.Ok
    }
} 