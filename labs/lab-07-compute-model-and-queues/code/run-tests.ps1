param(
    [switch]$Clean
)

$ErrorActionPreference = "Stop"

$Root = Split-Path -Parent $MyInvocation.MyCommand.Path
$BuildDir = Join-Path $Root "build"
$Exe = Join-Path $BuildDir "test_queue_ops.exe"

if ($Clean) {
    if (Test-Path $BuildDir) {
        Remove-Item -Recurse -Force $BuildDir
    }
    Write-Host "Cleaned build directory."
    exit 0
}

New-Item -ItemType Directory -Force -Path $BuildDir | Out-Null

$Sources = @(
    "src\queue_ops.c",
    "tests\test_queue_ops.c"
)

function Find-Compiler {
    foreach ($Name in @("cl.exe", "clang.exe", "gcc.exe", "cc.exe", "clang", "gcc", "cc")) {
        $Command = Get-Command $Name -ErrorAction SilentlyContinue
        if ($null -ne $Command) {
            return $Command
        }
    }

    return $null
}

function Find-VsDevCmd {
    $VsWhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"
    if (!(Test-Path $VsWhere)) {
        return $null
    }

    $InstallPath = & $VsWhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    if ([string]::IsNullOrWhiteSpace($InstallPath)) {
        return $null
    }

    $VsDevCmd = Join-Path $InstallPath "Common7\Tools\VsDevCmd.bat"
    if (!(Test-Path $VsDevCmd)) {
        return $null
    }

    return $VsDevCmd
}

function Invoke-MsvcBuildAndRun($VsDevCmd) {
    $ObjectDir = Join-Path $BuildDir "obj\\"
    $Rsp = Join-Path $BuildDir "msvc.rsp"
    New-Item -ItemType Directory -Force -Path $ObjectDir | Out-Null

    $RspLines = @(
        "/nologo",
        "/std:c11",
        "/W4",
        "/Iinclude"
    ) + $Sources + @(
        "/Fe`"$Exe`"",
        "/Fo`"$ObjectDir`""
    )

    Set-Content -Encoding ASCII -Path $Rsp -Value $RspLines

    $Cmd = "call `"$VsDevCmd`" -arch=x64 -host_arch=x64 >nul && cl.exe @`"$Rsp`" && `"$Exe`""
    & cmd.exe /d /s /c $Cmd
    $script:RunTestsExitCode = $LASTEXITCODE
}

Push-Location $Root
try {
    $Compiler = Find-Compiler
    if ($null -eq $Compiler) {
        $VsDevCmd = Find-VsDevCmd
        if ($null -ne $VsDevCmd) {
            Invoke-MsvcBuildAndRun $VsDevCmd
            exit $script:RunTestsExitCode
        }
    }

    if ($null -eq $Compiler) {
        Write-Error "No C compiler found. Install Visual Studio Build Tools, LLVM/Clang, or MinGW-w64 GCC, then re-run this script."
    }

    Write-Host "Using compiler: $($Compiler.Name)"

    if ($Compiler.Name -ieq "cl.exe") {
        $ObjectDir = Join-Path $BuildDir "obj\\"
        New-Item -ItemType Directory -Force -Path $ObjectDir | Out-Null

        $Args = @(
            "/nologo",
            "/std:c11",
            "/W4",
            "/Iinclude"
        ) + $Sources + @(
            "/Fe$Exe",
            "/Fo$ObjectDir"
        )
    } else {
        $Args = @(
            "-std=c11",
            "-Wall",
            "-Wextra",
            "-Werror",
            "-g",
            "-Iinclude"
        ) + $Sources + @(
            "-o",
            $Exe
        )
    }

    & $Compiler.Source @Args
    if ($LASTEXITCODE -ne 0) {
        exit $LASTEXITCODE
    }

    & $Exe
    exit $LASTEXITCODE
} finally {
    Pop-Location
}
