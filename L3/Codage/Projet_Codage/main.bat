del *.o
gcc -o hadamard.o -c Hadamard.c
gcc -o main hadamard.o -lm
main