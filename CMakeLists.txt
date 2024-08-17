#https://github.com/meemknight/cmakeSetup
#Version 1.0.0

cmake_minimum_required(VERSION 3.16)


#set this to true to ship the game!
#DELETE THE OUT FOLDER AFTER CHANGING THIS BECAUSE VISUAL STUDIO DOESN'T SEEM TO RECOGNIZE THIS CHANGE AND REBUILD!
option(PRODUCTION_BUILD "Make this a production build" OFF)

set(CMAKE_CXX_FLAGS "-std=c++11")
if(APPLE)
  add_definitions(-Wno-deprecated-declarations)
endif()


set(CMAKE_C_COMPILER "/usr/local/opt/gcc@12/bin/gcc-12")
set(CMAKE_CXX_COMPILER "/usr/local/opt/gcc@12/bin/g++-12")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(mygame)

add_subdirectory(thirdparty/raylib)
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
set(src "${CMAKE_CURRENT_SOURCE_DIR}/src")
add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)


if(PRODUCTION_BUILD)
	# setup the ASSETS_PATH macro to be in the root folder of your exe
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") 
	# remove the option to debug asserts.
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1) 
else()
	# This is useful to get an ASSETS_PATH in your IDE during development
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0) 
endif()

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES} )
# target_sources("${CMAKE_PROJECT_NAME}" PRIVATE "${src}/AudioManager/*.cpp" )
# target_sources("${CMAKE_PROJECT_NAME}" PRIVATE "${src}/Interfaces/*.cpp" )
# target_sources("${CMAKE_PROJECT_NAME}" PRIVATE "${src}/MainMenu/*.cpp" )
# target_sources("${CMAKE_PROJECT_NAME}" PRIVATE "${src}/PauseMenu/*.cpp" )
# target_sources("${CMAKE_PROJECT_NAME}" PRIVATE "${src}/Playing/*.cpp" )
# target_sources("${CMAKE_PROJECT_NAME}" PRIVATE "${src}/Playing/Entities/*.cpp" )
# target_sources("${CMAKE_PROJECT_NAME}" PRIVATE "${src}/Playing/Entities/Player/*.cpp" )
# target_sources("${CMAKE_PROJECT_NAME}" PRIVATE "${src}/Playing/LevelManager/*.cpp" )
# target_sources("${CMAKE_PROJECT_NAME}" PRIVATE "${src}/Playing/Objects/*.cpp" )


if(MSVC) # If using the VS compiler...
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
	set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console
	set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug<$<CONFIG:Debug>:Debug>")
	set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
endif()

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/AudioManager/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/Interfaces/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/LevelEditor/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/MainMenu/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/PauseMenu/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/Playing/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/Playing/Entities/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/Playing/Entities/Player/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/Playing/LevelManager/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/Playing/Objects/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/GUI/")


# Link and include raylib
target_link_libraries("${CMAKE_PROJECT_NAME}" "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib/lib/libraylib.a")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib/")

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
