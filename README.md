# dyNET

libc 및 외부 라이브러리 없이 C++로 작성한 경량 HTTP 프레임워크입니다.  
모든 시스템 콜은 x86_64 인라인 어셈블리로 커널에 직접 호출합니다.

## 구조
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

## 현재 기능

- 인라인 어셈블리 syscall 래퍼 (1~6인자)
- TCP 소켓 (socket / bind / listen / accept / read / write / close)
- HTTP 요청 파싱 (method / path / version)
- HTTP 응답 구성 및 전송
- 문자열 유틸리티 (dy_strcpy / dy_strcat / dy_itoa / dy_htons)

## 빌드
```bash
mkdir build && cd build
cmake .. && make -j$(nproc)
```

## 실행
```bash
./examples/hello_server/hello_server
```
```bash
curl http://localhost:8080/
# hello from dyNET
```

## TODO

- 라우터 (path 기반 핸들러 분기)
- 멀티클라이언트 (SYS_clone 스레드)