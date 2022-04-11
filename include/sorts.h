#include <string.h>

#define SWAP(x, y) do {													\
		unsigned char tmp[sizeof(x) == sizeof(y)						\
						  ? (signed)sizeof(x)							\
						  : -1];										\
		memcpy(tmp,&y, sizeof(x));										\
		memcpy(&y,&x, sizeof(x));										\
		memcpy(&x,tmp, sizeof(x));										\
	} while(0)


void bubbleSort(int arr[], int n);
void quickSort(int arr[], int low, int high);
void mergeSort(int arr[], int l, int r);
void heapSort(int arr[], int n);
void radixSort(int a[], int n);
