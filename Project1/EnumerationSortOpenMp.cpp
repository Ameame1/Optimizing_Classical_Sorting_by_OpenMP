#include<omp.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<random>
using namespace std;
//Ame Liu
//22910358

//Serial sorting
//Create two arrays. Array A is the sequence to be sorted, and array B is used to store the sorted sequence.
//Two for loops are used to compare enumeration sorting. The external for loop i = 0... i + +. Each time, we will select a value to compare with each number in the sequence. The purpose of this loop is to change this value.
//The purpose of the second for loop j = 0... j + + is to select a value to compare with each number in the sequence, which is "each number"
//After executing the for loop twice, we can compare each number in the sequence with these numbers in the sequence. If a [i] > a [j] performs the k + + operation, 
//it means to move the position of a [i] to the right. For example, 
//if the leftmost number a [0] in the sequence is larger than the five numbers in the sequence, execute k + + five times.
//Start with the first number [i] and compare with the numbers in the sequence. If [i] is smaller than the numbers in the sequence, put [i] in the position of the corresponding array b,
//The meaning of while loop is to judge whether the position of array b has a value at this time. If so (for example, if two numbers in array a are equal, their k + + times are also equal. 
//At this time, if you do not use while loop judgment, the old original value will be replaced by the new value. For example, 33325 may be arranged as 23 empty 5).
//Finally, b [k] = a [i] is to put the compared number in the position that should be placed in array b.
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
//Parallel sorting
//In principle, the position of all numbers in the array is fixed from the beginning. 
//The parallel operation does not affect the final order of all numbers, so you can directly use the OpenMP command of the for loop
void paEnumSort(double *a, double *b, int n)
{
	
#pragma omp parallel
 {	
	 #pragma omp for
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

}
int main()
{

	int n=100000;
	double a[n];
    double a1[n];
    double a2[n];
    double b1[n];
    double b2[n];
	double s1, s2, e1, e2;      //Timing system
	 std::random_device rd;
     std::mt19937 gen(rd());
     std::uniform_real_distribution<>random(1.0,100000.0);
     for(int i=0;i<n;i++) {
       a[i]=random(gen);
       //std::cout<<a[i]<<' ';
       }
       for(int i=0;i<n;i++)
       {  
          a1[i]=a[i];
          a2[i]=a[i];
           
       }
		s1 = omp_get_wtime();
		enumSort(a1, b1, n);
        e1 = omp_get_wtime();
		cout << "Serial operation time:" << e1 - s1 << endl;

		s2 = omp_get_wtime();
		paEnumSort(a2, b2, n);
		e2 = omp_get_wtime();
		cout << "Parallel operation time:" << e2 - s2 << endl;
		cout << endl;
		
	
	
}
