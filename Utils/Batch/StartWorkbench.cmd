@echo off
setlocal EnableExtensions EnableDelayedExpansion

:: Utility function to write colored lines
set "PSCALL=powershell -Command"

echo.
%PSCALL% "Write-Host '----------------------------------------' -ForegroundColor Gray"
%PSCALL% "Write-Host ' STARTING: OpenWorkbench.bat' -ForegroundColor Cyan"
%PSCALL% "Write-Host '----------------------------------------' -ForegroundColor Gray"

:: Check Globals.cfg
%PSCALL% "Write-Host 'Checking for Globals.cfg...' -ForegroundColor DarkCyan"
IF EXIST "..\Shared\Globals.cfg" (
    %PSCALL% "Write-Host '[OK] Globals.cfg found' -ForegroundColor Green"
    for /f "tokens=1* delims== eol=#" %%i in ('type "..\Shared\Globals.cfg"') do (
        set "%%i=%%j"
        %PSCALL% "Write-Host '[CFG] %%i=%%j' -ForegroundColor DarkYellow"
    )
) ELSE (
    %PSCALL% "Write-Host '[ERROR] Globals.cfg not found at ..\Shared\' -ForegroundColor Red"
    pause
    exit /b 1
)

:: Clean PDRIVE trailing slash
if defined PDRIVE (
    if "%PDRIVE:~-1%"=="\" set "PDRIVE=%PDRIVE:~0,-1%"
    %PSCALL% "Write-Host '[CLEAN] PDRIVE=%PDRIVE%' -ForegroundColor Yellow"
)

:: Kill any running Workbench app
%PSCALL% "Write-Host 'Killing existing workbenchApp.exe if running...' -ForegroundColor Magenta"
taskkill /f /im workbenchApp.exe >nul 2>&1

:: Set directory context
cd /D "%~dp0"
set batchDirectory=%cd%
%PSCALL% "Write-Host 'Current batch directory: %batchDirectory%' -ForegroundColor Gray"

:: Search for DayZ Tools install path in registry
%PSCALL% "Write-Host 'Searching for DayZ Tools in registry...' -ForegroundColor DarkCyan"
for /F "Tokens=2* skip=2" %%A In ('REG QUERY "HKCU\Software\bohemia interactive\Dayz Tools" /v "Path" 2^>nul') do (
    set "_DAYZTOOLSPATH=%%B"
)

IF NOT DEFINED _DAYZTOOLSPATH (
    %PSCALL% "Write-Host '[ERROR] DayZ Tools not found in registry.' -ForegroundColor Red"
    pause
    exit /b 1
)

%PSCALL% "Write-Host '[OK] DayZ Tools found at:' -ForegroundColor Green -NoNewline; Write-Host ' %_DAYZTOOLSPATH%' -ForegroundColor Cyan"

:: Set workbench path and launch
set workbenchDirectory=%_DAYZTOOLSPATH%\Bin\Workbench
%PSCALL% "Write-Host 'Workbench path:' -ForegroundColor Green -NoNewline; Write-Host ' %workbenchDirectory%' -ForegroundColor Cyan"

:: Change to Colorful-UI/Workbench directory on P:
%PSCALL% "Write-Host 'Changing to %PDRIVE%\Colorful-UI\Workbench...' -ForegroundColor DarkMagenta"
cd /d "%PDRIVE%\Colorful-UI\Workbench" || (
    %PSCALL% "Write-Host '[ERROR] Failed to change directory to %PDRIVE%\Colorful-UI\Workbench' -ForegroundColor Red"
    pause
    exit /b 1
)

:: Launch Workbench
%PSCALL% "Write-Host 'Launching Workbench...' -ForegroundColor Cyan"
"%workbenchDirectory%\workbenchApp.exe"

echo.
%PSCALL% "Write-Host '----------------------------------------' -ForegroundColor Gray"
%PSCALL% "Write-Host ' FINISHED: OpenWorkbench.bat' -ForegroundColor Green"
%PSCALL% "Write-Host '----------------------------------------' -ForegroundColor Gray"

endlocal
pause
exit /b 0
