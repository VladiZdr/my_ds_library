#include <vector>
#include "my_list.h"
#include <random>
#include <ctime>

template <typename K, typename V>
class SkipList {
private:
    std::vector<MyList<K,V>*> levels;

    //helper functions
    void set_levels(std::vector<MyList<K,V>*> new_levels){
        erase();
        if(new_levels.size() == 0){
            levels.push_back(new MyList<K, V>());
            return;
        }
        levels = new_levels;
    }
    
    size_t get_random_levels() {
        static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
        static std::bernoulli_distribution coin_flip(0.5); // 50% heads, 50% tails
        
        size_t count = 0;
        while (coin_flip(rng)) { // true = heads, false = tails
            count++;
        }
        return count;
    }
public:
    //constructors
    SkipList(){
        levels.push_back(new MyList<K, V>());
    }

    SkipList(SkipList& other){
        erase();
        std::vector<MyList<K,V>*> other_levels = other.get_levels();
        for(int i = 0 ; i < other_levels.size() ; i++){
            this->levels.push_back( new MyList<K, V>(*other_levels[i]) );
        }
    }

    SkipList(SkipList&& other) noexcept{
        erase();
        levels = std::move(other.levels);
        //other->set_levels(std::vector<MyList<K,V>*>());
    }

    SkipList& operator= (SkipList& other){
        
        if(this != &other){
            erase();
            std::vector<MyList<K,V>*> other_levels = other.get_levels();
            for(int i = 0 ; i < other_levels.size() ; i++){
                this->levels.push_back( new MyList<K, V>(*other_levels[i]) );
            }
        }

        return *this;
    }

    SkipList& operator= (SkipList&& other) noexcept{
        if(this != &other){
            erase();
            levels = std::move(other.levels);
            //other->set_levels({});
        }

        return *this;
    }
    //operations
    std::vector<MyList<K,V>*> get_levels(){
        return levels;
    }

    Node<K,V>* find(const K& key){
        //start from top level find
        size_t curr_level = levels.size() - 1;
        //find in top level node with largest key <= key
        Node<K,V>* curr_find = levels[curr_level]->find(key);

        while(curr_level > 0){
            //get down node
            curr_level--;
            curr_find = curr_find->get_down();
            //find in next level node with largest key <= key
            curr_find = levels[curr_level]->find_from(curr_find, key);
        }

        return curr_find;
    }

    size_t insert(Node<K,V>* node){
        //determine how many levels insert 
        size_t random_levels = get_random_levels() + 1;
        if(random_levels > levels.size()){
            for(size_t i = levels.size() ; i < random_levels ; i++){
                levels.push_back(new MyList<K, V>());
            }
        }
        
        //insert on each level starting from bottom
        Node<K,V>* prev_node = nullptr;
        for(size_t i = 0 ; i < random_levels ; i++){
        
            Node<K, V>* inserted = new Node<K,V> (node->get_key(), node->get_val());
            Node<K, V>* new_node = levels[i]->insert(inserted);
            
            //if i == 0 || i == random_levels - 1 up and down are null by constructor
            if(i != 0 && new_node != nullptr && prev_node != nullptr){
                prev_node->set_up(new_node);
                new_node->set_down(prev_node);
            }

            prev_node = new_node;
            delete inserted;
        }

        return random_levels;
    }

    bool remove(const K& key){
        //find node to remove
        Node<K,V>* node = find(key);
        //if not found find returns tail

        if(node == nullptr || node->get_key() != key){
            return false;
        }
        
        Node<K,V>* curr = node;
        size_t curr_level = 0;
        //remove from each level
        while(curr != nullptr){
            const K key = curr->get_key();
            levels[curr_level]->remove(key); 

            curr = curr->get_up();
            curr_level++;
        }

        return true;
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


