# Script untuk run dan check program
# Cara run:
# chmod +x check.sh
# sh check.sh

# Compile kernel
echo "COMPILING KERNEL . . ."
chmod +x compile_kernel.sh
sh compile_kernel.sh

echo "RUNNING PROGRAM . . ."
bochs -f if2230.config
