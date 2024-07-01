cmake_minimum_required (VERSION 3.25)
project(TowerDefenseGame VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MTd")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")

# header-file dir
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/SDL2/include)

# link-lib dir
link_directories(${PROJECT_SOURCE_DIR}/3rdparty/SDL2/lib)

# link lib file
link_libraries(SDL2)
link_libraries(SDL2_ttf)
link_libraries(SDL2_image)
link_libraries(SDL2_mixer)
link_libraries(SDL2_gfx)

# executable file
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/include/*.h ${PROJECT_SOURCE_DIR}/include/*.hpp)
add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES} ${HEADER_FILES})

# SDL dll
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/SDL2/lib/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/SDL2/lib/SDL2_image.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/SDL2/lib/SDL2_ttf.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/SDL2/lib/SDL2_mixer.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/asset"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/asset)