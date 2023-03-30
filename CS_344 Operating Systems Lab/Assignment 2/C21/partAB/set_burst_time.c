#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char* argv[])
{

	if(argc < 2)
	{
		printf(2, "Usage: setBurstTime...\n");
    	  	exit();
    	}
    	
    	int n = atoi(argv[1]);
    	
    	if(set_burst_time(n) < 0)
    	{
    		printf(2, "setBurstTime failed\n");
		exit();
	}
	
	printf(1, "Burst Time set to %d.\n", get_burst_time());
	
	exit();
}	
