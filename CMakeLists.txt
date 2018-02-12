cmake_minimum_required(VERSION 3.7) #Needs Version 3.8 for boost
project(Green_Editor)

set(CMAKE_CXX_STANDARD 11)


#TODO: SET TO FALSE
set(DEVELOPMENT_MODE TRUE CACHE BOOL "Include tests in build.")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake) #Include custom cmake files

file(GLOB_RECURSE SOURCE_FILES 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/com/ethanbreit/*.c) 

file(GLOB_RECURSE INCLUDE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/com/ethanbreit/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/com/ethanbreit/*.hpp)

set(SOURCE ${SOURCE_FILES} ${INCLUDE_FILES}) #Define Variable "Source" as all Green Engine Library Paths

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/com/ethanbreit) #Define the Green Engine include directories

add_executable(Green_Editor  ${SOURCE})



###
### Sources and Includes
###


include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Libraries.cmake)

#target_link_libraries(Green_Editor nanogui ${NANOGUI_EXTRA_LIBS})


green_engine_libs(includes libraries)


include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Libraries.cmake)
green_engine_libs(includes libraries)


#GE2

list(APPEND libraries ${CMAKE_CURRENT_SOURCE_DIR}/Green_Engine_2.lib)
list(APPEND includes ${CMAKE_CURRENT_SOURCE_DIR}/libs/headers/ge/)

include_directories(${includes})
target_link_libraries(Green_Editor ${libraries})


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/res/)


get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

###
### Include res into build path
###

#file(COPY "res" DESTINATION "${CMAKE_BINARY_DIR}")


if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)



set_target_properties(Green_Editor PROPERTIES LINKER_LANGUAGE "CXX")