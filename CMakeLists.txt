cmake_minimum_required (VERSION 3.23)

if (POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif ()

set(PROJECTNAME bullet)
project(${PROJECTNAME})

# message(STATUS "${BOOST_ROOT}/stage/lib")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
set(CMAKE_CXX_FLAGSD "${CMAKE_CXX_FLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/home/ztgx/codespace/depends/boost_1_79_0/boost/")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/home/ztgx/codespace/depends/boost_1_79_0/stage/lib")

aux_source_directory(src DIR_MAIN_SRCS)
add_executable(${PROJECTNAME} ${DIR_MAIN_SRCS} ${PROTO_SRCS})

# Add protobuf
# https://cmake.org/cmake/help/latest/module/FindProtobuf.html
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS protoc/bullet.proto)

# set(Boost_USE_STATIC_LIBS ON)
# set(Boost_NO_SYSTEM_PATHS ON)
# if (Boost_NO_SYSTEM_PATHS)
# 	message(STATUS ${BOOST_ROOT})
# 	message(STATUS ${BOOST_INCLUDE_DIRS})
# 	message(STATUS ${BOOST_LIBRARY_DIRS})
# endif (Boost_NO_SYSTEM_PATHS)

# cmake -DBoost_DIR=${Boost_DIR}  ..
find_package (Boost 1.79 NO_DEFAULT_PATH COMPONENTS system log log_setup filesystem thread REQUIRED)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	target_link_libraries(${PROJECTNAME} ${Boost_LIBRARIES})
endif()

link_directories(
	AFTER
	# ${CMAKE_CURRENT_SOURCE_DIR}/libs
)

target_include_directories(
	${PROJECTNAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
	$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/>
)

######################################
#
# link_libraries
#
######################################
# protobuf
target_link_libraries(${PROJECTNAME} ${Protobuf_LIBRARIES})

# Common
target_link_libraries(${PROJECTNAME} -lpthread)
target_link_libraries(${PROJECTNAME} -ldl)
