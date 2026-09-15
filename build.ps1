cmake --build build --config Release
if ($LASTEXITCODE -ne 0) { Write-Host "Build fallido" -ForegroundColor Red; exit 1 }

Copy-Item build\_deps\sfml-build\lib\Release\sfml-*.dll build\Release\ -Force
.\build\Release\Function_renderer.exe