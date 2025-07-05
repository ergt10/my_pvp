import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: transitionScreen
    color: "black"
    anchors.fill: parent

    signal transitionFinished()

    property string imageSource: "qrc:/assets/backgrounds/transition_1.png" // 仅使用第一张图片

    Image {
        id: transitionImage
        anchors.centerIn: parent
        source: imageSource
        fillMode: Image.PreserveAspectFit
        opacity: 0

        Behavior on opacity {
            NumberAnimation { duration: 1000 } // 图片淡入效果
        }
    }

    Timer {
        id: transitionTimer
        interval: 1500 // 显示 1.5 秒后触发
        repeat: false
        running: true

        onTriggered: {
            transitionFinished() // 触发过场动画完成信号
        }
    }

    Component.onCompleted: {
        transitionImage.opacity = 1 // 图片淡入
    }
}