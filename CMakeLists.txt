cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(nuanalysis)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-fconcepts)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(ROOT REQUIRED)
include("${ROOT_USE_FILE}")
include_directories(
    ${ROOT_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(event STATIC src/event.cxx)
add_library(tools STATIC src/tools.cxx)
# add_library(analysis STATIC src/analysis.cxx)
# add_library(analysis_plot STATIC src/analysis_plot.cxx)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -Wall -Wextra -Wpedantic -flto")

add_executable(genie_kaon genie_kaon.cxx)
target_link_libraries(genie_kaon ROOT::Tree ROOT::EG ROOT::ROOTDataFrame event tools nlohmann_json::nlohmann_json)
install(TARGETS genie_kaon DESTINATION bin)

add_executable(merge_plot merge_plot.cxx)
add_compile_options(-fconcepts)
target_link_libraries(merge_plot nlohmann_json::nlohmann_json ROOT::Tree ROOT::Hist ROOT::Gpad)
install(TARGETS merge_plot DESTINATION bin)