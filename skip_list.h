#include<vector>
#include "my_list.h"

template <typename K, typename V>
class SkipList {
private:
    std::vector<MyList<K,V>> levels;
public:
    //constructors
    SkipList(){
        levels = nullptr;
    }

    SkipList(SkipList&& other){
        this->levels = other.get_levels();

    }

    SkipList()
    //operations
    std::vector<MyList<K,V>> get_levels(){
        return levels;
    }
    void set_levels(std::vector<MyList<K,V>>* new_levels){
        levels = new_levels;
    }
    //cleanup
    ~MyList(){
        for(int i = 0 ; i < levels.size() ; i++){
            delete levels[i];
        }
    }
};