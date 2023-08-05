int printStr (char *ch);
int printInt (int n);
int readInt (int *eP);


// Find max of n numbers using array
int main() {
    int n;
    int a[10];
    int m;
    int i;
    n=readInt(&c);
    for(i = 0; i < n; i = i + 1) {
        m = readInt(&c);
a[i] = m; }
    m = a[0];
    for(i = 1; i < n; i = i + 1) {
        if (a[i] > m){
            m = a[i];
        }
    }
    printStr("Max of: ");
    printInt(a[0]);
    for(i = 1; i < n; i = i + 1) {
        printStr(", "); printInt(a[i]);
    }
    printStr(": = ");
    printInt(m);
    printStr("\n");
    return 0;
}

