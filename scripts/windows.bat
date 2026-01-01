@echo off
REM Navigate to project root
cd /d "%~dp0\.."

echo ================================
echo Building spiral-flap...
echo ================================
echo.

REM Create build directory if it doesn't exist
if not exist build mkdir build

REM Navigate to build directory
cd build

REM Configure CMake
echo Configuring CMake...
cmake -G "Visual Studio 17 2022" ..
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: CMake configuration failed!
    echo Check the error messages above for details [No need to panic You'll figure this out].
    pause
    exit /b 1
)

echo.

REM Build the project
echo Building project...
cmake --build . --config Release
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Build failed!
    echo Check the compilation errors above [No need to panic Aamir and Fatima I believe in you both....You'll figure this out :D].
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
