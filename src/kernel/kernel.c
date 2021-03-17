/* kernel.c */

/* MILESTONE 1 */
void handleInterrupt21 (int AX, int BX, int CX, int DX);
// Fungsi untuk menangani interrupt 0x21

void printString(char *string);
// Fungsi untuk mencetak string ke layar

void readString(char *string);
// Fungsi untuk menerima masukkan input string dari keyboard

void clear(char *buffer, int length); 
// Fungsi untuk mengisi buffer dengan 0

/* MILESTONE 2 */
void writeSector(char *buffer, int sector);
// Menulis sektor

void readSector(char *buffer, int sector);
// Membaca sektor

void writeFile(char *buffer, char *path, int *sectors, char parentIndex);
// Menulis file yang berada pada path dengan konten yaitu buffer sebanyak sectors (jumlah sektor)
// dari posisi parentIndex (Indeks dari sektor di folder parent)

void readFile(char *buffer, char *path, int *result, char parentIndex);
// Membaca file

/* SHELL */
void printWelcome();
// Mengoutput welcome message dengan printString

void runAll();
// Melakukan running terhadap fungsi-fungsi yang ada, kalau gapakai ini error

void shell();
// Program utama shell

/* SHELL FUNCTION */
void printShell(char *file);
// Memanfaatkan interrupt untuk melakukan print string pada shell

void printPath(char path);
// Mencetak current path ke layar

int indexOfPath2(char parentIdx, char *path, char *isFolder);
// Mendapatkan indeks dari file atau folder path

void getFileName(int index, char* filename);
// Ambil nama file

/* --------------------------- */
/* ----- Helper function ----- */
/* --------------------------- */
int div(int x, int y);
// Fungsi untuk membagi

int mod(int x, int y);
// Fungsi mod

int checkFirstLetter(char *string, char *charCheck, int length);
// Mengembalikan 1-0 value apakah string awalannya sama
// Mengecek apakah sebuah kata string diawali huruf pertama charCheck

int len(char *string, int capString);
// Mengembalikan panjang string misal 'ABC' () => { return 3 }
// Mereturn panjang dari sebuah string dengan batas maksimum capString

int isStringEqual (char* str1, char* str2, int len);
// Mengembalikan 1-0 value apakah string str 1 dan str 2 sama
// Cek apakah string str1 dan str2 sepanjang len merupakan string yang sama

int indexOfPath(char parentIndex, char *path);
// Mendapatkan indeks dari file path

int numEmptySectors(char *buffer, int sectors);
// Mendapatkan jumlah sektor yang masih kosong
// Dicek dari indeks sector ke 0 hingga <sectors>

int findFirstEmptySectors(char *buffer, int sectors);
// Mendapatkan sektor kosong pertama
// Dicek dari indeks sector ke 0 hingga <sectors>
// Asumsikan pasti ada sektor kosong

/* ===== MAIN PROGRAM ===== */
int main() {

	makeInterrupt21();

	runAll();

	while (1);
}

/* MILESTONE 1 */
void handleInterrupt21 (int AX, int BX, int CX, int DX){ 
	// Fungsi untuk menangani interrupt 0x21
	char AL, AH; 
	AL = (char) (AX); 
	AH = (char) (AX >> 8); 
	switch (AL) { 
		case 0x00: 
			printString(BX); 
			break; 
		case 0x01: 
			readString(BX); 
			break; 
		case 0x02: 
			readSector(BX, CX); 
			break; 
		case 0x03: 
			writeSector(BX, CX); 
			break; 
		case 0x04: 
			readFile(BX, CX, DX, AH); 
			break; 
		case 0x05: 
			writeFile(BX, CX, DX, AH); 
			break;
		default: 
			printString("Invalid interrupt"); 
	} 
}

void printString(char *string){
	// Fungsi untuk mencetak string ke layar
	int i = 0;
	char c = string[i];

	while (c != 0) {
		interrupt(0x10, 0xe * 256 + c, 0, 0, 0); // Memanggil interrupt 0x10
		i += 1;
		c = string[i];
	}
}

void readString(char *string){
// Fungsi untuk menerima masukkan input string dari keyboard
	int i = 0;
	char c = interrupt(0x16, 0, 0, 0, 0);		// Memanggil interrupt 0x16

	while (c != 0xd) {	// Selama belum ada masukkan enter
		string[i] = c;
		interrupt(0x10, 0xe * 256 + c, 0, 0, 0);
		i += 1;
		c = interrupt(0x16, 0, 0, 0, 0);
		while (c == 0x8) {	// Selama belum ada masukkan backspace
			// Mendelete string yang telah dimasukkan
			if (i > 0) {
				i -= 1;
			}
			c = interrupt(0x16, 0, 0, 0 ,0);			
		}
	}
	string[i] = 0xa;
	string[i+1] = 0x0;
}

void clear(char *buffer, int length){
	// Fungsi untuk mengisi buffer dengan 0
	int i;	

	for (i = 0; i < length; i++) {	
		buffer[i] = 0;	
	}
}

/* MILESTONE 2 */
void readSector(char *buffer, int sector){
	// Membaca sektor
	interrupt(0x13, 0x201, buffer, div(sector, 36) * 0x100 + mod(sector, 18) + 1, mod(div(sector, 18), 2) * 0x100);
}

void writeSector(char *buffer, int sector){
	// Menulise sektor
	interrupt(0x13, 0x301, buffer, div(sector, 36) * 0x100 + mod(sector, 18) + 1, mod(div(sector, 18), 2) * 0x100);
}

void readFile(char *buffer, char *path, int *result, char parentIndex){
	
	int fileIdx; int secIdx;
	int secNum = 0; 
	int secPos;
	char sectors[512]; char files[1024];

	int shiftConditional = fileIdx >> 8;

	fileIdx = indexOfPath(parentIndex, path);
	if (fileIdx == -1) {
		*result = -1;
		return;
	} else if (shiftConditional == 0x1) {
		*result = -1;
		return;
	}

	readSector(files, 0x101);
	readSector(files + 512, 0x102);
	readSector(sectors, 0x103);
	secIdx = files[fileIdx * 16 + 1];
	while (secNum < 16) {
		secPos = secNum;
		secPos += secIdx * 16;
		
		if (sectors[secPos] != 0) {
			readSector(buffer + (secNum * 512), sectors[secPos]);
		} else {
			break;
		}
		secNum++;
	}
	*result = 1;
}

void writeFile(char *buffer, char *path, int *sectors, char parentIndex){
	// Menulis file yang berada pada path dengan konten yaitu buffer sebanyak sectors (jumlah sektor)
	// dari posisi parentIndex (Indeks dari sektor di folder parent)

	int filesIdx;
	int sectorsIdx;
	int sectorTarget;
	int i;

	char arr_map[512];
	char arr_files[1024];
	char arr_sectors[512];
	char dir;

	// Baca sektor dari map (0x100), files (0x101-0x102), dan sectors (0x103), simpan ke dalam array
	readSector(arr_map, 256);
	readSector(arr_files, 0x101);
	readSector(arr_files+512, 0x102);
	readSector(arr_sectors, 0x103);
	
	// parentIndex harus dicek agar valid
	if(parentIndex != 0xFF && arr_files[(16*parentIndex)+1]!=0xFF) {
		printString("Error -4 : Folder error, tidak dapat menulis file");
		*arr_sectors = -4;
		return;
	}

	// Jika valid, simpan paretIndex pada variabel dir
	dir = parentIndex;

	// Cek apakah ada file duplikat
	// File duplikat : File dengan nama yang sama
	for (filesIdx = 0; filesIdx < 64; filesIdx++) {
		if (arr_files[filesIdx * 16] == dir){
			if (isStringEqual(path, arr_files + (filesIdx * 16) + 2, 14) == 1) {
				printString("Error -1 : Nama file sudah ada. Tidak dapat menulis file");
				*arr_sectors = -1;
				return;
			}
		}
	}

	// Cek apakah ada kasus line kosong pada file
	for (filesIdx = 0; filesIdx < 64; filesIdx++) {
		if (arr_files[(filesIdx << 4) + 2] == 0) {
			// Tidak ditemukan file ataupun folder
			break;
		}

	}

	if (filesIdx == 64) {
		// Cek apakah sector sudah penuh
		printString("Error -2 : Entry file sector tidak cukup. Tidak dapat menulis file");
		*arr_sectors = -2;
		return;
	} else if (numEmptySectors(arr_map, 256) < *sectors) {
		// Cek apakah map sudah penuh
		printString("Error -3 : Map sector tidak cukup. Tidak dapat menulis file");
		*arr_sectors = -3;
		return;
	}

	// Cek line kosong pada sektor
	for(sectorsIdx = 0; sectorsIdx < 32; sectorsIdx++) {
		if(arr_sectors[sectorsIdx << 4] == 0){
			// Ada line kosong
			break;
		}
	}

	// Cek apakah sectors sector sudah penuh
	if(sectorsIdx == 32) {
		printString("Error -3 : Sectors sector tidak cukup. Tidak dapat menulis file");
		*arr_sectors = -3;
		return;
	}

	// Bersihkan line pada file
	clear(arr_files + (filesIdx << 4), 16);
	
	// Penulisan tanda pada line file
	// Tulis P value
	arr_files[filesIdx<<4] = dir;

	// Tulis S value
	arr_files[(filesIdx<<4) + 1] = sectorsIdx;

	// Tulis filename pada line file
	for (i = 0; i < 14; i++) {
		if (path[i] == 0)
			break;
		arr_files[(filesIdx<<4) + 2 + i] = path[i];
	}

	// Tulis isi file berupa konten dari buffer
	for (i = 0; i < *arr_sectors; i++) {
		// Ambil sektor kosong pertama
		sectorTarget = findFirstEmptySectors(arr_map, 256);
		
		// Akses sektor terkait pada map sectors
		arr_map[sectorTarget] = 0xFF;

		// Simpan sector target pada sectors sector
		sectors[(sectorsIdx << 4) + i] = sectorTarget;

		writeSector(buffer + (i << 9), sectorTarget);
	}

	printString("Berhasil menulis file");

	// Simpan hasil dan tulis kembali ke system image
	writeSector(arr_map, 0x100);
	writeSector(arr_files, 0x101);
	writeSector(arr_files+512, 0x102);
	writeSector(arr_sectors, 0x103);
}

/* SHELL */
void printWelcome(){
	// Mengoutput welcome message dengan printString
	printString("\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
	printString("  _--                  --_                                   \r\n");    
	printString(" <                        >)        _            ___  ____   \r\n");   
	printString(" |                         |    ___| |__   __ _ / _ \\/ ___|  \r\n");  
	printString("  \\._                   _./    / __| '_ \\ / _` | | | \\___ \\  \r\n");  
	printString("     ```--. . , ; .--'''      | (__| | | | (_| | |_| |___) | \r\n");  
	printString("           | |   |             \\___|_| |_|\\__,_|\\___/|____/  \r\n");   
	printString("        .-=||  | |=-.                                        \r\n");      
	printString("        `-=#$%&%$#=-'                                        \r\n");       
	printString("           | ;  :|                                           \r\n");      
	printString("  _____.,-#%&$@%#&#~,._____                                  \r\n");       

	printString("\r\nWelcome to chaOS!\r\n");

	return;
}

void runAll(){
	// Melakukan running terhadap fungsi-fungsi yang ada, kalau gapakai ini error
	// KAMUS
	char line[100];				// Variabel untuk menampung input string
	char buffertest[512]; 		// Test read file
	int res = 1;				// Test read file

	// DEBUGGING
	// Ubah parameter sesuai keperluan debugging 0 = false, 1 = true
	int DEBUG_READ_PRINT_STRING = 0;
	int DEBUG_READ_WRITE_FILE = 0;

	// ALGORITMA	
	putInMemory(0xB000, 0x8000, 'c');
	putInMemory(0xB000, 0x8001, 0xD);
	putInMemory(0xB000, 0x8002, 'h');
	putInMemory(0xB000, 0x8003, 0xD);
	putInMemory(0xB000, 0x8004, 'a');
	putInMemory(0xB000, 0x8005, 0xD);
	putInMemory(0xB000, 0x8160, 'O');
	putInMemory(0xB000, 0x8161, 0x7);
	putInMemory(0xB000, 0x8162, 'S');
	putInMemory(0xB000, 0x8163, 0x7);
	putInMemory(0xB000, 0x8164, '!'); 
	putInMemory(0xB000, 0x8165, 0x7);

	if (DEBUG_READ_PRINT_STRING) {
		printString("Test input string:\r\n");
		readString(line);
		printString("\r\nTest print variable:\r\n");
		printString(line);
		printString("\r\nYeet it works!\r\n");
	}

	if (DEBUG_READ_WRITE_FILE) {
		readFile(buffertest, "test.txt", &res, 0x00);
		printString("\r\nPass test read file\r\n");
	}

	printWelcome();
	shell();
}

void shell(){
	// Program utama shell
	char command[128];
	char resultCommand[15];
	char fileBuff[512];
	char parentIdx = 0xFF;
	char pathEnvIdx = 0xFF;		// Posisi $PATH
	char isFolder;
	char folderContent[32 * 2 + 1];

	int pathIdx = 0;
    int filesIdx;
	int i, j, k;
	int bi, bj;
	int validFlag = 1;
	int catFlag = 1;
    int exitFlag = 0;

	// Bersihkan buffer
	clear(fileBuff[512]);
	clear(command, 128);
	clear(resultCommand, 15);	        

	while(!exitFlag) {
		printPath(parentIdx);

		// Baca input command
		interrupt(0x21, 0x01, command, 0, 0);

		if (checkFirstLetter(command, "cd ", 3)) {
			// SHELL : cd
			pathIdx = indexOfPath2(parentIdx, command + 3, &isFolder);
			if(pathIdx == -1 || !isFolder) {
				printShell("\r\nDirektori tidak ditemukan\r\n");
			} else {
				parentIdx = pathIdx;
			}
		} else if (checkFirstLetter(command, "cat", 3)) {
			// SHELL : cat

			// Interrupt ke sebuah tempat yang tidak dimengerti
			// interrupt(0x21, ???, fileBuff, command+4, &catFlag);
			
			//if (catFlag == -1){
			//	printShell("\r\nFile tidak ditemukan\r\n");
			//} else {
			//	printShell(fileBuff);
			//}
		} else if (checkFirstLetter(command, "ls", 2)) {
			// SHELL : ls
			// ls telah dicoba diimplementasikan pada ls.c namun belum sempurna
		} else if (checkFirstLetter(command, "ln", 2)) {
			// SHELL : ln
			printShell("\r\nMaaf ln belum diimplementasikan :(\r\n");
		} else {
			printShell("\r\nPerintah tidak valid!\r\n");
		}

        // Bersihkan buffer
		clear(command, 128);
		clear(resultCommand, 15);
	}
	return;
}

/* SHELL FUNCTION */
void printShell(char *file) {
    // Memanfaatkan interrupt untuk melakukan print string pada shell
	interrupt(0x21, 0x00, file, 0, 0);

	// ALTERNATIF
	// printString(file);
}

void printPath(char parentIdx) {
    // Mencetak current path ke layar
	char folderPrio[32];
	char files[1024];
	char str[512 + 1];
	int filesIdx;
	int idx;
	int i, j;

    i = 0;
    j = 0;
	
	printShell("\r\nshell@chaOS:~/");

	filesIdx = parentIdx;

	if (filesIdx != 0xFF){
		// Panggil readSector
		interrupt(0x21, 0x02, files, 0x101, 0);
		interrupt(0x21, 0x02, files + 512, 0x102, 0);

		// Track root folder
		idx = 0;
		while (filesIdx != 0xFF)
		{
			folderPrio[idx] = filesIdx;
			idx++;
			filesIdx = files[filesIdx * 16];
		}

		// Buat string
		while (idx != 0)
		{
			idx -= 1;
			i = 0;
			while (files[(folderPrio[idx] * 16) + 2 + i] != 0x00)
			{
				str[j] = files[(folderPrio[idx] * 16) + 2 + i];
				i += 1;
				j += 1;
			}
			if (idx != 0) {
				str[j] = '/';
				j += 1;
			}
		}
		str[j] = 0;
		printShell(str);
	}
	printShell("$ ");
}

int indexOfPath2(char parentIdx, char *path, char *isFolder){
	// Mendapatkan indeks dari file atau folder path
	int storeSize = 512; char files[1024];
	char found = 0; char numCapFile = 0x40;
	char size = 0x10; char currentPath = 0;
	char i = 0; char parentCopy = parentIdx;

	if (!found){
		interrupt(0x21, 0x02, files, 0x101, 0);
		interrupt(0x21, 0x02, files + storeSize, 0x102, 0);
	} else{
		return -1;
	}

    // Path awal
	if (path[1] == '/' && path[0] == '.'){	
		currentPath += 2;
	}

	if (path[0] == '/'){
		parentCopy = 0xFF;
		currentPath ++;
	}

    // Ambil index dari path
	while (path[currentPath] != 0x00){
		if (path[currentPath] == '/'){
            // Ubah posisi ke dalam folder
			if (found == 0){
				return -1;
			}
			found = 0;
			currentPath++;
		} else if (path[currentPath] == '.' && path[currentPath + 1] == '.' && path[currentPath + 2] == '/'){
			// Posisi up ke folder lain
			if (parentCopy == 0xFF){ 
				return -1;
			}

			parentCopy = files[parentCopy * 16];
			currentPath += 3;
		} else {
            // Cek seluruh files untuk memeriksa nama file dan folder
			if (parentCopy != files[i * 16] || files[i * 16 + 2] == 0){
				// Jika file tidak ada di parentCopy
                i++;
			} else if (checkFirstLetter(path + currentPath, files + i * 16 + 2, 14)){
				// File ditemukan
                currentPath += len(files + i * 16 + 2, 14);
				found = 1;
				parentCopy = i;
				i = 0;
			} else {
				i++;        // File belum ditemukan
			}

			if (i >= numCapFile){
				return -1;  // File tidak ditemukan
			}
		}
	}

    *isFolder = ((parentCopy == 0xFF) || (files[parentCopy * 16 + 1] == 0xFF));

    return parentCopy;
}
