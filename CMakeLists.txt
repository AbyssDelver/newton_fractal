
cmake_minimum_required(VERSION 3.21)
project(newton LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(newton main.cpp)
target_link_libraries(newton PRIVATE sfml-graphics)
target_compile_features(newton PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET newton POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:newton> $<TARGET_FILE_DIR:newton> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS newton)