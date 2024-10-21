#ifndef MAP_H
#define MAP_H

#include <string>
#include <iostream>
#include <cstdint>
#include <stdexcept>
#include "../data_structures/vector.hpp"

using namespace std;

template <typename T>
struct Destinations { // map с тремя полями
private:
    struct Node {
        char start;
        char end;
        T value;
        Node* next;

        Node(char k, char m, T v) : start(k), end(m), value(v), next(nullptr) {}
    };

    Node** data; // указатель на массив указателей
    int cap;
    int len;
    double loadFactor;

public:
    Destinations() {
        cap = 16;
        len = 0;
        loadFactor = 0.50;

        data = new Node*[cap];

        for (int i = 0; i < cap; i++) {
            data[i] = nullptr;
        }
    }

    Node** getData() const {
        return data;
    }

    int getLen() const {
        return len;
    }

    int getCap() const {
        return cap;
    }

    uint32_t hash(char start, char end) const {
        uint32_t hash = 5381;
        hash = ((hash << 5) + hash) + start;
        hash = ((hash << 5) + hash) + end;
        return hash;
    }

    void put(char start, char end, T value) {
        if (static_cast<double>(len) / cap >= loadFactor) {
            rehash(cap * 2);
        }

        uint32_t index = hash(start, end) % cap; // Вычисляется индекс бакета с помощью хэш-функции

        if (data[index] == nullptr) { // бакета нет
            data[index] = new Node(start, end, value); // создается новый элемент
        } else { // бакет есть -> добавляем в него
            Node* current = data[index];
            while (current != nullptr) {
                if (current->start == start && current->end == end) {
                    current->value = value; // обновление значения
                    return;
                }
                if (current->next == nullptr) {
                    current->next = new Node(start, end, value); // добавляем новый элемент
                    break;
                }
                current = current->next;
            }
        }

        len++;
    }

    T get(char start, char end) const {
        uint32_t index = hash(start, end) % cap;

        Node* current = data[index];
        while (current != nullptr) {
            if (current->start == start && current->end == end) {
                return current->value;
            }
            current = current->next;
        }

        throw runtime_error("Pair start-end not found");
    }

    void remove(char start, char end) {
        uint32_t index = hash(start, end) % cap;

        Node* prev = nullptr;
        Node* current = data[index];

        while (current != nullptr) {
            if (current->start == start && current->end == end) {
                if (prev == nullptr) {
                    data[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                len--;
                return;
            }
            prev = current;
            current = current->next;
        }

        throw runtime_error("Pair start-end not found");
    }

    void rehash(int newcap) {
        Node** newMap = new Node*[newcap]; // новый массив бакетов увеличенного размера

        for (int i = 0; i < newcap; i++) {
            newMap[i] = nullptr;
        }

        for (int i = 0; i < cap; i++) {
            Node* current = data[i];
            while (current != nullptr) {
                Node* next = current->next;
                uint32_t newIndex = hash(current->start, current->end) % newcap;

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

    Vector<pair<char, char>> pairs() {
        Vector<pair<char, char>> result;

        for (int i = 0; i < cap; i++) {
            Node* node = data[i];

            while (node != nullptr) {
                result.pushBack(pair<char, char>(node->start, node->end));
                node = node->next;
            }
        }

        return result;
    }

    string join() {
        string result = "";

        for (int i = 0; i < cap; i++) {
            Node* current = data[i];
            while (current != nullptr) {
                result += string(1, current->start) + "-" + string(1, current->end) + "," + to_string(current->value) + ";";
                current = current->next;
            }
        }
        if (!result.empty()) {
            result = result.substr(0, result.size() - 1); // удаляем последнюю точку с запятой
        }
        return result;
    }
};

template <typename T>
ostream& operator<<(ostream& os, const Destinations<T>& map) {
    auto data = map.getData();
    for (int i = 0; i < map.getCap(); i++) {
        if (data[i] != nullptr) {
            auto current = data[i];
            os << i << ": ";
            while (current != nullptr) {
                os << "(" << current->start << "," << current->end << ") - " << current->value << "; ";
                current = current->next;
            }
            os << endl;
        }
    }
    return os;
}

#endif
