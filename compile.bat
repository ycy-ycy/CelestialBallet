if not exist "build" (
    mkdir build
)

cd build
cmake ..
cmake --build . --config Release
Release\StellarBallet.exe
cd ..