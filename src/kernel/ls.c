/* ls.c */
/* Perintah shell ls */

char folderContent[32 * 2 + 1];

void listContent(char parentIdx, int *fileCount);

void getFileName(int index, char* filename);

void getFolderContent2(int index, char* filename, char* isFolder) ;

int main() {
    int n, i;
    char filename[15];
    char currentDir;
    char isFolder;

    listContent(currentDir, &n);
    for (i = 0; i < n; i++) {
        getFolderContent2(i, filename, &isFolder);
        printString(filename);
        if (isFolder) {
            printString("/"); // Formatting aja
        }
    }

    return 0;
}

void listContent(char parentIdx, int *fileCount) {
	char files[1024];
    char content[65];

	interrupt(0x21, 0x02, files, 0x101, 0);
	interrupt(0x21, 0x02, files + 512, 0x102, 0);
	
	// Melakukan interrupt namun tidak dimengerti
	// interrupt(0x21, ??? , content, fileCount, 0);
}


int isEntryFolder(int idx) {
	// Apakah sebuah entry adalah folder
    char files[1024];

    if (idx == 0xFF) {
        return 1;
    } else if (idx >= 64 || idx < 0) {
        return -1;
    }

    interrupt(0x21, 0x02, files, 0x101, 0);
    interrupt(0x21, 0x02, files+512, 0x102, 0);

    if(files[(idx << 4)+1] == 0xFF){
        return 1;
    }

    return 0;
}


void getFileName(int index, char* filename) {
	// Ambil nama file
    char files[1024];
    int i;

    // Interrupt ke sector
    interrupt(0x21, 0x02, files, 0x101, 0);
    interrupt(0x21, 0x02, files+512, 0x102, 0);

    for (i = 0; i < 14; i++) {
        filename[i] = files[index * 16 + 2 + i];
    }
}

void getFolderContent2(int index, char* filename, char* isFolder) {
	// Ambil isi konten dalam sebuah folder
    getFileName(folderContent[index], filename);
    *isFolder = (char)isEntryFolder(folderContent[index]);
}