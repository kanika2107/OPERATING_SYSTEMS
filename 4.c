#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
int main(int argc, char* argv[])
{
//	printf("%s",argv[1]);
	int a;
	char mode[]="0775";
	int i;
	i=strtol(mode,0,8);
        a=chmod("../../../../a",i);
	FILE *fp1, *fp2;
	char ac;
	fp1=fopen(argv[1],"r");
	chdir("../../../../a");
	fp2=fopen(argv[1],"w");
	ac=fgetc(fp1);
	while(ac!=EOF)
	{
		fputc(ac,fp2);
		ac=fgetc(fp1);
	}
//	fputc('\0',fp2);
	fclose(fp1);
	fclose(fp2);
	char mode1[]="0000";
	i=strtol(mode1,0,8);
	a=chmod(".",i);

        return 0;
}

