cmake_minimum_required(VERSION 3.16)
project(NotesManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(SQLITECPP_PATH ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SQLiteCpp)
set(SQLITECPP_INTERNAL_SQLITE ON CACHE BOOL "" FORCE)
add_subdirectory(${SQLITECPP_PATH} EXCLUDE_FROM_ALL)

set(CMAKE_AUTOMOC ON)

add_executable(notes_manager
  include/mainwindow.hpp
  include/addNoteDialog.hpp
  include/editNoteDialog.hpp
  src/main_qt.cpp
  src/mainwindow.cpp
  src/addNoteDialog.cpp
  src/editNoteDialog.cpp
  src/database_manager.cpp
  src/vault.cpp
)

target_include_directories(notes_manager PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${SQLITECPP_PATH}/include
)

target_link_libraries(notes_manager PRIVATE
  Qt6::Core
  Qt6::Widgets
  SQLiteCpp
)

if(MSVC)
    target_compile_options(notes_manager PRIVATE /W4)
else()
    target_compile_options(notes_manager PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()

find_package(GTest REQUIRED)

add_executable(test_runner
  tests/test_database.cpp
  src/database_manager.cpp
)

target_link_libraries(test_runner
  GTest::gtest
  GTest::gtest_main
  SQLiteCpp
  Qt6::Core
)

target_include_directories(test_runner PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${SQLITECPP_PATH}/include
)

add_test(NAME DatabaseTest COMMAND test_runner)
