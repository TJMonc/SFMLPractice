start /wait "" cmake -G "MinGW Makefiles" -S . -B "./Build"
cd Build
start /wait "" make
cd "C:\Users\terra\Downloads\Projects\repos\VSCodeRepos\SFMLPractice\bin"
start SFMLPractice.exe
