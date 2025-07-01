#include <iostream>
using namespace std;

void selectionSort(int *arr, int len) {
    static int id = 0;
    id++;
    for (int i = 0; i < len; i++) {
        int min = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        swap(arr[min], arr[i]);
    }
}

void print(int *arr, int len) {
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
}

int main() {
    int arr[] = {5, 7, 1, 3, 4, 6, 0};

    cout << "Selection Sort: " << endl;
    cout << "Orginal Array: ";
    print(arr, 7);
    selectionSort(arr, 7);
    cout << "Sorted Array: ";
    print(arr, 7);

    return 0;
}
