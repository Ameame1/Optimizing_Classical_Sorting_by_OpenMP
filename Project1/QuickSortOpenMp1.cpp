#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<random>
#include<omp.h>
using namespace std;
//Ame Liu
//22910358

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



int main()
{                   
   int n=100000;
   std::random_device rd;      //Generate 100000 double floating point numbers.
   std::mt19937 gen(rd());
   std::uniform_real_distribution<>random(1.0,100000.0);
    double a1[n];
	double b1[n];
  
       for(int i=0;i<n;i++) {
       a1[i]=random(gen);
       //std::cout<<a1[i]<<' ';
       }     
	   for(int i=0;i<n;i++){
	   b1[i]=a1[i];   
	   }
   double a2[n];
   double b2[n];
  for(int i=0;i<n;i++) {
       a2[i]=random(gen);
       //std::cout<<a2[i]<<' ';
       }
  for(int i=0;i<n;i++){
	   b2[i]=a2[i];        //Make sure a1[] = b1[], a2[] = b2[], a3[] = b3[]
	   }	              
   double a3[n];
   double b3[n];
  for(int i=0;i<n;i++) {
       a3[i]=random(gen);
       //std::cout<<a2[i]<<' ';
       }
  for(int i=0;i<n;i++){
	   b3[i]=a3[i];   
	   }   
	double a4[n];
	double b4[n];
  for(int i=0;i<n;i++) {
       a4[i]=random(gen);
       //std::cout<<a2[i]<<' ';
       }  
  for(int i=0;i<n;i++){
	   b4[i]=a4[i];   
	   } 
	    
	     
    double s1, s2, e1, e2;        //Timing system
	s1 = omp_get_wtime(); 
    QuickSort(a1,0,n-1); //(a,0,n-1)
	QuickSort(a2,0,n-1); 
	QuickSort(a3,0,n-1);
	QuickSort(a4,0,n-1); 
	e1 = omp_get_wtime();
	cout << "Serial operation time:" << e1 - s1 << endl;
	 //for (int i = 0;i<10000;i++)
        {
        //cout<<a1[i]<<' ';
        }
	cout << endl;
	s2 = omp_get_wtime();
 #pragma omp parallel sections
 {
    #pragma omp section
     {       
   QuickSort(b1,0,n-1); //(a,0,n-1)
	 }
	#pragma omp section
	{
	QuickSort(b2,0,n-1);     //Perform 4 quick sorts in parallel
	}
	#pragma omp section
	{
	QuickSort(b3,0,n-1);
	}
    #pragma omp section
	{
	QuickSort(b4,0,n-1);
	}
    
 }	
	e2 = omp_get_wtime();
    cout << "Parallel operation time:" << e2 - s2 << endl;
	 //for (int i = 0;i<10000;i++)
        {
        //cout<<a2[i]<<' ';
        }
    
	
	cout << endl;




    return 0;
}