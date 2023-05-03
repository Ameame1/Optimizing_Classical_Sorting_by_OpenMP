#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<random>
#include<omp.h>
using namespace std;
//Ame Liu
//22910358

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

double s1, s2, e1, e2;     //Timing system

s1 = omp_get_wtime(); 
MergeSort (a,0,n-1);
//for(int i=0;i<n;i++)
//{
//    cout<<a[i]<<' ';
//}
e1 = omp_get_wtime();

cout << "Serial operation time:" << e1 - s1 << endl;
cout << endl;

s2 = omp_get_wtime(); 
#pragma omp parallel sections
{
 #pragma omp section	
 MergeSort (d,0,m-1);       //MergeSorting of two arrays d,e at the same time.
 #pragma omp section
 MergeSort (e,0,m-1);
}
while(left<m && right<m)       //When the left and right arrays are not finished.
{
    if(d[left]<=e[right])
    b[k++]=d[left++];        // if the small on the left row is left, the pointer moves one unit to the right. If the small on the right row is right, the pointer moves one unit to the right. 
    else
    b[k++]=e[right++];
}
while(left<m)
{
    b[k++]=d[left++];       //If the left row is finished, copy all the rest on the right. If the right row is finished, copy all the rest on the left.  

}
while(right<m)
{
    b[k++]=e[right++];
}

e2 = omp_get_wtime();
cout << "Parallel operation time:" << e2 - s2 << endl;
cout << endl;

return 0;
}