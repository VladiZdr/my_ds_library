#include <stdexcept>
#include "node.h"

template <typename K, typename V>
class MyList{
private:
    Node<K, V>* start;

    std::size_t size;

public:
    //constructors
    MyList(){
        start = nullptr;
        size = 0;
    }

    MyList(Node<K, V>* start_n){
        if(start_n == nullptr) {
            start = nullptr;
            size = 0;
            return;
        }

        this->start = new Node<K, V>(start_n->get_key(), start_n->get_val());

        size = 1;
    }

    MyList(const MyList<K, V>& other){
        Node<K, V>* tmp2 = other.begin();

        start = nullptr;
        size = other.length();

        if(tmp2 != nullptr){
            start = new Node<K, V>(tmp2->get_key(), tmp2->get_val());
            tmp2 = tmp2->get_next();
        }

        Node<K, V>* tmp1 = start;

        while(tmp2 != nullptr){
            Node<K, V>* next = new Node<K, V>(tmp2->get_key(), tmp2->get_val());
            next->set_prev(tmp1);
            tmp1->set_next(next);

            tmp2 = tmp2->get_next();
            tmp1 = next;
        }
    }

    MyList(MyList<K, V>&& other) noexcept{
        this->start = other.begin();
        this->size = other.length();

        other.start = nullptr;
        other.size = 0;
    }

    //assigments
    MyList& operator=(MyList<K, V>&& other) noexcept{
        if(this != &other){
            erase();

            this->start = other.begin();
            this->size = other.length();

            other.start = nullptr;
            other.size = 0;
        }

        return *this;
    }
    
    MyList& operator=(const MyList<K, V>& other){
        if(this != &other){
            erase();

            Node<K, V>* tmp = other.begin();
            if(tmp == nullptr){
                start = nullptr;
                size = 0;
                return *this;
            }

            start = new Node<K, V>(tmp->get_key(), tmp->get_val());
            Node<K, V>* curr = start;
            tmp = tmp->get_next();

            while(tmp != nullptr){
                Node<K, V>* next = new Node<K, V>(tmp->get_key(), tmp->get_val());
                curr->set_next(next);
                next->set_prev(curr);

                curr = next;
                tmp = tmp->get_next();
            }

            size = other.length();
        }

        return *this;
    }
    //operations
    Node<K, V>* begin() const{
        return start;
    }

    std::size_t length() const{
        return size;
    }

    //insert without transfering ownership
    void insert(Node<K, V>* new_node){
        if(new_node == nullptr){
            return;
        }

        Node<K, V>* el = new Node<K, V>(new_node->get_key(), new_node->get_val());
        
        el->set_prev(nullptr);
        el->set_next(nullptr);

        if(start == nullptr){
            start = el;
            size = 1;
            return;
        }

        if(el->get_key() < start->get_key()){
            el->set_next(start);
            start->set_prev(el);
            start = el;
            size++;
            return;
        }

        Node<K, V>* tmp = start;
        while(tmp->get_next() != nullptr && tmp->get_next()->get_key() <= el->get_key()){
            tmp = tmp->get_next();
        }

        el->set_next(tmp->get_next());
        el->set_prev(tmp);

        if(tmp->get_next() != nullptr){
            tmp->get_next()->set_prev(el);
        }

        tmp->set_next(el);
        size++;
    }

    bool remove(const K& k){
        Node<K, V>* tmp = get_node(k);
        if (tmp == nullptr) {
            return false;
        }

        if (tmp->get_prev() != nullptr) {
            tmp->get_prev()->set_next(tmp->get_next());
        } else {
            start = tmp->get_next();
        }

        if (tmp->get_next() != nullptr) {
            tmp->get_next()->set_prev(tmp->get_prev());
        }

        delete tmp;
        size--;
        return true;
    }

    //nullptr if not found
    Node<K, V>* get_node(const K& k) const{
        Node<K, V>* tmp = start;
        
        while(tmp != nullptr){
            if(tmp->get_key() == k) return tmp;

            tmp = tmp->get_next();
        }

        return nullptr;
    }
    
    //lower/upper_bound -> nullptr if not found
    Node<K, V>* lower_bound(const K& k) const{
        Node<K, V>* tmp = start;
        if(tmp == nullptr){
            return nullptr;
        }
        while(tmp->get_key() < k){
            if(tmp->get_next() == nullptr){
                return nullptr;
            }
            tmp = tmp->get_next();
        }

        return tmp;
    }

    Node<K, V>* upper_bound(const K& k) const{
        Node<K, V>* tmp = start;
        if(tmp == nullptr){
            return nullptr;
        }

        while(tmp->get_key() <= k){
            if(tmp->get_next() == nullptr){
                return nullptr;
            }
            tmp = tmp->get_next();
        }

        return tmp;
    }
    
    //successor/predeccessor
    Node<K, V>* successor(const K& k) const{
        Node<K, V>* tmp = get_node(k);

        return (tmp == nullptr) ? tmp : tmp->get_next();
    }
    
    Node<K, V>* predeccessor(const K& k) const{
        Node<K, V>* tmp = get_node(k);

        return tmp == nullptr ? tmp : tmp->get_prev();
    }
    
    //update
    bool update(const K& k, const V& v){
        Node<K, V>* tmp = get_node(k);

        if(tmp == nullptr) return false;

        tmp->set_val(v);

        return true;
    }

    //rank(x): how many elements in list with key < k
    std::size_t rank(const K& k) const{
        Node<K, V>* tmp = start;
        
        std::size_t r = 0;
        while(tmp != nullptr){
            if(tmp->get_key() >= k) return r;

            tmp = tmp->get_next();
            r++;
        }

        return r;
    }
    
    //deep copy from other and destry other
    void merge(MyList<K, V>& other){
        if(this == &other){
            return;
        }
        //move other to this
        if(start==nullptr){
            *this = other;
            other.erase();
            return;
        }

        Node<K, V>* curr1 = start;
        Node<K, V>* curr2 = other.begin();

        while(curr1->get_next() != nullptr){
            if(curr2 == nullptr){
                break;
            }
            
            //find first node in L1 with key > curr2.key
            while(curr1->get_key() < curr2->get_key()){
                if(curr1->get_next() == nullptr){
                    break;
                }
                curr1 = curr1->get_next();
            }
            if(curr1->get_next() == nullptr){
                break;
            }

            //insert el from L2 in L1
            Node<K, V>* to_add = new Node<K, V>(curr2->get_key(), curr2->get_val());
            if(curr1->get_prev() != nullptr){
                Node<K, V>* tmp = curr1->get_prev();

                tmp->set_next(to_add);
                to_add->set_prev(tmp);
            }
            //if curr1 = start
            else{
                start = to_add;
            }
            curr1->set_prev(to_add);
            to_add->set_next(curr1);

            curr2 = curr2->get_next();
        }

        //insert any left elements from L2
        while(curr2 != nullptr && curr1->get_key() > curr2->get_key()){
            Node<K, V>* to_add = new Node<K, V>(curr2->get_key(), curr2->get_val());
            
            if(curr1->get_prev() != nullptr){
                Node<K, V>* tmp = curr1->get_prev();

                tmp->set_next(to_add);
                to_add->set_prev(tmp);
            }
            else{
                start = to_add;
            }
            curr1->set_prev(to_add);
            to_add->set_next(curr1);
            
            curr2 = curr2->get_next();
        }
        while(curr2 != nullptr){
            Node<K, V>* to_add = new Node<K, V>(curr2->get_key(), curr2->get_val());

            to_add->set_prev(curr1);
            curr1->set_next(to_add);
            to_add->set_next(nullptr);

            curr1 = curr1->get_next();
            curr2 = curr2->get_next();
        }

        size+=other.length();
        other.erase();
    }

    //cleanup
    void erase(){
        Node<K,V>* tmp = start;
        while(tmp != nullptr){
            Node<K, V>* next = tmp->get_next();
            delete tmp;
            tmp = next;
        }
        size = 0;
        start = nullptr;
    }
    ~MyList(){
        erase();
    }
};



