# Script untuk generate disk image dan bootloader awal
# Cara run:
# chmod +x make_system.sh
# sh make_system.sh

# Generate disk image
dd if=/dev/zero of=system.img bs=512 count=2880

# Bootloader
nasm bootloader.asm -o bootloader
dd if=bootloader of=system.img bs=512 count=1 conv=notrunc