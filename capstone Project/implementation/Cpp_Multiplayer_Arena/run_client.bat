@echo off
if not exist client.exe (
    echo client.exe not found. Run build.bat first.
    pause
    exit /b 1
)
if "%~1"=="" (
    client.exe 127.0.0.1
) else (
    client.exe %~1
)
pause
