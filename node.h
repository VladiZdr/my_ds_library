template <typename K, typename V>
class Node{
private:
    Node<K,V>* next_;
    Node<K,V>* prev_;
    Node<K,V>* down_;
    Node<K,V>* up_;
    K key_;
    V val_;

    //destroy
    void erase(){
        if(next_ != nullptr){
            next_->set_prev(prev_);
        }
        if(prev_ != nullptr){
            prev_->set_next(next_);
        }
        next_ = nullptr;
        prev_ = nullptr;
        key_ = K{};
        val_ = V{};
    }
public:

    //constructors
    Node(){
        next_ = nullptr;
        prev_ = nullptr;
        down_ = nullptr;
        up_ = nullptr;
        key_ = K{};
        val_ = V{};
    }

    Node(const K& key, const V& val){
        this->key_ = key;
        this->val_ = val;
        next_ = nullptr;
        prev_ = nullptr;
        down_ = nullptr;
        up_ = nullptr;
    }

    Node(Node<K,V>* next, Node<K,V>* prev, Node<K,V>* up, Node<K,V>* down, const K& key, const V& val){
        this.next_ = next;
        this.prev_ = prev;
        this.up_ = up;
        this.down_ = down;
        this.key_ = key;
        this.val_ = val;
    }

    Node(const Node<K,V>& other){
        this.next_ = other.get_next();
        this.prev_ = other.get_prev();
        this.down_ = other.get_down();
        this.up_ = other.get_up();
        this.key_ = other.get_key();
        this.val_ = other.get_val();
    }
    
    Node(Node<K,V>&& other) noexcept{
        if(this == &other) return;

        this.next_ = other.get_next();
        this.prev_ = other.get_prev();
        this.up_ = other.get_up();
        this.down_ = other.get_down();
        this.key_ = other.get_key();
        this.val_ = other.get_val();

        other.set_next(nullptr);
        other.set_prev(nullptr);
        other.set_up(nullptr);
        other.set_down(nullptr);
        other.set_key(K{});
        other.set_val(V{});
    }

    Node& operator=(const Node& other){
        if(this != &other){
            this.next_ = other.get_next();
            this.prev_ = other.get_prev();
            this.up_ = other.get_up();
            this.down_ = other.get_down();
            this.key_ = other.get_key();
            this.val_ = other.get_val();
        }

        return *this;
    }

    //getters
    Node<K,V>* get_next() const{
        return next_;
    }

    Node<K,V>* get_prev() const{
        return prev_;
    }

    Node<K,V>* get_down() const{
        return down_;
    }

    Node<K,V>* get_up() const{
        return up_;
    }

    const K& get_key() const{
        return key_;
    }
    
    const V& get_val() const{
        return val_;
    }

    //setter
    void set_next(Node<K,V>* new_next){
        next_ = new_next;
    }

    void set_prev(Node<K,V>* new_prev){
        prev_ = new_prev;
    }
    
    void set_up(Node<K,V>* new_up){
        up_ = new_up;
    }

    void set_down(Node<K,V>* new_down){
        down_ = new_down;
    }

    void set_key(const K& new_key){
        key_ = new_key;
    }

    void set_val(const V& new_val){
        val_ = new_val;
    }
};