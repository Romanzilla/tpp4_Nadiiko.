cmake_minimum_required(VERSION 3.20)
project(StatAnalysisProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Статична бібліотека (Етап 1)
add_library(StatAnalysisStatic STATIC src/StatAnalysis.cpp)
target_include_directories(StatAnalysisStatic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(TestStaticA app/main_static.cpp)
target_link_libraries(TestStaticA PRIVATE StatAnalysisStatic)

# 2. Динамічна бібліотека (Етап 2)
add_library(StatAnalysis SHARED src/StatAnalysis.cpp)
target_compile_definitions(StatAnalysis PRIVATE STATANALYSIS_SHARED STATANALYSIS_EXPORTS)
target_include_directories(StatAnalysis PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
