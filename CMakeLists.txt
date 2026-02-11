cmake_minimum_required(VERSION 3.16)
project(PasswordManager VERSION 1.0.0 LANGUAGES CXX)

# C++20 стандарт
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Пути для заголовочных файлов
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Исходные файлы
set(SOURCES
    src/entry.cpp
    src/password_entry.cpp
    src/note_entry.cpp
    src/vault.cpp
    #src/app.cpp
    src/serializer.cpp
    test/test_serialize.cpp
)

# Исполняемый файл
add_executable(password_manager ${SOURCES})

# Опции компиляции для разных платформ
if(MSVC)
    target_compile_options(password_manager PRIVATE /W4 /WX)
else()
    target_compile_options(password_manager PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
