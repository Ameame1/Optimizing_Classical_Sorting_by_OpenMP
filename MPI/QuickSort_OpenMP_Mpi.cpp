 #include <stdio.h>
 #include <sys/time.h>
 #include <stdlib.h>
 #include <time.h>
 #include <mpi.h>
 #include <iostream>
 #include<random>
 #include <fstream>
 #include<string>
 #include<omp.h>
using namespace std;
 #define N 100

 void QuickSort(double *arr,int low,int high)
{
	//If the interval is more than one number
    if(low < high)
	{
		double temp = arr[low]; //Take the first number of the interval as the reference number.
		int i = low;   //From right to left, find those larger than the temp value, and from left to right, find those larger than the temp value.
		int j = high;
		//Perform a while loop
		while(i < j)
		{
			//When the number on the right is greater than the number of baselines, skip and continue looking to the left.
			//Jump out of loop when conditions are not met
			while(i<j && arr[j] > temp) // 
				j--;
			//Fill in the number of reference elements less than or equal to the right into the corresponding position on the right
			arr[i] = arr[j];
			//When the number on the left is less than or equal to the base number, skip and continue looking to the right
		
			while(i<j && arr[i] <= temp)
				i++;
			//Fill in the number of elements on the left that are larger than the baseline element in the corresponding position on the left
			arr[j] = arr[i];
		}
		
		arr[i] = temp;
	
		
            QuickSort(arr,low,i-1);
		
   
		    QuickSort(arr,i+1,high);
       
    }   

	else
		return;
}

int main(int argc, char* argv[]){
double MPI_start_time,MPI_end_time, end_time, start_time; 
int size,rank;
    MPI_Init(&argc, &argv);	//初始化
    MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    int m=N/2;
    double* ff = new double[N];
    double* f = new double[N];
    double* a = new double[N];
    double* b = new double[N];
    double* c = new double[N];
    double* d = new double[N];
    double* b1 = new double[m];
    double* b2 = new double[m];
    int left=0;
    int right=0;
    int k=0;
    std::ifstream ifs("unsorted_array.txt", std::ios::binary | std::ios::in);
	ifs.read((char*)ff, sizeof(double) * N );
	ifs.close();
	#pragma omp parallel
    {
    #pragma omp for
    for(int i=0;i<N;i++) {
          a[i]=ff[i];
          b[i]=ff[i];
    //std::cout<<a[i]<<' ';
    }
    #pragma omp for
    for(int i=0;i<m;i++)
    {
	  b1[i]=b[i];
	  b2[i]=b[i+m];
    
    } 
    }
    MPI_start_time=MPI_Wtime();
    if(rank==1){
    QuickSort(b1,0,m-1);
    MPI_Send(b1,m,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
    }    
    else if(rank==0){
        MPI_Recv(b1,m,MPI_DOUBLE,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        QuickSort(b2,0,m-1);
    
    while(left<m && right<m)       //When the left and right arrays are not finished.
    {
    if(b1[left]<=b2[right])
    b[k++]=b1[left++];        // if the small on the left row is left, the pointer moves one unit to the right. If the small on the right row is right, the pointer moves one unit to the right. 
    else
    b[k++]=b2[right++];
    }
    while(left<m)
    {
    b[k++]=b1[left++];       //If the left row is finished, copy all the rest on the right. If the right row is finished, copy all the rest on the left.  

    }
    while(right<m)
    {
    b[k++]=b2[right++];
    }
    MPI_end_time=MPI_Wtime();
    printf("Parallel operation time = %fs\n",MPI_end_time-MPI_start_time);
    start_time=MPI_Wtime();
	QuickSort(a,0,N-1);
	end_time=MPI_Wtime();
    printf("Serial operation time = %fs\n",end_time-start_time);
    
   MPI_Finalize();	//退出mpi系统
    
    
    return 0;
    
}
}