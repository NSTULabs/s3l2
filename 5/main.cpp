#include "../dst/tree.hpp"


int main() {
    Tree tree;
    for (int i : {7, 3, 2, 1, 9, 5, 4, 6, 8, 0}) {
        if (tree.depth(i) != -1) {
            continue;
        }

        tree.insertNum(i);
        cout << tree.depth(i) << " ";
    }
    cout << endl;
    cout << tree << endl;
    return 0;
}