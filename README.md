# Computer Graphics Lab — graphics.h (WinBGIm)

This repository holds all lab programs written in C/C++ using the `graphics.h` library.

---

## Setup (Windows + MinGW/GCC)

`graphics.h` on modern Windows uses the **WinBGIm** library.

### Step 1 — Install MinGW (if not already installed)
Download and install [MinGW-w64](https://www.mingw-w64.org/) or use [MSYS2](https://www.msys2.org/).
Make sure `g++` is in your PATH.

```
g++ --version
```

### Step 2 — Download WinBGIm files
Download the WinBGIm package from:
> https://winbgim.codecutter.org/

You need three files:
| File | Destination in this repo |
|------|--------------------------|
| `graphics.h` | `include/` |
| `winbgim.h` | `include/` |
| `libbgi.a` | `lib/` |

### Step 3 — Verify structure
```
lab work/
├── include/
│   ├── graphics.h
│   └── winbgim.h
├── lib/
│   └── libbgi.a
├── labs/
│   ├── lab1/
│   ├── lab2/
│   └── lab3/
├── output/
├── compile.bat
└── README.md
```

---

## Compiling a Program

### Using the batch script (recommended)
```
compile.bat labs\lab1\main.cpp lab1
```
This compiles and places the `.exe` inside `output/`.

### Manual compile command
```
g++ your_file.cpp -o output\program.exe -I include -L lib -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
```

---

 

## Notes
- Always call `closegraph()` before exiting.
- Use `getch()` to pause the window before it closes.
- The graphics window opens at runtime automatically.
