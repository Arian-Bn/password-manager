# 📝 Notes Manager

A desktop note-taking application built with C++20 and Qt6. Create, edit, delete, and search notes stored in a local SQLite database. Clean architecture with RAII, smart pointers, and OOP design.

---

## 📊 Current Status: Week 1 Completed ✅

**Goal Achieved:** Core GUI with note CRUD operations and SQLite persistence.

### ✅ What's Working Now:
- **Qt6 GUI**: Main window with note list, add and delete buttons
- **SQLite Database**: Persistent storage with notes table
- **Add Notes**: Dialog with title and content fields
- **Delete Notes**: Confirmation dialog, cascading delete
- **Memory Safety**: RAII with smart pointers, no leaks

### 🚀 Next Steps:
- Search by title
- Categories and filtering
- Edit notes on double-click

---

## 🛠️ Technologies Used

- **C++20** — Modern C++ with latest features
- **Qt6** — GUI framework (Widgets, signals/slots)
- **SQLite3** — Local database via SQLiteCpp
- **CMake 3.16+** — Cross-platform build system
- **Git** — Version control

---

## 📁 Project Structure

- `include/` — Header files
- `src/` — Source files
- `CMakeLists.txt` — Build configuration

---

## 🚀 Build & Run

### Prerequisites
- C++20 compatible compiler (GCC 10+, Clang 12+)
- Qt6 (Core, Widgets)
- CMake 3.16+

### Build Instructions
```bash
git clone <repository-url>
cd notes-manager

cmake -B build
cmake --build build

# Run application
./build/notes_manager
