#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/types.h>
#include <unistd.h>
void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
  
// A function to implement bubble sort  
void bubbleSort(int arr[], int n)  
{  
    int i, j;  
    for (i = 0; i < n-1; i++)      
      
    // Last i elements are already in place  
    for (j = 0; j < n-i-1; j++)  
        if (arr[j] > arr[j+1])  
            swap(&arr[j], &arr[j+1]);

}  
  
int main(){
	int arreglo[] = {5,2,3,1,4};
	int pid = fork();
	if (pid > 0){
		bubbleSort(arreglo,5);
		for (int i = 0; i < 5; i++) printf("%d\t",arreglo[i]);
	printf("\n");

	}


	else {
		for (int i = 0; i < 5; i++) printf("%d\t",arreglo[i]);
  	printf("\n");

	}
	return 0;
}