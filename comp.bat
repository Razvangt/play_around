gcc  -c src/function.c  -o build/function.o 
gcc   src/main.c build/function.o -o build/output.exe 


%~dp0/build/output.exe
