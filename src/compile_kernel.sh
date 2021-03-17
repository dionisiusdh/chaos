# Script untuk compile kernel
# Cara run:
# chmod +x compile_kernel.sh
# sh compile_kernel.sh

echo "Compiling kernel..."
bcc -ansi -c -o ./kernel/kernel.o ./kernel/kernel.c

# Kalau ada file .c baru di ./src/kernel/ tambahkan ini
echo "Compiling other files..."
bcc -ansi -c -o ./kernel/math.o ./kernel/math.c
bcc -ansi -c -o ./kernel/string.o ./kernel/string.c
bcc -ansi -c -o ./kernel/sector.o ./kernel/sector.c
# bcc -ansi -c -o ./kernel/filebaru.o ./kernel/filebaru.c

nasm -f as86 ./kernel/kernel.asm -o ./kernel/kernel_asm.o

echo "Linking asm files with o..."
# Kalau ada file .c baru di ./src/kernel/ tambahkan ini
ld86 -o kernel.bin -d ./kernel/kernel.o ./kernel/kernel_asm.o ./kernel/math.o ./kernel/string.o ./kernel/sector.o
# ld86 -o kernel -d ./kernel/kernel.o ./kernel/kernel_asm.o ./kernel/math.o ......... filebaru.o

echo "Inserting kernel to image..."
dd if=kernel.bin of=system.img bs=512 conv=notrunc seek=1
