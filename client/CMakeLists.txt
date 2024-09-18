cmake_minimum_required(VERSION 3.16)
project(CryptoMadness_Client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/Users/jordan/Qt/6.7.2/macos")

find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

include_directories(/opt/homebrew/Cellar/cryptopp/8.9.0/include/cryptopp)
link_directories(/opt/homebrew/Cellar/cryptopp/8.9.0/lib)

file(GLOB SOURCES "src/*.cpp" "src/ui/*.cpp")

add_executable(CryptoMadness_Client ${SOURCES})

target_link_libraries(CryptoMadness_Client Qt6::Widgets Qt6::Core cryptopp)