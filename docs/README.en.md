# dyNET

A lightweight HTTP framework written in C++ with no libc or external dependencies.  
All system calls are made directly via inline assembly (x86_64).

## Structure
```
dyNET/
├── include/dynet/
│   ├── dysyscall.hpp
│   ├── dysocket.hpp
│   ├── dyhttp.hpp
│   └── dyutils.hpp
├── src/
│   ├── dysyscall.cpp
│   ├── dysocket.cpp
│   ├── dyhttp.cpp
│   └── dyutils.cpp
└── examples/
    └── hello_server/
        └── main.cpp
```

## Features

- Inline assembly syscall wrapper (1~6 arguments)
- TCP socket (socket / bind / listen / accept / read / write / close)
- HTTP request parsing (method / path / version)
- HTTP response builder
- String utilities (dy_strcpy / dy_strcat / dy_itoa / dy_htons)

## Build
```bash
mkdir build && cd build
cmake .. && make -j$(nproc)
```

## Usage
```bash
./examples/hello_server/hello_server
```
```bash
curl http://localhost:8080/
# hello from dyNET
```

## TODO

- Router (path-based handler dispatch)
- Multi-client support (SYS_clone threads)