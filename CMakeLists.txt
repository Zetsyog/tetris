# Works with 3.11 and tested through 3.19
cmake_minimum_required(VERSION 3.11...3.19)

# Project name and a few useful settings. Other commands can pick up the results
project(
  tetris
  VERSION 0.1
  DESCRIPTION "A tetris clone made with SDL2"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES src/main.cpp
          src/App.cpp
          src/game/Piece.cpp
          src/game/Game.cpp
          src/events/EventManager.cpp
          src/gui/Screen.cpp
          src/gui/Gui.cpp
          src/gui/Image.cpp
          src/gui/Button.cpp
          src/gui/Label.cpp
          src/gui/GameScreen.cpp
          src/gui/MainMenuScreen.cpp
          src/util/FPSCounter.cpp
          src/graphics/Renderer.cpp
          src/graphics/Drawable.cpp
          src/graphics/Texture.cpp
          src/graphics/Color.cpp
          src/resources/ResourceManager.cpp
          src/resources/Music.cpp
          )

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} "")
#Bring the headers, such as Student.h into the project
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_sources(${PROJECT_NAME} PUBLIC ${SOURCES})

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf)
pkg_search_module(SDL2MIXER REQUIRED SDL2_mixer)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})