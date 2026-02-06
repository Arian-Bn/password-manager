# 🔐 C++ Password Manager

A secure password manager built from scratch in C++20, following a disciplined 14-week development plan. This project demonstrates professional C++ development practices, modern architecture, and security principles.

---

## 📊 Current Status: Week 1 Completed ✅

**Week 1 Goal Achieved:** Basic foundation with OOP architecture and console interface.

### ✅ What's Working Now:
- **Object-Oriented Architecture**: Abstract `Entry` base class with `PasswordEntry` and `NoteEntry` derivatives
- **Memory Management**: Using `std::unique_ptr` for automatic resource management
- **Console Interface**: Full-featured menu system with CRUD operations
- **Clean Project Structure**: Proper separation of headers and source files
- **CMake Build System**: Cross-platform compilation support

### 🚀 Next Steps (Week 2):
- File persistence for data storage
- Memory leak prevention with smart pointers
- Enhanced error handling

---

## 🛠️ Technologies Used

- **C++20** - Modern C++ with latest features
- **CMake 3.16+** - Cross-platform build system
- **Git** - Version control with daily commits
- **Object-Oriented Design** - Polymorphism, encapsulation, inheritance
- **RAII Principles** - Resource management through object lifetimes

---

## 📁 Project Structure

Проект организован по классической схеме:
- `include/` — заголовочные файлы классов
- `src/` — исходный код
- `CMakeLists.txt` — конфигурация сборки

Основные классы: `Entry` (абстрактный), `PasswordEntry`, `NoteEntry`, `Vault`.

---

## 🚀 Build & Run

### Prerequisites
- C++20 compatible compiler (GCC 10+, Clang 12+, MSVC 2019+)
- CMake 3.16+

### Build Instructions
```bash
# Clone repository
git clone <repository-url>
cd password-manager

# Configure and build
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel

# Run application
./password_manager
