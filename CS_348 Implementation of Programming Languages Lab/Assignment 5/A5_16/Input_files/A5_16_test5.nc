int printStr (char *ch);
int printInt (int n);
int readInt (int *eP);

void swap(int *p, int *q) {
    int t = *p;
    *p = *q;
    *q = t;
    return;
}
int main() {
    int x;
    int y;
    x = readInt(&c);
    y = readInt(&c);
    printStr("Before swap:\n");
    printStr("x = "); printInt(x);
    printStr(" y = "); printInt(y);
    swap(&x, &y);
    printStr("\nAfter swap:\n");
    printStr("x = "); printInt(x);
    printStr(" y = "); printInt(y);
    printStr("\n");
    return 0;
}


