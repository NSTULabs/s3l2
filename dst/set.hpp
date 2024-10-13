#ifndef MAP_H
#define MAP_H

#include <string>
#include <iostream>
#include <cstdint>

#include "array.hpp"

using namespace std;

struct Set {
private:
    struct Node {
        int key;
        Node* next;

        Node(int k) : key(k), next(nullptr) {}
    };

    Node** data;
    int cap;
    int len;
    double loadFactor;

public:
    Set() {
        cap = 16;
        len = 0;
        loadFactor = 0.50;

        data = new Node*[cap];

        for (int i = 0; i < cap; i++) {
            data[i] = nullptr;
        }
    }

    Array<int> getData() const {
        Array<int> result;

        for (int i = 0; i < cap; i++) {
            Node* current = data[i];
            while (current!= nullptr) {
                result.pushBack(current->key);
                current = current->next;
            }
        }

        return result;
    }

    int getLen() const {
        return len;
    }

    int getCap() const {
        return cap;
    }

    uint32_t hash(int key) const {
        uint32_t hash = 5381;
        hash = ((hash << 5) + hash) + key;
        return hash;
    }

    void put(int key) {
        if (static_cast<double>(len) / cap >= loadFactor) {
            rehash(cap * 2);
        }

        uint32_t index = hash(key) % cap;

        if (data[index] == nullptr) { // бакета нет
            data[index] = new Node(key);
        } else { // бакет есть -> добавляем в него
            Node* current = data[index];
            if (current->key == key) {
                return;
            }

            while (current->next != nullptr) {
                if (current->key == key) {
                    return;
                }
                current = current->next;
            }

            current->next = new Node(key);
        }

        len++;
    }

    bool contains(int key) const {
        for (int i = 0; i < cap; i++) {
            Node* current = data[i];
            while (current!= nullptr) {
                if (key == current->key) {
                    return true;
                }
                current = current->next;
            }
        }

        return false;
    }

    void remove(int key) {
        uint32_t index = hash(key) % cap;

        Node* prev = nullptr;
        Node* current = data[index];

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    data[index] = current->next;
                    delete current;
                    len--;
                    return;
                } else {
                    prev = current->next;
                    delete current;
                    len--;
                    return;
                }
            }
            prev = current;
            current = current->next;
        }

        throw runtime_error("Key not found");
    }

    void rehash(int newcap) {
        Node** newMap = new Node*[newcap];

        for (int i = 0; i < newcap; i++) {
            newMap[i] = nullptr;
        }

        for (int i = 0; i < cap; i++) {
            Node* current = data[i];
            while (current != nullptr) {
                Node* next = current->next;
                uint32_t newIndex = hash(current->key) % newcap;
                
                if (newMap[newIndex] == nullptr) { // бакета нет
                    current->next = nullptr;
                    newMap[newIndex] = current;
                } else { // бакет есть -> добавляем в него
                    Node* currentNewMap = newMap[newIndex];

                    while (currentNewMap->next != nullptr) {
                        currentNewMap = currentNewMap->next;
                    }
                    current->next = nullptr;
                    currentNewMap->next = current;
                }
                current = next;
            }
        }

        delete[] data;
        data = newMap;
        cap = newcap;
    }

    string join() {
        string result = "";

        for (int i = 0; i < cap; i++) {
            Node* current = data[i];
            while (current != nullptr) {
                result += current->key + ",";
                current = current->next;
            }
        }
        result = result.substr(0, result.size() - 1);
        return result;
    }
};

ostream& operator<<(ostream& os, const Set& set) {
    os << set.getData();
    return os;
}

#endif
