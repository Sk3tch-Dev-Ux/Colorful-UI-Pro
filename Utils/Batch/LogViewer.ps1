param (
    [string]$LogPath
)

function Write-HighlightMessage ($msg) {
    # Tokenize by keywords to colorize
    $tokens = [regex]::Split($msg, '(\[.*?\]|\b(?i:error|fail|exception)\b|\b(?i:warning)\b|\b(?i:success|done|connected|initialized)\b|>>)')

    foreach ($token in $tokens) {
        if ([string]::IsNullOrEmpty($token)) { continue }

        if ($token -match '^\[CuiButton\]') {
            Write-Host $token -NoNewline -ForegroundColor Magenta
        }
        elseif ($token -match '^\[.*\]$') {
            Write-Host $token -NoNewline -ForegroundColor DarkCyan
        }
        elseif ($token -match '(?i:error|fail|exception)') {
            Write-Host $token -NoNewline -ForegroundColor Red
        }
        elseif ($token -match '(?i:warning)') {
            Write-Host $token -NoNewline -ForegroundColor Yellow
        }
        elseif ($token -match '(?i:success|done|connected|initialized)') {
            Write-Host $token -NoNewline -ForegroundColor Green
        }
        elseif ($token -eq '>>') {
            Write-Host $token -NoNewline -ForegroundColor DarkGray
        }
        else {
            Write-Host $token -NoNewline -ForegroundColor White
        }
    }
    Write-Host ""
}

Write-Host "Tailing log: $LogPath" -ForegroundColor Gray
Write-Host "-----------------------------------------------------------" -ForegroundColor Gray

Get-Content -Path $LogPath -Wait | ForEach-Object {
    $line = $_
    
    # 1. Parse Standard CUI Log Format: "Timestamp [Date] - Message"
    # Regex: ^(prefix) \[(date)\] - (content)$
    if ($line -match '^(.*?) \[(.*?)\] - (.*)$') {
        $prefix = $matches[1]
        $date   = $matches[2]
        $content = $matches[3]

        # Print Prefix (DarkGray)
        Write-Host "$prefix " -NoNewline -ForegroundColor DarkGray
        
        # Print Date (DarkGray brackets, Gray text)
        Write-Host "[" -NoNewline -ForegroundColor DarkGray
        Write-Host $date -NoNewline -ForegroundColor Gray
        Write-Host "] " -NoNewline -ForegroundColor DarkGray

        # Print Separator
        Write-Host "- " -NoNewline -ForegroundColor DarkGray

        # 2. Analyze Content for hierarchy (Source - Message) logic
        # format often: "Class.Method() - Message"
        if ($content -match '^([a-zA-Z0-9_]+\.[a-zA-Z0-9_]+\([^\)]*\)) - (.*)$') {
            $source  = $matches[1]
            $message = $matches[2]

            # Print Source (Cyan)
            Write-Host "$source " -NoNewline -ForegroundColor Cyan
            Write-Host "- " -NoNewline -ForegroundColor DarkGray
            
            # Print Message (Keyword highlighted)
            Write-HighlightMessage $message
            
        } else {
            # Just parsed content
            Write-HighlightMessage $content
        }

    } else {
        # Fallback for lines that don't match the standard timestamp format (headers, custom logs)
        Write-HighlightMessage $line
    }
}
