#include <vector>
#include "my_list.h"
#include <random>
#include <ctime>

template <typename K, typename V>
class SkipList {
private:
    std::vector<MyList<K,V>*> levels;
public:
    //constructors
    SkipList(){}

    SkipList(const SkipList& other){
        erase();
        std::vector<MyList<K,V>*> other_levels = other.get_levels();
        for(int i = 0 ; i < other_levels.size() ; i++){
            this->levels.push_back( new MyList<K, V>(*other_levels[i]) );
        }
    }

    SkipList(SkipList&& other) noexcept{
        this->levels = std::move(other.levels);
    }

    SkipList& operator= (const SkipList& other){
        std::vector<MyList<K,V>*> other_levels = other.get_levels();
        for(int i = 0 ; i < other_levels.size() ; i++){
            this->levels.push_back( new MyList<K, V>(*other_levels[i]) );
        }

        return *this;
    }

    SkipList& operator= (SkipList&& other) noexcept{
        if(this != &other){
            erase();
            levels = std::move(other.levels);
        }

        return *this;
    }
    //operations
    std::vector<MyList<K,V>*> get_levels(){
        return levels;
    }
    void set_levels(std::vector<MyList<K,V>*> new_levels){
        erase();
        levels = new_levels;
    }

    Node<K,V>* find(const K& key){
        size_t curr_level = levels.size() - 1;
        Node<K,V>* curr_find = levels[curr_level]->find(key);

        while(curr_level > 0){
            curr_level--;
            curr_find = curr_find->get_down();
            curr_find = levels[curr_level]->find_from(curr_find, key);
        }

        return curr_find;
    }

    void insert(Node<K,V>& node){
        //on how many levels insert 
        size_t random_levels = get_random_levels() + 1;
        if(random_levels > levels.size()){
            for(size_t i = levels.size() ; i < random_levels ; i++){
                levels.push_back(new MyList<K, V>());
            }
        }
        
        //insert on each level starting from bottom
        Node<K,V>* prev_node = nullptr;
        for(size_t i = 0 ; i < random_levels ; i++){
        
            Node<K, V>* new_node = levels[i]->insert(node->get_key(), node->get_value());
            
            //if i == 0 || i == random_levels - 1 up and down are null by constructor
            if(i != 0){
                prev_node->set_up(new_node);
                new_node->set_down(prev_node);
            }

            prev_node = new_node;
        }

    }

    bool remove(const K& key){
        Node<K,V>* node = find(key);
        if(node == nullptr){
            return false;
        }
        
        Node<K,V>* curr = node;
        Node<K,V>* next = nullptr;

        while(curr != nullptr){
            curr->get_prev()->set_next(curr->get_next());
            curr->get_next()->set_prev(curr->get_prev());

            next = curr->get_up();
            
            delete curr;
            curr = next;
        }

        return true;
    }

    //helper functions
    size_t get_random_levels() {
        static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
        static std::bernoulli_distribution coin_flip(0.5); // 50% heads, 50% tails
        
        size_t count = 0;
        while (coin_flip(rng)) { // true = heads, false = tails
            count++;
        }
        return count;
    }
    //cleanup
    void erase(){
        for(int i = 0 ; i < levels.size() ; i++){
            delete levels[i];
        }
        levels.clear();
    }
    ~SkipList(){
        erase();
    }
};


