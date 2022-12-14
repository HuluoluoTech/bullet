cmake_minimum_required (VERSION 3.23)

if (POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif ()

set(PROJECTNAME robots)
project(${PROJECTNAME})

# message(STATUS "${BOOST_DIR}/stage/lib")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
set(CMAKE_CXX_FLAGSD "${CMAKE_CXX_FLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Add protobuf
# https://cmake.org/cmake/help/latest/module/FindProtobuf.html
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ../protoc/bullet.proto)

aux_source_directory(. DIR_MAIN_SRCS)
add_executable(${PROJECTNAME} ${DIR_MAIN_SRCS} ${PROTO_SRCS} ../src/packet.cpp ../src/buffer.cpp)

set(Boost_USE_STATIC_LIBS ON)
find_package (Boost 1.79 NO_DEFAULT_PATH COMPONENTS system log log_setup filesystem thread)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	target_link_libraries(${PROJECTNAME} ${Boost_LIBRARIES})
endif()

link_directories(
	AFTER
	# ${CMAKE_CURRENT_SOURCE_DIR}/libs
	${BOOST_DIR}/stage/lib
)

include_directories(../src/)

target_include_directories(
	${PROJECTNAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
	$<BUILD_INTERFACE:${BOOST_DIR}/>
)

target_link_libraries(${PROJECTNAME} -lpthread)
target_link_libraries(${PROJECTNAME} -ldl)

# protobuf
target_link_libraries(${PROJECTNAME} ${Protobuf_LIBRARIES})
