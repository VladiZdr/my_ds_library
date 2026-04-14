#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

template <typename T>
class MyStack{

private:
    size_t max_size;
    size_t curr_size;

    T* data;

public:
    MyStack(){
        max_size = 2;
        curr_size = 0;

        data = new T[max_size];
    }

    MyStack(vector<T> init_data){
        MyStack();
        for(size_t i =0; i< init_data.size() ; i++){
            push(init_data[i]);
        }
    }

    void push(T el){
        if(curr_size == max_size){
            try{
                resize();
            }catch(const overflow_error& e){
                cout << "Error during resize: " << e.what() << endl;
            }catch(const exception& e){
                cout <<e.what() <<endl;
            }
        }

        data[curr_size] = el;

        curr_size++;
    }

    T top(){
        if(curr_size == 0){
            throw underflow_error("Not enough elements");
        }
        return data[curr_size - 1];
    }

    T pop(){
        if(curr_size == 0){
            throw underflow_error("Not enough elements");
        }
        return data[--curr_size];
    }

    size_t size(){
        return curr_size;
    }

    bool empty(){
        return curr_size == 0;
    }

    size_t maximum_size(){
        return max_size;
    }

    void resize(){
        if(max_size <= SIZE_MAX/2){
            max_size *= 2;
        }
        else if(max_size <= SIZE_MAX){
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

    void reinit(){
        *this = MyStack<T>();
    }

    ~MyStack(){
        delete[] data;
    }
     
};
 
