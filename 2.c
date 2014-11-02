/* Write iterative and recursive code for square matrix multiplication. Find the largest dimension for which you are able to successfully carryout matrix multiplication. Report the number of page faults and TLB hit ratio. Can we compute the page fault ratio too? */
//usr/bin/time ./a.out also gives the number of page faults
// perf stat -e dTLB-load-misses,iTLB-load-misses ./a.out
// perf stat -e iTLB-loads ./a.out
/*5
  1 2 3 4 5
  1 2 3 4 5
  1 2 3 4 5
  1 2 3 4 5
  1 2 3 4 5
  1 2 3 4 5
  1 2 3 4 5
  1 2 3 4 5
  1 2 3 4 5
  1 2 3 4 5
  */
//for the above input
//37/(638+37) is thr tlb hit ratio
//0.054814814814814816

//This is iterative square matrix multiplication
// the largest dimension for which you are able to successfully carryout matrix multiplication is 835
//
#include<stdio.h>
#include<sys/resource.h>
#include<sys/time.h>
#include<unistd.h>
int main()
{
	int m;
	struct rusage usage;
	scanf("%d",&m);
	int i,j;
	int arr1[m][m];
	int arr2[m][m];
	int arr3[m][m];
	getrusage(RUSAGE_SELF, &usage);
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			scanf("%d",&arr1[i][j]);
		}
	}
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			scanf("%d",&arr2[i][j]);
		}
	}

	int k;
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			arr3[i][j]=0;
			for(k=0;k<m;k++)
			{
				arr3[i][j]+=arr1[i][k]*arr2[k][j];
			}
		}
	}

	
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("%d ",arr3[i][j]);
		}
		printf("\n");
	
	}
	//ru_majflt gives the number of major page faults ie when disk access is required
	//ru_minflt gives the number of minor page faults ie when page allocation to tlb is made
	printf("Number of page faults are %ld",usage.ru_majflt + usage.ru_minflt);
	
	return 0;
}


