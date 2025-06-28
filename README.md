# PvP Fighting Game

A 2D fighting game (Death vs Naruto style) built with C++, Qt6, QML, and MVVM architecture.
Supports local two-player mode, health/energy system, and VNC-based GUI display in Docker.

## 目录结构

```
assets/         # 游戏资源（图片、音效等）
qml/            # QML界面(View层)
src/            # C++源码(Model/ViewModel/Controller)
dockerfile      # Docker构建环境
run_game.sh     # 一键构建并运行脚本
```

## 快速开始（Docker +  + VNC）

### 1. 安装依赖
- Docker Desktop
- VNC Viewer

### 2. 构建并运行游戏

在项目根目录下打开WSL终端，执行：

```bash
chmod +x run_game.sh
./run_game.sh
```

- 脚本会自动构建Docker镜像、编译项目并启动VNC服务器（端口5900）。

### 3. 连接VNC查看游戏界面

- 打开 VNC Viewer
- 连接到：`localhost:5900`
- 无需密码，直接连接即可看到游戏窗口

## 游戏操作

- Player 1: WASD 移动，J/K/L 攻击，U 格挡
- Player 2: 方向键移动，1/2/3 攻击，0 格挡

## 常见问题

- **VNC无法连接？**  
  请确保5900端口未被防火墙拦截，且脚本已正常运行。
- **构建失败？**  
  请确认Docker Desktop已启动，且WSL终端有权限访问Docker。
- **如何停止游戏/容器？**  
  直接关闭VNC窗口或按`Ctrl+C`，脚本会自动清理容器。

## 其他说明

- 所有依赖均在Docker中自动安装，无需本地配置Qt/vcpkg。
- 项目采用MVVM架构，QML为View层，C++为Model/ViewModel/Controller。

