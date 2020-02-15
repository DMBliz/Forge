include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/functions.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependecies)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependecies/include)

set(CMAKE_CXX_STANDARD 14)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependecies/bin)

if(WIN32)
    set(OS Win32)
    add_definitions(-DWIN32)
elseif(OSX)
    set(OS OSX)
    set(CMAKE_C_FLAGS "-x objective-c")
    set(CMAKE_CXX_FLAGS "-x objective-c++")
    add_definitions(-DOSX)
elseif(LINUX)
    #Linux is not supported for now
    #because there is a fucking hell of window managers and distributes
    #but of course we can have abbreviation for it
    set(OS LNX)
endif()

set(GAPI OGL)

add_definitions(-DOGL)


file(GLOB headers
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Containers/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/FileSystem/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Graphics/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Graphics/OGL/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Input/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Math/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Api/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Resources/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Scene/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/Serializers/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/Serializers/JSON/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/Serializers/JSON/nlohmann_json/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/detail/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Utilities/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Api/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/${OS}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/${OS}/Context/${GAPI}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Dependecies/include/glad/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Dependecies/include/stb_image/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Dependecies/include/assimp/*.h")

file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Containers/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/FileSystem/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Graphics/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Graphics/OGL/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Input/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Math/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Api/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Resources/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Scene/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/Serializers/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/Serializers/JSON/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/Serializers/JSON/nlohmann_json/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/detail/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Utilities/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Api/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/${OS}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/${OS}/Context/${GAPI}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Dependecies/include/assimp/*.cpp"
        "${CMAKE_SOURCE_DIR}/Core/Dependecies/src/glad/glad.c")


if(OSX)
    file(GLOB sources ${sources}
            "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/${OS}/*.mm"
            "${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/${OS}/Context/${GAPI}/*.mm")
endif()

message("source files:")

foreach(v IN LISTS sources)
    message(${v})
endforeach()

message("header files:")

foreach(v IN LISTS headers)
    message(${v})
endforeach()

assign_source_group(${sources})
assign_source_group(${headers})

add_library(Core STATIC ${sources} ${headers})

if(OSX)
    target_link_libraries(Core "-framework Cocoa"
            "-framework IOKit"
            "-framework OpenGL"
            "-framework CoreVideo"
            "-framework Metal")

    target_link_libraries(Core general libassimp.a)
endif()

if(WIN32)
    target_link_libraries(Core general opengl32.lib)
    target_link_libraries(Core general assimp-vc140-mt.lib)
endif()


