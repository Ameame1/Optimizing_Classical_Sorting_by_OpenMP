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
{  int k=0;
   int i=0;
   int n=100000;
   int left=0;
   int right=0;
   int m=n/2;
   double a[n];
   double b[n];
   double c[n];
   double e[m];
   double d[m];
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<>random(1.0,100000.0);
   for(int i=0;i<n;i++) {
       a[i]=random(gen);
       //std::cout<<a[i]<<' ';
       }
	//quickSort(a,0,n-1);   
	   for(int i=0;i<n;i++){
	   b[i]=a[i];
	   }
  for(int i=0;i<m;i++)
  {
	  d[i]=b[i];
	  e[i]=b[i+m];
  }

double s1, s2, e1, e2;

s1 = omp_get_wtime(); 
QuickSort(a,0,n-1);
//for (int i = 0;i<n;i++)
//    {
//    cout<<a[i]<<' ';
//        }
e1 = omp_get_wtime();

cout << "Serial operation time:" << e1 - s1 << endl;
cout << endl;

s2 = omp_get_wtime(); 
#pragma omp parallel sections
{
 #pragma omp section	   
 QuickSort(d,0,m-1);      //quickSorting of two arrays d,e at the same time.
 #pragma omp section
 QuickSort(e,0,m-1);
}
while(left<m && right<m)      //When the left and right arrays are not finished.    
{
    if(d[left]<=e[right])
    b[k++]=d[left++];
    else 
    b[k++]=e[right++];          // if the small on the left row is left, the pointer moves one unit to the right. If the small on the right row is right, the pointer moves one unit to the right. 
}
while(left<m)
{
    b[k++]=d[left++];

}                               //If the left row is finished, copy all the rest on the right. If the right row is finished, copy all the rest on the left.       
while(right<m)
{
    b[k++]=e[right++];
}

e2 = omp_get_wtime();
cout << "Parallel operation time:" << e2 - s2 << endl;
cout << endl;

return 0;
}