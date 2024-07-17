[![Windows Build](https://github.com/bartekordek/CUL/actions/workflows/cmake-windows.yml/badge.svg?branch=master)](https://github.com/bartekordek/CUL/actions/workflows/cmake-windows.yml)
[![Linux Build](https://github.com/bartekordek/CUL/actions/workflows/cmake.yml/badge.svg)](https://github.com/bartekordek/CUL/actions/workflows/cmake.yml)

## Synopsis

CUL - Common Utility Library.

1. Library overview.
    - Filesystem: FSApi: it can perform some generic filesystem features:
        - get current (working directory.)
        - get file/directory creation time.
        - do file existence check.
        - get file size.
        - check whether the file is a generic file
        - list files under a directory.
        - calculate file md5.
        - get file modification time.
    - GenericUtils
        - ConsoleUtilities: simple parsing of input parameters.
        - DelegateTemplate: unreal-like delegate structures for... delegating lambdas.
        - IConfigFile: simple config file support.
        - ScopeExit: execute lambda at the end of scope.
        - SimpleAssert: the name says everything.
        - ILogger: simple logging utility, a wrapper on spdlog.
        - Math: mostly useless math utils.
        - Memory:
            - MemoryPool: slow, lazy memory pool.
            - MemoryTracker: it is able to track allocations/realocations with their stacks. It can also dump all active allocations at the time.
        - STL_IMPORTS: if you want to disable all warnings from STL library (not our fault to have them!) you may use it.
        - String: i really do not want to tell you.


Currently, the project is built in the Linux env, but not everything was tested.

## Code Example

For code examples, please check how they are being used in the tests:
```libculTests/src```

## Motivation

My motivation to create such a library:
- The main reason for this library is for me to learn.
- Also, as it is a utility library, the main functionality is to have some repeating code in one, easy-to-use place.

## Installation

Just add cul_static or cul_dynamic to your cmake project.
Just like examples, take a look at:
```
libculTests/CMakeLists.txt
```


## License
Beer/coffee license. Check my account for more information.
You can use it just like an MIT license.