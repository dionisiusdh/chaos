# Script untuk compile loadFile
# Cara run:
# chmod +x compile_loadFile.sh
# sh compile_loadFile.sh

gcc ./loadFile/loadFile.c -o ./loadFile/loadFile

echo "Test load file..."
./loadFile/loadFile ./test/test.txt test
