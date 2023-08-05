void main()
{
    int n = -2;
    int arr[10];
    char c = 'hello';
    printf("A random string!\t\n");

    /* This is a 
    multi line 
    comment ? */

    int a = 0;
    int b = 1;
    for (int i = 0; i < 10; i = i + 1)
    {
        a = n / i;
        b = b % i + n;
    }
    
    // This is a single line comment!
    if (b <= 30) n = a + 30;
    else n = a;

    return 0;
}