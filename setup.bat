@echo off

REM Check if vcpkg is already cloned, if not, clone it
IF NOT EXIST "vcpkg" (
    echo Cloning vcpkg...
    git clone https://github.com/microsoft/vcpkg.git
) ELSE (
    echo vcpkg already cloned
)

REM Bootstrap vcpkg if it hasn't been bootstrapped yet
IF NOT EXIST "vcpkg\vcpkg.exe" (
    echo Bootstrapping vcpkg...
    cd vcpkg
    call bootstrap-vcpkg.bat
    cd ..
) ELSE (
    echo vcpkg already bootstrapped
)

REM Install required dependencies based on vcpkg.json
echo Installing dependencies...
vcpkg\vcpkg install

REM Create build directory if it doesn't exist
IF NOT EXIST "build" (
    echo Creating build directory...
    mkdir build
) ELSE (
    echo Build directory already exists
)

echo Setup complete!
