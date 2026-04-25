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

// COPY ASSIGNMENT TEST 0: both empty
{
    MyList<int> a;
    MyList<int> b;

    a = b;

    assert(a.begin() == nullptr);
    assert(a.length() == 0);

    assert(b.begin() == nullptr);
    assert(b.length() == 0);
}
// COPY ASSIGNMENT TEST 1: this empty, other has 3 nodes
{
    MyList<int> a;

    Node<int>* n1 = new Node<int>(10, 100);
    Node<int>* n2 = new Node<int>(20, 200);
    Node<int>* n3 = new Node<int>(30, 300);

    MyList<int> b;
    b.insert(n1);
    b.insert(n2);
    b.insert(n3);
    Node<int>* b1 = b.begin();
    Node<int>* b2 = b1->get_next();
    Node<int>* b3 = b2->get_next();

    a = b;

    assert(a.length() == 3);
    assert(a.begin() != nullptr);
    assert(a.begin() != b.begin()); // deep copy

    Node<int>* a1 = a.begin();
    Node<int>* a2 = a1->get_next();
    Node<int>* a3 = a2->get_next();

    assert(a1->get_key() == 10 && a1->get_val() == 100);
    assert(a2->get_key() == 20 && a2->get_val() == 200);
    assert(a3->get_key() == 30 && a3->get_val() == 300);

    assert(a1->get_prev() == nullptr);
    assert(a1->get_next() == a2);
    assert(a2->get_prev() == a1);
    assert(a2->get_next() == a3);
    assert(a3->get_prev() == a2);
    assert(a3->get_next() == nullptr);

    // b unchanged
    assert(b.length() == 3);
    assert(b.begin() == b1);
    assert(b1->get_key() == 10 && b1->get_val() == 100);
    assert(b2->get_key() == 20 && b2->get_val() == 200);
    assert(b3->get_key() == 30 && b3->get_val() == 300);
    assert(b1->get_prev() == nullptr);
    assert(b1->get_next() == b2);
    assert(b2->get_prev() == b1);
    assert(b2->get_next() == b3);
    assert(b3->get_prev() == b2);
    assert(b3->get_next() == nullptr);

    delete n1;
    delete n2;
    delete n3;
}
// COPY ASSIGNMENT TEST 2: other empty, this has 3 nodes
{
    Node<int>* n1 = new Node<int>(10, 100);
    Node<int>* n2 = new Node<int>(20, 200);
    Node<int>* n3 = new Node<int>(30, 300);

    MyList<int> a;
    a.insert(n1);
    a.insert(n2);
    a.insert(n3);

    MyList<int> b;

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
    Node<int>* a1n = new Node<int>(10, 100);
    Node<int>* a2n = new Node<int>(20, 200);
    Node<int>* bn  = new Node<int>(15, 150);

    MyList<int> a;
    a.insert(a1n);
    a.insert(a2n);

    MyList<int> b;
    b.insert(bn);
    Node<int>* b1 = b.begin();

    a = b;

    assert(a.length() == 1);
    assert(a.begin() != nullptr);
    assert(a.begin() != b.begin());

    assert(a.begin()->get_key() == 15);
    assert(a.begin()->get_val() == 150);
    assert(a.begin()->get_prev() == nullptr);
    assert(a.begin()->get_next() == nullptr);

    // b unchanged
    assert(b.length() == 1);
    assert(b.begin() == b1);
    assert(b1->get_key() == 15);
    assert(b1->get_val() == 150);
    assert(b1->get_prev() == nullptr);
    assert(b1->get_next() == nullptr);

    delete a1n;
    delete a2n;
    delete bn;
}
// COPY ASSIGNMENT TEST 4: this has 2 nodes, other has 3 nodes
{
    Node<int>* a1n = new Node<int>(5, 50);
    Node<int>* a2n = new Node<int>(25, 250);

    Node<int>* b1n = new Node<int>(10, 100);
    Node<int>* b2n = new Node<int>(20, 200);
    Node<int>* b3n = new Node<int>(30, 300);

    MyList<int> a;
    a.insert(a1n);
    a.insert(a2n);

    MyList<int> b;
    b.insert(b1n);
    b.insert(b2n);
    b.insert(b3n);
    Node<int>* b1 = b.begin();
    Node<int>* b2 = b1->get_next();
    Node<int>* b3 = b2->get_next();

    a = b;

    assert(a.length() == 3);
    assert(a.begin() != nullptr);
    assert(a.begin() != b.begin());

    Node<int>* x1 = a.begin();
    Node<int>* x2 = x1->get_next();
    Node<int>* x3 = x2->get_next();

    assert(x1->get_key() == 10 && x1->get_val() == 100);
    assert(x2->get_key() == 20 && x2->get_val() == 200);
    assert(x3->get_key() == 30 && x3->get_val() == 300);

    assert(x1->get_prev() == nullptr);
    assert(x1->get_next() == x2);
    assert(x2->get_prev() == x1);
    assert(x2->get_next() == x3);
    assert(x3->get_prev() == x2);
    assert(x3->get_next() == nullptr);

    // b unchanged
    assert(b.length() == 3);
    assert(b.begin() == b1);
    assert(b1->get_key() == 10 && b1->get_val() == 100);
    assert(b2->get_key() == 20 && b2->get_val() == 200);
    assert(b3->get_key() == 30 && b3->get_val() == 300);

    assert(b1->get_prev() == nullptr);
    assert(b1->get_next() == b2);
    assert(b2->get_prev() == b1);
    assert(b2->get_next() == b3);
    assert(b3->get_prev() == b2);
    assert(b3->get_next() == nullptr);

    delete a1n;
    delete a2n;
    delete b1n;
    delete b2n;
    delete b3n;
}

// MOVE ASSIGNMENT TEST 0: both empty
{
    MyList<int> a;
    MyList<int> b;

    a = std::move(b);

    assert(a.begin() == nullptr);
    assert(a.length() == 0);

    assert(b.begin() == nullptr);
    assert(b.length() == 0);
}
// MOVE ASSIGNMENT TEST 1: this empty, other has 3 nodes
{
    Node<int>* n1 = new Node<int>(10, 100);
    Node<int>* n2 = new Node<int>(20, 200);
    Node<int>* n3 = new Node<int>(30, 300);

    MyList<int> a;

    MyList<int> b;
    b.insert(n1);
    b.insert(n2);
    b.insert(n3);

    Node<int>* old_begin = b.begin();
    Node<int>* old_second = old_begin->get_next();
    Node<int>* old_third = old_second->get_next();

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
    Node<int>* n1 = new Node<int>(10, 100);
    Node<int>* n2 = new Node<int>(20, 200);
    Node<int>* n3 = new Node<int>(30, 300);

    MyList<int> a;
    a.insert(n1);
    a.insert(n2);
    a.insert(n3);

    MyList<int> b;

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
    Node<int>* a1n = new Node<int>(10, 100);
    Node<int>* a2n = new Node<int>(20, 200);
    Node<int>* bn  = new Node<int>(15, 150);

    MyList<int> a;
    a.insert(a1n);
    a.insert(a2n);

    MyList<int> b;
    b.insert(bn);

    Node<int>* old_begin = b.begin();

    a = std::move(b);

    assert(a.length() == 1);
    assert(a.begin() == old_begin);
    assert(a.begin()->get_key() == 15);
    assert(a.begin()->get_val() == 150);
    assert(a.begin()->get_prev() == nullptr);
    assert(a.begin()->get_next() == nullptr);

    assert(b.begin() == nullptr);
    assert(b.length() == 0);

    delete a1n;
    delete a2n;
    delete bn;
}
// MOVE ASSIGNMENT TEST 4: this has 2 nodes, other has 3 nodes
{
    Node<int>* a1n = new Node<int>(5, 50);
    Node<int>* a2n = new Node<int>(25, 250);

    Node<int>* b1n = new Node<int>(10, 100);
    Node<int>* b2n = new Node<int>(20, 200);
    Node<int>* b3n = new Node<int>(30, 300);

    MyList<int> a;
    a.insert(a1n);
    a.insert(a2n);

    MyList<int> b;
    b.insert(b1n);
    b.insert(b2n);
    b.insert(b3n);

    Node<int>* old_begin = b.begin();
    Node<int>* old_second = old_begin->get_next();
    Node<int>* old_third = old_second->get_next();

    a = std::move(b);

    assert(a.length() == 3);
    assert(a.begin() == old_begin);

    Node<int>* x1 = a.begin();
    Node<int>* x2 = x1->get_next();
    Node<int>* x3 = x2->get_next();

    assert(x1 == old_begin);
    assert(x2 == old_second);
    assert(x3 == old_third);

    assert(x1->get_key() == 10 && x1->get_val() == 100);
    assert(x2->get_key() == 20 && x2->get_val() == 200);
    assert(x3->get_key() == 30 && x3->get_val() == 300);

    assert(x1->get_prev() == nullptr);
    assert(x1->get_next() == x2);
    assert(x2->get_prev() == x1);
    assert(x2->get_next() == x3);
    assert(x3->get_prev() == x2);
    assert(x3->get_next() == nullptr);

    assert(b.begin() == nullptr);
    assert(b.length() == 0);

    delete a1n;
    delete a2n;
    delete b1n;
    delete b2n;
    delete b3n;
}

    std::cout << "Assignement tests passed!\n";

// INSERT TEST 1: new_node == nullptr, list unchanged
{
    Node<int>* n1 = new Node<int>(10, 100);
    Node<int>* n2 = new Node<int>(20, 200);

    MyList<int> l;
    l.insert(n1);
    l.insert(n2);

    Node<int>* old_head = l.begin();
    Node<int>* old_second = old_head->get_next();

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
    Node<int>* new_node = new Node<int>(10, 100);

    MyList<int> l;
    l.insert(new_node);

    assert(l.length() == 1);
    assert(l.begin() != nullptr);

    assert(l.begin() != new_node); // deep copy
    assert(l.begin()->get_key() == 10);
    assert(l.begin()->get_val() == 100);

    assert(l.begin()->get_prev() == nullptr);
    assert(l.begin()->get_next() == nullptr);

    delete new_node;
}
// INSERT TEST 3: smaller key than head goes to front
{
    Node<int>* n1 = new Node<int>(10, 100);
    Node<int>* n2 = new Node<int>(20, 200);
    Node<int>* new_node = new Node<int>(5, 50);

    MyList<int> l;
    l.insert(n1);
    l.insert(n2);
    l.insert(new_node);

    assert(l.length() == 3);

    Node<int>* h = l.begin();
    Node<int>* s = h->get_next();
    Node<int>* t = s->get_next();

    assert(h != new_node); // deep copy
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
    Node<int>* n1 = new Node<int>(10, 100);
    Node<int>* n2 = new Node<int>(20, 200);
    Node<int>* n3 = new Node<int>(30, 300);
    Node<int>* new_node = new Node<int>(40, 400);

    MyList<int> l;
    l.insert(n1);
    l.insert(n2);
    l.insert(n3);
    l.insert(new_node);

    assert(l.length() == 4);

    Node<int>* a = l.begin();
    Node<int>* b = a->get_next();
    Node<int>* c = b->get_next();
    Node<int>* d = c->get_next();

    assert(d != new_node); // deep copy
    assert(d->get_key() == 40);
    assert(d->get_val() == 400);

    assert(a->get_key() == 10);
    assert(b->get_key() == 20);
    assert(c->get_key() == 30);

    assert(a->get_prev() == nullptr);
    assert(a->get_next() == b);
    assert(b->get_prev() == a);
    assert(b->get_next() == c);
    assert(c->get_prev() == b);
    assert(c->get_next() == d);
    assert(d->get_prev() == c);
    assert(d->get_next() == nullptr);

    delete n1;
    delete n2;
    delete n3;
    delete new_node;
}
// INSERT TEST 5: insert key 3 into keys 1,2,4,5 gives 1,2,3,4,5
{
    Node<int>* n1 = new Node<int>(1, 10);
    Node<int>* n2 = new Node<int>(2, 20);
    Node<int>* n4 = new Node<int>(4, 40);
    Node<int>* n5 = new Node<int>(5, 50);
    Node<int>* new_node = new Node<int>(3, 30);

    MyList<int> l;
    l.insert(n1);
    l.insert(n2);
    l.insert(n4);
    l.insert(n5);
    l.insert(new_node);

    assert(l.length() == 5);

    Node<int>* a = l.begin();
    Node<int>* b = a->get_next();
    Node<int>* c = b->get_next();
    Node<int>* d = c->get_next();
    Node<int>* e = d->get_next();

    assert(c != new_node); // deep copy
    assert(c->get_key() == 3);
    assert(c->get_val() == 30);

    assert(a->get_key() == 1);
    assert(b->get_key() == 2);
    assert(d->get_key() == 4);
    assert(e->get_key() == 5);

    assert(a->get_prev() == nullptr);
    assert(a->get_next() == b);

    assert(b->get_prev() == a);
    assert(b->get_next() == c);

    assert(c->get_prev() == b);
    assert(c->get_next() == d);

    assert(d->get_prev() == c);
    assert(d->get_next() == e);

    assert(e->get_prev() == d);
    assert(e->get_next() == nullptr);

    delete n1;
    delete n2;
    delete n4;
    delete n5;
    delete new_node;
}

    std::cout << "Insert tests passed!\n";

// REMOVE TEST 1: key not in list
{
    Node<int>* n1 = new Node<int>(10, 100);
    Node<int>* n2 = new Node<int>(20, 200);
    Node<int>* n3 = new Node<int>(30, 300);

    MyList<int> l;
    l.insert(n1);
    l.insert(n2);
    l.insert(n3);

    bool removed = l.remove(25);

    assert(!removed);
    assert(l.length() == 3);

    Node<int>* a = l.begin();
    Node<int>* b = a->get_next();
    Node<int>* c = b->get_next();

    assert(a->get_key() == 10);
    assert(b->get_key() == 20);
    assert(c->get_key() == 30);

    assert(a->get_prev() == nullptr);
    assert(a->get_next() == b);
    assert(b->get_prev() == a);
    assert(b->get_next() == c);
    assert(c->get_prev() == b);
    assert(c->get_next() == nullptr);

    delete n1;
    delete n2;
    delete n3;
}
// REMOVE TEST 2: remove head
{
    Node<int>* n1 = new Node<int>(10, 100);
    Node<int>* n2 = new Node<int>(20, 200);
    Node<int>* n3 = new Node<int>(30, 300);

    MyList<int> l;
    l.insert(n1);
    l.insert(n2);
    l.insert(n3);

    bool removed = l.remove(10);

    assert(removed);
    assert(l.length() == 2);

    Node<int>* a = l.begin();
    Node<int>* b = a->get_next();

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
    Node<int>* n1 = new Node<int>(10, 100);
    Node<int>* n2 = new Node<int>(20, 200);
    Node<int>* n3 = new Node<int>(30, 300);

    MyList<int> l;
    l.insert(n1);
    l.insert(n2);
    l.insert(n3);

    bool removed = l.remove(30);

    assert(removed);
    assert(l.length() == 2);

    Node<int>* a = l.begin();
    Node<int>* b = a->get_next();

    assert(a->get_key() == 10);
    assert(b->get_key() == 20);

    assert(a->get_prev() == nullptr);
    assert(a->get_next() == b);
    assert(b->get_prev() == a);
    assert(b->get_next() == nullptr);

    delete n1;
    delete n2;
    delete n3;
}
// REMOVE TEST 4: remove 3rd node in a 5-node list
{
    Node<int>* n1 = new Node<int>(10, 100);
    Node<int>* n2 = new Node<int>(20, 200);
    Node<int>* n3 = new Node<int>(30, 300);
    Node<int>* n4 = new Node<int>(40, 400);
    Node<int>* n5 = new Node<int>(50, 500);

    MyList<int> l;
    l.insert(n1);
    l.insert(n2);
    l.insert(n3);
    l.insert(n4);
    l.insert(n5);

    bool removed = l.remove(30);

    assert(removed);
    assert(l.length() == 4);

    Node<int>* a = l.begin();
    Node<int>* b = a->get_next();
    Node<int>* c = b->get_next();
    Node<int>* d = c->get_next();

    assert(a->get_key() == 10);
    assert(b->get_key() == 20);
    assert(c->get_key() == 40);
    assert(d->get_key() == 50);

    assert(a->get_prev() == nullptr);
    assert(a->get_next() == b);

    assert(b->get_prev() == a);
    assert(b->get_next() == c);

    assert(c->get_prev() == b);
    assert(c->get_next() == d);

    assert(d->get_prev() == c);
    assert(d->get_next() == nullptr);

    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
}

    std::cout << "Remove tests passed!\n";

// GET_NODE TEST 1: key not in list -> nullptr
{
    Node<int>* n1 = new Node<int>(10, 100);
    Node<int>* n2 = new Node<int>(20, 200);
    Node<int>* n3 = new Node<int>(30, 300);

    MyList<int> l;
    l.insert(n1);
    l.insert(n2);
    l.insert(n3);

    Node<int>* result = l.get_node(25);

    assert(result == nullptr);

    delete n1;
    delete n2;
    delete n3;
}
// GET_NODE TEST 2: get head
{
    Node<int>* n1 = new Node<int>(10, 100);
    Node<int>* n2 = new Node<int>(20, 200);
    Node<int>* n3 = new Node<int>(30, 300);

    MyList<int> l;
    l.insert(n1);
    l.insert(n2);
    l.insert(n3);

    Node<int>* result = l.get_node(10);

    assert(result != nullptr);
    assert(result == l.begin());

    assert(result->get_key() == 10);
    assert(result->get_val() == 100);
    assert(result->get_prev() == nullptr);
    assert(result->get_next() != nullptr);
    assert(result->get_next()->get_key() == 20);

    delete n1;
    delete n2;
    delete n3;
}
// GET_NODE TEST 3: get tail
{
    Node<int>* n1 = new Node<int>(10, 100);
    Node<int>* n2 = new Node<int>(20, 200);
    Node<int>* n3 = new Node<int>(30, 300);

    MyList<int> l;
    l.insert(n1);
    l.insert(n2);
    l.insert(n3);

    Node<int>* result = l.get_node(30);

    assert(result != nullptr);
    assert(result->get_key() == 30);
    assert(result->get_val() == 300);
    assert(result->get_next() == nullptr);
    assert(result->get_prev() != nullptr);
    assert(result->get_prev()->get_key() == 20);

    delete n1;
    delete n2;
    delete n3;
}
// GET_NODE TEST 4: get second node
{
    Node<int>* n1 = new Node<int>(10, 100);
    Node<int>* n2 = new Node<int>(20, 200);
    Node<int>* n3 = new Node<int>(30, 300);

    MyList<int> l;
    l.insert(n1);
    l.insert(n2);
    l.insert(n3);

    Node<int>* result = l.get_node(20);

    assert(result != nullptr);
    assert(result->get_key() == 20);
    assert(result->get_val() == 200);

    assert(result->get_prev() != nullptr);
    assert(result->get_prev()->get_key() == 10);

    assert(result->get_next() != nullptr);
    assert(result->get_next()->get_key() == 30);

    delete n1;
    delete n2;
    delete n3;
}

    std::cout << "Get_Node tests passed!\n";
    return 0;
}
