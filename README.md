# 📝 Notes Manager

[![CI](https://github.com/Arian-Bn/notes-manager/actions/workflows/build.yml/badge.svg)](https://github.com/Arian-Bn/notes-manager/actions/workflows/build.yml)

A desktop note-taking application built with C++20 and Qt6. Create, edit, delete, search, and categorize notes stored in a local SQLite database. Clean architecture with RAII, smart pointers, and OOP design.

---

## 📊 Current Status: Week 5 Completed ✅

**Goal Achieved:** Full-featured note manager with categories, search, and edit capabilities.

### ✅ What's Working Now:
- **Qt6 GUI**: Main window with note list, add, delete, and exit buttons
- **SQLiteCpp Database**: Persistent storage with entries and notes tables
- **Add Notes**: Dialog with title, content, and category fields
- **Edit Notes**: Double-click to edit with pre-filled data
- **Delete Notes**: Confirmation dialog with cascading delete
- **Search**: Real-time search by title as you type
- **Category Filter**: Dropdown with unique categories from database
- **Note Details**: Click note to view full content and category
- **Input Validation**: Title cannot be empty (red highlight + placeholder text)
- **Unit Tests**: 11 Google Test cases covering add, delete, search, filter, update, validation, edge cases, and duplicates
- **Memory Safety**: RAII with smart pointers, no leaks
- **Foreign Key Constraints**: ON DELETE CASCADE with PRAGMA foreign_keys=ON

### 🚀 Next Steps:
- Google Test integration
- Unit tests for database operations
- CI/CD with GitHub Actions

---

## 🛠️ Technologies Used

- **C++20** — Modern C++ with latest features
- **Qt6** — GUI framework (Widgets, signals/slots)
- **SQLiteCpp** — C++ wrapper for SQLite3 (included as git submodule)
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
- Git (for submodule)

### Build Instructions

```bash
git clone <repository-url>
cd notes-manager

# Initialize submodule
git submodule update --init --recursive

# Configure and build
cmake -B build
cmake --build build

# Run application
./build/notes_manager
