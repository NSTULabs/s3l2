/*

Необходимо реализовать алгоритм, который определяет, являются ли
строки изоморфными. Две строки a и b считаются изоморфными, если символы
в a можно заменить на b. Символ сопоставляется только одному другому,
порядок символов должен сохраняться.
Пример:
"fall" и "redd" изоморфны.
"mad" и "odd" не изоморфны.

*/
#include "../dst/map.hpp"


bool isIsomorphic(string str1, string str2) {
    if (str1.length() != str2.length()) {
        return false;
    }

    Map<char> map;
    for (int i = 0; i < str1.length(); i++) {
        string symbol1 = to_string(str1[i]);
        string symbol2 = to_string(str2[i]);

        if (map.contains(symbol1)) {
            if (map.get(symbol1) != str2[i]) {
                return false;
            }
        } else {
            map.put(symbol1, str2[i]);
            map.put(symbol2, str1[i]);
        }
    }

    return true;
}

int main() {
    cout << isIsomorphic("egg", "add") << endl; // true
    cout << isIsomorphic("foo", "bar") << endl; // false
    cout << isIsomorphic("paper", "title") << endl; // true
    cout << isIsomorphic("fall", "redd") << endl; // true
    cout << isIsomorphic("mad", "odd") << endl; // false
    cout << isIsomorphic("dad", "ada") << endl; // false

    return 0;
}