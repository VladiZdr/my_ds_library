#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include "my_stack.h" 

using namespace std;

void test_empty_pop() {
    cout << "Test: pop on empty stack\n";
    MyStack<int> s;

    try {
        s.pop();
        cout << " FAIL: No exception thrown\n";
    } catch (const underflow_error& e) {
        cout << " PASS: Caught underflow -> " << e.what() << endl;
    }
}

void test_empty_top() {
    cout << "\nTest: top on empty stack\n";
    MyStack<int> s;

    try {
        s.top();
        cout << " FAIL: No exception thrown\n";
    } catch (const underflow_error& e) {
        cout << " PASS: Caught underflow -> " << e.what() << endl;
    }
}

void test_basic_push_pop() {
    cout << "\nTest: basic push/pop\n";
    MyStack<int> s;

    s.push(10);
    s.push(20);

    if (s.top() == 20) {
        cout << " PASS: top correct\n";
    } else {
        cout << " FAIL: wrong top\n";
    }

    int val = s.pop();
    if (val == 20 && s.top() == 10) {
        cout << " PASS: pop correct\n";
    } else {
        cout << " FAIL: pop incorrect\n";
    }
}

void test_resize() {
    cout << "\nTest: resize behavior\n";
    MyStack<int> s;

    for (int i = 0; i < 100; i++) {
        s.push(i);
    }

    if (s.size() == 100) {
        cout << " PASS: resize worked\n";
    } else {
        cout << " FAIL: resize failed\n";
    }
}

void test_large_data() {
    cout << "\nTest: large data push\n";
    MyStack<int> s;

    try {
        for (int i = 0; i < 100000; i++) {
            s.push(i);
        }
        cout << " PASS: handled large input\n";
    } catch (exception& e) {
        cout << " FAIL: crashed on large input\n";
    }
}

void test_strings() {
    cout << "\nTest: stack with std::string\n";
    MyStack<string> s;

    s.push("hello");
    s.push("world");

    if (s.pop() == "world" && s.pop() == "hello") {
        cout << " PASS: string support works\n";
    } else {
        cout << " FAIL: string handling broken\n";
    }
}

void test_interleaved_operations() {
    cout << "\nTest: interleaved push/pop\n";
    MyStack<int> s;

    s.push(1);
    s.push(2);
    s.pop();
    s.push(3);

    if (s.top() == 3) {
        cout << " PASS\n";
    } else {
        cout << " FAIL\n";
    }
}

void test_size_tracking() {
    cout << "\nTest: size tracking\n";
    MyStack<int> s;

    s.push(1);
    s.push(2);
    s.pop();

    if (s.size() == 1) {
        cout << " PASS\n";
    } else {
        cout << " FAIL\n";
    }
}

int main() {
    test_empty_pop();
    test_empty_top();
    test_basic_push_pop();
    test_resize();
    test_large_data();
    test_strings();
    test_interleaved_operations();
    test_size_tracking();

    cout << "\nAll tests completed.\n";
    return 0;
}