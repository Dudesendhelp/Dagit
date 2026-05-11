cmake_minimum_required(VERSION 3.10)

project(dagit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

find_package(OpenSSL REQUIRED)

add_executable(dagit
    main.cpp
    ${SOURCES}
)

target_include_directories(dagit PRIVATE 
    include
    external
)

target_link_libraries(dagit PRIVATE OpenSSL::Crypto)
