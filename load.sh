bcc -ansi -c -o src/test.o src/test.c
nasm -f as86 src/asm/lib.asm -o out/lib_asm.o
ld86 -o linkedtest -d src/test.o out/math.o out/std.o out/lib_asm.o
./other/loadFile out/mangga.img linkedtest
./other/loadFile out/mangga.img 1.txt
./other/loadFile out/mangga.img 2.txt
