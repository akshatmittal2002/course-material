int printStr (char *ch);
int printInt (int n);
int readInt (int *eP);

// Compute the factorial
int main() {
    int n;
    int i = 0;
    int r = 1;
    n = readInt(&c);
   
    for(i = 1; i <= n; i = i + 1){
    	r=r*i;
    }
        
    printInt(n);
    printStr("! = ");
    printInt(r);
    printStr("\n");
    return 0;
}

