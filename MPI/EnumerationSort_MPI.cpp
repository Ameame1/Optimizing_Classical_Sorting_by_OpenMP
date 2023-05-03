#include <stdio.h>
 #include <sys/time.h>
 #include <stdlib.h>
 #include <time.h>
 #include <mpi.h>
 #include <iostream>
 #include<random>
 #include <fstream>
 #include<string>
 #define N 50000

void enumSort(double *a, double *b, int n)
{
	for (int i = 0; i < n; i++)
	{
		int k = 0;
		for (int j = 0; j < n; j++)        
		{
			if (a[i] > a[j])
				k++;
		}
		while (b[k] != 0)
			k++;
		b[k] = a[i];
	}
}




int main(int argc, char* argv[]){
double MPI_start_time,MPI_end_time, end_time, start_time; 
int size,rank;
    MPI_Init(&argc, &argv);	//初始化
    MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    int m=N/2;
    double* ff = new double[N];
    double a[N];
    double b[N];
    double c[N];
    double a1[N];
    double a2[N];
    double b1[m];
    double b2[m];
    double c1[m];
    double c2[m];
    int left=0;
    int right=0;
    int k=0;
    int* d = new int[N];
    std::ifstream ifs("unsorted_array.txt", std::ios::binary | std::ios::in);
	ifs.read((char*)ff, sizeof(double) * N );
	ifs.close();
	for(int i=0;i<N;i++) {
          a[i]=ff[i];
          
    //std::cout<<a[i]<<' ';
    }
   
    for(int i=0;i<m;i++)
    {
	  b1[i]=a[i];
	  b2[i]=a[i+m];
    }    
    MPI_start_time=MPI_Wtime();
    if(rank==1){
    enumSort(b1,c1,m);
    MPI_Send(c1,m+1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
    }    
    else if(rank==0){
        MPI_Recv(c1,m+1,MPI_DOUBLE,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        enumSort(b2,c2,m);
    
    while(left<m && right<m)       //When the left and right arrays are not finished.
    {
    if(c1[left]<=c2[right])
    b[k++]=c1[left++];        // if the small on the left row is left, the pointer moves one unit to the right. If the small on the right row is right, the pointer moves one unit to the right. 
    else
    b[k++]=c2[right++];
    }
    while(left<m)
    {
    b[k++]=c1[left++];       //If the left row is finished, copy all the rest on the right. If the right row is finished, copy all the rest on the left.  

    }
    while(right<m)
    {
    b[k++]=c2[right++];
    }
    MPI_end_time=MPI_Wtime();
    printf("Parallel operation time = %fs\n",MPI_end_time-MPI_start_time);
    start_time=MPI_Wtime();
	enumSort(a,c,N);
	end_time=MPI_Wtime();
    printf("Serial operation time = %fs\n",end_time-start_time);
  
    } 
    MPI_Finalize();	//退出mpi系统
    //...
    
    return 0;
    
}