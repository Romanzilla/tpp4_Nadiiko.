cmake_minimum_required(VERSION 3.20)
project(StudentA_ImplicitClient LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ImplicitClientA main.cpp)
target_compile_definitions(ImplicitClientA PRIVATE CORRANALYSIS_SHARED)
target_include_directories(ImplicitClientA PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/CorrAnalysis/include)
target_link_libraries(ImplicitClientA PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/CorrAnalysis/lib/CorrAnalysis.lib)

add_custom_command(TARGET ImplicitClientA POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/CorrAnalysis/bin/CorrAnalysis.dll"
    "$<TARGET_FILE_DIR:ImplicitClientA>"
)
