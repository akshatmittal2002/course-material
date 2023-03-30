#include "types.h"
#include "user.h"

#define NUM_CHILD 20
#define NUM 20
#define PAGE_SIZE 4096

int main(int argc, char *argv[]){

    printf(1, "--------------------------------------------------------------------------------------------\n");
    printf(1, "|           Event           | PID | VA |                      Remark                       |\n");
    printf(1, "--------------------------------------------------------------------------------------------\n");

    for (int i = 1; i <= NUM_CHILD; i++){
        if (fork() != 0)
            continue;
        
        char *ptr[NUM];
    
        // Allocate 4KB to each of the char pointer
        for(int j = 0; j < NUM; j++)
            ptr[j] = (char *)malloc(PAGE_SIZE);
        
        // Assign values to the allocated memory
        for (int j = 0; j < NUM; j++){
            for (int k = 0; k < PAGE_SIZE; k++)
                ptr[j][k] = (i + j * k) % 128;
        }
        
        // Error detection to check correct fuctioning of our implementation
        for (int j=0; j < NUM; j++){
            for (int k=0; k < PAGE_SIZE; k++){
                if (ptr[j][k] != (i + j * k) % 128)
                    printf(1, "Error at i = %d, j = %d, k = %d, val = %c\n", i, j, k, ptr[j][k]);
            }
        }
            
        exit();
    }

    for (int i = 1; i <= NUM_CHILD; i++)
        wait();
    
    return 0;
}