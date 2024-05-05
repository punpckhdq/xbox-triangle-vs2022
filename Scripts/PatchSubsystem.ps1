param([string]$exepath = "default.exe")

# Open up the exe
$bytes = [System.IO.File]::ReadAllBytes($exepath)

# Read where the PE header is
$e_lfanew = [BitConverter]::ToUInt32($bytes, 0x3C)

# Assume 32 bit optional header
$subsystemOffset = $e_lfanew + 0x5c

# Xbox subsytem
$subsystemBytes = [BitConverter]::GetBytes([Int16]0x000E)

# Modify field and and save
$bytes[$subsystemOffset] = $subsystemBytes[0]
$bytes[$subsystemOffset+1] = $subsystemBytes[1]
[System.IO.File]::WriteAllBytes($exepath, $bytes)
