#include "main.h"

int grades[7] = {0,59,69,79,89,99,100}; //Place grades in this array

struct Solutions   		//adding structure to align data in memory for the solutions
{
	//integers of solutions
	int min_Value;		//minimum value variable
	int max_Value;		//maximum value variable
	int median;		//median value variable
	int mean;		//mean value variable
	int As;		//A variable
	int Bs;		//B variable
	int Cs;		//C variable
	int Ds;		//D variable
	int Fs;		//F variable
}sol;					//declaring struct variable


void sort (int arr[], int size);		//function for sorting the grade array
int Median(int arr[], int size);		//function for finding median
void letterGrade(int arr[], int size);	//function for letter grade counter

int main(void)
{
	int i, size, sum;					//declaring counter variable, size variable, and sum variable
	sum = 0;							//initialize sum to 0
	size = sizeof(grades)/sizeof(int);	//obtaining size of the array
	for (i=0; i<=size-1; i++)			//for loop to calculate the sum of all grades
	{
		sum += grades[i];				//sum=elements of grades array added together
	}
	sort(grades,size);					//call sort function to sort the grades from lowest to greatest
	sol.min_Value = grades[0];			//first(lowest) element is stored in min_Value in struct Solutions
	sol.max_Value = grades[size-1];		//last(greatest) element is stored in max_Value in struct Solutions
	sol.mean = sum/size;				//sum/size is stored in mean in struct Solutions
	sol.median = Median(grades,size);	//calling median function to store median in to struct Solutions
	letterGrade(grades, size);			//calling letter grade counter function

	while(1);							//while forever loop
}

void sort(int arr[], int size) 			//defining the sorting function
{
    int i, j, pointer; 					//counter, pointer and temp variables
    for (i = 0; i < size-1; i++) 		//for-loop checks variables
    {
        pointer = i; 					//set pointer to i
        for (j = i+1; j < size; j++) 	//for-loop, starting at i+1
          if (arr[j] < arr[pointer]) 	//check if element is smaller
            pointer = j; 				//set the pointer to j
        int temp = arr[pointer]; 		//if element is smaller, swap the values using temporary variable
    	arr[pointer] = arr[i];
    	arr[i] = temp;
    }
}

int Median(int arr[], int size)			//defining function Median
{
	int rem, med;						//variable for remainder and median
	rem = size%2;						//check if size is even or odd checking remainder using % modulus
	if(rem == 1)						//if remainder is 1, the size is odd
	{
		med= arr[size/2];				//median is the middle element in the array once it's been sorted
	}
	else								//if remainder is not 1,the size is even (ex: 0,2)
	{
		med = (arr[size/2]+arr[(size/2)-1])/2;  //median is the average of middle two element once the array has been sorted
	}
	return med;							//return median value
}

void letterGrade(int arr[], int size)  	//defining letter grade counter function
{
	int i;								//variable i, indicates to cycle through the array
	for(i=0; i <= size-1; i++)			//for-loop for the array's elements
	{
		if(arr[i] <= 100 && arr[i] >= 90) //if the grade is between 100 and 90
		{
			sol.As++;    				//add +1 to the As variable in struct Solutions
		}
		if(arr[i] < 90 && arr[i] >= 80) //if the grade is between 89 to 80
		{
			sol.Bs++;					//add +1 to the Bs variable in struct Solutions
		}
		if(arr[i] < 80 && arr[i] >= 70) //if the grade is between 79 and 70
		{
			sol.Cs++;					//add +1 to the Cs variable in struct Solutions
		}
		if(arr[i] < 70 && arr[i] >= 60) //if the grade is between 69 and 60
		{
			sol.Ds++;					//add +1 to the Ds variable in struct Solutions
		}
		if(arr[i] < 60)					//if the grade is less than 59
		{
			sol.Fs++;					//add +1 to the Fs variable in struct Solutions
		}
	}
}
