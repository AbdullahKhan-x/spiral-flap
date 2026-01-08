@echo off
setlocal enabledelayedexpansion

REM Navigate to project root
cd /d "%~dp0\.."

echo ================================
echo Starting Build Process...
echo ================================
echo.

REM --- AUTO CLEANING STEP ---
if exist build (
    echo Cleaning old build cache to prevent conflicts...
    rd /s /q build
    timeout /t 1 /nobreak >nul
)

REM Create fresh build directory
mkdir build
cd build

REM --- ATTEMPT 1: Visual Studio 2026 ---
echo Checking for Visual Studio 2026...
cmake -G "Visual Studio 18 2026" .. >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [OK] Visual Studio 2026 detected and configured!
    set VS_USED=2026
    goto :BUILD_STEP
)

REM Clean up failed attempt
cd ..
if exist build rd /s /q build
timeout /t 1 /nobreak >nul
mkdir build
cd build

REM --- ATTEMPT 2: Visual Studio 2022 ---
echo VS 2026 not found. Checking for Visual Studio 2022...
cmake -G "Visual Studio 17 2022" .. >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [OK] Visual Studio 2022 detected and configured!
    set VS_USED=2022
    goto :BUILD_STEP
)

REM Clean up failed attempt
cd ..
if exist build rd /s /q build
timeout /t 1 /nobreak >nul
mkdir build
cd build

REM --- ATTEMPT 3: Auto-detect ANY Visual Studio version ---
echo VS 2022 not found either. Scanning for ANY Visual Studio installation...
echo.

REM List of all Visual Studio generators to try (newest to oldest)
set "GENERATORS=Visual Studio 18 2026|Visual Studio 17 2022|Visual Studio 16 2019|Visual Studio 15 2017|Visual Studio 14 2015"

for %%G in (%GENERATORS%) do (
    echo Trying: %%G...
    cmake -G "%%G" .. >nul 2>&1
    if !ERRORLEVEL! EQU 0 (
        echo [OK] Found and configured: %%G
        set VS_USED=%%G
        goto :BUILD_STEP
    )
    REM Clean up after each failed attempt
    cd ..
    if exist build rd /s /q build
    timeout /t 1 /nobreak >nul
    mkdir build
    cd build
)

REM --- COMPLETE FAILURE ---
echo.
echo ========================================
echo ERROR: No Visual Studio installation found!
echo ========================================
echo.
echo We tried the following generators:
for %%G in (%GENERATORS%) do echo   - %%G
echo.
echo Troubleshooting steps:
echo 1. Install Visual Studio 2022 or 2019 with "Desktop development with C++"
echo 2. Verify CMake can see VS by running: cmake --help
echo 3. Check your CMake version:
cmake --version
echo.
echo Available generators on your system:
cmake --help | findstr /C:"Visual Studio"
echo.
echo [No need to panic Aamir and Fatima, you'll figure this out! :D]
pause
exit /b 1

:BUILD_STEP
echo.
echo ================================
echo Building project with: %VS_USED%
echo ================================
cmake --build . --config Release
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Build failed!
    echo [No need to panic Aamir and Fatima I believe in you both....You'll figure this out :D].
    pause
    exit /b 1
)

echo.
echo ================================
echo Build successful!
echo Executable location: bin\spiral-flap.exe
echo ================================
echo.
echo Run with: bin\spiral-flap.exe
pause
