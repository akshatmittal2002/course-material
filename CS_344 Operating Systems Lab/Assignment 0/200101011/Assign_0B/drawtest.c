#include "types.h"
#include "user.h"

int main(int argc, char const *argv[])
{
    const int size = 2000;
    void *buf = malloc(size);
    int art_size = draw(buf,size);
    if(art_size == -1){
        printf(1, "Error: Could not allocate buffer!\n");
    }
    else{
        printf(1,"%s\n", (char*)buf);
    }
    exit();
}
