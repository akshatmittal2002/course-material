int printStr(char *ch);
int printInt(int n);
int readInt(int *eP);

// Sort an array
int main() {
    int n ;
    int c;
    int a[10];
    int m;
    int i;
    int j;
    
    n = readInt(&c);
    for (i = 0; i < n; i = i + 1) {
        m = readInt(&c);
        a[i] = m; 
    }

    for (i = 0; i < n - 1; i = i + 1) {
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j = j + 1) {
            if (a[j] > a[j + 1]) {
            	int r;
            	r = a[j+1];
            	a[j+1] = a[j];
            	a[j]=r;
            }
        }
    }

    for (i = 0; i < n; i = i + 1) {
        printInt(a[i]); 
        if (i != n - 1) {
            printStr(" ");
        }
    }
    printStr("\n");
    
    return 0;
}

