cmake_minimum_required(VERSION 3.16)
project(PasswordManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

add_executable(password_manager ${SOURCES})

target_include_directories(password_manager PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SQLITECPP_PATH}/include
)

target_link_libraries(password_manager PRIVATE 
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
