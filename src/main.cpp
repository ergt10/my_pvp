#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "viewmodels/GameViewModel.h"
#include "utils/GameEngine.h"
#include "utils/ResourceManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    qDebug() << "启动应用程序...";
    
    // 注册QML类型
    qmlRegisterType<GameViewModel>("Game", 1, 0, "GameViewModel");
    qDebug() << "QML类型注册完成";
    
    // 初始化游戏引擎
    GameEngine::getInstance().initialize();
    
    // 加载资源
    ResourceManager::getInstance().loadResources();
    
    QQmlApplicationEngine engine;
    
    // 添加QML导入路径
    engine.addImportPath("qrc:/qml");
    engine.addImportPath(":/qml");
    qDebug() << "QML导入路径设置完成";
    
    // 创建游戏视图模型实例
    auto gameViewModel = new GameViewModel(&app);
    engine.rootContext()->setContextProperty("gameViewModel", gameViewModel);
    qDebug() << "GameViewModel创建并设置为上下文属性";
    
    const QUrl url(QStringLiteral("qrc:/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        qDebug() << "QML对象创建回调:" << obj << objUrl;
        if (!obj && url == objUrl) {
            qDebug() << "QML加载失败，退出应用";
            QCoreApplication::exit(-1);
        } else if (obj && url == objUrl) {
            qDebug() << "QML加载成功！";
        }
    }, Qt::QueuedConnection);
    
    qDebug() << "开始加载QML文件:" << url;
    engine.load(url);
    
    qDebug() << "进入事件循环...";
    return app.exec();
} 