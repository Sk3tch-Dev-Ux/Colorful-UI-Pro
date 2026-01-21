param (
    [string]$LogPath
)

Write-Host "Tailing log: $LogPath" -ForegroundColor Gray
Write-Host "-----------------------------------------------------------" -ForegroundColor Gray

Get-Content -Path $LogPath -Wait | ForEach-Object {
    $line = $_
    # Split by brackets, error keywords, warnings, etc.
    # We capture delimiters to keep them in the token stream
    $tokens = [regex]::Split($line, '(\[.*?\]|\b(?i:error|fail|exception)\b|\b(?i:warning)\b|\b(?i:success|done|connected)\b)')
    
    foreach ($token in $tokens) {
        if ([string]::IsNullOrEmpty($token)) { continue }

        if ($token -match '^\[.*\]$') {
            # Brackets and content
            Write-Host $token -NoNewline -ForegroundColor Cyan
        }
        elseif ($token -match '(?i)error|fail|exception') {
            # Errors
            Write-Host $token -NoNewline -ForegroundColor Red
        }
        elseif ($token -match '(?i)warning') {
            # Warnings
            Write-Host $token -NoNewline -ForegroundColor Yellow
        }
        elseif ($token -match '(?i)success|done|connected') {
            # Success
            Write-Host $token -NoNewline -ForegroundColor Green
        }
        else {
            # Default text
            Write-Host $token -NoNewline -ForegroundColor White
        }
    }
    Write-Host "" # End of line
}
