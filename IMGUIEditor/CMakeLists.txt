include(${CMAKE_SOURCE_DIR}/Core/cmake/functions.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependecies)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependecies/include)

include_directories(${CMAKE_SOURCE_DIR}/Core/Source)
include_directories(${CMAKE_SOURCE_DIR}/Core/Dependecies)
include_directories(${CMAKE_SOURCE_DIR}/Core/Dependecies/include)

link_directories(${CMKAE_LIBRARY_OUTPUT_DIRECTORY})
link_directories(${CMAKE_SOURCE_DIR}/Core/Dependecies/bin)

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Controls/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Dependecies/imgui/*.h"
"${CMAKE_SOURCE_DIR}/Core/Dependecies/include/glad/*.h")

file(GLOB sources  "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Dependecies/imgui/*.cpp"
"${CMAKE_SOURCE_DIR}/Core/Dependecies/src/glad/glad.c"
"${CMAKE_SOURCE_DIR}/Core/Dependecies/src/glad/glad_wgl.c")

assign_source_group(${sources})
assign_source_group(${headers})

add_executable(Editor ${sources} ${headers})

target_link_libraries(Editor general Core)
target_link_libraries(Editor general assimp-vc140-mt.lib)