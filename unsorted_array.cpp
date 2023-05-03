#include <math.h>
#include <fstream>
#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<random>
#include<mpi.h>

int main(int argc, char* argv[]){
	double MPI_start_time,MPI_end_time, end_time, start_time; 
    int size,rank;
    MPI_Init(&argc, &argv);	//初始化
    MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    int n=100000;
    double* f = new double[n];
	double* ff = new double[n];
	double* c = new double[n];
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<>random(1.0,100000.0);
   for(int i=0;i<n;i++) {
       f[i]=random(gen);
       
       }

	if(rank==1){
    std::ofstream  ofs("unsorted_array.txt", std::ios::binary | std::ios::out);
	ofs.write((const char*)f, sizeof(double) * n);
	ofs.close();
	
	
	std::ifstream ifs("unsorted_array.txt", std::ios::binary | std::ios::in);
	ifs.read((char*)ff, sizeof(double) * n);
	ifs.close();
	MPI_Send(f,n+1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	MPI_Send(ff,n+1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
    }    
    else if(rank==0){
        MPI_Recv(f,n+1,MPI_DOUBLE,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(ff,n+1,MPI_DOUBLE,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        
	
	//for(int i=0;i<n;i++) {
       
    //   std::cout<<ff[i]<<' ';
    //   }
    for (int i = 0; i < n; i++)
	{  if(f[i]==ff[i])
	   c[i]=1;
	   else
	   c[i]=0;
	}
    size_t i=0;
   for(;i!=n;++i)
		if(c[i]!=1)
		    break;
	std::cout<<(i==n?"All things same":"Something wrong")<<std::endl;
	}
    MPI_Finalize();	//退出mpi系统
    //...
    
    return 0;

}
