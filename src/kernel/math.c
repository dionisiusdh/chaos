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