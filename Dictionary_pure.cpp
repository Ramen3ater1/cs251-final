#include "Dictionary_pure.h"
#include <sstream>


//create empty dictionary
Dictionary_Pure::Dictionary_Pure() : root(nullptr) {}
Dictionary_Pure::Dictionary_Pure(std::shared_ptr<Node> r): root(r) {}
Dictionary_Pure::Dictionary_Pure(const Dictionary_Pure &other) : root(other.root) {}

//find if key is in dictionary
bool Dictionary_Pure::contains(const std::string &key) const {
    //start from root node
    std::shared_ptr<Node> current = root;
    while (current != nullptr) {
        if (key == current->key) {
            return true;
        }
        //left key is smaller, right key is larger
        //if the key we are looking for is smaller than current key: go to left
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }   //current == nullptr: reached bottom
    return false;
}

int Dictionary_Pure::lookup(const std::string &key) const {
    //start from root node
    std::shared_ptr<Node> current = root;
    while (current != nullptr) {
        if (key == current->key) {
            return current->value;
        }
        //left key is smaller, right key is larger
        //if the key we are looking for is smaller than current 
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    throw std::runtime_error("key not found");
}

Dictionary_Pure Dictionary_Pure::add(const std::string &key, int value) const {
    return Dictionary_Pure(add_node(root, key, value));
}

//pure functional BST can't edit existing node, so it will create a new tree to return
std::shared_ptr<Dictionary_Pure::Node> Dictionary_Pure::add_node(const std::shared_ptr<Node> &node, const std::string &key, int value) {
    //found the right place to add node
    if (node == nullptr) {
        //create a new node
        return std::make_shared<Node>(key, value);
    }
    //
    if (key < node->key) {
        //if the key we are looking for is smaller than current 
        //in this case we need to make a new node
        return std::make_shared<Node>(
            node->key,
            node->value,    //copy key and node
            add_node(node->left, key, value),   //recursive
            node->right     //copy child
        );
    } else if (key > node->key){
        return std::make_shared<Node>(
            node->key,
            node->value,
            node->left,
            add_node(node->right, key, value)
        );
    } else {
        //key == node->key (key already exist => update value)
        return std::make_shared<Node>(
            node->key,
            value,
            node->left,
            node->right
        );
    }
}

#include <doctest.h>
#include <stdexcept>
#include <string>


TEST_CASE("empty dictionary") {
    Dictionary_Pure d;

    CHECK(d.contains("apple") == false);
    CHECK_THROWS_AS(d.lookup("apple"), std::runtime_error);
}

TEST_CASE("add one key") {
    Dictionary_Pure d;
    Dictionary_Pure d2 = d.add("apple", 10);

    CHECK(d.contains("apple") == false);
    CHECK(d2.contains("apple") == true);
    CHECK(d2.lookup("apple") == 10);
}

TEST_CASE("add multiple keys and lookup") {
    Dictionary_Pure d;
    Dictionary_Pure d2 = d.add("mango", 5);
    Dictionary_Pure d3 = d2.add("apple", 10);
    Dictionary_Pure d4 = d3.add("zebra", 20);

    CHECK(d4.contains("mango") == true);
    CHECK(d4.contains("apple") == true);
    CHECK(d4.contains("zebra") == true);

    CHECK(d4.lookup("mango") == 5);
    CHECK(d4.lookup("apple") == 10);
    CHECK(d4.lookup("zebra") == 20);
}

TEST_CASE("lookup missing key throws") {
    Dictionary_Pure d;
    Dictionary_Pure d2 = d.add("apple", 10);

    CHECK_THROWS_AS(d2.lookup("banana"), std::runtime_error);
}

TEST_CASE("contains works for missing and existing keys") {
    Dictionary_Pure d;
    Dictionary_Pure d2 = d.add("cat", 1).add("apple", 2).add("dog", 3);

    CHECK(d2.contains("cat") == true);
    CHECK(d2.contains("apple") == true);
    CHECK(d2.contains("dog") == true);
    CHECK(d2.contains("banana") == false);
}

TEST_CASE("pure functional behavior old versions stay unchanged") {
    Dictionary_Pure d0;
    Dictionary_Pure d1 = d0.add("b", 2);
    Dictionary_Pure d2 = d1.add("a", 1);
    Dictionary_Pure d3 = d2.add("c", 3);

    CHECK(d0.contains("a") == false);
    CHECK(d0.contains("b") == false);
    CHECK(d0.contains("c") == false);

    CHECK(d1.contains("b") == true);
    CHECK(d1.contains("a") == false);
    CHECK(d1.contains("c") == false);

    CHECK(d2.contains("b") == true);
    CHECK(d2.contains("a") == true);
    CHECK(d2.contains("c") == false);

    CHECK(d3.contains("a") == true);
    CHECK(d3.contains("b") == true);
    CHECK(d3.contains("c") == true);
}

TEST_CASE("updating existing key replaces value") {
    Dictionary_Pure d;
    Dictionary_Pure d2 = d.add("apple", 10);
    Dictionary_Pure d3 = d2.add("apple", 99);

    CHECK(d2.lookup("apple") == 10);
    CHECK(d3.lookup("apple") == 99);
}

TEST_CASE("copy constructor keeps old version independent under add") {
    Dictionary_Pure d0;
    Dictionary_Pure d1 = d0.add("mango", 5).add("apple", 10);

    Dictionary_Pure copy(d1);
    Dictionary_Pure d2 = copy.add("zebra", 20);

    CHECK(copy.contains("mango") == true);
    CHECK(copy.contains("apple") == true);
    CHECK(copy.contains("zebra") == false);

    CHECK(d2.contains("mango") == true);
    CHECK(d2.contains("apple") == true);
    CHECK(d2.contains("zebra") == true);

    CHECK(copy.lookup("mango") == 5);
    CHECK(copy.lookup("apple") == 10);
    CHECK(d2.lookup("zebra") == 20);
}