cmake_minimum_required(VERSION 3.10)
project(CryptoMadness_Server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch arm64 -mmacosx-version-min=10.14 -g") 

include_directories(include)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

include_directories(/opt/homebrew/Cellar/cryptopp/8.9.0/include/cryptopp)
link_directories(/opt/homebrew/Cellar/cryptopp/8.9.0/lib)

option(INCLUDE_OPCODE "Include opcode.o in the build" ON)

set(OBJS)

if(INCLUDE_OPCODE)
    list(APPEND OBJS ${CMAKE_SOURCE_DIR}/src/opcode/opcode.o)
    add_definitions(-DINCLUDE_OPCODE)
    message(STATUS "Including opcode.o")
else()
    message(STATUS "Not including opcode.o")
endif()

file(GLOB SOURCES "src/*.cpp" "src/command/*.cpp")

add_executable(CryptoMadness_Server ${CMAKE_SOURCE_DIR}/../key/key.o ${SOURCES} ${OBJS})

target_link_libraries(CryptoMadness_Server
    cryptopp
    OpenSSL::SSL
    OpenSSL::Crypto
)

message(STATUS "Building CryptoMadness_Server with INCLUDE_OPCODE=${INCLUDE_OPCODE}")
