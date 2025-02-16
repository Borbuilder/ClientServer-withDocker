cmake_minimum_required(VERSION 3.10)
project(ClientServer-withDocker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(server
    calculator/calculator.cpp
    server/serverfunc.cpp
    server/server.cpp
)

target_include_directories(server 
    PRIVATE
    ${CMAKE_SOURCE_DIR}/httplib
    ${CMAKE_SOURCE_DIR}/calculator
)

add_executable(client
    client/clientfunc.cpp
    client/client.cpp
)

target_include_directories(client 
    PRIVATE
    ${CMAKE_SOURCE_DIR}/httplib
)