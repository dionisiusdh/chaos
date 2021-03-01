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


	printString("\r\nHello\r\n");
	printString("Test input string:\r\n");
	readString(line);
	printString("\r\nTest print variable:\r\n");
	printString(line);
	printString("\r\nYeet it works!\r\n");

	makeInterrupt21();
	while (1);
}

/* ===== FUNCTION IMPLEMENTATION ===== */
void handleInterrupt21 (int AX, int BX, int CX, int DX){
	// Fungsi untuk menangani interrupt 0x21
	switch (AX) {
		case 0x0:
		  printString(BX);
		  break;
		case 0x1:
		  readString(BX);
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
