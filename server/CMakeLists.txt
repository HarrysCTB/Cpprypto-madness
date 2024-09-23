cmake_minimum_required(VERSION 3.10)
project(CryptoMadness_Server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

include_directories(/opt/homebrew/Cellar/cryptopp/8.9.0/include/cryptopp)
link_directories(/opt/homebrew/Cellar/cryptopp/8.9.0/lib)

set(OBJS ${CMAKE_SOURCE_DIR}/../key/key.o) 

file(GLOB SOURCES "src/*.cpp" "src/command/*.cpp")

add_executable(CryptoMadness_Server ${SOURCES} ${OBJS})

target_link_libraries(CryptoMadness_Server
    cryptopp
    OpenSSL::SSL
    OpenSSL::Crypto
)
