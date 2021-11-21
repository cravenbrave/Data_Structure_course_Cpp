// C++ program for Merge Sort
#include <iostream>
using namespace std;

// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(int arr[], int left, int mid, int right, int temp[])
{
	int i = left;	 //左序列指针
	int j = mid + 1; //右序列指针
	int t = 0;		 //临时数组指针
	while (i <= mid && j <= right)
	{
		if (arr[i] <= arr[j])
		{
			temp[t++] = arr[i++];
		}
		else
		{
			temp[t++] = arr[j++];
		}
	}
	while (i <= mid)
	{ //将左边剩余元素填充进temp中
		temp[t++] = arr[i++];
	}
	while (j <= right)
	{ //将右序列剩余元素填充进temp中
		temp[t++] = arr[j++];
	}
	t = 0;
	//将temp中的元素全部拷贝到原数组中
	while (left <= right)
	{
		arr[left] = temp[t];
		left++;
		t++;
	}
	// auto const subArrayOne = mid - left + 1;
	// auto const subArrayTwo = right - mid;

	// // Create temp arrays
	// auto *leftArray = new int[subArrayOne],
	// 	*rightArray = new int[subArrayTwo];

	// // Copy data to temp arrays leftArray[] and rightArray[]
	// for (auto i = 0; i < subArrayOne; i++)
	// 	leftArray[i] = array[left + i];
	// for (auto j = 0; j < subArrayTwo; j++)
	// 	rightArray[j] = array[mid + 1 + j];

	// auto indexOfSubArrayOne = 0, // Initial index of first sub-array
	// 	indexOfSubArrayTwo = 0; // Initial index of second sub-array
	// int indexOfMergedArray = left; // Initial index of merged array

	// // Merge the temp arrays back into array[left..right]
	// while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
	// 	if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
	// 		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
	// 		indexOfSubArrayOne++;
	// 	}
	// 	else {
	// 		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
	// 		indexOfSubArrayTwo++;
	// 	}
	// 	indexOfMergedArray++;
	// }
	// // Copy the remaining elements of
	// // left[], if there are any
	// while (indexOfSubArrayOne < subArrayOne) {
	// 	array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
	// 	indexOfSubArrayOne++;
	// 	indexOfMergedArray++;
	// }
	// // Copy the remaining elements of
	// // right[], if there are any
	// while (indexOfSubArrayTwo < subArrayTwo) {
	// 	array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
	// 	indexOfSubArrayTwo++;
	// 	indexOfMergedArray++;
	// }
}
void mergeSort(int array[], int const begin, int const end, int temp[])
{
	if (begin >= end)
		return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid, temp);
	mergeSort(array, mid + 1, end, temp);
	merge(array, begin, mid, end, temp);
}
// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int array[], int size)
{
	int temp[size];
	mergeSort(array, 0, size - 1, temp);
}

// UTILITY FUNCTIONS
// Function to print an array
void printArray(int A[], int size)
{
	for (auto i = 0; i < size; i++)
		cout << A[i] << " ";
}

// Driver code
int main()
{
	int arr[] = {12, 11, 13, 5, 6, 7};
	auto arr_size = sizeof(arr) / sizeof(arr[0]);

	cout << "Given array is \n";
	printArray(arr, arr_size);

	mergeSort(arr, arr_size);
	// mergeSort(arr, 0, arr_size - 1);

	cout << "\nSorted array is \n";
	printArray(arr, arr_size);
	cout << endl;
	return 0;
}

// This code is contributed by Mayank Tyagi
// This code was revised by Joshua Estes
