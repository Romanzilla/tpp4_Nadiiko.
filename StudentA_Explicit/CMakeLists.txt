cmake_minimum_required(VERSION 3.20)
project(StudentA_ExplicitClient LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ExplicitClientA main.cpp)

add_custom_command(TARGET ExplicitClientA POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/CorrAnalysis.dll"
    "$<TARGET_FILE_DIR:ExplicitClientA>"
)
