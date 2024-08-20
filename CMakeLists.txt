cmake_minimum_required(VERSION 3.5.0)
project(sudoku VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

include(GNUInstallDirs)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Boost 1.45.0 REQUIRED)

add_library(sudokusolver SHARED
    src/main_window.cpp
    src/sudoku_solver_logic.cpp
    src/window_keyboard_detect.cpp
    include/main_window.h
    include/sudoku_solver_logic.h
    include/window_keyboard_detect.h
)

target_include_directories(sudokusolver PUBLIC include)

target_link_libraries(sudokusolver
    Qt::Core
    Qt::Widgets
    ${Boost_LIBRARIES}
)

add_executable(sudoku src/main.cpp)
target_link_libraries(sudoku sudokusolver)
