#include "my_stack.h"

#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

template <typename T>
class AugmentedStack{

private:
    MyStack<T> stack;

    T sum;
    MyStack<T> min_elements;

public:
    AugmentedStack(){
        stack = MyStack<T>();

        sum = 0;
        min_elements = MyStack<T>();
    }

    void push(T el){
        sum += el;

        stack.push(el);
        
        if(min_elements.empty() || min_elements.top() >= el){
            min_elements.push(el);
        }
    }

    T pop(){
        if(stack.empty()){
            throw underflow_error("Not enough elements!");
        }
        T tmp = stack.pop();

        if(tmp == min_elements.top()){
            min_elements.pop();
        }

        sum-=tmp;
        return tmp;
    }

    T average(){
        return sum / stack.size();
    }
    T min(){
        return min_elements.top();
    }

};