#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
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

    //constructor for data
    MyStack(vector<T> init_data){
        max_size = 2;
        curr_size = 0;

        data = new T[max_size];

        for(size_t i =0; i< init_data.size() ; i++){
            push(init_data[i]);
        }
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
    void push(T el){
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

    //remove last element
    T pop(){
        if(curr_size == 0){
            throw underflow_error("Not enough elements for pop()");
        }
        return data[--curr_size];
    }

    //get size
    size_t size(){
        return curr_size;
    }

    //is empty
    bool empty(){
        return curr_size == 0;
    }

    //max elements in stack before resize() is called
    size_t maximum_size(){
        return max_size;
    }

    //double max size
    void resize(){
        if(max_size <= SIZE_MAX/2){
            max_size *= 2;
        }
        else if(max_size < SIZE_MAX){
            max_size = SIZE_MAX;
        }
        else{
            throw overflow_error("Stack reached maximum possible size");
        }

        T* tmp = new T[max_size];
        copy(data, data + curr_size, tmp);

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
 
