#include <iostream>
#include <functional>
#include "destinations.hpp"
#include "set.hpp"
#include "../data_structures/vector.hpp"

Vector<int> findLengths(char fromFirst, char toFirst, Destinations<int>& destinations) {
    Vector<int> lengths;

    auto pairs = destinations.pairs();
    function<void(char, int, Set&)> find = [&](char cur, int length, Set& dots) { // dots - посещённые точки
        if (cur == toFirst) { // мы прибыли, куда хотели
            lengths.pushBack(length);
            return;
        }
        
        for (int i = 0; i < pairs.size(); i++) {
            pair<char, char> p = pairs.get(i);
            if (p.first == cur && !dots.contains(p.second)) { // 1. Находим пары, где первая точка наша. 2. Точки, куда мы хотим мы хотим пойти, не должно быть в уже посещённых.
                // копируем множество и добавляем следующую точку
                auto newDots = dots.copy();
                newDots.put(p.second);
                
                find(p.second, length + destinations.get(p.first, p.second), newDots);
            }
        }
    };

    Set firstSet;
    firstSet.put(fromFirst);
    find(fromFirst, 0, firstSet);

    return lengths;
}

int main() {
    Destinations<int> destinations;
    destinations.put('A', 'B', 1);
    destinations.put('B', 'C', 2);
    destinations.put('A', 'C', 4);
    destinations.put('B', 'A', 1);
    destinations.put('B', 'B', 5);

    cout << destinations << endl;
    // cout << destinations.pairs() << endl;
    auto lengths = findLengths('A', 'C', destinations);
    cout << lengths.min() << endl;
    return 0;
}