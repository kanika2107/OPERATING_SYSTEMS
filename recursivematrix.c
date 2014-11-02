//perf stat -e dTLB-load-misses,iTLB-load-misses ./a.out
//perf stat -e iTLB-loads ./a.out
//input was 
/*
   2
   9 9
   8 8
   7 7
   6 6
   */
//0.08968058968058969=73/73+741


/*  Write iterative and recursive code for square matrix multiplication. Find the largest dimension for which you are able to successfully carryout matrix multiplication. Report the number of page faults and TLB hit ratio. Can we compute the page fault ratio too? 
*/



#include<stdio.h>
#include<sys/resource.h>
#include<sys/time.h>
#include<unistd.h>
void strassen(int a[100][100],int b[100][100],int c[100][100],int n)
{
	if(n==1)
	{
//		printf("kk%dkk%dkk  ",a[1][1],b[1][1]);
		c[1][1]=a[1][1]*b[1][1];
	}
	else
	{
		int a11[100][100];
		int a12[100][100];
		int a21[100][100];
		int a22[100][100];
		int b11[100][100];
		int b12[100][100];
		int b21[100][100];
		int b22[100][100];
		int c11[100][100];
		int c12[100][100];
		int c21[100][100];
		int c22[100][100];
		int i,j;
		int k=1;
		int l=1;
		for(i=1;i<=n/2;i++)
		{
			for(j=1;j<=n/2;j++)
			{
				a11[k][l]=a[i][j];
				b11[k][l]=b[i][j];
				l++;
			}
			k++;
			l=1;
		}
		k=1;
		l=1;
		for(i=(n/2)+1;i<=n;i++)
		{
			for(j=1;j<=n/2;j++)
			{
				a21[k][l]=a[i][j];
				b21[k][l]=b[i][j];
				l++;
			}
			k++;
			l=1;
		}
		k=1;
		l=1;
		for(i=1;i<=n/2;i++)
		{
			for(j=(n/2)+1;j<=n;j++)
			{
				a12[k][l]=a[i][j];
				b12[k][l]=b[i][j];
				l++;
			}
			k++;
			l=1;
		}
		k=1;
		l=1;
		for(i=(n/2)+1;i<=n;i++)
		{
			for(j=(n/2)+1;j<=n;j++)
			{
				a22[k][l]=a[i][j];
				b22[k][l]=b[i][j];
				l++;
			}
			k++;
			l=1;
		}
/*		for(i=1;i<=n/2;i++)
		{
			for(j=1;j<=n/2;j++)
			{
				printf("%d ",b11[1][1]);
			}
			printf("\n");
		}*/
		int arr1[100][100];
		int arr2[100][100];
		int arr3[100][100];
		int arr4[100][100];
		int arr5[100][100];
		int arr6[100][100];
		int arr7[100][100];
		int arr8[100][100];
		strassen(a11,b11,arr1,n/2);
/*		for(i=1;i<=n/2;i++)
		{
			for(j=1;j<=n/2;j++)
			{
				printf("%d ",arr1[i][j]);
			}
			printf("\n");
		}*/
		strassen(a12,b21,arr2,n/2);
		strassen(a11,b12,arr3,n/2);
		strassen(a12,b22,arr4,n/2);
		strassen(a21,b11,arr5,n/2);
		strassen(a22,b21,arr6,n/2);
		strassen(a21,b12,arr7,n/2);
		strassen(a22,b22,arr8,n/2);
		for(i=1;i<=n/2;i++)
		{
			for(j=1;j<=n/2;j++)
			{
				c11[i][j]=arr1[i][j]+arr2[i][j];
				c12[i][j]=arr3[i][j]+arr4[i][j];
				c21[i][j]=arr5[i][j]+arr6[i][j];
				c22[i][j]=arr8[i][j]+arr7[i][j];
			}
		}
		k=1;
		l=1;
		for(i=1;i<=n/2;i++)
		{
			for(j=1;j<=n/2;j++)
			{
				c[k][l++]=c11[i][j];
			}
			l=1;
			k++;
		}
		k=1;
		l=(n/2)+1;
		for(i=1;i<=n/2;i++)
		{
			for(j=1;j<=n/2;j++)
			{
				c[k][l++]=c12[i][j];
			}
			l=(n/2)+1;
			k++;
		}
		k=(n/2)+1;
		l=1;
		for(i=1;i<=n/2;i++)
		{
			for(j=1;j<=n/2;j++)
			{
				c[k][l++]=c21[i][j];
			}
			k++;
			l=1;
		}
		k=(n/2)+1;
		l=(n/2)+1;
		for(i=1;i<=n/2;i++)
		{
			for(j=1;j<=n/2;j++)
			{
				c[k][l++]=c22[i][j];
			}
			k++;
			l=(n/2)+1;
		}
	}
	



}
int main()
{
	int n;
	scanf("%d",&n);
	int i,j;
	int arr1[100][100];
	int arr2[100][100];
	int arr3[100][100];
	struct rusage usage;
	getrusage(RUSAGE_SELF, &usage);

	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			scanf("%d",&arr1[i][j]);
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			scanf("%d",&arr2[i][j]);
		}
	}
	strassen(arr1,arr2,arr3,n);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			printf("%d ",arr3[i][j]);
		}
		printf("\n");
	}
	printf(" the number of page faults are %ld ",usage.ru_majflt + usage.ru_minflt);
	return 0;
}

