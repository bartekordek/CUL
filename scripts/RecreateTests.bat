cls
rd /s /q Build-Windows
mkdir Build-Windows
cd Build-Windows
cmake -G "Visual Studio 16 2019" .. -DCMAKE_BUILD_TYPE=Debug
cd ..