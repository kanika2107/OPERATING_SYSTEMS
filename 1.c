/* Implement the time command. You have to report the user, system and real time. Most important you have to handle Ctrl-C. After a Ctrl-C you have to print the statistics collected so far. 
*/





/*
 Real is wall clock time - time from start to finish of the call. This is all elapsed time including time slices used by other processes and time the process spends blocked (for example if it is waiting for I/O to complete).

 User is the amount of CPU time spent in user-mode code (outside the kernel) within the process. This is only actual CPU time used in executing the process. Other processes and time the process spends blocked do not count towards this figure.

 Sys is the amount of CPU time spent in the kernel within the process. This means executing CPU time spent in system calls within the kernel, as opposed to library code, which is still running in user-space.
   */
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include<time.h>
#include <signal.h>
int STOP = 0;
void sigint_handler(int sig) {
	    printf("\nCTRL-C detected\n");
	    STOP = 1;
}
int main() {
	signal(SIGINT, sigint_handler);
	struct rusage usage;
	clock_t t;
	double cpu_time_used;
	int i, j, k = 0;
	/*The first parameter, who, specifies for whom the report is required. The value of who could be RUSAGE_SELF, RUSAGE_CHILDREN or RUSAGE_THREAD. If who is RUSAGE_SELF, the information for the calling process is returned. If who is RUSAGE_CHILDREN, then the information regarding all children of the calling process that have terminated and been waited for is returned. If who is RUSAGE_THREAD, the the information about the calling thread is returned. The second parameter is a pointer to struct rusage. */

	getrusage(RUSAGE_SELF, &usage);
	t=clock();
	while(1)
	{
		if(STOP)
		{
			break;
		}
		//We will place our code here
	for (i = 0; i < 100000; i++) {
		if(STOP)
			break;
		for (j = 0; j < 10000; j++) {
			if(STOP)
				break;
			k += 20; 
		}
	}

	if(i==100000)//otherwise if i dont press ctrl-c while loop will keep on executing for infinite times
		break;
	}
	t=clock()-t;
	//
	getrusage(RUSAGE_SELF, &usage);
	printf("System time: %ld.%06ld sec\n",usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
	printf("User time:   %ld.%06ld sec\n",usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	printf("real time is %f seconds\n", time_taken);
	return 0;
}
