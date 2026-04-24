template <typename T>
class Node{
private:
    Node<T>* next_;
    Node<T>* prev_;
    T key_;
    T val_;
public:

    //constructors
    Node(){
        next = nullptr;
        prev = nullptr;
        key = T{};
        val = T{};
    }

    Node(const T& key, const T& val){
        this.key_ = key;
        this.val_ = val;
    }

    Node(Node<T>* next, Node<T>* prev, const T& key, const T& val){
        this.next_ = next;
        this.prev_ = prev;
        this.key_ = key;
        this.val_ = val;
    }

    Node(const Node<T>& other){
        this.next_ = other.get_next();
        this.prev_ = other.get_prev();
        this.key_ = other.get_key();
        this.val_ = other.get_val();
    }
    
    Node(const Node<T>&& other) noexcept{
        if(this == other) return;

        this.next_ = other.get_next();
        this.prev_ = other.get_prev();
        this.key_ = other.get_key();
        this.val_ = other.get_val();

        other.set_next(nullptr);
        other.set_prev(nullptr);
        other.set_key(T{});
        other.set_val(T{});
    }

    Node& operator=(const Node& other){
        if(this != other){
            this.next_ = other.get_next();
            this.prev_ = other.get_prev();
            this.key_ = other.get_key();
            this.val_ = other.get_val();
        }

        return *this;
    }

    //getters
    Node<T>* get_next() const{
        return next_;
    }

    Node<T>* get_prev() const{
        return prev_;
    }

    const T& get_key() const{
        return key_;
    }
    
    const T& get_val() const{
        return val_;
    }

    //setter
    void set_next(Node<T>* new_next){
        next_ = new_next;
    }

    void set_prev(Node<T>* new_prev){
        prev_ = new_prev;
    }
    
    void set_key(Node<T>* new_key){
        key_ = new_key;
    }

    void set_val(Node<T>* new_val){
        val_ = new_val;
    }
};