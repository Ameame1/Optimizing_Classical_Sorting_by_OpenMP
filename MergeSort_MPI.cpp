 #include <stdio.h>
 #include <sys/time.h>
 #include <stdlib.h>
 #include <time.h>
 #include <mpi.h>
 #include <iostream>
 #include<random>
 #include <fstream>
 #include<string>
 #define N 1000

void Merge(double arr[],int low,int mid,int high){
    //Low is the first element of the 1st ordered zone, i points to the 1st element, and mid is the last element of the 1st ordered zone.
    int i=low,j=mid+1,k=0;  //Mid + 1 is the first element of the second ordered region, and j points to the first element.
    double *temp=new double[high-low+1]; //Temp array temporarily stores the merged ordered sequence.
    while(i<=mid&&j<=high){
        if(arr[i]<=arr[j]) //Which side is smaller, which side is placed directly into the temparray.
            temp[k++]=arr[i++];
        else
            temp[k++]=arr[j++];
    }
    while(i<=mid)  //After the comparison, if there is an array left that indicates that the rest is already in order of sequence, copy directly.
        temp[k++]=arr[i++];
    while(j<=high)
        temp[k++]=arr[j++];
    for(i=low,k=0;i<=high;i++,k++)//Save the sequence back to the range of low to high in arr.
    arr[i]=temp[k];        
    delete []temp;   //Free up memory.
}

void MergeSort (double arr [], int low,int high) {      //incise
    if(low>=high) { return; } // Stop when all sequence lengths are 1.
    int mid =  low + (high - low)/2;  //Gets the element in the middle of the sequence.
    
    MergeSort(arr,low,mid);  // Recursive to the left half.
          
    MergeSort(arr,mid+1,high);  //  Recursive to the right half.

         
      
    Merge(arr,low,mid,high);  // merge.
         
}

int main(int argc, char* argv[]){
double MPI_start_time,MPI_end_time, end_time, start_time; 
int size,rank;
    MPI_Init(&argc, &argv);	//初始化
    MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    int m=N/2;
    double* f = new double[N];
    double* ff = new double[N];
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
	for(int i=0;i<N;i++) {
          a[i]=ff[i];
          b[i]=ff[i];
    //std::cout<<a[i]<<' ';
    }
    for(int i=0;i<m;i++)
    {
	  b1[i]=b[i];
	  b2[i]=b[i+m];
    } 
    MPI_start_time=MPI_Wtime();
    if(rank==1){
    MergeSort(b1,0,m-1);
    MPI_Send(b1,m,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
    }    
    else if(rank==0){
        MPI_Recv(b1,m,MPI_DOUBLE,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MergeSort(b2,0,m-1);
    
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
    printf("Parallel operation time: = %fs\n",MPI_end_time-MPI_start_time);
    start_time=MPI_Wtime();
	MergeSort(a,0,N-1);
	end_time=MPI_Wtime();
    printf("Serial operation time = %fs\n",end_time-start_time);
    
    for(int i=0;i<N;i++) {
          f[i]=b[i];
         
    }
    std::ofstream  ofs("MergeSort_MPI.txt", std::ios::binary | std::ios::out);
	ofs.write((const char*)f, sizeof(double) * N);
	ofs.close();
     
    std::ifstream ifs("MergeSort_MPI.txt", std::ios::binary | std::ios::in);
	ifs.read((char*)ff, sizeof(double) * N);
	ifs.close();
	for (int i = 0; i < N; i++)
	{  if(a[i]==ff[i])
	   c[i]=1;
	   else
	   c[i]=0;
	}
    size_t i=0;
   for(;i!=N;++i)
		if(c[i]!=1)
		    break;
	std::cout<<(i==N?"All things same":"Something wrong")<<std::endl;
	

    
    }    



    MPI_Finalize();	//退出mpi系统
   
    
    return 0;
    
}