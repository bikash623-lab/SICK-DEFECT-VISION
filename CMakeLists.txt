cmake_minimum_required(VERSION 3.20)
project(SICKVision)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_library(sick_core_lib STATIC
    cpp_core/acquisition.cpp
    cpp_core/preprocessor.cpp
)

target_include_directories(sick_core_lib PUBLIC cpp_core/)
target_link_libraries(sick_core_lib ${OpenCV_LIBS})

add_executable(test_acquisition cpp_core/test_acq_main.cpp)
target_link_libraries(test_acquisition sick_core_lib)

add_executable(test_preprocessor cpp_core/test_prep_main.cpp)
target_link_libraries(test_preprocessor sick_core_lib)

add_subdirectory(practice)
