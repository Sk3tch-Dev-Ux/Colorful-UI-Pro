@echo off
TITLE CUI Log Viewer
CLS

:SearchLoop
echo Searching for new CUI logs...
cd /d "%~dp0..\..\Servers\!ClientDiagLogs" 2>nul

for /f "delims=" %%F in ('dir cui_logs_*.log /b /o-d /t:c 2^>nul') do (
    set "LATEST_LOG=%%F"
    goto :Found
)

timeout /t 2 /nobreak >nul
goto :SearchLoop

:Found
if not defined LATEST_LOG (
    goto :SearchLoop
)

echo Tailing: %LATEST_LOG%
echo -----------------------------------------------------------
powershell -ExecutionPolicy Bypass -File "%~dp0LogViewer.ps1" -LogPath "%LATEST_LOG%"
