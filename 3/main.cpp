/*

Необходимо реализовать алгоритм, который должен разбить множество
натуральных чисел на непересекающиеся подмножества, разница между суммами
которых была бы минимальна. Вывести получившиеся подмножества и разницу
их сумм.
Пример:
множество S = {5, 8, 1, 14, 7}.
Получим два подмножества {5, 14} и {8, 1, 7}. Разница между их
суммами - 3.

*/

#include <iostream>
#include "../dst/set.hpp"
#include "../dst/array.hpp"

int main() {
    Array<int> arr;
    for (int i : {5, 8, 1, 14, 7}) {
        arr.pushBack(i);
    }
    arr.sort();
    arr.reverse();

    Set set1, set2;
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < arr.size(); i++) {
        int el = arr.get(i);
        if (sum1 > sum2) {
            sum2 += el;
            set2.put(el);
        } else {
            sum1 += el;
            set1.put(el);
        }
    }

    cout << set1 << endl;
    cout << set2 << endl;

    return 0;
}