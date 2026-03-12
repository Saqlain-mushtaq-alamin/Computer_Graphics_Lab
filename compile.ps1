param(
    [Parameter(Mandatory=$true)][string]$Source,
    [Parameter(Mandatory=$true)][string]$Name
)

$out = "output\$Name.exe"
Write-Host "Compiling $Source ..."

g++ $Source -o $out -I include -L lib -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

if ($LASTEXITCODE -eq 0) {
    Write-Host "`nBuild successful: $out"
    Write-Host "Running program...`n"
    & ".\$out"
} else {
    Write-Host "`nBuild FAILED. Check errors above."
}
