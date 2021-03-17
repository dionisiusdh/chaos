# Script untuk membuat image dari file system
# Cara run:
# chmod +x make_filesystem.sh
# sh make_filesystem.sh

# Buat image
dd if=/dev/zero of=map.img bs=512 count=1
dd if=/dev/zero of=files.img bs=512 count=2
dd if=/dev/zero of=sectors.img bs=512 count=1

echo "\nJalankan hexedit map.img, ubah isi dari map.img agar byte ke-0 hingga ke-10 bernilai 0xFF yang berarti bahwa sektor tersebut terisi (oleh kernel)\n

Kemudian ubah juga posisi 0x100 hingga 0x103 ke map.img menjadi 0xFF\n"
read -p "Sudah melakukannya? [Y,n]\n" input 
case $input in
  y|Y)  dd if=map.img of=system.img bs=512 count=1 seek=256 conv=notrunc
	dd if=files.img of=system.img bs=512 count=2 seek=257 conv=notrunc
	dd if=sectors.img of=system.img bs=512 count=1 seek=259 conv=notrunc;; 
  n|N) echo "Jalankan ulang script." ;;
esac
