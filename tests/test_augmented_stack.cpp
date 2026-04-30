#include <iostream>
#include <stdexcept>
#include <cassert>
#include <vector>
#include "augmented_stack.h" 

using namespace std;

int main(){

//push pop tests
{
    AugmentedStack<int> s;

    bool threw = false;
    try{
        s.pop();
    }catch(const underflow_error&){
        threw = true;
    }

    assert(threw);

    s.push(5);
    s.push(3);
    s.push(8);
    s.push(2);
    s.push(7);

    assert(s.min() == 2);

    assert(s.pop() == 7);
    assert(s.min() == 2);

    assert(s.pop() == 2);
    assert(s.min() == 3);
}

    cout<< "push pop tests passed\n";

//average tests
{
    AugmentedStack<int> s;

    bool threw = false;

    try {
        s.average();
    } catch (const underflow_error&) {
        threw = true;
    }

    assert(threw); //stack empty
}
{
    AugmentedStack<int> s;

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    assert(s.average() == 3); // (1+2+3+4+5)/5 = 3
}
{
    AugmentedStack<int> s;

    s.push(2);
    s.push(4);
    s.push(6);

    assert(s.average() == 4);

    assert(s.pop() == 6);
    assert(s.average() == 3);
}


    cout<< "avg tests passed\n";
//min tests
{
    AugmentedStack<int> s;

    bool threw = false;

    try {
        s.min();
    } catch (const underflow_error&) {
        threw = true;
    }

    s.push(10);
    s.push(4);
    s.push(6);

    assert(s.min() == 4);

    assert(threw);
}
{
    //duplicate-min test
    AugmentedStack<int> s;

    s.push(5);
    s.push(2);
    s.push(4);
    s.push(2);

    assert(s.min() == 2);

    assert(s.pop() == 2);
    assert(s.min() == 2);

    assert(s.pop() == 4);
    assert(s.min() == 2);

    assert(s.pop() == 2);
    assert(s.min() == 5);
}
{
    AugmentedStack<int> s;

    s.push(12);
    s.push(7);
    s.push(15);
    s.push(3);
    s.push(9);
    s.push(3);
    s.push(14);
    s.push(1);
    s.push(8);
    s.push(1);
    s.push(11);
    s.push(6);
    s.push(2);
    s.push(2);
    s.push(10);

    assert(s.min() == 1);

    assert(s.pop() == 10);
    assert(s.min() == 1);

    assert(s.pop() == 2);
    assert(s.min() == 1);

    assert(s.pop() == 2);
    assert(s.min() == 1);

    assert(s.pop() == 6);
    assert(s.min() == 1);

    assert(s.pop() == 11);
    assert(s.min() == 1);

    assert(s.pop() == 1);
    assert(s.min() == 1);  // second 1 still present

    assert(s.pop() == 8);
    assert(s.min() == 1);

    assert(s.pop() == 1);
    assert(s.min() == 3);  // now both 1s are gone

    assert(s.pop() == 14);
    assert(s.min() == 3);

    assert(s.pop() == 3);
    assert(s.min() == 3);  // duplicate 3 still present

    assert(s.pop() == 9);
    assert(s.min() == 3);

    assert(s.pop() == 3);
    assert(s.min() == 7);  // now both 3s are gone

    assert(s.pop() == 15);
    assert(s.min() == 7);

    assert(s.pop() == 7);
    assert(s.min() == 12);

    assert(s.pop() == 12);
}

    cout<<"min tests passed\n";
//contains tests
{
    AugmentedStack<int> s;
    //empty
    assert(!s.contains(5));

    s.push(4);
    s.push(7);
    s.push(2);
    s.push(9);

    assert(s.contains(7));
    assert(!s.contains(5));
    //bottom & top els
    assert(s.contains(4));
    assert(s.contains(9));

}

    cout<<"All test passed";
}