cmake_minimum_required (VERSION 3.23)

if (POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif ()

set(PROJECTNAME bullet)
project(${PROJECTNAME})


# message(STATUS "${BOOST_DIR}/stage/lib")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
set(CMAKE_CXX_FLAGSD "${CMAKE_CXX_FLAGS} -O0 -Wall -g -ggdb")

aux_source_directory(src DIR_MAIN_SRCS)
add_executable(${PROJECTNAME} ${DIR_MAIN_SRCS})

link_directories(
	AFTER
	${CMAKE_CURRENT_SOURCE_DIR}/libs
	${BOOST_DIR}/stage/lib
)

target_include_directories(
	${PROJECTNAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes/>
	$<BUILD_INTERFACE:${BOOST_DIR}/>
)

# Boost
target_link_libraries(${PROJECTNAME} -lboost_filesystem)
target_link_libraries(${PROJECTNAME} -lboost_system)

target_link_libraries(${PROJECTNAME} -lpthread)
target_link_libraries(${PROJECTNAME} -ldl)
