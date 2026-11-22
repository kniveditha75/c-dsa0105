@echo off
setlocal
echo Building C++ Multiplayer Arena...
g++ server.cpp -o server.exe -std=c++17 -lws2_32
if errorlevel 1 (
    echo.
    echo ERROR: Server build failed. Check that MinGW-w64 g++ is installed and on PATH.
    exit /b 1
)
g++ client.cpp -o client.exe -std=c++17 -lws2_32
if errorlevel 1 (
    echo.
    echo ERROR: Client build failed. Check compiler output above.
    exit /b 1
)
echo.
echo Build successful: server.exe and client.exe are ready.
endlocal
