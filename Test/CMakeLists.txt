cmake_minimum_required (VERSION 2.8)
project (Test)

ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)

## include library
include_directories ("../")
#add_subdirectory ("")
#add_subdirectory("${CMAKE_BINARY_DIR}/../SGui")

# add the executable
add_executable(Test Test.cpp Window.cpp SDLWindow.cpp "../SGuiExternal/GLRenderContext.cpp" "../SGuiExternal/gl_declares.cpp")

# ---------------------------------------------

# SGui
set(LIBS ${LIBS} "${CMAKE_BINARY_DIR}/../SGui/libSGui.a")

# Find SDL
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
	include_directories(${SDL2_INCLUDE_DIR})
	set(LIBS ${LIBS} ${SDL2_LIBRARY})
endif (SDL2_FOUND)

# Find OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
	#Message(${OPENGL_INCLUDE_DIR})
	include_directories(${OPENGL_INCLUDE_DIR})
	set(LIBS ${LIBS} ${OPENGL_LIBRARIES})
endif (OPENGL_FOUND)

# ---------------------------------------------

target_link_libraries(Test ${LIBS})
