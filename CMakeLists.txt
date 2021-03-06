cmake_minimum_required(VERSION 3.10)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0074 NEW) #controls how find_package() behaves

project(Chess)
set(EXECUTABLE_NAME "Chess")


include_directories(Source/Game)
include_directories(Source/Util)
include_directories(Source/View)


add_executable(${EXECUTABLE_NAME}
        Source/Game/Board.h
        Source/Game/Board.cpp
        Source/Game/Game.h
        Source/Game/Game.cpp
        Source/Game/Piece.h
        Source/Game/Piece.cpp
        Source/Game/Player.h
        Source/Game/Player.cpp
        Source/Game/Square.h
        Source/Game/Square.cpp
        Source/Game/Support.h
        Source/Game/Support.cpp
        Source/Util/Config.h
        Source/Util/Config.cpp
        Source/Util/Random.hpp
        Source/Util/tree.hh
        Source/Util/Util.h
        Source/Util/Util.hpp
        Source/Util/Util.cpp
        Source/View/DisplayData.h
        Source/View/DisplayData.cpp
        Source/View/DisplayData.mm
        Source/View/MacOSSpecificDeclarations.h
        Source/View/Window.h
        Source/View/Window.cpp
        Source/View/Window.mm
        Source/main.cpp
)

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR}/)

#target_link_libraries(${EXECUTABLE_NAME} stdc++ "-framework Foundation" "-framework Cocoa" objc)

# Detect and add SFML
find_package(SFML COMPONENTS audio graphics window system)
add_library(SFML SHARED IMPORTED)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()