cmake_minimum_required(VERSION 3.16)
project(CryptoMadness_Client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ENV_USER $ENV{USER})
set(CMAKE_PREFIX_PATH /Users/${ENV_USER}/Qt/6.7.2/macos/lib/cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

find_path(CRYPTOPP_INCLUDE_DIR NAMES cryptlib.h PATHS /opt/homebrew/Cellar/cryptopp/8.9.0/include/cryptopp)
find_library(CRYPTOPP_LIBRARY NAMES cryptopp PATHS /opt/homebrew/Cellar/cryptopp/8.9.0/lib)

if(NOT CRYPTOPP_INCLUDE_DIR OR NOT CRYPTOPP_LIBRARY)
    message(FATAL_ERROR "Unable to find cryptopp library or include directory")
endif()

include_directories(${CRYPTOPP_INCLUDE_DIR})

file(GLOB SOURCES "src/*.cpp" "src/ui/*.cpp")

add_executable(CryptoMadness_Client ${SOURCES})

target_link_libraries(CryptoMadness_Client
    Qt6::Widgets
    Qt6::Core
    ${CRYPTOPP_LIBRARY}
)

target_include_directories(CryptoMadness_Client PRIVATE
    include
    include/ui
)
