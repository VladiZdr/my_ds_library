#include "my_stack.h"
#include <vector>
#include <stdexcept>
#include <type_traits>


template <typename T>
class AugmentedStack{
static_assert(std::is_arithmetic<T>::value);

private:
    MyStack<T> stack;

    T sum;
    MyStack<T> min_elements;

public:
    AugmentedStack(){
        sum = T{};
    }

    void push(const T& el){
        sum += el;

        stack.push(el);
        
        if(min_elements.empty() || el <= min_elements.top()){
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

    double average() const{
        if(stack.empty()){
            throw underflow_error("Empty stack -> no average");
        }
        return sum / static_cast<T>(stack.size());
    }
    const T& min() const{
        if(stack.empty()){
            throw underflow_error("Empty stack -> no min");
        }
        return min_elements.top();
    }

    bool empty() const{
        return stack.empty();
    }

    size_t size() const{
        return stack.size();
    }

    bool contains(const T& el){
        MyStack<T> tmp;
        bool found = false;

        while (!stack.empty()){
            T curr = stack.pop();
            tmp.push(curr);

            if( curr == el ){
                found = true;
                break;
            }
        }

        while(!tmp.empty()){
            stack.push( tmp.pop() );
        }

        return found;
    }

    //lower/upper_bound
    //successor/predeccessor
    //delete
    //update
    //rank(x) -> k-th element
    //LRU/MRU -> least/most recently used
    //intersect / merge
};