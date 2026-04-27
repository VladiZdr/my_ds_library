#include <cassert>
#include <iostream>
#include <utility>

#include "my_list.h"

int main() {
    // DEFAULT CONSTRUCTOR TEST
    {
        MyList<int, int> l;

        assert(l.begin() == nullptr);
        assert(l.length() == 0);
    }

    // NODE* CONSTRUCTOR TEST: normal node
    {
        Node<int, int>* start_n = new Node<int, int>(10, 20);
        MyList<int, int> l(start_n);

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
        Node<int, int>* start_n = nullptr;
        MyList<int, int> l(start_n);

        assert(l.begin() == nullptr);
        assert(l.length() == 0);
    }

    // COPY CONSTRUCTOR TEST: empty list
    {
        MyList<int, int> other;
        MyList<int, int> copy(other);

        assert(copy.begin() == nullptr);
        assert(copy.length() == 0);
    }

    // COPY CONSTRUCTOR TEST: one node
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);

        MyList<int, int> other;
        other.insert(n1);

        MyList<int, int> copy(other);

        assert(copy.begin() != nullptr);
        assert(copy.length() == 1);
        assert(copy.begin()->get_key() == 10);
        assert(copy.begin()->get_val() == 100);
        assert(copy.begin()->get_prev() == nullptr);
        assert(copy.begin()->get_next() == nullptr);
        assert(copy.begin() != other.begin());

        delete n1;
    }

    // COPY CONSTRUCTOR TEST: three nodes, deep copy and links
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> other;
        other.insert(n1);
        other.insert(n2);
        other.insert(n3);

        MyList<int, int> copy(other);

        assert(copy.length() == 3);
        Node<int, int>* c1 = copy.begin();
        Node<int, int>* c2 = c1->get_next();
        Node<int, int>* c3 = c2->get_next();

        assert(c1->get_key() == 10 && c1->get_val() == 100);
        assert(c2->get_key() == 20 && c2->get_val() == 200);
        assert(c3->get_key() == 30 && c3->get_val() == 300);

        assert(c1 != other.begin());
        assert(c2 != other.begin()->get_next());
        assert(c3 != other.begin()->get_next()->get_next());

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
        MyList<int, int> other;
        MyList<int, int> moved(std::move(other));

        assert(moved.begin() == nullptr);
        assert(moved.length() == 0);
        assert(other.begin() == nullptr);
        assert(other.length() == 0);
    }

    // MOVE CONSTRUCTOR TEST: one node
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);

        MyList<int, int> other;
        other.insert(n1);

        Node<int, int>* old_begin = other.begin();

        MyList<int, int> moved(std::move(other));

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
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> other;
        other.insert(n1);
        other.insert(n2);
        other.insert(n3);

        Node<int, int>* old_begin = other.begin();
        Node<int, int>* old_second = old_begin->get_next();
        Node<int, int>* old_third = old_second->get_next();

        MyList<int, int> moved(std::move(other));

        assert(moved.begin() == old_begin);
        assert(moved.length() == 3);

        Node<int, int>* m1 = moved.begin();
        Node<int, int>* m2 = m1->get_next();
        Node<int, int>* m3 = m2->get_next();

        assert(m1 == old_begin);
        assert(m2 == old_second);
        assert(m3 == old_third);

        assert(m1->get_prev() == nullptr);
        assert(m1->get_next() == m2);
        assert(m2->get_prev() == m1);
        assert(m2->get_next() == m3);
        assert(m3->get_prev() == m2);
        assert(m3->get_next() == nullptr);

        assert(other.begin() == nullptr);
        assert(other.length() == 0);

        delete n1;
        delete n2;
        delete n3;
    }

    std::cout << "Constructor tests passed!\n";

    // COPY ASSIGNMENT TEST 0: both empty
    {
        MyList<int, int> a;
        MyList<int, int> b;

        a = b;

        assert(a.begin() == nullptr);
        assert(a.length() == 0);
        assert(b.begin() == nullptr);
        assert(b.length() == 0);
    }

    // COPY ASSIGNMENT TEST 1: this empty, other has 3 nodes
    {
        MyList<int, int> a;

        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> b;
        b.insert(n1);
        b.insert(n2);
        b.insert(n3);

        Node<int, int>* b1 = b.begin();
        Node<int, int>* b2 = b1->get_next();
        Node<int, int>* b3 = b2->get_next();

        a = b;

        assert(a.length() == 3);
        assert(a.begin() != nullptr);
        assert(a.begin() != b.begin());

        Node<int, int>* a1 = a.begin();
        Node<int, int>* a2 = a1->get_next();
        Node<int, int>* a3 = a2->get_next();

        assert(a1->get_key() == 10 && a1->get_val() == 100);
        assert(a2->get_key() == 20 && a2->get_val() == 200);
        assert(a3->get_key() == 30 && a3->get_val() == 300);

        assert(b.length() == 3);
        assert(b.begin() == b1);
        assert(b1->get_key() == 10 && b1->get_val() == 100);
        assert(b2->get_key() == 20 && b2->get_val() == 200);
        assert(b3->get_key() == 30 && b3->get_val() == 300);

        delete n1;
        delete n2;
        delete n3;
    }

    // COPY ASSIGNMENT TEST 2: other empty, this has 3 nodes
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> a;
        a.insert(n1);
        a.insert(n2);
        a.insert(n3);

        MyList<int, int> b;

        a = b;

        assert(a.begin() == nullptr);
        assert(a.length() == 0);
        assert(b.begin() == nullptr);
        assert(b.length() == 0);

        delete n1;
        delete n2;
        delete n3;
    }

    // COPY ASSIGNMENT TEST 3: this has 2 nodes, other has 1 node
    {
        Node<int, int>* a1n = new Node<int, int>(10, 100);
        Node<int, int>* a2n = new Node<int, int>(20, 200);
        Node<int, int>* bn = new Node<int, int>(15, 150);

        MyList<int, int> a;
        a.insert(a1n);
        a.insert(a2n);

        MyList<int, int> b;
        b.insert(bn);
        Node<int, int>* b1 = b.begin();

        a = b;

        assert(a.length() == 1);
        assert(a.begin() != nullptr);
        assert(a.begin() != b.begin());
        assert(a.begin()->get_key() == 15);
        assert(a.begin()->get_val() == 150);

        assert(b.length() == 1);
        assert(b.begin() == b1);
        assert(b1->get_key() == 15);
        assert(b1->get_val() == 150);

        delete a1n;
        delete a2n;
        delete bn;
    }

    // COPY ASSIGNMENT TEST 4: this has 2 nodes, other has 3 nodes
    {
        Node<int, int>* a1n = new Node<int, int>(5, 50);
        Node<int, int>* a2n = new Node<int, int>(25, 250);

        Node<int, int>* b1n = new Node<int, int>(10, 100);
        Node<int, int>* b2n = new Node<int, int>(20, 200);
        Node<int, int>* b3n = new Node<int, int>(30, 300);

        MyList<int, int> a;
        a.insert(a1n);
        a.insert(a2n);

        MyList<int, int> b;
        b.insert(b1n);
        b.insert(b2n);
        b.insert(b3n);

        Node<int, int>* b1 = b.begin();
        Node<int, int>* b2 = b1->get_next();
        Node<int, int>* b3 = b2->get_next();

        a = b;

        assert(a.length() == 3);
        Node<int, int>* x1 = a.begin();
        Node<int, int>* x2 = x1->get_next();
        Node<int, int>* x3 = x2->get_next();

        assert(x1->get_key() == 10 && x1->get_val() == 100);
        assert(x2->get_key() == 20 && x2->get_val() == 200);
        assert(x3->get_key() == 30 && x3->get_val() == 300);

        assert(b.length() == 3);
        assert(b.begin() == b1);
        assert(b1->get_key() == 10 && b1->get_val() == 100);
        assert(b2->get_key() == 20 && b2->get_val() == 200);
        assert(b3->get_key() == 30 && b3->get_val() == 300);

        delete a1n;
        delete a2n;
        delete b1n;
        delete b2n;
        delete b3n;
    }

    // MOVE ASSIGNMENT TEST 0: both empty
    {
        MyList<int, int> a;
        MyList<int, int> b;

        a = std::move(b);

        assert(a.begin() == nullptr);
        assert(a.length() == 0);
        assert(b.begin() == nullptr);
        assert(b.length() == 0);
    }

    // MOVE ASSIGNMENT TEST 1: this empty, other has 3 nodes
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> a;
        MyList<int, int> b;
        b.insert(n1);
        b.insert(n2);
        b.insert(n3);

        Node<int, int>* old_begin = b.begin();
        Node<int, int>* old_second = old_begin->get_next();
        Node<int, int>* old_third = old_second->get_next();

        a = std::move(b);

        assert(a.length() == 3);
        assert(a.begin() == old_begin);
        assert(a.begin()->get_next() == old_second);
        assert(old_second->get_next() == old_third);
        assert(b.begin() == nullptr);
        assert(b.length() == 0);

        delete n1;
        delete n2;
        delete n3;
    }

    // MOVE ASSIGNMENT TEST 2: other empty, this has 3 nodes
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> a;
        a.insert(n1);
        a.insert(n2);
        a.insert(n3);

        MyList<int, int> b;

        a = std::move(b);

        assert(a.begin() == nullptr);
        assert(a.length() == 0);
        assert(b.begin() == nullptr);
        assert(b.length() == 0);

        delete n1;
        delete n2;
        delete n3;
    }

    // MOVE ASSIGNMENT TEST 3: this has 2 nodes, other has 1 node
    {
        Node<int, int>* a1n = new Node<int, int>(10, 100);
        Node<int, int>* a2n = new Node<int, int>(20, 200);
        Node<int, int>* bn = new Node<int, int>(15, 150);

        MyList<int, int> a;
        a.insert(a1n);
        a.insert(a2n);

        MyList<int, int> b;
        b.insert(bn);
        Node<int, int>* old_begin = b.begin();

        a = std::move(b);

        assert(a.length() == 1);
        assert(a.begin() == old_begin);
        assert(a.begin()->get_key() == 15);
        assert(a.begin()->get_val() == 150);
        assert(b.begin() == nullptr);
        assert(b.length() == 0);

        delete a1n;
        delete a2n;
        delete bn;
    }

    // MOVE ASSIGNMENT TEST 4: this has 2 nodes, other has 3 nodes
    {
        Node<int, int>* a1n = new Node<int, int>(5, 50);
        Node<int, int>* a2n = new Node<int, int>(25, 250);

        Node<int, int>* b1n = new Node<int, int>(10, 100);
        Node<int, int>* b2n = new Node<int, int>(20, 200);
        Node<int, int>* b3n = new Node<int, int>(30, 300);

        MyList<int, int> a;
        a.insert(a1n);
        a.insert(a2n);

        MyList<int, int> b;
        b.insert(b1n);
        b.insert(b2n);
        b.insert(b3n);

        Node<int, int>* old_begin = b.begin();
        Node<int, int>* old_second = old_begin->get_next();
        Node<int, int>* old_third = old_second->get_next();

        a = std::move(b);

        assert(a.length() == 3);
        assert(a.begin() == old_begin);

        Node<int, int>* x1 = a.begin();
        Node<int, int>* x2 = x1->get_next();
        Node<int, int>* x3 = x2->get_next();

        assert(x1 == old_begin);
        assert(x2 == old_second);
        assert(x3 == old_third);
        assert(b.begin() == nullptr);
        assert(b.length() == 0);

        delete a1n;
        delete a2n;
        delete b1n;
        delete b2n;
        delete b3n;
    }

    std::cout << "Assignment tests passed!\n";

    // INSERT TEST 1: new_node == nullptr, list unchanged
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);

        Node<int, int>* old_head = l.begin();
        Node<int, int>* old_second = old_head->get_next();

        l.insert(nullptr);

        assert(l.length() == 2);
        assert(l.begin() == old_head);
        assert(l.begin()->get_next() == old_second);
        assert(old_head->get_key() == 10);
        assert(old_second->get_key() == 20);

        delete n1;
        delete n2;
    }

    // INSERT TEST 2: insert into empty list makes deep copy head
    {
        Node<int, int>* new_node = new Node<int, int>(10, 100);

        MyList<int, int> l;
        l.insert(new_node);

        assert(l.length() == 1);
        assert(l.begin() != nullptr);
        assert(l.begin() != new_node);
        assert(l.begin()->get_key() == 10);
        assert(l.begin()->get_val() == 100);
        assert(l.begin()->get_prev() == nullptr);
        assert(l.begin()->get_next() == nullptr);

        delete new_node;
    }

    // INSERT TEST 3: smaller key than head goes to front
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* new_node = new Node<int, int>(5, 50);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);
        l.insert(new_node);

        assert(l.length() == 3);

        Node<int, int>* h = l.begin();
        Node<int, int>* s = h->get_next();
        Node<int, int>* t = s->get_next();

        assert(h != new_node);
        assert(h->get_key() == 5);
        assert(h->get_val() == 50);
        assert(s->get_key() == 10);
        assert(t->get_key() == 20);

        assert(h->get_prev() == nullptr);
        assert(h->get_next() == s);
        assert(s->get_prev() == h);
        assert(s->get_next() == t);
        assert(t->get_prev() == s);
        assert(t->get_next() == nullptr);

        delete n1;
        delete n2;
        delete new_node;
    }

    // INSERT TEST 4: higher key than tail goes to back
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);
        Node<int, int>* new_node = new Node<int, int>(40, 400);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);
        l.insert(n3);
        l.insert(new_node);

        assert(l.length() == 4);

        Node<int, int>* a = l.begin();
        Node<int, int>* b = a->get_next();
        Node<int, int>* c = b->get_next();
        Node<int, int>* d = c->get_next();

        assert(d != new_node);
        assert(d->get_key() == 40);
        assert(d->get_val() == 400);
        assert(a->get_key() == 10);
        assert(b->get_key() == 20);
        assert(c->get_key() == 30);

        delete n1;
        delete n2;
        delete n3;
        delete new_node;
    }

    // INSERT TEST 5: insert key 3 into keys 1,2,4,5 gives 1,2,3,4,5
    {
        Node<int, int>* n1 = new Node<int, int>(1, 10);
        Node<int, int>* n2 = new Node<int, int>(2, 20);
        Node<int, int>* n4 = new Node<int, int>(4, 40);
        Node<int, int>* n5 = new Node<int, int>(5, 50);
        Node<int, int>* new_node = new Node<int, int>(3, 30);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);
        l.insert(n4);
        l.insert(n5);
        l.insert(new_node);

        assert(l.length() == 5);

        Node<int, int>* a = l.begin();
        Node<int, int>* b = a->get_next();
        Node<int, int>* c = b->get_next();
        Node<int, int>* d = c->get_next();
        Node<int, int>* e = d->get_next();

        assert(c != new_node);
        assert(a->get_key() == 1);
        assert(b->get_key() == 2);
        assert(c->get_key() == 3);
        assert(d->get_key() == 4);
        assert(e->get_key() == 5);

        delete n1;
        delete n2;
        delete n4;
        delete n5;
        delete new_node;
    }

    std::cout << "Insert tests passed!\n";

    // REMOVE TEST 1: key not in list
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);
        l.insert(n3);

        bool removed = l.remove(25);

        assert(!removed);
        assert(l.length() == 3);

        Node<int, int>* a = l.begin();
        Node<int, int>* b = a->get_next();
        Node<int, int>* c = b->get_next();

        assert(a->get_key() == 10);
        assert(b->get_key() == 20);
        assert(c->get_key() == 30);

        delete n1;
        delete n2;
        delete n3;
    }

    // REMOVE TEST 2: remove head
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);
        l.insert(n3);

        bool removed = l.remove(10);

        assert(removed);
        assert(l.length() == 2);

        Node<int, int>* a = l.begin();
        Node<int, int>* b = a->get_next();

        assert(a->get_key() == 20);
        assert(b->get_key() == 30);
        assert(a->get_prev() == nullptr);
        assert(a->get_next() == b);
        assert(b->get_prev() == a);
        assert(b->get_next() == nullptr);

        delete n1;
        delete n2;
        delete n3;
    }

    // REMOVE TEST 3: remove tail
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);
        l.insert(n3);

        bool removed = l.remove(30);

        assert(removed);
        assert(l.length() == 2);

        Node<int, int>* a = l.begin();
        Node<int, int>* b = a->get_next();

        assert(a->get_key() == 10);
        assert(b->get_key() == 20);

        delete n1;
        delete n2;
        delete n3;
    }

    // REMOVE TEST 4: remove 3rd node in a 5-node list
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);
        Node<int, int>* n4 = new Node<int, int>(40, 400);
        Node<int, int>* n5 = new Node<int, int>(50, 500);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);
        l.insert(n3);
        l.insert(n4);
        l.insert(n5);

        bool removed = l.remove(30);

        assert(removed);
        assert(l.length() == 4);

        Node<int, int>* a = l.begin();
        Node<int, int>* b = a->get_next();
        Node<int, int>* c = b->get_next();
        Node<int, int>* d = c->get_next();

        assert(a->get_key() == 10);
        assert(b->get_key() == 20);
        assert(c->get_key() == 40);
        assert(d->get_key() == 50);

        delete n1;
        delete n2;
        delete n3;
        delete n4;
        delete n5;
    }

    std::cout << "Remove tests passed!\n";

    // GET_NODE TESTS
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);
        l.insert(n3);

        assert(l.get_node(25) == nullptr);

        Node<int, int>* head = l.get_node(10);
        assert(head != nullptr);
        assert(head == l.begin());

        Node<int, int>* second = l.get_node(20);
        assert(second != nullptr);
        assert(second->get_prev()->get_key() == 10);
        assert(second->get_next()->get_key() == 30);

        Node<int, int>* tail = l.get_node(30);
        assert(tail != nullptr);
        assert(tail->get_prev()->get_key() == 20);
        assert(tail->get_next() == nullptr);

        delete n1;
        delete n2;
        delete n3;
    }

    std::cout << "Get_Node tests passed!\n";

    // LOWER_BOUND TESTS
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);
        l.insert(n3);

        assert(l.lower_bound(25)->get_key() == 30);
        assert(l.lower_bound(10)->get_key() == 10);
        assert(l.lower_bound(11)->get_key() == 20);
        assert(l.lower_bound(30)->get_key() == 30);

        delete n1;
        delete n2;
        delete n3;
    }

    // UPPER_BOUND TESTS
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);
        l.insert(n3);

        assert(l.upper_bound(25)->get_key() == 30);
        assert(l.upper_bound(10)->get_key() == 20);
        assert(l.upper_bound(11)->get_key() == 20);
        assert(l.upper_bound(30) == nullptr);

        delete n1;
        delete n2;
        delete n3;
    }

    std::cout << "Bound tests passed!\n";

    // SUCCESSOR / PREDECESSOR TESTS
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);
        l.insert(n3);

        assert(l.successor(25) == nullptr);
        assert(l.predeccessor(25) == nullptr);

        assert(l.successor(10)->get_key() == 20);
        assert(l.predeccessor(10) == nullptr);

        assert(l.successor(30) == nullptr);
        assert(l.predeccessor(30)->get_key() == 20);

        assert(l.successor(20)->get_key() == 30);
        assert(l.predeccessor(20)->get_key() == 10);

        delete n1;
        delete n2;
        delete n3;
    }

    std::cout << "Successor/Predecessor tests passed!\n";

    // UPDATE TESTS
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);
        l.insert(n3);

        bool updated = l.update(25, 999);
        assert(!updated);

        assert(l.update(10, 101));
        assert(l.update(20, 202));
        assert(l.update(30, 303));
        assert(l.update(20, 222));

        Node<int, int>* a = l.begin();
        Node<int, int>* b = a->get_next();
        Node<int, int>* c = b->get_next();

        assert(a->get_val() == 101);
        assert(b->get_val() == 222);
        assert(c->get_val() == 303);

        delete n1;
        delete n2;
        delete n3;
    }

    std::cout << "Update tests passed!\n";

    // RANK TESTS
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);
        l.insert(n3);

        assert(l.rank(40) == 3);
        assert(l.rank(5) == 0);
        assert(l.rank(10) == 0);
        assert(l.rank(20) == 1);

        delete n1;
        delete n2;
        delete n3;
    }

    std::cout << "Rank tests passed!\n";

    // ERASE TEST
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);
        l.insert(n3);

        l.erase();

        assert(l.begin() == nullptr);
        assert(l.length() == 0);

        assert(n1 != nullptr);
        assert(n2 != nullptr);
        assert(n3 != nullptr);
        assert(n1->get_key() == 10);
        assert(n2->get_key() == 20);
        assert(n3->get_key() == 30);

        delete n1;
        delete n2;
        delete n3;
    }

    std::cout << "Erase tests passed!\n";

    // MERGE TEST 1: self-merge
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> l;
        l.insert(n1);
        l.insert(n2);
        l.insert(n3);

        l.merge(l);

        assert(l.length() == 3);
        assert(l.begin()->get_key() == 10);
        assert(l.begin()->get_next()->get_key() == 20);
        assert(l.begin()->get_next()->get_next()->get_key() == 30);

        delete n1;
        delete n2;
        delete n3;
    }

    // MERGE TEST 2: this empty
    {
        MyList<int, int> l1;

        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> l2;
        l2.insert(n1);
        l2.insert(n2);
        l2.insert(n3);

        l1.merge(l2);

        assert(l1.length() == 3);
        assert(l2.begin() == nullptr);
        assert(l2.length() == 0);

        delete n1;
        delete n2;
        delete n3;
    }

    // MERGE TEST 3: other empty
    {
        Node<int, int>* n1 = new Node<int, int>(10, 100);
        Node<int, int>* n2 = new Node<int, int>(20, 200);
        Node<int, int>* n3 = new Node<int, int>(30, 300);

        MyList<int, int> l1;
        l1.insert(n1);
        l1.insert(n2);
        l1.insert(n3);

        MyList<int, int> l2;
        l1.merge(l2);

        assert(l1.length() == 3);
        assert(l2.begin() == nullptr);
        assert(l2.length() == 0);

        delete n1;
        delete n2;
        delete n3;
    }

    // MERGE TEST 4: other has 1 node merged in middle of 4-node this
    {
        Node<int, int>* a1 = new Node<int, int>(1, 10);
        Node<int, int>* a2 = new Node<int, int>(2, 20);
        Node<int, int>* a4 = new Node<int, int>(4, 40);
        Node<int, int>* a5 = new Node<int, int>(5, 50);
        Node<int, int>* b3 = new Node<int, int>(3, 30);

        MyList<int, int> l1;
        l1.insert(a1);
        l1.insert(a2);
        l1.insert(a4);
        l1.insert(a5);

        MyList<int, int> l2;
        l2.insert(b3);

        l1.merge(l2);

        assert(l1.length() == 5);
        assert(l2.begin() == nullptr);
        assert(l2.length() == 0);

        Node<int, int>* n1p = l1.begin();
        Node<int, int>* n2p = n1p->get_next();
        Node<int, int>* n3p = n2p->get_next();
        Node<int, int>* n4p = n3p->get_next();
        Node<int, int>* n5p = n4p->get_next();

        assert(n1p->get_key() == 1);
        assert(n2p->get_key() == 2);
        assert(n3p->get_key() == 3);
        assert(n4p->get_key() == 4);
        assert(n5p->get_key() == 5);

        delete a1;
        delete a2;
        delete a4;
        delete a5;
        delete b3;
    }

    // MERGE TEST 5: l1 = 2; l2 = 1;3;4;5;
    {
        Node<int, int>* a2 = new Node<int, int>(2, 20);
        Node<int, int>* b1 = new Node<int, int>(1, 10);
        Node<int, int>* b3 = new Node<int, int>(3, 30);
        Node<int, int>* b4 = new Node<int, int>(4, 40);
        Node<int, int>* b5 = new Node<int, int>(5, 50);

        MyList<int, int> l1;
        l1.insert(a2);

        MyList<int, int> l2;
        l2.insert(b1);
        l2.insert(b3);
        l2.insert(b4);
        l2.insert(b5);

        l1.merge(l2);

        int expected[] = {1, 2, 3, 4, 5};
        Node<int, int>* cur = l1.begin();
        for (int i = 0; i < 5; ++i) {
            assert(cur != nullptr);
            assert(cur->get_key() == expected[i]);
            cur = cur->get_next();
        }
        assert(cur == nullptr);

        delete a2;
        delete b1;
        delete b3;
        delete b4;
        delete b5;
    }

    // MERGE TEST 6: l1 = 1;3;5;7; l2 = 2;4;6;8;
    {
        Node<int, int>* a1 = new Node<int, int>(1, 10);
        Node<int, int>* a3 = new Node<int, int>(3, 30);
        Node<int, int>* a5 = new Node<int, int>(5, 50);
        Node<int, int>* a7 = new Node<int, int>(7, 70);

        Node<int, int>* b2 = new Node<int, int>(2, 20);
        Node<int, int>* b4 = new Node<int, int>(4, 40);
        Node<int, int>* b6 = new Node<int, int>(6, 60);
        Node<int, int>* b8 = new Node<int, int>(8, 80);

        MyList<int, int> l1;
        l1.insert(a1);
        l1.insert(a3);
        l1.insert(a5);
        l1.insert(a7);

        MyList<int, int> l2;
        l2.insert(b2);
        l2.insert(b4);
        l2.insert(b6);
        l2.insert(b8);

        l1.merge(l2);

        int expected[] = {1, 2, 3, 4, 5, 6, 7, 8};
        Node<int, int>* cur = l1.begin();
        for (int i = 0; i < 8; ++i) {
            assert(cur != nullptr);
            assert(cur->get_key() == expected[i]);
            cur = cur->get_next();
        }
        assert(cur == nullptr);

        delete a1;
        delete a3;
        delete a5;
        delete a7;
        delete b2;
        delete b4;
        delete b6;
        delete b8;
    }

    // MERGE TEST 7: l1 = 1;2;3;4;5;7; l2 = 6;8;9;
    {
        Node<int, int>* a1 = new Node<int, int>(1, 10);
        Node<int, int>* a2 = new Node<int, int>(2, 20);
        Node<int, int>* a3 = new Node<int, int>(3, 30);
        Node<int, int>* a4 = new Node<int, int>(4, 40);
        Node<int, int>* a5 = new Node<int, int>(5, 50);
        Node<int, int>* a7 = new Node<int, int>(7, 70);

        Node<int, int>* b6 = new Node<int, int>(6, 60);
        Node<int, int>* b8 = new Node<int, int>(8, 80);
        Node<int, int>* b9 = new Node<int, int>(9, 90);

        MyList<int, int> l1;
        l1.insert(a1);
        l1.insert(a2);
        l1.insert(a3);
        l1.insert(a4);
        l1.insert(a5);
        l1.insert(a7);

        MyList<int, int> l2;
        l2.insert(b6);
        l2.insert(b8);
        l2.insert(b9);

        l1.merge(l2);

        int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        Node<int, int>* cur = l1.begin();
        for (int i = 0; i < 9; ++i) {
            assert(cur != nullptr);
            assert(cur->get_key() == expected[i]);
            cur = cur->get_next();
        }
        assert(cur == nullptr);

        delete a1;
        delete a2;
        delete a3;
        delete a4;
        delete a5;
        delete a7;
        delete b6;
        delete b8;
        delete b9;
    }

    // MERGE TEST 8: l1 = 4;5; l2 = 1;2;3;6;7;8;
    {
        Node<int, int>* a4 = new Node<int, int>(4, 40);
        Node<int, int>* a5 = new Node<int, int>(5, 50);

        Node<int, int>* b1 = new Node<int, int>(1, 10);
        Node<int, int>* b2 = new Node<int, int>(2, 20);
        Node<int, int>* b3 = new Node<int, int>(3, 30);
        Node<int, int>* b6 = new Node<int, int>(6, 60);
        Node<int, int>* b7 = new Node<int, int>(7, 70);
        Node<int, int>* b8 = new Node<int, int>(8, 80);

        MyList<int, int> l1;
        l1.insert(a4);
        l1.insert(a5);

        MyList<int, int> l2;
        l2.insert(b1);
        l2.insert(b2);
        l2.insert(b3);
        l2.insert(b6);
        l2.insert(b7);
        l2.insert(b8);

        l1.merge(l2);

        int expected[] = {1, 2, 3, 4, 5, 6, 7, 8};
        Node<int, int>* cur = l1.begin();
        for (int i = 0; i < 8; ++i) {
            assert(cur != nullptr);
            assert(cur->get_key() == expected[i]);
            cur = cur->get_next();
        }
        assert(cur == nullptr);

        delete a4;
        delete a5;
        delete b1;
        delete b2;
        delete b3;
        delete b6;
        delete b7;
        delete b8;
    }

    std::cout << "Merge tests passed!\n";

    return 0;
}