cd "C:\Users\terra\Downloads\Projects\repos\SFMLPractice"
cmake -G "MinGW Makefiles" -S . -B "./Build" -D CMAKE_CXX_COMPILER="C:\msys64\mingw32(13.1.0)\bin\g++.exe"
cmake --build Build
cd bin
