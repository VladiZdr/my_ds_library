#include "skip_list.h"
#include <cassert>
#include <iostream>

// Helper function to create a node for testing
Node<int, int>* create_test_node(int key, int value) {
    return new Node<int, int>(key, value);
}

// Helper function to verify node links
void verify_node_links(Node<int, int>* node, Node<int, int>* expected_next, 
                     Node<int, int>* expected_prev, Node<int, int>* expected_up, 
                     Node<int, int>* expected_down, int expected_key, int expected_val) {
    assert(node != nullptr);
    assert(node->get_key() == expected_key);
    assert(node->get_val() == expected_val);
    assert(node->get_next() == expected_next);
    assert(node->get_prev() == expected_prev);
    assert(node->get_up() == expected_up);
    assert(node->get_down() == expected_down);
}

// Helper function to verify list structure
void verify_list_structure(MyList<int, int>* list, int expected_size) {
    assert(list != nullptr);
    assert(list->length() == expected_size);
    
    if (expected_size == 0) {
        assert(list->begin() == nullptr);
    }
}

void test_default_constructor() {
    // Test default constructor properly initializes first level with default constructor of MyList
    SkipList<int, int> skiplist;
    
    // Verify that there is exactly one level after default construction
    auto levels = skiplist.get_levels();
    assert(levels.size() == 1);
    
    // Verify that the first level is properly initialized (empty list)
    // MyList default constructor sets start = nullptr and size = 0
    assert(levels[0] != nullptr); 
    assert(levels[0]->begin() == nullptr);  
    assert(levels[0]->length() == 0); 
    
    std::cout << "Default constructor test passed!" << std::endl;
}

// Copy Constructor Tests
void test_copy_constructor_nullptr() {
    SkipList<int, int> original;
    SkipList<int, int> copied(original);
    
    auto original_levels = original.get_levels();
    auto copied_levels = copied.get_levels();
    
    // Both should have one level
    assert(original_levels.size() == 1);
    assert(copied_levels.size() == 1);
    
    // Both should be empty
    assert(original_levels[0]->begin() == nullptr);
    assert(copied_levels[0]->begin() == nullptr);
    assert(original_levels[0]->length() == 0);
    assert(copied_levels[0]->length() == 0);
    
    // Should be different objects (deep copy)
    assert(original_levels[0] != copied_levels[0]);
    
    std::cout << "Copy constructor nullptr test passed!" << std::endl;
}

void test_copy_constructor_empty_list() {
    SkipList<int, int> original;
    // Create an empty list with multiple levels by inserting and removing
    Node<int, int>* temp_node = new Node<int, int>(1, 100);
    original.insert(temp_node);

    
    assert(original.remove(1));
    
    SkipList<int, int> copied(original);
    
    auto original_levels = original.get_levels();
    auto copied_levels = copied.get_levels();
    
    // Should have same number of levels
    
    assert(original_levels.size() == copied_levels.size());
        
    // All levels should be empty
    for (size_t i = 0; i < original_levels.size(); i++) {
        assert(original_levels[i]->begin() == nullptr);
        assert(copied_levels[i]->begin() == nullptr);
        assert(original_levels[i]->length() == 0);
        assert(copied_levels[i]->length() == 0);
        // Different objects (deep copy)
        assert(original_levels[i] != copied_levels[i]);
    }
    
    delete temp_node;
    std::cout << "Copy constructor empty list test passed!" << std::endl;
}

void test_copy_constructor_one_node() {
    SkipList<int, int> original;
    Node<int, int>* test_node = new Node<int, int>(5, 500);
    original.insert(test_node);
    
    SkipList<int, int> copied(original);
    
    auto original_levels = original.get_levels();
    auto copied_levels = copied.get_levels();
    
    // Should have same number of levels
    assert(original_levels.size() == copied_levels.size());
    
    // Check each level has the same structure
    for (size_t i = 0; i < original_levels.size(); i++) {
        assert(original_levels[i]->length() == copied_levels[i]->length());
        
        if (original_levels[i]->length() > 0) {
            auto orig_node = original_levels[i]->begin();
            auto copied_node = copied_levels[i]->begin();
            
            // Same values
            assert(orig_node->get_key() == copied_node->get_key());
            assert(orig_node->get_val() == copied_node->get_val());
            
            // But different objects (deep copy)
            assert(orig_node != copied_node);
            
            // Links should be null for single node
            assert(copied_node->get_next() == nullptr);
            assert(copied_node->get_prev() == nullptr);
        }
        
        // Different list objects
        assert(original_levels[i] != copied_levels[i]);
    }
    delete test_node;
    
    std::cout << "Copy constructor one node test passed!" << std::endl;
}

void test_copy_constructor_three_nodes_deep() {
    SkipList<int, int> original;
    
    // Insert three nodes
    Node<int, int>* node1 = new Node<int, int>(1, 100);
    Node<int, int>* node2 = new Node<int, int>(2, 200);
    Node<int, int>* node3 = new Node<int, int>(3, 300);
    original.insert(node1);
    original.insert(node2);
    original.insert(node3);
    
    SkipList<int, int> copied(original);
    
    auto original_levels = original.get_levels();
    auto copied_levels = copied.get_levels();
    
    // Should have same number of levels
    assert(original_levels.size() == copied_levels.size());
    
    // Check deep copy on each level
    for (size_t i = 0; i < original_levels.size(); i++) {
        assert(original_levels[i]->length() == copied_levels[i]->length());
        
        if (original_levels[i]->length() > 0) {
            auto orig_curr = original_levels[i]->begin();
            auto copied_curr = copied_levels[i]->begin();
            
            // Traverse and compare all nodes
            while (orig_curr != nullptr && copied_curr != nullptr) {
                // Same values
                assert(orig_curr->get_key() == copied_curr->get_key());
                assert(orig_curr->get_val() == copied_curr->get_val());
                
                // But different objects (deep copy)
                assert(orig_curr != copied_curr);
                
                // Check next/prev links are properly set up in copy
                if (copied_curr->get_next() != nullptr) {
                    assert(copied_curr->get_next()->get_prev() == copied_curr);
                }
                if (copied_curr->get_prev() != nullptr) {
                    assert(copied_curr->get_prev()->get_next() == copied_curr);
                }
                
                orig_curr = orig_curr->get_next();
                copied_curr = copied_curr->get_next();
            }
            
            // Should reach end of both lists simultaneously
            assert(orig_curr == nullptr);
            assert(copied_curr == nullptr);
        }
        
        // Different list objects
        assert(original_levels[i] != copied_levels[i]);
    }
    
    // Verify deep copy by modifying original and checking copy is unaffected
    Node<int, int>* new_node = new Node<int, int>(4, 400);
    original.insert(new_node);
    
    // Copy should not have the new node
    for (size_t i = 0; i < copied_levels.size(); i++) {
        assert(copied_levels[i]->get_node(4) == nullptr);
    }
    
    delete node1;
    delete node2;
    delete node3;
    delete new_node;
    std::cout << "Copy constructor three nodes deep test passed!" << std::endl;
}

// Move Constructor Tests
void test_move_constructor_nullptr() {
    SkipList<int, int> original;
    SkipList<int, int> moved(std::move(original));
    
    auto moved_levels = moved.get_levels();
    
    // Moved object should have one level
    assert(moved_levels.size() == 1);
    
    // Should be empty
    assert(moved_levels[0]->begin() == nullptr);
    assert(moved_levels[0]->length() == 0);
    
    // Original should be in moved-from state (empty levels)
    auto original_levels = original.get_levels();
    assert(original_levels.size() == 0);
    
    std::cout << "Move constructor nullptr test passed!" << std::endl;
}

void test_move_constructor_empty_list() {
    SkipList<int, int> original;
    // Create empty list with potential multiple levels
    Node<int, int>* temp_node = new Node<int, int>(1, 100);
    original.insert(temp_node);
    original.remove(1);
    
    SkipList<int, int> moved(std::move(original));
    
    auto moved_levels = moved.get_levels();
    auto original_levels = original.get_levels();
    
    // Moved object should have the levels
    assert(moved_levels.size() >= 1);
    
    // All levels should be empty
    for (size_t i = 0; i < moved_levels.size(); i++) {
        assert(moved_levels[i]->begin() == nullptr);
        assert(moved_levels[i]->length() == 0);
    }
    
    // Original should be empty
    assert(original_levels.size() == 0);
    
    delete temp_node;
    std::cout << "Move constructor empty list test passed!" << std::endl;
}

void test_move_constructor_one_node() {
    SkipList<int, int> original;
    Node<int, int>* test_node = new Node<int, int>(5, 500);
    original.insert(test_node);
    
    // Store original level count for verification
    size_t original_level_count = original.get_levels().size();
    
    SkipList<int, int> moved(std::move(original));
    
    auto moved_levels = moved.get_levels();
    auto original_levels = original.get_levels();
    
    // Moved object should have the same number of levels
    assert(moved_levels.size() == original_level_count);
    
    // Should have the node
    bool found_node = false;
    for (size_t i = 0; i < moved_levels.size(); i++) {
        if (moved_levels[i]->get_node(5) != nullptr) {
            found_node = true;
            auto node = moved_levels[i]->get_node(5);
            assert(node->get_key() == 5);
            assert(node->get_val() == 500);
            break;
        }
    }
    assert(found_node);
    
    // Original should be empty
    assert(original_levels.size() == 0);
    
    delete test_node;
    std::cout << "Move constructor one node test passed!" << std::endl;
}

void test_move_constructor_three_nodes() {
    SkipList<int, int> original;
    
    // Insert three nodes
    Node<int, int>* node1 = new Node<int, int>(1, 100);
    Node<int, int>* node2 = new Node<int, int>(2, 200);
    Node<int, int>* node3 = new Node<int, int>(3, 300);
    original.insert(node1);
    original.insert(node2);
    original.insert(node3);
    
    // Store original level count
    size_t original_level_count = original.get_levels().size();
    
    SkipList<int, int> moved(std::move(original));
    
    auto moved_levels = moved.get_levels();
    auto original_levels = original.get_levels();
    
    // Moved object should have the same number of levels
    assert(moved_levels.size() == original_level_count);
    
    // Should have all three nodes
    for (int key = 1; key <= 3; key++) {
        bool found_key = false;
        for (size_t i = 0; i < moved_levels.size(); i++) {
            auto node = moved_levels[i]->get_node(key);
            if (node != nullptr) {
                assert(node->get_key() == key);
                assert(node->get_val() == key * 100);
                found_key = true;
                break;
            }
        }
        assert(found_key);
    }
    
    // Original should be empty
    assert(original_levels.size() == 0);
        
    delete node1;
    delete node2;
    delete node3;
    std::cout << "Move constructor three nodes test passed!" << std::endl;
}

// Assignment Operator Tests
void test_copy_assignment_both_empty() {
    SkipList<int, int> this_list;
    SkipList<int, int> other_list;
        
    this_list = other_list;
        
    auto this_levels = this_list.get_levels();
    auto other_levels = other_list.get_levels();
        
    // Both should have one level
    assert(this_levels.size() == 1);
    assert(other_levels.size() == 1);
        
    // Both should be empty
    assert(this_levels[0]->begin() == nullptr);
    assert(other_levels[0]->begin() == nullptr);
    assert(this_levels[0]->length() == 0);
    assert(other_levels[0]->length() == 0);
        
    // Should be different objects (deep copy)
    assert(this_levels != other_levels);
    assert(this_levels[0] != other_levels[0]);
        
    std::cout << "Copy assignment both empty test passed!" << std::endl;
}

void test_copy_assignment_other_empty_this_three() {
    SkipList<int, int> this_list;
    SkipList<int, int> other_list;

    Node<int, int>* node3 = new Node<int, int>(1, 100);
    Node<int, int>* node4 = new Node<int, int>(2, 200);
    Node<int, int>* node5 = new Node<int, int>(3, 300);
    this_list.insert(node3);
    this_list.insert(node4);
    this_list.insert(node5);
        
    this_list = other_list;
        
    auto this_levels = this_list.get_levels();
    auto other_levels = other_list.get_levels();
        
    // Both should have one level
    assert(this_levels.size() == 1);
    assert(other_levels.size() == 1);
        
    // Both should be empty
    assert(this_levels[0]->begin() == nullptr);
    assert(other_levels[0]->begin() == nullptr);
    assert(this_levels[0]->length() == 0);
    assert(other_levels[0]->length() == 0);
        
    // Should be different objects (deep copy)
    assert(this_levels != other_levels);
    assert(this_levels[0] != other_levels[0]);

    delete node3;
    delete node4;
    delete node5;
        
    std::cout << "Copy assignment other empty this three test passed!" << std::endl;
}

void test_copy_assignment_this_two_other_one() {
    SkipList<int, int> this_list;
    SkipList<int, int> other_list;
        
    // Add two nodes to this_list
    Node<int, int>* node1 = new Node<int, int>(10, 1000);
    Node<int, int>* node2 = new Node<int, int>(20, 2000);
    this_list.insert(node1);
    this_list.insert(node2);
        
    // Add one node to other_list
    Node<int, int>* node3 = new Node<int, int>(5, 500);
    other_list.insert(node3);
        
    // Assign other_list to this_list
    this_list = other_list;
        
    auto this_levels = this_list.get_levels();
    auto other_levels = other_list.get_levels();
        
    // Should have same number of levels
    assert(this_levels.size() == other_levels.size());
        
    // this_list should now have the same content as other_list
    for (size_t i = 0; i < this_levels.size(); i++) {
        assert(this_levels[i]->length() == other_levels[i]->length());
            
        if (other_levels[i]->length() > 0) {
            auto this_node = this_levels[i]->begin();
            auto other_node = other_levels[i]->begin();
                
            // Should have same values
            assert(this_node->get_key() == other_node->get_key());
            assert(this_node->get_val() == other_node->get_val());
                
            // But different objects (deep copy)
            assert(this_node != other_node);
        }
            
        // Different list objects
        assert(this_levels[i] != other_levels[i]);
    }
        
    // Verify this_list no longer has the old nodes
    for (size_t i = 0; i < this_levels.size(); i++) {
        assert(this_levels[i]->get_node(10) == nullptr);
        assert(this_levels[i]->get_node(20) == nullptr);
    }
        
    // Verify this_list now has the new node
    bool found_node = false;
    for (size_t i = 0; i < this_levels.size(); i++) {
        if (this_levels[i]->get_node(5) != nullptr) {
            found_node = true;
            auto node = this_levels[i]->get_node(5);
            assert(node->get_key() == 5);
            assert(node->get_val() == 500);
            break;
        }
    }
    assert(found_node);
        
    // Clean up allocated nodes
    delete node1;
    delete node2;
    delete node3;
        
    std::cout << "Copy assignment this two other one test passed!" << std::endl;
}

void test_copy_assignment_this_two_other_three() {
    SkipList<int, int> this_list;
    SkipList<int, int> other_list;
        
    // Add two nodes to this_list
    Node<int, int>* node1 = new Node<int, int>(10, 1000);
    Node<int, int>* node2 = new Node<int, int>(20, 2000);
    this_list.insert(node1);
    this_list.insert(node2);
        
    // Add three nodes to other_list
    Node<int, int>* node3 = new Node<int, int>(1, 100);
    Node<int, int>* node4 = new Node<int, int>(2, 200);
    Node<int, int>* node5 = new Node<int, int>(3, 300);
    other_list.insert(node3);
    other_list.insert(node4);
    other_list.insert(node5);
        
    // Assign other_list to this_list
    this_list = other_list;
        
    auto this_levels = this_list.get_levels();
    auto other_levels = other_list.get_levels();
        
    // Should have same number of levels
    assert(this_levels.size() == other_levels.size());
        
    // Check deep copy on each level
    for (size_t i = 0; i < this_levels.size(); i++) {
        assert(this_levels[i]->length() == other_levels[i]->length());
            
        if (other_levels[i]->length() > 0) {
            auto this_curr = this_levels[i]->begin();
            auto other_curr = other_levels[i]->begin();
                
            // Traverse and compare all nodes
            while (this_curr != nullptr && other_curr != nullptr) {
                // Same values
                assert(this_curr->get_key() == other_curr->get_key());
                assert(this_curr->get_val() == other_curr->get_val());
                    
                // But different objects (deep copy)
                assert(this_curr != other_curr);
                    
                // Check links are properly set up
                if (this_curr->get_next() != nullptr) {
                    assert(this_curr->get_next()->get_prev() == this_curr);
                }
                if (this_curr->get_prev() != nullptr) {
                    assert(this_curr->get_prev()->get_next() == this_curr);
                }
                    
                this_curr = this_curr->get_next();
                other_curr = other_curr->get_next();
            }
                
            // Should reach end of both lists simultaneously
            assert(this_curr == nullptr);
            assert(other_curr == nullptr);
        }
            
        // Different list objects
        assert(this_levels[i] != other_levels[i]);
    }
        
    // Verify this_list no longer has the old nodes
    for (size_t i = 0; i < this_levels.size(); i++) {
        assert(this_levels[i]->get_node(10) == nullptr);
        assert(this_levels[i]->get_node(20) == nullptr);
    }
        
    // Verify this_list now has the new nodes
    for (int key = 1; key <= 3; key++) {
        bool found_key = false;
        for (size_t i = 0; i < this_levels.size(); i++) {
            if (this_levels[i]->get_node(key) != nullptr) {
                found_key = true;
                auto node = this_levels[i]->get_node(key);
                assert(node->get_key() == key);
                assert(node->get_val() == key * 100);
                break;
            }
        }
        assert(found_key);
    }
        
    // Clean up allocated nodes
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
        
    std::cout << "Copy assignment this two other three test passed!" << std::endl;
}

void test_move_assignment_both_empty(){
    SkipList<int, int> this_list;
    SkipList<int, int> other_list;    
        
    // Move empty other_list to this_list
    this_list = std::move(other_list);
        
    auto this_levels = this_list.get_levels();
    auto other_levels = other_list.get_levels();
        
    // this_list should have one level (from other_list)
    assert(this_levels.size() == 1);
        
    // Should be empty
    assert(this_levels[0]->begin() == nullptr);
    assert(this_levels[0]->length() == 0);
        
    // other_list should be empty after move
    assert(other_levels.size() == 0);

        
    std::cout << "Move assignment both empty test passed!" << std::endl;
}

void test_move_assignment_other_empty_this_three() {
    SkipList<int, int> this_list;
    SkipList<int, int> other_list;
        
    // Add three nodes to this_list
    Node<int, int>* node1 = new Node<int, int>(1, 100);
    Node<int, int>* node2 = new Node<int, int>(2, 200);
    Node<int, int>* node3 = new Node<int, int>(3, 300);
    this_list.insert(node1);
    this_list.insert(node2);
    this_list.insert(node3);
        
    // Move empty other_list to this_list
    this_list = std::move(other_list);
        
    auto this_levels = this_list.get_levels();
    auto other_levels = other_list.get_levels();
        
    // this_list should have one level (from other_list)
    assert(this_levels.size() == 1);
        
    // Should be empty
    assert(this_levels[0]->begin() == nullptr);
    assert(this_levels[0]->length() == 0);
        
    // other_list should be empty after move
    assert(other_levels.size() == 0);
        
    // Clean up allocated nodes
    delete node1;
    delete node2;
    delete node3;
        
    std::cout << "Move assignment other empty this three test passed!" << std::endl;
}

void test_move_assignment_this_two_other_one() {
    SkipList<int, int> this_list;
    SkipList<int, int> other_list;
        
    // Add two nodes to this_list
    Node<int, int>* node1 = new Node<int, int>(10, 1000);
    Node<int, int>* node2 = new Node<int, int>(20, 2000);
    this_list.insert(node1);
    this_list.insert(node2);
        
    // Add one node to other_list
    Node<int, int>* node3 = new Node<int, int>(5, 500);
    other_list.insert(node3);
        
    // Store original level count
    size_t other_level_count = other_list.get_levels().size();
        
    // Move other_list to this_list
    this_list = std::move(other_list);
        
    auto this_levels = this_list.get_levels();
    auto other_levels = other_list.get_levels();
        
    // this_list should have the same number of levels as other_list had
    assert(this_levels.size() == other_level_count);
        
    // Should have the node from other_list
    bool found_node = false;
    for (size_t i = 0; i < this_levels.size(); i++) {
        if (this_levels[i]->get_node(5) != nullptr) {
            found_node = true;
            auto node = this_levels[i]->get_node(5);
            assert(node->get_key() == 5);
            assert(node->get_val() == 500);
            break;
        }
    }
    assert(found_node);
        
    // Should not have the old nodes
    for (size_t i = 0; i < this_levels.size(); i++) {
        assert(this_levels[i]->get_node(10) == nullptr);
        assert(this_levels[i]->get_node(20) == nullptr);
    }
        
    // other_list should be empty after move
    assert(other_levels.size() == 0);
        
    // Clean up allocated nodes
    delete node1;
    delete node2;
    delete node3;
        
    std::cout << "Move assignment this two other one test passed!" << std::endl;
}

void test_move_assignment_this_two_other_three() {
    SkipList<int, int> this_list;
    SkipList<int, int> other_list;
        
    // Add two nodes to this_list
    Node<int, int>* node1 = new Node<int, int>(10, 1000);
    Node<int, int>* node2 = new Node<int, int>(20, 2000);
    this_list.insert(node1);
    this_list.insert(node2);
        
    // Add three nodes to other_list
    Node<int, int>* node3 = new Node<int, int>(1, 100);
    Node<int, int>* node4 = new Node<int, int>(2, 200);
    Node<int, int>* node5 = new Node<int, int>(3, 300);
    other_list.insert(node3);
    other_list.insert(node4);
    other_list.insert(node5);
        
    // Store original level count
    size_t other_level_count = other_list.get_levels().size();
        
    // Move other_list to this_list
    this_list = std::move(other_list);
        
    auto this_levels = this_list.get_levels();
    auto other_levels = other_list.get_levels();
        
    // this_list should have the same number of levels as other_list had
    assert(this_levels.size() == other_level_count);
        
    // Should have all three nodes from other_list
    for (int key = 1; key <= 3; key++) {
        bool found_key = false;
        for (size_t i = 0; i < this_levels.size(); i++) {
            if (this_levels[i]->get_node(key) != nullptr) {
                found_key = true;
                auto node = this_levels[i]->get_node(key);
                assert(node->get_key() == key);
                assert(node->get_val() == key * 100);
                break;
            }
        }
        assert(found_key);
    }
        
    // Should not have the old nodes
    for (size_t i = 0; i < this_levels.size(); i++) {
        assert(this_levels[i]->get_node(10) == nullptr);
        assert(this_levels[i]->get_node(20) == nullptr);
    }
        
    // other_list should be empty after move
    assert(other_levels.size() == 0);
        
    // Clean up allocated nodes
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
        
    std::cout << "Move assignment this two other three test passed!" << std::endl;
}

int main() {
    test_default_constructor();
        
    // ... (rest of the code remains the same)
    test_copy_constructor_nullptr();
    test_copy_constructor_empty_list();
    test_copy_constructor_one_node();
    test_copy_constructor_three_nodes_deep();
    
    // Move constructor tests
    test_move_constructor_nullptr();
    test_move_constructor_empty_list();
    test_move_constructor_one_node();
    test_move_constructor_three_nodes();
    
    // Copy assignment operator tests
    test_copy_assignment_both_empty();
    test_copy_assignment_other_empty_this_three();
    test_copy_assignment_this_two_other_one();
    test_copy_assignment_this_two_other_three();
    
    // Move assignment operator tests
    test_move_assignment_both_empty();
    test_move_assignment_other_empty_this_three();
    test_move_assignment_this_two_other_one();
    test_move_assignment_this_two_other_three();
    
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}