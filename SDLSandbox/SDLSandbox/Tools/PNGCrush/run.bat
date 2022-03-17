REM Removing incorrect sRGB profile from PNG files

for /R ../../Assets/ %%i in (*.png) do pngcrush.exe -ow -rem allb -reduce %%i