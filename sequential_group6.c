#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc,char *argv[])
{
	FILE *first,*second;
	int status1,status2;
	int i=0,j=0,k=0,l=0;
	int arr1[205000],arr2[205000];
	int *arr3;
	double time;
	
	clock_t start,end;
	
	arr3=(int *)malloc(410000*sizeof(int));
	
	printf("Sequential program launched\n");
	
	first=fopen(argv[1],"r");
	second=fopen(argv[2],"r");
	
	printf("Reading file1.txt\n");
	printf("Reading file2.txt\n");
	
	start=clock();
	printf("Timer started\n");
	
	if(first==NULL || second==NULL)
		printf("Cannot open the files!");
	else
	{
		status1=fscanf(file1,"%d",&arr1[i]);
		status2=fscanf(file2,"%d",&arr2[j]);
		
		while(status1!=EOF && status2!=EOF)
		{
			i++;
			j++;
			
			status1=fscanf(file1,"%d",&arr1[i]);
			status2=fscanf(file2,"%d",&arr2[j]);
		}
		
		fclose(first);
		fclose(second);
	}
	
	double sum=0;
	
	for(k=0;k<205000;k++)
	{
		sum+=arr1[k]+arr2[k];
	}
	
	double average=sum/410000;
	
	for(k=0;k<205000;k++)
	{
		*(arr3+k)=arr1[k];
	}
	
	for(l=0;l<205000;l++)
	{
		*(arr3+(l+205000))=arr2[l];
	}
	
	double variance=0;
	
	for(k=0;k<410000;k++)
	{
		variance+=pow((*(arr3+k)-average),2);
	}
	
	double std_dev=sqrt(variance/410000);
	
	printf("The average is: %f\n",average);
	printf("The standard deviation: %f\n",std_dev);
	
	end=clock();
	
	time=((double)(end-start))/CLOCKS_PER_SEC;
	
	printf("Calculation completed in %f milliseconds.\n",(time*1000));
	
	return 0;
}
