cmake_minimum_required(VERSION 3.26)
project(client)

set(CMAKE_CXX_STANDARD 20)

add_executable(client source/main.cpp
        source/Engine.cpp
        headers/Engine.h
        source/Grid.cpp
        headers/Grid.h
        source/MousePos.cpp
        headers/MousePos.h
        source/MainMenu.cpp
        headers/MainMenu.h
        source/Player.cpp
        headers/Player.h
        source/Game.cpp
        headers/Game.h
        source/WaitingRoom.cpp
        headers/WaitingRoom.h
        source/Lobby.cpp
        headers/Lobby.h
        source/Server.cpp
        headers/Server.h
        headers/Client.h
        source/Client.cpp)

include_directories(headers /usr/include c:/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(client ${SFML_LIBRARIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()