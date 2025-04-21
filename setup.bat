@echo off

REM Check if vcpkg is already cloned, if not, clone it
IF NOT EXIST "vcpkg" (
    echo Cloning vcpkg...
    git clone https://github.com/microsoft/vcpkg.git
) ELSE (
    echo vcpkg already cloned
)

REM Build vcpkg if it hasn't been built yet
IF NOT EXIST "vcpkg\bootstrap-vcpkg.bat" (
    echo Building vcpkg...
    cd vcpkg
    .\bootstrap-vcpkg.bat
    cd ..
) ELSE (
    echo vcpkg already built
)

REM Install required dependencies based on vcpkg.json
echo Installing dependencies...
vcpkg\vcpkg install

echo vcpkg setup complete!
