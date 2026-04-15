#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include <vector>
#include <iostream>
#include "my_stack.h" 

using namespace std;

int main(){

    // DEFAULT CONSTRUCTOR TESTS
    {
        MyStack<int> s;

        assert(s.size() == 0);

        assert(s.maximum_size() == 2);

        s.push(10);
        s.push(20);
        assert(s.top() == 20);
    }

    // COPY CONSTRUCTOR TESTS
    {
        MyStack<int> original;
        original.push(1);
        original.push(2);

        MyStack<int> copyStack(original);

        // Test 1: size
        assert(copyStack.size() == original.size());

        // Test 2: max_size
        assert(copyStack.maximum_size() == original.maximum_size());

        // Test 3: data contents
        assert(copyStack.top() == original.top());
        copyStack.pop();
        original.pop();
        assert(copyStack.top() == original.top());
    }

    // VECTOR CONSTRUCTOR TESTS
    {
        vector<int> v = {1, 2, 3};
        MyStack<int> s(v);

        // Test 1: size
        assert(s.size() == 3);

        // Test 2: max_size (should have resized at least once)
        assert(s.maximum_size() >= 3);

        // Test 3: data contents (LIFO order)
        assert(s.top() == 3);
        s.pop();
        assert(s.top() == 2);
    }

    //For vector constructor full data check
    {
        vector<int> v = {5, 6, 7, 8};
        MyStack<int> s(v);

        for(int i = 8; i >= 5; --i){
            assert(s.top() == i);
            s.pop();
        }
        assert(s.empty());
    }

    // OPERATOR= TESTS
    {
        // Test 1: correct reassignment
        MyStack<int> a;
        a.push(1);
        a.push(2);

        MyStack<int> b;
        b.push(10);

        b = a;

        assert(b.size() == a.size());
        assert(b.top() == a.top());
    }

    {
        // Test 2: no shallow copy
        MyStack<int> a;
        a.push(1);
        a.push(2);

        MyStack<int> b;
        b = a;

        a.pop();

        // b should remain unchanged
        assert(b.size() == 2);
        assert(b.top() == 2);
    }

    {
        // Test 3: full content
        MyStack<int> a;
        a.push(3);
        a.push(4);
        a.push(5);

        MyStack<int> b;
        b = a;

        assert(b.size() == a.size());
        assert(b.maximum_size() == a.maximum_size());

        while(!a.empty()){
            assert(b.top() == a.top());
            b.pop();
            a.pop();
        }
        assert(b.empty());
    }

    cout<<"Constructors and operator= tests passed\n";

    // REINIT TEST
    {
        MyStack<int> s;
        s.push(1);
        s.push(2);

        s.reinit();

        assert(s.size() == 0 && s.maximum_size() == 2 && s.empty());
    }

    // SIZE TESTS (before / after push & pop)
    {
        MyStack<int> s;

        assert(s.size() == 0);

        s.push(10);

        assert(s.size() == 1);
    }

    {
        MyStack<int> s;
        s.push(10);
        s.push(20);

        // before pop
        assert(s.size() == 2);

        s.pop();

        // after pop
        assert(s.size() == 1);
    }

    // PUSH TEST data
    {
        MyStack<int> s;
        size_t old_max = s.maximum_size();

        s.push(42);

        assert(s.size() == 1 && s.top() == 42 && s.maximum_size() == old_max);
    }

    // POP TEST data
    {
        MyStack<int> s;
        s.push(1);
        s.push(2);

        int val = s.pop();

        assert(val == 2 && s.size() == 1 && s.top() == 1);
    }

    // EMPTY TESTS
    {
        MyStack<int> s;

        assert(s.empty());

        s.push(5);

        assert(!s.empty());
    }

    cout<<"Tests till resize passed\n";
    // RESIZE TESTS

    // 1. normal resize (max_size <= SIZE_MAX/2)
    {
        MyStack<int> s;

        size_t old_max = s.maximum_size();

        s.push(1);
        s.push(2);
        s.push(3); //resize

        assert(s.maximum_size() == old_max * 2);
    }

    /*
        max_size * sizeof(T) <= implementation_limit
            If this overflows or exceeds limits → bad_array_new_length is thrown

    // 2. resize to SIZE_MAX 
    {
        MyStack<int> s;

        // force: SIZE_MAX/2 < max_size < SIZE_MAX
        size_t near_max = SIZE_MAX/2 + 1;
        s.set_maximum_size(near_max);

        s.resize();

        assert(s.maximum_size() == SIZE_MAX);
    }

    // 3. resize overflow error (max_size == SIZE_MAX)
    {
        MyStack<int> s;

        s.set_maximum_size(SIZE_MAX);

        bool threw = false;

        try{
            s.resize();
        }catch(const overflow_error&){
            threw = true;
        }

        assert(threw);
    }*/

    // 4. data integrity after resize
    {
        MyStack<int> s;

        s.push(1);
        s.push(2);

        size_t old_max = s.maximum_size();

        s.push(3); //resize

        assert(s.maximum_size() == old_max * 2);

        // check data preserved
        assert(s.pop() == 3);
        assert(s.pop() == 2);
        assert(s.pop() == 1);
    }

    // MAX_SIZE LOGIC TESTS
    {
        MyStack<int> s;

        size_t old_max = s.maximum_size();

        s.push(1);
        s.push(2);
        s.push(3); // resize

        assert(s.maximum_size() == old_max * 2);
    }

    std::cout << "All tests passed!\n";
    return 0;
}