project(Sandbox)
cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)

set(CORE ${CMAKE_CURRENT_SOURCE_DIR}/../Core)
include(${CORE}/cmake/functions.cmake)

include_directories(${CORE}/Source)
include_directories(${CORE}/Dependecies/include)

link_directories(${CORE}/Dependecies/bin)


file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
        "${CMAKE_SOURCE_DIR}/Core/Dependecies/src/glad/glad.c")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
        "${CMAKE_SOURCE_DIR}/Core/Dependecies/include/glad/*.h")

assign_source_group(${sources})
assign_source_group(${headers})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Core ${CMAKE_CURRENT_BINARY_DIR}/Core)


if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    file(GLOB_RECURSE resources_src "${CMAKE_CURRENT_SOURCE_DIR}/Resources/**")
    assign_source_group(${resources_src})
    foreach(resource IN LISTS resources_src)
        file(RELATIVE_PATH relative_test ${CMAKE_CURRENT_SOURCE_DIR} ${resource})
        message("Adding resource to build ${resource}")
        add_custom_command(
                OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${relative_test}"
                COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${relative_test}" "${CMAKE_CURRENT_BINARY_DIR}/${relative_test}"
                DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${relative_test}"
        )
        list(APPEND resources "${CMAKE_CURRENT_BINARY_DIR}/${relative_test}")
    endforeach()

endif()


add_executable(Sandbox ${headers} ${sources} ${resources})

target_link_libraries(Sandbox general Core)
target_link_libraries(Sandbox general Core)

