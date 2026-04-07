cmake_minimum_required(VERSION 3.16)
project(PasswordManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(SQLITECPP_PATH ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SQLiteCpp)

set(SQLITECPP_INTERNAL_SQLITE ON CACHE BOOL "" FORCE)

add_subdirectory(${SQLITECPP_PATH} EXCLUDE_FROM_ALL)

message(STATUS "========================================")
message(STATUS "SQLiteCpp path: ${SQLITECPP_PATH}")
message(STATUS "SQLiteCpp include dir: ${SQLITECPP_PATH}/include")

if(EXISTS ${SQLITECPP_PATH}/include/SQLiteCpp/Database.h)
    message(STATUS "✓ SQLiteCpp/Database.h found")
else()
    message(WARNING "✗ SQLiteCpp/Database.h NOT found!")
    message(STATUS "  Checking alternative paths:")
    
    if(EXISTS ${SQLITECPP_PATH}/SQLiteCpp/Database.h)
        message(STATUS "  ✓ Found at: ${SQLITECPP_PATH}/SQLiteCpp/Database.h")
    endif()
    if(EXISTS ${SQLITECPP_PATH}/src/Database.h)
        message(STATUS "  ✓ Found at: ${SQLITECPP_PATH}/src/Database.h")
    endif()
endif()

if(TARGET SQLiteCpp)
    message(STATUS "✓ SQLiteCpp target exists")
    
    get_target_property(SQLITECPP_INCLUDE_DIRS SQLiteCpp INTERFACE_INCLUDE_DIRECTORIES)
    if(SQLITECPP_INCLUDE_DIRS)
        message(STATUS "  Target include dirs: ${SQLITECPP_INCLUDE_DIRS}")
    endif()
else()
    message(WARNING "✗ SQLiteCpp target does NOT exist")
endif()
message(STATUS "========================================")

set(SOURCES
    src/entry.cpp
    src/password_entry.cpp
    src/note_entry.cpp
    src/vault.cpp
    src/app.cpp
    src/serializer.cpp
    src/database_manager.cpp
)

set(CMAKE_AUTOMOC ON)
add_executable(password_manager ${SOURCES})
add_executable(securevault_qt 
  src/main_qt.cpp 
  src/mainwindow.cpp
  include/mainwindow.hpp
  include/addPasswordDialog.hpp
  include/addNoteDialog.hpp
  src/database_manager.cpp
  src/entry.cpp
  src/password_entry.cpp
  src/note_entry.cpp
  src/vault.cpp
  src/addPasswordDialog.cpp
  src/addNoteDialog.cpp
)

set_target_properties(securevault_qt PROPERTIES AUTOMOC ON)
target_include_directories(password_manager PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SQLITECPP_PATH}/include
    /usr/include/qt6
    /usr/include/qt6/QtWidgets
    /usr/include/qt6/QtCore
)

target_include_directories(securevault_qt PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${SQLITECPP_PATH}/include
)

target_link_libraries(password_manager PRIVATE 
    SQLiteCpp
)


target_link_libraries(securevault_qt PRIVATE
  Qt6::Core
  Qt6::Widgets
  SQLiteCpp
)

if(UNIX AND NOT APPLE)
    target_link_libraries(password_manager PRIVATE pthread dl)
elseif(APPLE)
    target_link_libraries(password_manager PRIVATE)
endif()

if(MSVC)
    target_compile_options(password_manager PRIVATE /W4)
else()
    target_compile_options(password_manager PRIVATE -Wall -Wextra -Wpedantic)
endif()
