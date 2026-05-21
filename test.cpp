#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Dictionary_hash.h"

#include <stdexcept>
#include <string>

TEST_CASE("empty dictionary has no keys") {
    Dictionary_Hash d;

    CHECK(d.contains("apple") == false);
    CHECK(d.contains("banana") == false);
    CHECK(d.contains("") == false);
}

TEST_CASE("lookup on empty dictionary throws") {
    Dictionary_Hash d;

    CHECK_THROWS_AS(d.lookup("apple"), std::runtime_error);
    CHECK_THROWS_AS(d.lookup(""), std::runtime_error);
}

TEST_CASE("add one key") {
    Dictionary_Hash d1;

    Dictionary_Hash d2 = d1.add("apple", 10);

    CHECK(d1.contains("apple") == false);

    CHECK(d2.contains("apple") == true);
    CHECK(d2.lookup("apple") == 10);
}

TEST_CASE("add multiple keys and lookup them") {
    Dictionary_Hash d1;

    Dictionary_Hash d2 = d1.add("apple", 10);
    Dictionary_Hash d3 = d2.add("banana", 20);
    Dictionary_Hash d4 = d3.add("cat", 30);
    Dictionary_Hash d5 = d4.add("dog", 40);

    CHECK(d5.contains("apple") == true);
    CHECK(d5.contains("banana") == true);
    CHECK(d5.contains("cat") == true);
    CHECK(d5.contains("dog") == true);

    CHECK(d5.lookup("apple") == 10);
    CHECK(d5.lookup("banana") == 20);
    CHECK(d5.lookup("cat") == 30);
    CHECK(d5.lookup("dog") == 40);
}

TEST_CASE("lookup missing key after adding other keys throws") {
    Dictionary_Hash d;

    d = d.add("apple", 10);
    d = d.add("banana", 20);

    CHECK(d.contains("cat") == false);
    CHECK_THROWS_AS(d.lookup("cat"), std::runtime_error);
}

TEST_CASE("add does not modify old dictionary") {
    Dictionary_Hash d1;

    Dictionary_Hash d2 = d1.add("apple", 10);
    Dictionary_Hash d3 = d2.add("banana", 20);
    Dictionary_Hash d4 = d3.add("cat", 30);

    CHECK(d1.contains("apple") == false);
    CHECK(d1.contains("banana") == false);
    CHECK(d1.contains("cat") == false);

    CHECK(d2.contains("apple") == true);
    CHECK(d2.lookup("apple") == 10);
    CHECK(d2.contains("banana") == false);
    CHECK(d2.contains("cat") == false);

    CHECK(d3.contains("apple") == true);
    CHECK(d3.contains("banana") == true);
    CHECK(d3.lookup("apple") == 10);
    CHECK(d3.lookup("banana") == 20);
    CHECK(d3.contains("cat") == false);

    CHECK(d4.contains("apple") == true);
    CHECK(d4.contains("banana") == true);
    CHECK(d4.contains("cat") == true);
    CHECK(d4.lookup("apple") == 10);
    CHECK(d4.lookup("banana") == 20);
    CHECK(d4.lookup("cat") == 30);
}

TEST_CASE("updating existing key returns new dictionary") {
    Dictionary_Hash d1;

    Dictionary_Hash d2 = d1.add("apple", 10);
    Dictionary_Hash d3 = d2.add("apple", 99);

    CHECK(d2.contains("apple") == true);
    CHECK(d3.contains("apple") == true);

    CHECK(d2.lookup("apple") == 10);
    CHECK(d3.lookup("apple") == 99);
}

TEST_CASE("updating one key does not affect other keys") {
    Dictionary_Hash d1;

    Dictionary_Hash d2 = d1.add("apple", 10);
    Dictionary_Hash d3 = d2.add("banana", 20);
    Dictionary_Hash d4 = d3.add("apple", 99);

    CHECK(d3.lookup("apple") == 10);
    CHECK(d3.lookup("banana") == 20);

    CHECK(d4.lookup("apple") == 99);
    CHECK(d4.lookup("banana") == 20);
}

TEST_CASE("updating same key multiple times keeps versions separate") {
    Dictionary_Hash d1;

    Dictionary_Hash d2 = d1.add("apple", 10);
    Dictionary_Hash d3 = d2.add("apple", 20);
    Dictionary_Hash d4 = d3.add("apple", 30);
    Dictionary_Hash d5 = d4.add("apple", 40);

    CHECK(d1.contains("apple") == false);

    CHECK(d2.lookup("apple") == 10);
    CHECK(d3.lookup("apple") == 20);
    CHECK(d4.lookup("apple") == 30);
    CHECK(d5.lookup("apple") == 40);
}

TEST_CASE("empty string key works") {
    Dictionary_Hash d1;

    Dictionary_Hash d2 = d1.add("", 123);

    CHECK(d1.contains("") == false);

    CHECK(d2.contains("") == true);
    CHECK(d2.lookup("") == 123);
}

TEST_CASE("negative and zero values work") {
    Dictionary_Hash d1;

    Dictionary_Hash d2 = d1.add("zero", 0);
    Dictionary_Hash d3 = d2.add("negative", -10);

    CHECK(d3.lookup("zero") == 0);
    CHECK(d3.lookup("negative") == -10);
}

TEST_CASE("many keys can be added and looked up") {
    Dictionary_Hash d;

    for (int i = 0; i < 100; i++) {
        d = d.add("key" + std::to_string(i), i);
    }

    for (int i = 0; i < 100; i++) {
        CHECK(d.contains("key" + std::to_string(i)) == true);
        CHECK(d.lookup("key" + std::to_string(i)) == i);
    }
}

TEST_CASE("resize and rehash preserve all keys") {
    Dictionary_Hash d;

    for (int i = 0; i < 200; i++) {
        d = d.add("item" + std::to_string(i), i * 10);
    }

    for (int i = 0; i < 200; i++) {
        CHECK(d.contains("item" + std::to_string(i)) == true);
        CHECK(d.lookup("item" + std::to_string(i)) == i * 10);
    }
}

TEST_CASE("old dictionary remains valid after later resize") {
    Dictionary_Hash d1;

    Dictionary_Hash d2 = d1.add("apple", 10);

    Dictionary_Hash d3 = d2;

    for (int i = 0; i < 200; i++) {
        d3 = d3.add("key" + std::to_string(i), i);
    }

    CHECK(d2.contains("apple") == true);
    CHECK(d2.lookup("apple") == 10);
    CHECK(d2.contains("key100") == false);

    CHECK(d3.contains("apple") == true);
    CHECK(d3.lookup("apple") == 10);
    CHECK(d3.contains("key100") == true);
    CHECK(d3.lookup("key100") == 100);
}

TEST_CASE("copy constructor copies dictionary contents") {
    Dictionary_Hash d1;

    d1 = d1.add("apple", 10);
    d1 = d1.add("banana", 20);

    Dictionary_Hash d2(d1);

    CHECK(d2.contains("apple") == true);
    CHECK(d2.contains("banana") == true);

    CHECK(d2.lookup("apple") == 10);
    CHECK(d2.lookup("banana") == 20);
}

TEST_CASE("copy constructor keeps pure functional behavior") {
    Dictionary_Hash d1;

    d1 = d1.add("apple", 10);

    Dictionary_Hash d2(d1);
    Dictionary_Hash d3 = d2.add("apple", 99);

    CHECK(d1.lookup("apple") == 10);
    CHECK(d2.lookup("apple") == 10);
    CHECK(d3.lookup("apple") == 99);
}

TEST_CASE("assignment operator copies dictionary contents") {
    Dictionary_Hash d1;
    Dictionary_Hash d2;

    d1 = d1.add("apple", 10);
    d1 = d1.add("banana", 20);

    d2 = d1;

    CHECK(d2.contains("apple") == true);
    CHECK(d2.contains("banana") == true);

    CHECK(d2.lookup("apple") == 10);
    CHECK(d2.lookup("banana") == 20);
}

TEST_CASE("assignment operator replaces old contents") {
    Dictionary_Hash d1;
    Dictionary_Hash d2;

    d1 = d1.add("apple", 10);

    d2 = d2.add("cat", 30);
    d2 = d2.add("dog", 40);

    d2 = d1;

    CHECK(d2.contains("apple") == true);
    CHECK(d2.lookup("apple") == 10);

    CHECK(d2.contains("cat") == false);
    CHECK(d2.contains("dog") == false);
}

TEST_CASE("assignment keeps versions separate") {
    Dictionary_Hash d1;

    d1 = d1.add("apple", 10);

    Dictionary_Hash d2;
    d2 = d1;

    Dictionary_Hash d3 = d2.add("banana", 20);

    CHECK(d1.contains("apple") == true);
    CHECK(d1.lookup("apple") == 10);
    CHECK(d1.contains("banana") == false);

    CHECK(d2.contains("apple") == true);
    CHECK(d2.lookup("apple") == 10);
    CHECK(d2.contains("banana") == false);

    CHECK(d3.contains("apple") == true);
    CHECK(d3.contains("banana") == true);
    CHECK(d3.lookup("banana") == 20);
}

TEST_CASE("self assignment does not break dictionary") {
    Dictionary_Hash d;

    d = d.add("apple", 10);
    d = d.add("banana", 20);

    d = d;

    CHECK(d.contains("apple") == true);
    CHECK(d.contains("banana") == true);

    CHECK(d.lookup("apple") == 10);
    CHECK(d.lookup("banana") == 20);
}

TEST_CASE("contains remains correct after updates and resize") {
    Dictionary_Hash d;

    for (int i = 0; i < 150; i++) {
        d = d.add("key" + std::to_string(i), i);
    }

    for (int i = 0; i < 150; i += 2) {
        d = d.add("key" + std::to_string(i), i + 1000);
    }

    for (int i = 0; i < 150; i++) {
        CHECK(d.contains("key" + std::to_string(i)) == true);

        if (i % 2 == 0) {
            CHECK(d.lookup("key" + std::to_string(i)) == i + 1000);
        } else {
            CHECK(d.lookup("key" + std::to_string(i)) == i);
        }
    }

    CHECK(d.contains("not_found") == false);
    CHECK_THROWS_AS(d.lookup("not_found"), std::runtime_error);
}