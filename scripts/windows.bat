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
    echo Cleaning old build cache...
    rd /s /q build
    timeout /t 1 /nobreak >nul
)

REM Create fresh build directory
mkdir build
cd build

REM --- ATTEMPT 1: Visual Studio 2026 ---
echo Checking for Visual Studio 2026...
cmake -G "Visual Studio 18 2026" -A x64 .. >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [OK] Visual Studio 2026 detected and configured!
    set VS_USED=2026
    goto :BUILD_STEP
)

REM Clean and recreate build directory for next attempt
cd ..
rd /s /q build >nul 2>&1
timeout /t 1 /nobreak >nul
mkdir build
cd build

REM --- ATTEMPT 2: Visual Studio 2022 ---
echo Checking for Visual Studio 2022...
cmake -G "Visual Studio 17 2022" -A x64 .. >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [OK] Visual Studio 2022 detected and configured!
    set VS_USED=2022
    goto :BUILD_STEP
)

REM Clean and recreate build directory for next attempt
cd ..
rd /s /q build >nul 2>&1
timeout /t 1 /nobreak >nul
mkdir build
cd build

REM --- ATTEMPT 3: Visual Studio 2019 ---
echo Checking for Visual Studio 2019...
cmake -G "Visual Studio 16 2019" -A x64 .. >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [OK] Visual Studio 2019 detected and configured!
    set VS_USED=2019
    goto :BUILD_STEP
)

REM --- FAILURE ---
echo.
echo ================================
echo ERROR: No Visual Studio found!
echo ================================
echo.
echo Install Visual Studio 2022/2026 with "Desktop development with C++"
pause
exit /b 1

:BUILD_STEP
echo.
echo ================================
echo Building with Visual Studio %VS_USED%
echo ================================
echo.
cmake --build . --config Release
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ================================
    echo BUILD FAILED - SEE ERRORS ABOVE
    echo ================================
	echo  WE ARE ON THIS JOURNEY TOGETHER I KNOW IT IS FRUSTRATING WHEN THINGS AREN'T WORKING 
	echo  BUT I ALSO KNOW YOU HAVE WHAT IT TAKES TO GET THROUGH THIS.
	echo YOU'LL FIGURE IT OUT AAMIR AND FATIMA I BELIEVE IN YOU.
	echo <(• •<) ^ (•o•)^ (>• •)>  isn't this small ascii character cute :D it looks like it is warming up to go again.
	echo also no pressure if you feel frustrated please take a break your health is more important than this project...
	echo (\_/)    
	echo ( •_•)   A cute bunny to cheer you up. it is giving you a heart <3;
	echo /  ><3    
	echo
	echo                                                                   
	echo                                                                   

echo  ___    ___ ________  ___  ___          ________  ________  _________   
echo |\  \  /  /|\   __  \|\  \|\  \        |\   ____\|\   __  \|\___   ___\ 
echo \ \  \/  / | \  \|\  \ \  \\\  \       \ \  \___|\ \  \|\  \|___ \  \_| 
echo  \ \    / / \ \  \\\  \ \  \\\  \       \ \  \  __\ \  \\\  \   \ \  \  
echo   \/  /  /   \ \  \\\  \ \  \\\  \       \ \  \|\  \ \  \\\  \   \ \  \ 
echo __/  / /      \ \_______\ \_______\       \ \_______\ \_______\   \ \__\
echo|\___/ /        \|_______|\|_______|        \|_______|\|_______|    \|__|
echo\|___|/                                                                  
echo                                                                         
echo                                                                         
echo _________  ___  ___  ___  ________                                      
echo|\___   ___\\  \|\  \|\  \|\   ____\                                     
echo\|___ \  \_\ \  \\\  \ \  \ \  \___|_                                    
echo     \ \  \ \ \   __  \ \  \ \_____  \                                   
echo      \ \  \ \ \  \ \  \ \  \|____|\  \                                  
echo       \ \__\ \ \__\ \__\ \__\____\_\  \                                 
echo        \|__|  \|__|\|__|\|__|\_________\                                
echo                             \|_________|                                
echo
echo



    pause
    exit /b 1
)
if "%VS_USED%"=="2026" (
echo ================================
echo Build successful!
echo ================================
echo Executable: bin\spiral-flap.exe
echo 
echo YOU DID IT KING I BELIEVED IN YOU  :)
echo.
) else if "%VS_USED%"=="2022" (
echo ================================
echo Build successful!
echo ================================
echo Executable: bin\spiral-flap.exe
echo SLAYYYYYYY.
)

echo          _____                    _____            _____          
echo         /\    \                  /\    \          /\    \         
echo        /::\    \                /::\____\        /::\    \        
echo       /::::\    \              /:::/    /       /::::\    \       
echo      /::::::\    \            /:::/    /       /::::::\    \      
echo     /:::/\:::\    \          /:::/    /       /:::/\:::\    \     
echo    /:::/__\:::\    \        /:::/    /       /:::/__\:::\    \    
echo    \:::\   \:::\    \      /:::/    /       /::::\   \:::\    \   
echo  ___\:::\   \:::\    \    /:::/    /       /::::::\   \:::\    \  
echo /\   \:::\   \:::\    \  /:::/    /       /:::/\:::\   \:::\    \ 
echo/::\   \:::\   \:::\____\/:::/____/       /:::/  \:::\   \:::\____\
echo\:::\   \:::\   \::/    /\:::\    \       \::/    \:::\  /:::/    /
echo \:::\   \:::\   \/____/  \:::\    \       \/____/ \:::\/:::/    / 
echo  \:::\   \:::\    \       \:::\    \               \::::::/    /  
echo   \:::\   \:::\____\       \:::\    \               \::::/    /   
echo    \:::\  /:::/    /        \:::\    \              /:::/    /    
echo     \:::\/:::/    /          \:::\    \            /:::/    /     
echo      \::::::/    /            \:::\    \          /:::/    /      
echo       \::::/    /              \:::\____\        /:::/    /       
echo        \::/    /                \::/    /        \::/    /        
echo         \/____/                  \/____/          \/____/         
                                                                   
echo      _____                _____                _____              
echo     |\    \              |\    \              |\    \             
echo     |:\____\             |:\____\             |:\____\            
echo     |::|   |             |::|   |             |::|   |            
echo     |::|   |             |::|   |             |::|   |            
echo     |::|   |             |::|   |             |::|   |            
echo     |::|   |             |::|   |             |::|   |            
echo     |::|   |             |::|   |             |::|   |            
echo     |::|___|______       |::|___|______       |::|___|______      
echo     /::::::::\    \      /::::::::\    \      /::::::::\    \     
echo    /::::::::::\____\    /::::::::::\____\    /::::::::::\____\    
echo   /:::/~~~~/~~         /:::/~~~~/~~         /:::/~~~~/~~          
echo  /:::/    /           /:::/    /           /:::/    /             
echo /:::/    /           /:::/    /           /:::/    /              
echo/:::/    /           /:::/    /           /:::/    /               
echo\::/    /            \::/    /            \::/    /                
echo \/____/              \/____/              \/____/                 
echo                                                                   
                                                                   
pause
