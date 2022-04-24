#include "sorts.h"
#include "swap_tracker.h"
#include <math.h>

void highlight_all(int arr[], int n) {
	for (int i = 0; i < n; i++) set_swap_highlight(i);
	insert_swap(n - 1, n - 1);
}

/**** BUBBLE SORT ****/
void bubble_sort(int arr[], int n) {
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			set_swap_highlight(j + 1);
			if (arr[j] > arr[j + 1]) {
				SWAP(arr[j], arr[j + 1]);
				insert_swap(j, j + 1);
			}
		}
	}
}
/*********************/

/**** SELECTION SORT ****/
void selection_sort(int arr[], int n) {
	int i, j, min;

	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			set_swap_highlight(j);
			if (arr[j] < arr[min]) min = j;
		}

			SWAP(arr[min], arr[i]);
			insert_swap(min, i);
		}
}
/************************/

/**** INSERTION SORT ****/
void insertion_sort(int arr[], int n) {
	int i, key, j;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key) {
			set_swap_highlight(j + 1);
			arr[j + 1] = arr[j];
			set_swap_value(j + 1, arr[j]);
			j = j - 1;
		}

		arr[j + 1] = key;
		set_swap_value(j + 1, key);
	}
}
/************************/

/**** QUICK SORT ****/
int partition(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j < high; j++) {
		set_swap_highlight(j);
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

void quick_sort(int arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		quick_sort(arr, low, pi - 1);
		quick_sort(arr, pi + 1, high);
	}
}
/********************/

/**** MERGE SORT ****/
void merge(int arr[], int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1], R[n2];

	for (i = 0; i < n1; i++) {
		L[i] = arr[l + i];
		set_swap_highlight(l + i);
	}

	for (j = 0; j < n2; j++) {
		R[j] = arr[m + 1 + j];
		set_swap_highlight(m + 1 + j);
	}

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

void merge_sort(int arr[], int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;

		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}
/********************/

/**** HEAP SORT ****/
void heapify(int arr[], int n, int i) {
    int max = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < n && arr[leftChild] > arr[max]) {
		max = leftChild;
		set_swap_highlight(max);
	}

    if (rightChild < n && arr[rightChild] > arr[max]) {
		max = rightChild;
		set_swap_highlight(max);
	}

    if (max != i) {
		SWAP(arr[i], arr[max]);
		insert_swap(i, max);
		heapify(arr, n, max);
    }
}

void heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
		SWAP(arr[0], arr[i]);
		insert_swap(0, i);
		heapify(arr, i, 0);
    }
}
/*******************/

/**** RADIX SORT ****/
void radix_sort(int arr[], int n) {
	int maximum = arr[0];
	int digits = 0;

	for (int i = 1; i < n; i++)
		if (maximum < arr[i]) {
			maximum = arr[i];
			set_swap_highlight(i);
		}

	while (maximum > 0) {
		digits++;
		maximum /= 10;
	}

	for (int i = 0; i < digits; i++) {
		int power = pow(10, i);
		int new_array[n];
		int count[10];

		memset(count, 0, sizeof(count));

		for (int j = 0; j < n; j++) {
			int num = (arr[j] / power) % 10;
			count[num]++;
		}

		for (int j = 1; j < 10; j++) count[j] += count[j - 1];

		for (int j = n - 1; j >= 0; j--) {
			int num = (arr[j] / power) % 10;

			new_array[count[num] - 1] = arr[j];
			count[num]--;
			set_swap_highlight(j);
		}

		for(int j = 0; j < n; j++) {
			arr[j] = new_array[j];
			set_swap_value(j, new_array[j]);
		}
	}
}
/********************/

void cocktail_sort(int arr[], int n) {
	int swapped = 1;
	int start = 0;
	int end = n - 1;

	while (swapped) {
		swapped = 0;

		for (int i = start; i < end; i++) {
			set_swap_highlight(i);
			if (arr[i] > arr[i + 1]) {
				SWAP(arr[i], arr[i + 1]);
				insert_swap(i, i + 1);
				swapped = 1;
			}
		}

		if (!swapped) break;

		swapped = 0;

		end--;

		for (int i = end - 1; i >= start; i--) {
			set_swap_highlight(i);
			if (arr[i] > arr[i + 1]) {
				SWAP(arr[i], arr[i + 1]);
				insert_swap(i, i + 1);
				swapped = 1;
			}
		}

		start++;
	}
}
