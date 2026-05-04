// #include <iostream>
// #include <vector>
// #include <omp.h>
// #include <algorithm>

// using namespace std;

// // 🔹 Sequential Bubble Sort
// void bubbleSort(vector<int> &arr) {
//     int n = arr.size();
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n - i - 1; j++) {
//             if (arr[j] > arr[j + 1]) {
//                 swap(arr[j], arr[j + 1]);
//             }
//         }
//     }
// }

// // 🔹 Parallel Bubble Sort (Odd-Even Sort)
// void parallelBubbleSort(vector<int> &arr) {
//     int n = arr.size();

//     for (int i = 0; i < n; i++) {
//         // Even phase
//         #pragma omp parallel for
//         for (int j = 0; j < n - 1; j += 2) {
//             if (arr[j] > arr[j + 1]) {
//                 swap(arr[j], arr[j + 1]);
//             }
//         }

//         // Odd phase
//         #pragma omp parallel for
//         for (int j = 1; j < n - 1; j += 2) {
//             if (arr[j] > arr[j + 1]) {
//                 swap(arr[j], arr[j + 1]);
//             }
//         }
//     }
// }

// // 🔹 Merge function
// void merge(vector<int> &arr, int left, int mid, int right) {
//     vector<int> temp(right - left + 1);

//     int i = left, j = mid + 1, k = 0;

//     while (i <= mid && j <= right) {
//         if (arr[i] <= arr[j])
//             temp[k++] = arr[i++];
//         else
//             temp[k++] = arr[j++];
//     }

//     while (i <= mid)
//         temp[k++] = arr[i++];

//     while (j <= right)
//         temp[k++] = arr[j++];

//     for (int i = left; i <= right; i++)
//         arr[i] = temp[i - left];
// }

// // 🔹 Sequential Merge Sort
// void mergeSort(vector<int> &arr, int left, int right) {
//     if (left >= right) return;

//     int mid = (left + right) / 2;

//     mergeSort(arr, left, mid);
//     mergeSort(arr, mid + 1, right);
//     merge(arr, left, mid, right);
// }

// // 🔹 Parallel Merge Sort
// void parallelMergeSort(vector<int> &arr, int left, int right, int depth) {
//     if (left >= right) return;

//     int mid = (left + right) / 2;

//     if (depth <= 0) {
//         mergeSort(arr, left, mid);
//         mergeSort(arr, mid + 1, right);
//     } else {
//         #pragma omp parallel sections
//         {
//             #pragma omp section
//             parallelMergeSort(arr, left, mid, depth - 1);

//             #pragma omp section
//             parallelMergeSort(arr, mid + 1, right, depth - 1);
//         }
//     }

//     merge(arr, left, mid, right);
// }

// // 🔹 Utility to print array
// void printArray(vector<int> &arr) {
//     for (int x : arr)
//         cout << x << " ";
//     cout << endl;
// }

// int main() {
//     int n = 100000;
//     vector<int> arr(n);

//     // Generate random data
//     for (int i = 0; i < n; i++)
//         arr[i] = rand() % 10000;

//     vector<int> arr1 = arr;
//     vector<int> arr2 = arr;
//     vector<int> arr3 = arr;
//     vector<int> arr4 = arr;

//     double start, end;

//     // 🔹 Sequential Bubble Sort
//     start = omp_get_wtime();
//     bubbleSort(arr1);
//     end = omp_get_wtime();
//     cout << "Sequential Bubble Sort Time: " << end - start << endl;

//     // 🔹 Parallel Bubble Sort
//     start = omp_get_wtime();
//     parallelBubbleSort(arr2);
//     end = omp_get_wtime();
//     cout << "Parallel Bubble Sort Time: " << end - start << endl;

//     // 🔹 Sequential Merge Sort
//     start = omp_get_wtime();
//     mergeSort(arr3, 0, n - 1);
//     end = omp_get_wtime();
//     cout << "Sequential Merge Sort Time: " << end - start << endl;

//     // 🔹 Parallel Merge Sort
//     start = omp_get_wtime();
//     parallelMergeSort(arr4, 0, n - 1, 4); // depth controls parallelism
//     end = omp_get_wtime();
//     cout << "Parallel Merge Sort Time: " << end - start << endl;

//     return 0;
// }

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

#define SIZE 10000

// ============================
// Sequential Bubble Sort
// ============================
void bubbleSortSeq(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ============================
// Parallel Bubble Sort
// ============================
void bubbleSortParallel(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        // Even phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }

        // Odd phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ============================
// Merge Function
// ============================
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }

    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

// ============================
// Sequential Merge Sort
// ============================
void mergeSortSeq(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSortSeq(arr, l, m);
        mergeSortSeq(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ============================
// Parallel Merge Sort
// ============================
void mergeSortParallel(vector<int>& arr, int l, int r, int depth) {
    if (l < r) {
        int m = (l + r) / 2;

        if (depth <= 0) {
            mergeSortSeq(arr, l, m);
            mergeSortSeq(arr, m + 1, r);
        } else {
            #pragma omp parallel sections
            {
                #pragma omp section
                mergeSortParallel(arr, l, m, depth - 1);

                #pragma omp section
                mergeSortParallel(arr, m + 1, r, depth - 1);
            }
        }

        merge(arr, l, m, r);
    }
}

// ============================
// Utility Functions
// ============================
void generateRandom(vector<int>& arr) {
    for (int& x : arr) {
        x = rand() % 100000;
    }
}

// ============================
// Main
// ============================
int main() {
    vector<int> arr(SIZE), temp;

    srand(time(0));
    generateRandom(arr);

    double start, end;

    // -------- Bubble Sort Sequential --------
    temp = arr;
    start = omp_get_wtime();
    bubbleSortSeq(temp);
    end = omp_get_wtime();
    cout << "Sequential Bubble Sort Time: " << (end - start) << " sec\n";

    // -------- Bubble Sort Parallel --------
    temp = arr;
    start = omp_get_wtime();
    bubbleSortParallel(temp);
    end = omp_get_wtime();
    cout << "Parallel Bubble Sort Time: " << (end - start) << " sec\n";

    // -------- Merge Sort Sequential --------
    temp = arr;
    start = omp_get_wtime();
    mergeSortSeq(temp, 0, SIZE - 1);
    end = omp_get_wtime();
    cout << "Sequential Merge Sort Time: " << (end - start) << " sec\n";

    // -------- Merge Sort Parallel --------
    temp = arr;
    start = omp_get_wtime();
    mergeSortParallel(temp, 0, SIZE - 1, 4);
    end = omp_get_wtime();
    cout << "Parallel Merge Sort Time: " << (end - start) << " sec\n";

    return 0;
}

// openmp command= -fopenmp
