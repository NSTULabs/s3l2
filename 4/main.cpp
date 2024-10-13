#include <iostream>
#include "../dst/array.hpp"
#include <vector>

int main() {
    Array<int> arr;
    const int targetSum = 5;
    for (int i : {4, -7, 1, 5, -4, 0, -3, 2, 4, 1}) {
        arr.pushBack(i);
    }

    Array<Array<int>> subArrays;
    for (int i1 = 0; i1 < arr.size(); i1++) {
        int sum = arr.get(i1);
        int c = 1;
        if (sum == targetSum) {
            Array<int> subArray;
            subArray.pushBack(sum);
            subArrays.pushBack(subArray);
        }
        for (int i2 = i1 + 1; i2 < arr.size(); i2++) {
            sum += arr.get(i2);
            c++;
            if (sum == targetSum) {
                Array<int> subArray;
                for (int j = i2 - c + 1; j <= i2; j++) {
                    subArray.pushBack(arr.get(j));
                }
                subArrays.pushBack(subArray);
            }
        }
    }

    for (int i = 0; i < subArrays.size(); i++) {
        cout << subArrays.get(i) << endl;
    }

    return 0;
}