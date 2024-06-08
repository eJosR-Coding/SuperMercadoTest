#ifndef SORTING_HPP
#define SORTING_HPP

#include <vector>
#include <functional>

using namespace std;

template<typename T>
class Sorting {
public:
    // Método público para ordenar usando QuickSort
    void quicksort(vector<T>& arr, function<bool(const T&, const T&)> comp) {
        quicksort(arr, 0, arr.size() - 1, comp);
    }

    // Método público para ordenar usando MergeSort
    void mergesort(vector<T>& arr, function<bool(const T&, const T&)> comp) {
        vector<T> temp(arr.size());
        mergesort(arr, temp, 0, arr.size() - 1, comp);
    }

    // Método público para ordenar usando HeapSort
    void heapsort(vector<T>& arr, function<bool(const T&, const T&)> comp) {
        for (int i = arr.size() / 2 - 1; i >= 0; --i) {
            heapify(arr, arr.size(), i, comp);
        }
        for (int i = arr.size() - 1; i > 0; --i) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0, comp);
        }
    }

private:
    // Métodos privados que implementan QuickSort
    void quicksort(vector<T>& arr, int left, int right, function<bool(const T&, const T&)> comp) {
        if (left < right) {
            int pivotIndex = partition(arr, left, right, comp);
            quicksort(arr, left, pivotIndex - 1, comp);
            quicksort(arr, pivotIndex + 1, right, comp);
        }
    }

    int partition(vector<T>& arr, int left, int right, function<bool(const T&, const T&)> comp) {
        T pivot = arr[right];
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            if (comp(arr[j], pivot)) {
                ++i;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[right]);
        return i + 1;
    }

    // Métodos privados que implementan MergeSort
    void mergesort(vector<T>& arr, vector<T>& temp, int left, int right, function<bool(const T&, const T&)> comp) {
        if (left < right) {
            int center = (left + right) / 2;
            mergesort(arr, temp, left, center, comp);
            mergesort(arr, temp, center + 1, right, comp);
            merge(arr, temp, left, center + 1, right, comp);
        }
    }

    void merge(vector<T>& arr, vector<T>& temp, int leftPos, int rightPos, int rightEnd, function<bool(const T&, const T&)> comp) {
        int leftEnd = rightPos - 1;
        int tempPos = leftPos;
        int numElements = rightEnd - leftPos + 1;

        while (leftPos <= leftEnd && rightPos <= rightEnd) {
            if (comp(arr[leftPos], arr[rightPos])) {
                temp[tempPos++] = move(arr[leftPos++]);
            }
            else {
                temp[tempPos++] = move(arr[rightPos++]);
            }
        }

        while (leftPos <= leftEnd) {
            temp[tempPos++] = move(arr[leftPos++]);
        }

        while (rightPos <= rightEnd) {
            temp[tempPos++] = move(arr[rightPos++]);
        }

        for (int i = 0; i < numElements; ++i, --rightEnd) {
            arr[rightEnd] = move(temp[rightEnd]);
        }
    }

    // Métodos privados que implementan HeapSort
    void heapify(vector<T>& arr, int n, int i, function<bool(const T&, const T&)> comp) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && comp(arr[largest], arr[left])) {
            largest = left;
        }

        if (right < n && comp(arr[largest], arr[right])) {
            largest = right;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest, comp);
        }
    }
};

#endif // SORTING_HPP
