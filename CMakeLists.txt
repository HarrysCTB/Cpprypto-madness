cmake_minimum_required(VERSION 3.10)

project(CryptoMadness)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(/opt/homebrew/Cellar/cryptopp/8.9.0/include/cryptopp)

link_directories(/opt/homebrew/Cellar/cryptopp/8.9.0/lib)

file(GLOB SOURCES "src/*.cpp")

add_executable(CryptoMadness ${SOURCES})

target_link_libraries(CryptoMadness cryptopp)