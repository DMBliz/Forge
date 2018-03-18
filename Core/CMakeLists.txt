include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependecies)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependecies/include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependecies/bin)

add_definitions(-DOGL)

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Containers/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/FileSystem/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/FileSystem/Windows/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Graphics/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Graphics/OpenGL/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Graphics/OpenGL/Windows/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Input/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Input/Windows/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Math/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Windows/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Resources/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Scene/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/Serializers/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/Serializers/JSON/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/Serializers/JSON/nlohmann_json/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/detail/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Utilities/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Dependecies/include/glad/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Dependecies/include/stb_image/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/Dependecies/include/assimp/*.h")

file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Containers/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/FileSystem/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/FileSystem/Windows/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Graphics/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Graphics/OpenGL/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Graphics/OpenGL/Windows/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Input/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Input/Windows/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Math/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Windows/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Resources/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Scene/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/Serializers/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/Serializers/JSON/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/Serializers/JSON/nlohmann_json/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Serialization/detail/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Source/Utilities/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/Dependecies/include/assimp/*.cpp"
"${CMAKE_SOURCE_DIR}/Core/Dependecies/src/glad/glad.c"
"${CMAKE_SOURCE_DIR}/Core/Dependecies/src/glad/glad_wgl.c")

add_library(Core STATIC ${sources} ${headers})

target_link_libraries(Core general opengl32.lib)
target_link_libraries(Core general assimp-vc140-mt.lib)