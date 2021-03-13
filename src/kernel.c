/* kernel.c */

/* ===== FUNCTION ===== */
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
// Menulis file

void readFile(char *buffer, char *path, int *result, char parentIndex);
// Membaca file

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

int indexOfPath(char parentIndex, char *path);
// Mendapatkan indeks dari file path


/* ===== MAIN PROGRAM ===== */
int main() {
	// KAMUS
	char line[100];	// Variabel untuk menampung input string
	
	// ALGORITMA	
	putInMemory(0xB000, 0x8000, 'H');
	putInMemory(0xB000, 0x8001, 0xD);
	putInMemory(0xB000, 0x8002, 'a');
	putInMemory(0xB000, 0x8003, 0xD);
	putInMemory(0xB000, 0x8004, 'o');
	putInMemory(0xB000, 0x8005, 0xD);
	putInMemory(0xB000, 0x8160, 'A');
	putInMemory(0xB000, 0x8161, 0x7);
	putInMemory(0xB000, 0x8162, 'B');
	putInMemory(0xB000, 0x8163, 0x7);
	putInMemory(0xB000, 0x8164, 'C'); 
	putInMemory(0xB000, 0x8165, 0x7);

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


	printString("\r\nHelloooo\r\n");
	printString("Test input string:\r\n");
	readString(line);
	printString("\r\nTest print variable:\r\n");
	printString(line);
	printString("\r\nYeet it works!\r\n");

	makeInterrupt21();
	while (1);
}

/* ===== FUNCTION IMPLEMENTATION ===== */
void handleInterrupt21 (int AX, int BX, int CX, int DX) { 
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

int div(int x, int y){
	// Fungsi untuk pembagian x dan y
	int res = 0;
	while(res*y <= x){
		res++;
	}
	return res-1;
}

int mod(int x, int y){
	// Fungsi untuk menghitung hasil mod
	while(x >= y){
		x -= y;
	}
	return x;
}

void readSector(char *buffer, int sector){
	// Membaca sektor
	interrupt(0x13, 0x201, buffer, div(sector, 36) * 0x100 + mod(sector, 18) + 1, mod(div(sector, 18), 2) * 0x100);
}

void writeSector(char *buffer, int sector){
	// Menulise sektor
	interrupt(0x13, 0x301, buffer, div(sector, 36) * 0x100 + mod(sector, 18) + 1, mod(div(sector, 18), 2) * 0x100);
}


int checkFirstLetter(char *string, char *charCheck, int length){
	// Mengembalikan 1-0 value apakah string awalannya sama
	// Mengecek apakah sebuah kata string diawali huruf pertama charCheck
	int i;

	for (i = 0; i < length; i++) {
		if (string[i] != charCheck[i]){
			return 0;
		} else if (charCheck[i] == 0){
			return 1;
		}
	}
	// jaga jaga
	return 1;
}

int len(char *string, int capString){
	// Mengembalikan panjang string misal 'ABC' () => { return 3 }
	// Mereturn panjang dari sebuah string dengan batas maksimum capString
	int count = 0;
	for (count = 0; count < capString; count++) {
		if (string[count] == 0) {
			return count;
		}
	} 
}

int indexOfPath(char parentIndex, char *path){
	// Mendapatkan indeks dari file path
	int storeSize = 512; char files[1024];
	char found = 0; char numCapFile = 0x40;
	char size = 0x10; char currentPath = 0;
	char i = 0; char parentCopy = parentIndex;

	if (!found){
		interrupt(0x21, 0x02, files, 0x101, 0);
		interrupt(0x21, 0x02, files + storeSize, 0x102, 0);
	} else{
		return -1;
	}

	if (path[1] == '/' && path[0] == '.'){	
		currentPath += 2;
	}

	if (path[0] == '/'){
		parentCopy = 0xFF;
		currentPath ++;
	}

	while (path[currentPath] != 0x00){

		if (path[currentPath] == '/'){
			if (found == 0){
				return -1;
			}
			found = 0;
			currentPath++;

		} else if (path[currentPath] == '.' && path[currentPath + 1] == '.' && path[currentPath + 2] == '/'){
			
			if (parentCopy == 0xFF){ 
				return -1;
			}

			parentCopy = files[parentCopy * 16];
			currentPath += 3;

		} else{
			if (parentCopy != files[i * 16] || files[i * 16 + 2] == 0){
				i++;
			} else if (checkFirstLetter(path + currentPath, files + i * 16 + 2, 14)){
				currentPath += len(files + i * 16 + 2, 14);
				found = 1;
				parentCopy = i;
				i = 0;
			} else{
				i++;
			}

			if (i >= numCapFile){
				return -1;
			}
		}
	}

	if (files[parentCopy * 16 + 1] != 0xFF && parentCopy != 0xFF){
		return parentCopy;
	} else{
		return (parentCopy | 0x100);
	}
}

void readFile(char *buffer, char *path, int *result, char parentIndex) {
	
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
	// Menulis file
}
