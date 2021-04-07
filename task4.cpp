#include <iostream>
#include <ctime>
#include <chrono>

class Sort{
public:
    virtual int* sort(
            int* array, std::size_t size,
            std::size_t& swapCount,
            std::size_t& comparationCount
             ) = 0;

protected:

    void swap(int* arr, size_t i, size_t j){
        int tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;
        _swapCount++;
    }

    std::size_t _swapCount = 0;
    std::size_t _comparationCount = 0;
};

class InsertionSort : public Sort{
public:
    int* sort(int *array, std::size_t size, std::size_t &swapCount, std::size_t &comparationCount) override {
        for(size_t i = 1; i < size; i++) {
            for (int j = i; j > 0 && array[j - 1] > array[j]; j--) {
                swap(array, j - 1, j);
                _comparationCount += 2;
            }

            _comparationCount++;
        }

        comparationCount = _comparationCount;
        swapCount = _swapCount;

    }
};

class SelectionSort : public Sort{
public:
    int* sort(int *array, std::size_t size, std::size_t &swapCount, std::size_t &comparationCount) override {
        for (std::size_t i = 0; i < size; i++) {
            comparationCount++;
            std::size_t maxIndex = 0;
            int maxElem = array[0];
            for(std::size_t j = 0; j <= size - i - 1; j++){
                _comparationCount++;
                if(array[j] > maxElem){
                    maxElem = array[j];
                    maxIndex = j;
                }
                _comparationCount++;
            }

            swap(array, maxIndex, size-i - 1);

        }

        comparationCount = _comparationCount;
        swapCount = _swapCount;

    }
};

class BubbleSort : public Sort{
public:
    int* sort(int *array, std::size_t size, std::size_t &swapCount, std::size_t &comparationCount) override {
        for (std::size_t i = 0; i < size; i++) {
            comparationCount++;
            for(std::size_t j = 0; j < size - i - 1; j++){
                _comparationCount++;
                if(array[j] > array[j+1]){
                    swap(array, j, j+1);
                }
                _comparationCount++;
            }


        }

        comparationCount = _comparationCount;
        swapCount = _swapCount;

    }
};

class QuickSort : public Sort{
public:
    int* sort(int *array, std::size_t size, std::size_t &swapCount, std::size_t &comparationCount) override {
        quickSortRec(array, 0, size-1);

        comparationCount = _comparationCount;
        swapCount = _swapCount;

    }

    void quickSortRec(int arr[], int low, int high)
    {
        if (low < high)
        {
            _comparationCount++;

            int pivot = partition(arr, low, high);

            quickSortRec(arr, low, pivot - 1);
            quickSortRec(arr, pivot + 1, high);
        }
    }

private:
    int partition (int arr[], int low, int high)
    {
        int pivot = arr[high];    // pivot
        int i = (low - 1);

        for (int j = low; j <= high- 1; j++)
        {
            _comparationCount++;

            if (arr[j] <= pivot)
            {
                i++;
                swap(arr, i, j);
            }
            _comparationCount++;
        }
        swap(arr, i + 1, high);
        return (i + 1);
    }
};

template<class T>
class Measurer  {
public:
    int* measure(int* arr, std::size_t size, std::size_t& swapCount, std::size_t& comparationCount, double& timeSpent){
        auto start = std::chrono::high_resolution_clock::now();
        sorter.sort(arr, size, swapCount, comparationCount);
        auto end = std::chrono::high_resolution_clock::now();

        timeSpent = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();;
    }
private:
    T sorter;
};

class Menu{
private:
    enum Action {
        INSERTIONSORT = 1,
        SELECTIONSORT = 2,
        BUBBLESORT = 3,
        QUICKSORT = 4
    };

    friend std::istream& operator>>(std::istream &is, Action& action);

public:
    static void printResult(int* arr, size_t arraySize, std::size_t swapCount,
                            std::size_t comparationCount,
                            double timeSpent){

        std::cout << "Total time spent: " << timeSpent << std::endl;
        std::cout << "Comparations made: " << comparationCount << std::endl;
        std::cout << "Swaps made: " << swapCount << std::endl;

        std::cout << "Sorted array: ";
        for(size_t i = 0; i< arraySize; i++){
            std::cout << arr[i] << ' ';
        }

        std::cout << std::endl;
    }

    static void printMenu(){
        std::cout << "\t\tLaboratory work #4\n"
                  << "Print 1 to measure complexity of Insertion sort\n"
                  << "Print 2 to measure complexity of Selection sort\n"
                  << "Print 3 to measure complexity of Bubble sort\n"
                  << "Print 4 to measure complexity of Quick sort\n";


        Action choice;
        std::cin >> choice;

        switch (choice) {
            case INSERTIONSORT:{

                std::size_t arraySize;
                int* arr = getArray(arraySize);

                Measurer<InsertionSort> measurer;
                std::size_t swapCount, comparationCount;
                double timeSpent;

                measurer.measure(arr, arraySize, swapCount, comparationCount, timeSpent);

                printResult(arr, arraySize, swapCount, comparationCount, timeSpent);

                break;
            }
            case SELECTIONSORT:{

                std::size_t arraySize;
                int* arr = getArray(arraySize);

                Measurer<SelectionSort> measurer;
                std::size_t swapCount, comparationCount;
                double timeSpent;

                measurer.measure(arr, arraySize, swapCount, comparationCount, timeSpent);

                printResult(arr, arraySize, swapCount, comparationCount, timeSpent);


                break;
            }
            case BUBBLESORT:{

                std::size_t arraySize;
                int* arr = getArray(arraySize);

                Measurer<BubbleSort> measurer;
                std::size_t swapCount, comparationCount;
                double timeSpent;

                measurer.measure(arr, arraySize, swapCount, comparationCount, timeSpent);

                printResult(arr, arraySize, swapCount, comparationCount, timeSpent);


                break;
            }
            case QUICKSORT:{

                std::size_t arraySize;
                int* arr = getArray(arraySize);

                Measurer<QuickSort> measurer;
                std::size_t swapCount, comparationCount;
                double timeSpent;

                measurer.measure(arr, arraySize, swapCount, comparationCount, timeSpent);

                printResult(arr, arraySize, swapCount, comparationCount, timeSpent);

                break;
            }


        }
    }

private:
    static int* getArray(std::size_t& size){
        std::cout << "Enter array size: ";
        std::cin >> size;
        int* arr = new int[size];


        std::cout << "To enter array manually type 0, for random generation type 1: ";
        int choice;
        std::cin >> choice;

        if(choice == 0){
            for(std::size_t i = 0; i < size; i++){
                std::cout << "Enter " << i+1 << " element: ";
                std::cin >> arr[i];
            }
        }else if(choice == 1){
            for(std::size_t i = 0; i < size; i++){
                arr[i] = rand()/((RAND_MAX + 1u)/32000);
            }
        }

        return arr;
    }
};

std::istream& operator>>(std::istream &is, Menu::Action& action){
    int inputNumber;
    is >> inputNumber;

    switch (inputNumber) {
        case 1:{
            action = Menu::Action::INSERTIONSORT;
            return is;
        }
        case 2:{
            action = Menu::Action::SELECTIONSORT;
            return is;
        }
        case 3:{
            action = Menu::Action::BUBBLESORT;
            return is;
        }
        case 4:{
            action = Menu::Action::QUICKSORT;
            return is;
        }
    }
}


int main(){
    std::srand(std::time(nullptr));

    Menu::printMenu();
}