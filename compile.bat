@echo off
:: ============================================================
:: compile.bat — Build a graphics.h program with WinBGIm
:: Usage:  compile.bat <source_file> <output_name>
:: Example: compile.bat labs\lab1\main.cpp lab1
:: ============================================================

if "%~1"=="" (
    echo Usage: compile.bat ^<source_file^> ^<output_name^>
    echo Example: compile.bat labs\lab1\main.cpp lab1
    exit /b 1
)

if "%~2"=="" (
    echo Usage: compile.bat ^<source_file^> ^<output_name^>
    echo Example: compile.bat labs\lab1\main.cpp lab1
    exit /b 1
)

set SRC=%~1
set NAME=%~2
set OUT=output\%NAME%.exe

echo Compiling %SRC% ...
g++ "%SRC%" -o "%OUT%" -I include -L lib -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

if %ERRORLEVEL%==0 (
    echo.
    echo Build successful: %OUT%
    echo Running program...
    echo.
    "%OUT%"
) else (
    echo.
    echo Build FAILED. Check errors above.
)
