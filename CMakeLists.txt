cmake_minimum_required(VERSION 3.6.2)
project(Forge)
set(CMAKE_CXX_STANDARD 14)

set(CMKAE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMKAE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMKAE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WIN32 TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(OSX TRUE)
endif()

add_subdirectory(Core)
add_subdirectory(IMGUIEditor)
add_subdirectory(Sandbox)

add_dependencies(Editor Core)
add_dependencies(Sandbox Core)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Editor)
