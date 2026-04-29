param(
    [switch]$Clean
)

$ErrorActionPreference = "Stop"

$Root = Split-Path -Parent $MyInvocation.MyCommand.Path
$VsWhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"

if (!(Test-Path $VsWhere)) {
    throw "Could not find vswhere.exe at: $VsWhere"
}

$VsPath = & $VsWhere -latest -products * -requires Microsoft.Component.MSBuild -property installationPath

if (!$VsPath) {
    throw "Could not find a Visual Studio installation with MSBuild."
}

$VsDevCmd = Join-Path $VsPath "Common7\Tools\VsDevCmd.bat"

if (!(Test-Path $VsDevCmd)) {
    throw "Could not find VsDevCmd.bat at: $VsDevCmd"
}

$Target = if ($Clean) { "/t:Clean" } else { "" }
$Project = Join-Path $Root "build\StarTrek.compile.proj"

cmd /d /s /c "call `"$VsDevCmd`" -arch=x64 -host_arch=x64 && msbuild `"$Project`" $Target"

if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}
