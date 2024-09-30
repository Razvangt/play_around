g++  -c src/function.cpp  -o build/function.o 
g++  src/main.cpp build/function.o -o build/output.exe 


%~dp0/build/output.exe
