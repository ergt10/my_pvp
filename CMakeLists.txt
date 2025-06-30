cmake_minimum_required(VERSION 3.16)
project(PvPFightingGame VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required Qt components
find_package(Qt6 REQUIRED COMPONENTS Core Quick Multimedia Qml Gui QuickControls2)

# Qt specific settings
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Add executable
add_executable(PvPFightingGame
    src/main.cpp
    src/models/GameModel.cpp
    src/models/PlayerModel.cpp
    src/models/FighterModel.cpp
    src/viewmodels/GameViewModel.cpp
    src/viewmodels/PlayerViewModel.cpp
    src/viewmodels/FighterViewModel.cpp
    src/controllers/GameController.cpp
    src/controllers/InputController.cpp
    src/controllers/PhysicsController.cpp
    src/controllers/CollisionController.cpp
    src/utils/GameEngine.cpp
    src/utils/ResourceManager.cpp
    src/utils/SoundManager.cpp
    src/utils/SpriteProvider.cpp
    qml/qml.qrc
)

# Include directories
target_include_directories(PvPFightingGame PRIVATE
    src/
    src/models/
    src/viewmodels/
    src/controllers/
    src/utils/
)

# Link Qt libraries
target_link_libraries(PvPFightingGame
    Qt6::Core
    Qt6::Quick
    Qt6::Multimedia
    Qt6::Qml
    Qt6::Gui
    Qt6::QuickControls2
)

# Copy assets to build directory (if needed)
if(EXISTS ${CMAKE_SOURCE_DIR}/assets)
    file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
endif()

# 设置安装目标
install(TARGETS PvPFightingGame
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin
)

# Linux部署目标
add_custom_target(deploy
    COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR} --prefix ${CMAKE_BINARY_DIR}/deploy
    DEPENDS PvPFightingGame
    COMMENT "部署Linux应用程序..."
) 