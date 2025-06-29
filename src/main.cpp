#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "viewmodels/GameViewModel.h"
#include "utils/GameEngine.h"
#include "utils/ResourceManager.h"
#include "utils/SpriteProvider.h"
#include "utils/SpriteProvider.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    qmlRegisterType<GameViewModel>("Game", 1, 0, "GameViewModel");
    
    // 初始化游戏引擎
    GameEngine::getInstance().initialize();
    
    // 加载资源
    ResourceManager::getInstance().loadResources();
    
    QQmlApplicationEngine engine;
    
    // 注册图片提供器
    engine.addImageProvider(QLatin1String("sprites"), new SpriteProvider);
    
    // 添加QML导入路径
    engine.addImportPath("qrc:/qml");
    engine.addImportPath(":/qml");
    
    // 创建游戏视图模型实例
    auto gameViewModel = new GameViewModel(&app);
    engine.rootContext()->setContextProperty("gameViewModel", gameViewModel);
    
    const QUrl url(QStringLiteral("qrc:/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {}, Qt::QueuedConnection);
    
    engine.load(url);
    
    return app.exec();
} 