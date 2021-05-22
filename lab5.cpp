#include <iostream>
#include <chrono>
#include <algorithm>
#include <iterator>
#include <unistd.h>

int linearSearch(int* arr, int size, int seeking, int& comparisonCount){
    comparisonCount = 0;

    for(int i = 0; i < size; ++i){
        comparisonCount++;
        comparisonCount++;
        if(arr[i] == seeking){
            return i;
        }
    }
    return -1;
}

int barrierSearch(int* arr, int size, int seeking, int& comparisonCount){
    comparisonCount = 0;

    int last = arr[size - 1];
    arr[size - 1] = seeking;

    int i = 0;
    while(arr[i] != seeking){
        comparisonCount++;
        ++i;
    }

    comparisonCount+=2;
    if(i == size - 1 && last == seeking){
        return i;
    }

    return -1;
}

int binarySearch(int* arr, int size, int seeking, int& comparisonCount){
    comparisonCount = 0;

    int l = 0;
    int r = size - 1;

    while (l <= r) {
        comparisonCount++;
        int m = l + (r - l) / 2;

        comparisonCount++;
        if (arr[m] == seeking) {
            return m;
        }

        comparisonCount++;
        if (arr[m] < seeking) {
            l = m + 1;
        }else {
            r = m - 1;
        }
    }

    return -1;
}

void fillArrayRandom(int* arr, int size, int intervalBegin, int intervalEnd){

    for(int i = 0; i < size; i++){
        arr[i] = (rand() % (intervalEnd - intervalBegin)) + intervalBegin;
    }
}

int main() {
    srand (time(NULL));

    int sizes[] = {100, 500, 1'000, 3'000, 10'000, 100'000'0};

    for(int size : sizes){

        int mediumLinearComparisonCount = 0;
        int mediumBarrierComparisonCount = 0;
        int mediumBinaryComparisonCount = 0;

        double mediumLinearTimeSpent = 0;
        double mediumBarrierTimeSpent = 0;
        double mediumBinaryTimeSpent = 0;

        for(int i = 0; i < 3; i++){
            int arr[size];
            fillArrayRandom(arr, size, 0, size);
            int seeking = rand()%size;


            int linearSearchComparisonCount = 0;
            auto linearStartTime = std::chrono::high_resolution_clock::now();
            linearSearch(arr, size, seeking, linearSearchComparisonCount);
            auto linearEndTime = std::chrono::high_resolution_clock::now();
            double linearTimeSpent = std::chrono::duration_cast<std::chrono::microseconds>(linearEndTime - linearStartTime).count();

            int barrierSearchComparisonCount = 0;
            auto barrierStartTime = std::chrono::high_resolution_clock::now();
            barrierSearch(arr, size, seeking, barrierSearchComparisonCount);
            auto barrierEndTime = std::chrono::high_resolution_clock::now();
            double barrierTimeSpent = std::chrono::duration_cast<std::chrono::microseconds>(barrierEndTime - barrierStartTime).count();



            std::sort(arr, arr + size);

            int binarySearchComparisonCount = 0;
            auto binaryStartTime = std::chrono::high_resolution_clock::now();
            binarySearch(arr, size, seeking, binarySearchComparisonCount);
            auto binaryEndTime = std::chrono::high_resolution_clock::now();
            double binaryTimeSpent = std::chrono::duration_cast<std::chrono::microseconds>(binaryEndTime - binaryStartTime).count();

            mediumLinearComparisonCount += linearSearchComparisonCount / 3;
            mediumBarrierComparisonCount += barrierSearchComparisonCount / 3;
            mediumBinaryComparisonCount += binarySearchComparisonCount / 3;

            mediumLinearTimeSpent += linearTimeSpent / 3;
            mediumBarrierTimeSpent += barrierTimeSpent / 3;
            mediumBinaryTimeSpent += binaryTimeSpent / 3;

        }

        std::cout << "On array size " << size << " average :\n" <<
            "Linear: " << mediumLinearComparisonCount << " comparisons count, " << mediumLinearTimeSpent << " microseconds spent\n" <<
            "Barrier: " << mediumBarrierComparisonCount << " comparisons count, " << mediumBarrierTimeSpent << " microseconds spent\n" <<
            "Binary: " << mediumBinaryComparisonCount << " comparisons count, " << mediumBinaryTimeSpent << " microseconds spent\n";


    }

    return 0;
}
