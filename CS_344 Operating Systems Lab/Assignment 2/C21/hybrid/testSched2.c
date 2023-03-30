#include "types.h"
#include "stat.h"
#include "user.h"

#include "processInfo.h"
int main()
{	
	// array containing burst times
	int t[10] = {40, 70, 10, 90, 60, 30, 20, 80, 100, 50};
	long x = 0;
	set_burst_time(1);
	for(int i=0; i<10; i++)
	{
		// Fork process
		if(fork() != 0)
		{
			continue;
		}

		// Set burst time
		x = set_burst_time(t[i]);
		if(x < 0)
		{
			printf(1, "Could not set burst time for process %d!\n", getpid());
		}
		
		// IO bound process
		if(i % 3 == 0)
		{
			// mimicking IO wait
			for(int i2=0; i2<t[i]*10; i2++)
			{
				sleep(1);
			}
			printf(1, "(%d) IO Bound\t", i+1);
		}
		
		// CPU bound process
		else
		{
			double y = 0;
			// code to add delay
			for(int i2=0; i2<t[i]*500000; i2++)
			{
				y += 2.69 * 13.01;
			}
			x = y;
			printf(1, "(%d) CPU Bound(%d)\t", i+1, x);	
		}
		
		x = get_burst_time();
		// Collect process info
		struct processInfo *info;
		info = (struct processInfo*) malloc(sizeof(struct processInfo));
		getProcInfo(getpid(), info);
		printf(1, "Burst Time: %d\tContext Switches: %d\n", x, info->numberContextSwitches);
		exit();
	}
	while(wait() != -1);
	exit();
}