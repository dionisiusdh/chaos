int numEmptySectors(char *buffer, int sectors){
	// Mendapatkan jumlah sektor yang masih kosong
	// Dicek dari indeks sector ke 0 hingga <sectors>
	int n, i;

	n = 0;
	for (i=0; i<sectors; i++) {
		if (buffer[i] == 0x00) {
			n += 1;
		}
	}
	return n;
}

int findFirstEmptySectors(char *buffer, int sectors){
	int i;

	for (i = 0; i < sectors; i++) {
		if (buffer[i] == 0x00) {
			return i;
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