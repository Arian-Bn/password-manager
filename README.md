# 🔐 C++ Password Manager

A secure password manager built from scratch in C++20, following a disciplined 14-week development plan. This project demonstrates professional C++ development practices, modern architecture, and security principles.

---

## 📊 Current Status: Week 2 Completed ✅

**Week 2 Goal Achieved:** File persistence and memory safety.

### ✅ What's Working Now:
- **File Persistence**: Save/load vault to/from text files ✓
- **Serialization**: Convert entries to/from string format ✓
- **Memory Safety**: RAII with smart pointers, no leaks ✓
- **User Interface**: Save/Load menu options with auto-save ✓
- **Error Handling**: File not found, invalid input ✓

### 🚀 Next Steps (Week 3):
- SQLite database integration
- Data encryption with libsodium
- Master password protection

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
