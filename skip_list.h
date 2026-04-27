#include<vector>
#include "my_list.h"

template <typename K, typename V>
class SkipList {
private:
    std::vector<MyList<K,V>*> levels;
public:
    //constructors
    SkipList(){}

    SkipList(const SkipList& other){
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
        levels = new_levels;
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