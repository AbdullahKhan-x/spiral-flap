@echo off
setlocal
REM Navigate to project root
cd /d "%~dp0\.."

echo ================================
echo Starting Build Process...
echo ================================
echo.

REM --- AUTO CLEANING STEP ---
REM We delete the build folder every time to ensure no "Generator Mismatch"
if exist build (
    echo Cleaning old build cache to prevent conflicts...
    rd /s /q build
)

REM Create fresh build directory
mkdir build
cd build

REM --- ATTEMPT 1: Visual Studio 2026 ---
echo Attempting to configure for Visual Studio 2026...
cmake -G "Visual Studio 18 2026" ..
if %ERRORLEVEL% EQU 0 (
    echo [OK] Visual Studio 2026 detected.
    set VS_USED=2026
    goto :BUILD_STEP
)

REM --- ATTEMPT 2: Fallback to Visual Studio 2022 ---
echo VS 2026 not found or not supported by your CMake version.
echo Attempting to configure for Visual Studio 2022...
cmake -G "Visual Studio 17 2022" .. 
if %ERRORLEVEL% EQU 0 (
    echo [OK] Visual Studio 2022 detected.
    set VS_USED=2022
    goto :BUILD_STEP
)

REM --- FAILURE LOGIC ---
echo.
echo ERROR: Could not find Visual Studio 2022 or 2026.
echo Tip: Ensure you have CMake 4.2+ installed to use VS 2026!
echo [No need to panic, you'll figure this out].
pause
exit /b 1

:BUILD_STEP
echo.
echo ================================
echo Building project with VS %VS_USED%...
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