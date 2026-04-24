#include "node.h"

template <typename T>
class MyList{
private:
    Node<T>* start;

public:
    //constructors
    MyList(){
        start = nullptr;
    }

    MyList(const Node<T>& start){
        this.start = start;
    }

    MyList(const MyList<T>& other){
        this.start = other.start;
    }

    MyList(const MyList<T>&& other){
        this.start = other.start;
        if(this != other) other = nullptr;
    }

    //operations
    Node<T> begin() const{
        return start;
    }

    void insert(Node<T>& el){
        Node<T> tmp = start;
        if(tmp == nullptr){
            throw underflow_error("Not initialized start");
        }

        while(tmp != nullptr && el.key() >= tmp.key()){
            tmp = tmp.next();
        }

        Node<T> smaller = tmp.prev();
        el.set_prev(smaller);
        tmp.set_prev(el);

        el.set_next(tmp);
    }

    bool delete(const T& k){
        Node<T> tmp = start;
        if(tmp == nullptr){
            throw exception("No list avaiable!");
        }

        while(tmp.key() != k){
            if(tmp.next() == nullptr){
                return false;
            }
            tmp = tmp.next();
        }

        tmp.next().set_prev(tmp.prev());
        tmp.prev().set_next(tmp.next());

        return true;
    }

    Node<T> get_node(const T& k) const{
        Node<T> tmp = start;
        if(tmp == nullptr){
            throw exception("No list avaiable!");
        }

        while(tmp.key() != k){
            if(tmp.next() == nullptr){
                return false
            }
            tmp = tmp.next();
        }
        return tmp;
    }
    
    //lower/upper_bound
    Node<T> lower_bound(const T& k) const{
        Node<T> tmp = start;
        if(tmp == nullptr){
            throw exception("No list avaiable!");
        }
        while(tmp.key() < k){
            if(tmp.next() == nullptr){
                //return last element
                break;
            }
            tmp = tmp.next();
        }

        return tmp;
    }

    Node<T> upper_bound(const T& k) const{
        Node<T> tmp = get_node(k);

        return (tmp.next() == nullptr) ? tmp : tmp.next();
    }
    
    //successor/predeccessor
    Node<T> successor(const T& k) const{
        Node<T> tmp = get_node(k);

        return (tmp.next() == nullptr) ? tmp : tmp.next();
    }
    
    Node<T> predeccessor(const T& k) const{
        Node<T> tmp = get_node(k);

        return tmp.prev() == nullptr ? tmp : tmp.prev();
    }
    
    //update
    bool update(const T& k, const T& v){
        Node<T> tmp = start;
        if(tmp == nullptr){
            throw exception("No list avaiable!");
        }

        while(tmp.key() != k){
            if(tmp.next() == nullptr){
                return false
            }
            tmp = tmp.next();
        }

        tmp.set_val(v);

        return true;
    }

    //rank(x)
    int rank(const T& k) const{
        Node<T> tmp = start;
        if(tmp == nullptr){
            throw exception("No list avaiable!");
        }

        int r = 0;

        while(tmp.key() != k){
            if(tmp.next() == nullptr){
                return r;
            }
            tmp = tmp.next();
            r++;
        }

        return r;
    }
    
    //intersect / merge
    void merge(MyList<T>& other){
        Node<T> it = other.begin();

        if(it == nullptr){
            return;
        }

        if(start == nullptr){
            start = it;
            return;
        }

        while(it != nullptr){
            Node<T> next_node = it.next();
            insert(it);
            it = next_node;
        }
    }
};



