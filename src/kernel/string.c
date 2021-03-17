/* string.c */
// Segala fungsi yang berkaitan dengan pemrosesan string

void copyString(char * a, char * b){
	// Melakukan penyalinan string a ke b
	int i = 0;
	while (a[i] != 0x00) {
		a[i] = b[i];
		i++;
	}
	b[i] = 0;
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

int isStringEqual (char* str1, char* str2, int len){
	// Cek apakah string str1 dan str2 sepanjang len merupakan string yang sama
	int i;

	for (i=0; i<len; i++) {
		if (*(str1+i) != *(str2+i)) {
			return 0;
		}

		if (str1[i] == 0) {
			return 1;
		}
	}
	return 1;
}