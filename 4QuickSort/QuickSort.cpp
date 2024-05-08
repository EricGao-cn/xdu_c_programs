#include <iostream>
#include <vector>

int randomPivot(std::vector<int> &unsorted) {
    int index = rand() % unsorted.size();
    return unsorted[index];
}

void partition(std::vector<int> &unsorted, int pivot, std::vector<int> &less,
               std::vector<int> &equal, std::vector<int> &greater) {
    for (int i = 0; i < unsorted.size(); i++) {
        if (unsorted[i] < pivot) {
            less.push_back(unsorted[i]);
        } else if (unsorted[i] > pivot){
            greater.push_back(unsorted[i]);
        } else {
            equal.push_back(unsorted[i]);
        }
    }
}

std::vector<int> catenate(std::vector<int> less, std::vector<int> equal, std::vector<int> greater) {
    std::vector<int> sorted;
    sorted.insert(sorted.end(), less.begin(), less.end());
    sorted.insert(sorted.end(), equal.begin(), equal.end());
    sorted.insert(sorted.end(), greater.begin(), greater.end());
    return sorted;
}

std::vector<int> quickSort(std::vector<int> &unsorted) {
    if (unsorted.size() <= 1) {
        return unsorted;
    }
    int pivot = randomPivot(unsorted);
    std::vector<int> less, equal, greater;
    partition(unsorted, pivot, less, equal, greater);
    std::vector<int> sorted = catenate(quickSort(less), equal, quickSort(greater));
    return sorted;
}

int main() {
    std::vector<int> unsorted = {2, 3, 0, 0, 9, 2, 0, 0, 1, 3, 2};
    for (int i : unsorted) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::vector<int> sorted = quickSort(unsorted);
    for (int i : sorted) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    unsorted.clear();
    int tmp;
    std::cout << "下面输入你的数列，输入-1时表示输入结束" << std::endl;
    while (std::cin >> tmp) {
        if (tmp == -1) {
            break;
        }
        unsorted.push_back(tmp);
    }
    sorted = quickSort(unsorted);
    for (int i : sorted) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}