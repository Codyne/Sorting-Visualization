#ifndef SORTS_H
#define SORTS_H

#include <string.h>

enum sorts { BUBBLE_SORT, SELECTION_SORT, INSERTION_SORT, QUICK_SORT, MERGE_SORT,
	HEAP_SORT, RADIX_SORT };

#define SWAP(x, y) do {													\
		unsigned char tmp[sizeof(x) == sizeof(y)						\
						  ? (signed)sizeof(x)							\
						  : -1];										\
		memcpy(tmp,&y, sizeof(x));										\
		memcpy(&y,&x, sizeof(x));										\
		memcpy(&x,tmp, sizeof(x));										\
	} while(0)

void highlight_all(int arr[], int n);

void bubble_sort(int arr[], int n);
void selection_sort(int arr[], int n);
void insertion_sort(int arr[], int n);
void quick_sort(int arr[], int low, int high);
void merge_sort(int arr[], int l, int r);
void heap_sort(int arr[], int n);
void radix_sort(int a[], int n);

#endif
