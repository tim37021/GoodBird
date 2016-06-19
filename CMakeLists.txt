CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(GoodBird)

FIND_PACKAGE(OpenGL REQUIRED)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/thirdparty/SFML/" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/thirdparty/SFML/")
find_package(SFML 2 REQUIRED system window graphics network audio)

# Detect and add Box2D
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/thirdparty/Box2D/" ${CMAKE_MODULE_PATH})
set(BOX2D_ROOT "${CMAKE_SOURCE_DIR}/thirdparty/Box2D/")
find_package(Box2D REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
include_directories(${BOX2D_INCLUDE_DIR})
include_directories(thirdparty/glew/include)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSMFL_STATIC -DGLEW_STATIC -DGLEW_NO_GLU -std=c99 -g -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSMFL_STATIC -DGLEW_STATIC -DGLEW_NO_GLU -std=c++11 -g -Wall")

include_directories(./inc ./thirdparty/SMFL/include)
add_subdirectory(./thirdparty/glew/)

FILE(GLOB SRC_FILES
    "src/*.cpp"
)

ADD_EXECUTABLE(GoodBird ${SRC_FILES})
target_compile_options(GoodBird PRIVATE -static)
target_link_libraries(GoodBird m)
target_link_libraries(GoodBird ${SFML_LIBRARIES})
target_link_libraries(GoodBird ${OPENGL_LIBRARIES})
target_link_libraries(GoodBird glew)
target_link_libraries(GoodBird opengl32)
target_link_libraries(GoodBird ${BOX2D_LIBRARIES})
