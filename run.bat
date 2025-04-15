cd "C:\Users\terra\Downloads\Projects\repos\SFMLPractice"
cmake -G "MinGW Makefiles" -S . -B "./Build"
cmake --build Build
cd bin
start SFMLPractice.exe
