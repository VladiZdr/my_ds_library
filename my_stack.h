#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <memory>
using namespace std;


template <typename T>
class MyStack{

private:
    size_t max_size;
    size_t curr_size;

    T* data;

public:
    //default constructor
    MyStack(){
        max_size = 2;
        curr_size = 0;

        data = new T[max_size];
    }

    //copy constructor
    MyStack(const MyStack<T>& other){
        max_size = other.max_size;
        curr_size = other.curr_size;

        data = new T[max_size];
        copy(other.data, other.data + curr_size, data);
    }

    //move constructor
    MyStack(MyStack&& other) noexcept
        :max_size(other.max_size), curr_size(other.curr_size), data(other.data){

            other.data = nullptr;
            other.curr_size = 0;
            other.max_size = 0;
    }

    //constructor for data
    MyStack(const vector<T>& init_data){
        max_size = 2 * init_data.size();
        curr_size = init_data.size();

        data = new T[max_size];

        copy(init_data.begin(), init_data.end(), data);
    }

    MyStack& operator=(const MyStack& other){
        if(this != &other){

            delete[] data;

            max_size = other.max_size;
            curr_size = other.curr_size;

            data = new T[max_size];
            copy(other.data, other.data + curr_size, data);

        }

        return *this;
    }


    //add element
    void push(const T& el){
        if(curr_size == max_size){
            resize();
        }

        data[curr_size] = el;

        curr_size++;
    }

    //last element
    const T& top() const{
        if(curr_size == 0){
            throw underflow_error("Not enough elements for top()");
        }
        return data[curr_size - 1];
    }

    //remove last element and force return rvalue (useful if named value || compiler cannot prove it's last use)
    T pop(){
        if(curr_size == 0){
            throw underflow_error("Not enough elements for pop()");
        }
        return move(data[--curr_size]);
    }

    //get size
    size_t size() const{
        return curr_size;
    }

    //is empty
    bool empty() const{
        return curr_size == 0;
    }

    //max elements in stack before resize() is called
    size_t maximum_size() const{
        return max_size;
    }

    //double max size
    void resize(){
        size_t limit = allocator_traits<allocator<T>>::max_size(allocator<T>{});
        if(max_size <= SIZE_MAX/2){
            max_size *= 2;
        }
        else if(max_size < SIZE_MAX){
            max_size = SIZE_MAX;
        }
        else{
            throw overflow_error("Stack reached maximum possible size");
        }

        if(max_size > limit){
            throw bad_alloc();
        }

        T* tmp = new T[max_size];
        try{
            copy(data, data + curr_size, tmp);
        }
        catch(...){
            delete[] tmp;
            throw;
        }
        

        delete[] data;
        data = tmp;
    }

    //clear stack
    void reinit(){
        delete[] data;
        max_size = 2;
        curr_size = 0;

        data = new T[max_size];
    }

    ~MyStack(){
        delete[] data;
    }
     
};
 
