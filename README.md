# CUL — Common Utility Library

[![Windows Build](https://github.com/bartekordek/CUL/actions/workflows/cmake-windows.yml/badge.svg?branch=master)](https://github.com/bartekordek/CUL/actions/workflows/cmake-windows.yml)
[![Linux Build](https://github.com/bartekordek/CUL/actions/workflows/cmake.yml/badge.svg)](https://github.com/bartekordek/CUL/actions/workflows/cmake.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT%2FBeer-yellow.svg)](#license)
[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)

A personal C++ utility library providing reusable building blocks for filesystem access, logging, memory management, delegates, and more. Built with CMake and targeting C++23.

---

## Table of Contents

- [Features](#features)
- [Dependencies](#dependencies)
- [Building](#building)
- [Installation / Integration](#installation--integration)
- [Module Reference](#module-reference)
- [Examples](#examples)
- [Platform Support](#platform-support)
- [Motivation](#motivation)
- [License](#license)

---

## Features

| Module | Description |
|---|---|
| `FSApi` | Filesystem utilities (existence checks, sizes, MD5, timestamps, directory listing) |
| `ILogger` | Logging wrapper around [spdlog](https://github.com/gabime/spdlog) |
| `DelegateTemplate` | Unreal Engine-style delegate / callback system |
| `MemoryPool` | Simple memory pool allocator |
| `MemoryTracker` | Tracks allocations and dumps active allocation stacks |
| `IConfigFile` | Key-value config file reader/writer |
| `ConsoleUtilities` | Command-line argument parsing helpers |
| `ScopeExit` | RAII scope guard — executes a lambda at end of scope |
| `SimpleAssert` | Lightweight assertion utility |
| `STL_IMPORTS` | Warning-suppression wrappers for STL includes |
| `String` | String utility helpers |
| `Math` | Miscellaneous math utilities |

---

## Dependencies

All dependencies are bundled as git submodules under `deps/`:

- [spdlog](https://github.com/gabime/spdlog) — fast logging
- [glm](https://github.com/g-truc/glm) — math (vectors, matrices)
- [googletest](https://github.com/google/googletest) — unit testing
- [rapidjson](https://github.com/Tencent/rapidjson) — JSON parsing
- [boost](https://www.boost.org/) (selected headers: circular_buffer, stacktrace, variant, …)
- [zlib](https://zlib.net/) + [libpng](http://www.libpng.org/pub/png/libpng.html)
- [tracy](https://github.com/wolfpld/tracy) — profiling
- [nativefiledialog-extended](https://github.com/btzy/nativefiledialog-extended) — native file dialogs
- [CPP-DateTime-library](https://github.com/HowardHinnant/date) — date/time utilities
- [udp-discovery-cpp](https://github.com/hrissan/udp-discovery-cpp) — UDP network discovery

---

## Building

Clone the repository with all submodules:

```bash
git clone --recurse-submodules https://github.com/bartekordek/CUL.git
cd CUL
```

### Linux

```bash
cmake -S . -B Build-Linux -DCMAKE_BUILD_TYPE=Release
cmake --build Build-Linux
```

### Windows (MSVC)

```bat
cmake -S . -B Build-Windows -G "Visual Studio 17 2022"
cmake --build Build-Windows --config Release
```

Or use the provided helper script:

```bat
CreateProjects.bat
```

Build outputs are placed in:
- `Build-Linux/` on Linux
- `Build-Windows/` on Windows

---

## Installation / Integration

CUL is designed to be consumed as a CMake subdirectory. Add it to your project:

```cmake
add_subdirectory(path/to/CUL)

target_link_libraries(your_target PRIVATE cul_static)
# or
target_link_libraries(your_target PRIVATE cul_dynamic)
```

For a working example of this, see [`libculTests/CMakeLists.txt`](libculTests/CMakeLists.txt).

---

## Module Reference

### FSApi — Filesystem

```cpp
#include "CUL/Filesystem/FSApi.hpp"

auto& fs = CUL::FS::FSApi::getInstance();

fs.fileExist("path/to/file");          // bool
fs.getFileSize("path/to/file");        // size in bytes
fs.getMD5("path/to/file");             // std::string
fs.getFileModificationTime("...");     // timestamp
fs.listFiles("path/to/dir");           // std::vector<std::string>
```

### ILogger — Logging

```cpp
#include "CUL/Log/ILogger.hpp"

auto* logger = CUL::LOG::ILogger::getInstance();
logger->log("Hello, world!", CUL::LOG::Severity::INFO);
```

### DelegateTemplate — Delegates

```cpp
#include "CUL/GenericUtils/DelegateTemplate.hpp"

CUL::Delegate<void(int)> onEvent;
onEvent.bind([](int x) { /* handle event */ });
onEvent.execute(42);
```

### ScopeExit — Scope Guard

```cpp
#include "CUL/GenericUtils/ScopeExit.hpp"

{
    CUL::ScopeExit guard([]{ cleanup(); });
    // cleanup() is called automatically when guard goes out of scope
}
```

### MemoryTracker — Allocation Tracking

```cpp
#include "CUL/Memory/MemoryTracker.hpp"

// Enable tracking
CUL::Memory::MemoryTracker::getInstance().enable();

// ... do allocations ...

// Dump all active allocations with stack traces
CUL::Memory::MemoryTracker::getInstance().dumpAllocations();
```

---

## Examples

Full working examples can be found in the test suite:

```
libculTests/src/
```

---

## Platform Support

| Platform | Status |
|---|---|
| Linux (GCC/Clang) | ✅ Builds and tested via CI |
| Windows (MSVC) | ✅ Builds via CI |

> Note: Not all modules have been fully tested on all platforms. Contributions and bug reports welcome.

---

## Motivation

This library exists primarily as a learning project and a personal toolbox — a home for commonly needed C++ patterns so they don't have to be rewritten from scratch in every project.

---

## License

**Beer/Coffee License** — functionally equivalent to the MIT license.

You are free to use, modify, and distribute this code. If you find it useful, buying the author a beer or coffee is appreciated but never required.