# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté hello
project(game_engine)

# Crée des variables avec les fichiers à compiler
set(SRCS
    cpp/main.cpp
    cpp/FileManager.cpp
    )
    
set(HEADERS
    inc/FileManager.hpp
    inc/ServiceLocator.hpp
    )

# On indique que l'on veut un exécutable "hello" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(game_engine ${SRCS} ${HEADERS})

# Library linkage
find_library(LIB_LOCATION NAMES Lua52 PATHS lib)
target_link_libraries(game_engine ${LIB_LOCATION})
