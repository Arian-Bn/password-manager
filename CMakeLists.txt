cmake_minimum_required(VERSION 3.16)
project(PasswordManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SQLITECPP_PATH ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SQLiteCpp)

include_directories(${SQLITECPP_PATH}/include)

add_subdirectory(${SQLITECPP_PATH} EXCLUDE_FROM_ALL)

set(SOURCES
    src/entry.cpp
    src/password_entry.cpp
    src/note_entry.cpp
    src/vault.cpp
    src/app.cpp
    src/serializer.cpp
    #test/test_serialize.cpp\
    src/database_manager.cpp
)

add_executable(password_manager ${SOURCES})

target_link_libraries(password_manager PRIVATE 
  SQLiteCpp
    sqlite3
)

if(MSVC)
    target_compile_options(password_manager PRIVATE /W4 /WX)
else()
    target_compile_options(password_manager PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

