#include "sorts.h"
#include "swap_tracker.h"

void bubbleSort(int arr[], int n) {
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n-i-1; j++) {
			if (arr[j] > arr[j+1]) {
				SWAP(arr[j], arr[j+1]);
				insert_swap(j, j + 1);
			}
		}
	}
}

/**** QUICK SORT ****/
int partition(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j < high; j++) {
		if (arr[j] <= pivot) {
			i++;
			SWAP(arr[i], arr[j]);
			insert_swap(i, j);
		}
	}

	SWAP(arr[i + 1], arr[high]);
	insert_swap(i + 1, high);

	return (i + 1);
}

void quickSort(int arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}
/********************/

/**** MERGE SORT ****/
void merge(int arr[], int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			set_swap_value(k, L[i]);
			i++;
		} else {
			arr[k] = R[j];
			set_swap_value(k, R[j]);
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		set_swap_value(k, L[i]);
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R[j];
		set_swap_value(k, R[j]);
		j++;
		k++;
	}
}

void mergeSort(int arr[], int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;

		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}
/********************/

/**** HEAP SORT ****/
void heapify(int arr[], int n, int i) {
    int max = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < n && arr[leftChild] > arr[max]) max = leftChild;

    if (rightChild < n && arr[rightChild] > arr[max]) max = rightChild;

    if (max != i) {
		SWAP(arr[i], arr[max]);
		insert_swap(i, max);
		heapify(arr, n, max);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
		SWAP(arr[0], arr[i]);
		insert_swap(0, i);
		heapify(arr, i, 0);
    }
}
/*******************/
