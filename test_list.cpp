#include <cassert>
#include <iostream>

#include "my_list.h"

int main() {
    // DEFAULT CONSTRUCTOR TEST
    {
        MyList<int> l;

        assert(l.begin() == nullptr);
        assert(l.length() == 0);
    }

    // NODE* CONSTRUCTOR TEST: normal node
    {
        Node<int>* start_n = new Node<int>(10, 20);
        MyList<int> l(start_n);

        assert(l.begin() != nullptr);
        assert(l.length() == 1);

        assert(l.begin()->get_key() == 10);
        assert(l.begin()->get_val() == 20);

        assert(l.begin()->get_prev() == nullptr);
        assert(l.begin()->get_next() == nullptr);

        delete start_n;
    }

    // NODE* CONSTRUCTOR TEST: nullptr
    {
        Node<int>* start_n = nullptr;
        MyList<int> l(start_n);

        assert(l.begin() == nullptr);
        assert(l.length() == 0);
    }

    // COPY CONSTRUCTOR TEST: empty list
    {
        MyList<int> other;
        MyList<int> copy(other);

        assert(copy.begin() == nullptr);
        assert(copy.length() == 0);
    }
    // COPY CONSTRUCTOR TEST: one node
    {
        Node<int>* n1 = new Node<int>(10, 100);

        MyList<int> other;
        other.insert(n1);

        MyList<int> copy(other);

        assert(copy.begin() != nullptr);
        assert(copy.length() == 1);

        assert(copy.begin()->get_key() == 10);
        assert(copy.begin()->get_val() == 100);

        assert(copy.begin()->get_prev() == nullptr);
        assert(copy.begin()->get_next() == nullptr);

        assert(copy.begin() != other.begin()); // deep copy

        delete n1;
    }
    // COPY CONSTRUCTOR TEST: three nodes, deep copy and links
    {
        Node<int>* n1 = new Node<int>(10, 100);
        Node<int>* n2 = new Node<int>(20, 200);
        Node<int>* n3 = new Node<int>(30, 300);

        MyList<int> other;
        other.insert(n1);
        other.insert(n2);
        other.insert(n3);

        MyList<int> copy(other);

        assert(copy.length() == 3);
        assert(copy.begin() != nullptr);

        Node<int>* c1 = copy.begin();
        Node<int>* c2 = c1->get_next();
        Node<int>* c3 = c2->get_next();

        // values copied correctly
        assert(c1->get_key() == 10);
        assert(c1->get_val() == 100);

        assert(c2->get_key() == 20);
        assert(c2->get_val() == 200);

        assert(c3->get_key() == 30);
        assert(c3->get_val() == 300);

        // deep copies
        assert(c1 != other.begin());
        assert(c2 != other.begin()->get_next());
        assert(c3 != other.begin()->get_next()->get_next());

        // correct prev/next links
        assert(c1->get_prev() == nullptr);
        assert(c1->get_next() == c2);

        assert(c2->get_prev() == c1);
        assert(c2->get_next() == c3);

        assert(c3->get_prev() == c2);
        assert(c3->get_next() == nullptr);
        
        delete n1;
        delete n2;
        delete n3;
    }

    // MOVE CONSTRUCTOR TEST: empty list
    {
        MyList<int> other;
        MyList<int> moved(std::move(other));

        assert(moved.begin() == nullptr);
        assert(moved.length() == 0);

        assert(other.begin() == nullptr);
        assert(other.length() == 0);
    }
    // MOVE CONSTRUCTOR TEST: one node
    {
        Node<int>* n1 = new Node<int>(10, 100);

        MyList<int> other;
        other.insert(n1);

        Node<int>* old_begin = other.begin();

        MyList<int> moved(std::move(other));

        assert(moved.begin() == old_begin);
        assert(moved.length() == 1);

        assert(moved.begin()->get_key() == 10);
        assert(moved.begin()->get_val() == 100);

        assert(moved.begin()->get_prev() == nullptr);
        assert(moved.begin()->get_next() == nullptr);

        assert(other.begin() == nullptr);
        assert(other.length() == 0);

        delete n1;
    }
    // MOVE CONSTRUCTOR TEST: three nodes
    {
        Node<int>* n1 = new Node<int>(10, 100);
        Node<int>* n2 = new Node<int>(20, 200);
        Node<int>* n3 = new Node<int>(30, 300);

        MyList<int> other;
        other.insert(n1);
        other.insert(n2);
        other.insert(n3);

        Node<int>* old_begin = other.begin();
        Node<int>* old_second = old_begin->get_next();
        Node<int>* old_third = old_second->get_next();

        MyList<int> moved(std::move(other));

        assert(moved.begin() == old_begin);
        assert(moved.length() == 3);

        Node<int>* m1 = moved.begin();
        Node<int>* m2 = m1->get_next();
        Node<int>* m3 = m2->get_next();

        // ownership transferred
        assert(m1 == old_begin);
        assert(m2 == old_second);
        assert(m3 == old_third);

        // values preserved
        assert(m1->get_key() == 10);
        assert(m1->get_val() == 100);

        assert(m2->get_key() == 20);
        assert(m2->get_val() == 200);

        assert(m3->get_key() == 30);
        assert(m3->get_val() == 300);

        // links preserved
        assert(m1->get_prev() == nullptr);
        assert(m1->get_next() == m2);

        assert(m2->get_prev() == m1);
        assert(m2->get_next() == m3);

        assert(m3->get_prev() == m2);
        assert(m3->get_next() == nullptr);

        // moved-from list is empty
        assert(other.begin() == nullptr);
        assert(other.length() == 0);

        delete n1;
        delete n2;
        delete n3;
    }


    std::cout << "Constructor tests passed!\n";
    return 0;
}
