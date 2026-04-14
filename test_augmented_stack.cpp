#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "augmented_stack.h"  

using namespace std;

void test_empty_behavior() {
    cout << "Test: empty stack behavior\n";
    AugmentedStack<int> s;

    try {
        s.pop();
        cout << "   FAIL: pop() should throw\n";
    } catch (const exception&) {
        cout << "  PASS: pop() throws\n";
    }

    try {
        s.min();
        cout << "   FAIL: min() should throw\n";
    } catch (const exception&) {
        cout << "  PASS: min() throws\n";
    }
}

void test_basic_push() {
    cout << "\nTest: basic push\n";
    AugmentedStack<int> s;

    s.push(5);
    s.push(3);
    s.push(7);

    if (s.min() == 3) {
        cout << "  PASS: min correct\n";
    } else {
        cout << "   FAIL: min incorrect\n";
    }
}

void test_pop_updates_min() {
    cout << "\nTest: pop updates min\n";
    AugmentedStack<int> s;

    s.push(5);
    s.push(3);
    s.push(7);

    s.pop(); // removes 7

    if (s.min() == 3) {
        cout << "  PASS\n";
    } else {
        cout << "   FAIL\n";
    }

    s.pop(); // removes 3

    if (s.min() == 5) {
        cout << "  PASS\n";
    } else {
        cout << "   FAIL\n";
    }
}

void test_sum_and_average() {
    cout << "\nTest: sum / average\n";
    AugmentedStack<int> s;

    s.push(2);
    s.push(4);
    s.push(6);

    int avg = s.average();  // expected: 4

    if (avg == 4) {
        cout << "  PASS\n";
    } else {
        cout << "   FAIL: expected 4, got " << avg << endl;
    }

    s.pop(); // removes 6

    avg = s.average();  // expected: 3

    if (avg == 3) {
        cout << "  PASS\n";
    } else {
        cout << "   FAIL: average incorrect after pop\n";
    }
}

void test_increasing_sequence() {
    cout << "\nTest: increasing sequence\n";
    AugmentedStack<int> s;

    for (int i = 1; i <= 5; i++) {
        s.push(i);
    }

    if (s.min() == 1) {
        cout << "  PASS\n";
    } else {
        cout << "   FAIL\n";
    }
}

void test_decreasing_sequence() {
    cout << "\nTest: decreasing sequence\n";
    AugmentedStack<int> s;

    for (int i = 5; i >= 1; i--) {
        s.push(i);
    }

    if (s.min() == 1) {
        cout << "  PASS\n";
    } else {
        cout << "   FAIL\n";
    }
}

void test_duplicates() {
    cout << "\nTest: duplicate values\n";
    AugmentedStack<int> s;

    s.push(3);
    s.push(3);
    s.push(3);

    if (s.min() == 3) {
        cout << " PASS\n";
    } else {
        cout << " FAIL\n";
    }

    s.pop();
    if (s.min() == 3) {
        cout << " PASS\n";
    } else {
        cout << " FAIL\n";
    }
}

void test_large_input() {
    cout << "\nTest: large input\n";
    AugmentedStack<int> s;

    try {
        for (int i = 0; i < 10000; i++) {
            s.push(i);
        }
        cout << " PASS: handled large input\n";
    } catch (...) {
        cout << " FAIL: crashed on large input\n";
    }
}

int main() {
    test_empty_behavior();
    test_basic_push();
    test_pop_updates_min();
    test_sum_and_average();
    test_increasing_sequence();
    test_decreasing_sequence();
    test_duplicates();
    test_large_input();

    cout << "\nAll tests completed.\n";
    return 0;
}