# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.1)

# Notre projet est étiqueté hello
project(game_engine)

# Crée des variables avec les fichiers à compiler
set(SRCS
    cpp/AnimatedComponent.cpp
    cpp/Application.cpp
    cpp/ComponentHandler.cpp
    cpp/EntityHandler.cpp
    cpp/EventHandler.cpp
    cpp/FileManager.cpp
    cpp/GameEngine.cpp
    cpp/main.cpp
    cpp/MotionComponent.cpp
    cpp/PhysicsSystem.cpp
    cpp/RenderComponent.cpp
    cpp/RenderSystem.cpp
    cpp/ServiceLocator.cpp
    cpp/TextureHandler.cpp
    cpp/TransformComponent.cpp
    )
    
set(HEADERS
    inc/AnimatedComponent.hpp
    inc/Application.hpp
    inc/Component.hpp
    inc/ComponentHandler.hpp
    inc/EntityHandler.hpp
    inc/EventHandler.hpp
    inc/FileManager.hpp
    inc/GameEngine.hpp
    inc/Geometry.hpp
    inc/Matrix2D.hpp
    inc/MotionComponent.hpp
    inc/PhysicsSystem.hpp
    inc/RenderComponent.hpp
    inc/RenderSystem.hpp
    inc/ServiceLocator.hpp
    inc/SmartMap.hpp
    inc/System.hpp
    inc/SystemHandler.hpp
    inc/TextureHandler.hpp
    inc/TransformComponent.hpp
    inc/Vector2D.hpp
    )

# On indique que l'on veut un exécutable "hello" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(game_engine ${SRCS} ${HEADERS})

# Library linkage
find_library(LIB_LOCATION NAMES Lua52 PATHS lib)
target_link_libraries(game_engine ${LIB_LOCATION})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
