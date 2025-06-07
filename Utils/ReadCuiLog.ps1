$logFile = Join-Path $env:USERPROFILE 'Documents\DayZ\cui_logger.log'
Write-Host "Tailing $logFile"
Get-Content -Path $logFile -Wait -Tail 20
