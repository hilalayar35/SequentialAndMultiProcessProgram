#include <sys/types.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

int main(int argc,char *argv[])
{
	int status1=0;
	
	printf("Multi process program launched\n");
	
	pid_t pid;
	pid = fork();
	
	int SIZE=4096;
	char *name = "Project1";
	int shm_fd;
	void *ptr;
	void *ptr1;
	
	double time;
	clock_t start,end;
	
	if(pid < 0) {
		fprintf(stderr, "Fork Failed");
	}
	else if(pid == 0) {
		int i=0,j=0,k=0;
		int status2=0;
		int arr2[205000];
		int sum2=0;
		
		FILE *file2=fopen(argv[2],"r");
		
		shm_fd = shm_open(name,O_CREAT | O_RDWR, 0666);
		ftruncate(shm_fd,SIZE);
		ptr=mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shm_fd,0);
		
		if(file2==NULL)
			printf("Cannot open the file!");
		else
		{
			status2=fscanf(file2,"%d",&arr2[i]);
			
			while(status2!=EOF)
			{
				i++;
				status2=fscanf(file2,"%d",&arr2[i]);
			}
			
			fclose(file2);
		}	
		
		for(j=0;j<205000;j++)
			sum2+=arr2[j];
			
		ptr1=mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
		
		double avg1=atof(ptr1);
		
		double variance=0;
		
		for(k=0;k<205000;k++)
			variance+=pow((arr2[k]-avg1),2);
			
		sprintf(ptr,"%d",sum2);
		ptr+=8;
		
		sprintf(ptr,"%f",variance);
	}
	else {
		wait(NULL);
		
		FILE *file1=fopen(argv[1],"r");
		int m=0,n=0;
		int t,y,z;
		int arr1[205000];
		int sum1=0;
		double average=0;
		
		shm_fd = shm_open(name,O_RDWR, 0666);
		ptr=mmap(0,SIZE,PROT_READ,MAP_SHARED,shm_fd,0);
		
		if(file1==NULL)
			printf("Cannot open the file!");
		else
		{
			status1=fscanf(file1,"%d",&arr1[m]);
			
			while(status1!=EOF)
			{
				m++;
				status1=fscanf(file1,"%d",&arr1[m]);
			}
			
			fclose(file1);
		}
		
		printf("Parent has read file1.txt\n");
		printf("Child has read file2.txt\n");
		
		start=clock();
		printf("The parent started the timer.\n");
		
		for(n=0;n<205000;n++)
			sum1+=arr1[n];
			
		printf("Partial Sum is computed on parent\n");
		printf("Partial Sum is computed on child\n");
		
		int len=strlen(ptr);
		
		char first[8];
		char second[len-8];
		
		for(t=0;t<8;t++)
			first[t]=((char *)ptr)[t];
			
		for(y=0;y<(len-8);y++)
			second[y]=((char *)ptr)[y+8];
			
		printf("Child sent Partial sum to Parent\n");
		
		int sumtwo=atoi(first);
		
		average=(double)(sum1+sumtwo)/410000;
		
		printf("The global average is computed on parent\n");
		printf("The global average is: %f\n",average);
		
		ptr1=mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
		sprintf(ptr,"%f",average);
		
		printf("Parent sent global average to child\n");
		
		double variance1=0;
		
		for(z=0;z<205000;z++)
			variance1+=pow((arr1[z]-average),2);
			
		printf("Partial variance is computed on parent\n");
		
		double variance2=atof(second);
		
		printf("Partial variance is computed on child\n");
		printf("Child sent partial variance to parent\n");
		
		double std_dev=sqrt((variance1+variance2)/410000);
		
		printf("The standard deviation is computed on parent\n");
		printf("The standard deviation: %f\n",std_dev);
		
		end=clock();
		time=((double)(end-start))/CLOCKS_PER_SEC;
		
		printf("Calculation completed in %f milliseconds\n",(time*1000));		
	}
	
	return 0;
}
