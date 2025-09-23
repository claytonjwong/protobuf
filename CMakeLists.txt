cmake_minimum_required(VERSION 3.15)
project(ProtobufUDPExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf REQUIRED)

# Generate protobuf sources from .proto
set(PROTO_FILE ${CMAKE_CURRENT_SOURCE_DIR}/messages.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILE})

# Common library with protobuf + helpers
add_library(proto_helpers
    ${PROTO_SRCS}
    ${PROTO_HDRS}
    helpers.cpp
)
target_link_libraries(proto_helpers PUBLIC protobuf::libprotobuf)
target_include_directories(proto_helpers PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# Server executable
add_executable(server server.cpp)
target_link_libraries(server PRIVATE proto_helpers)

# Client executable
add_executable(client client.cpp)
target_link_libraries(client PRIVATE proto_helpers)
