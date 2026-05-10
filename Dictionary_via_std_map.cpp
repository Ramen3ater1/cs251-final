//
// Created by davew on 11/17/22.
//

#include "Dictionary_via_std_map.h"
#include "logic.h"

void Dictionary_via_std_map::insert(const std::string &key, int value) {
    contents[key] = value;
}

bool Dictionary_via_std_map::contains(const std::string &key) const {
    return contents.contains(key);
}

int Dictionary_via_std_map::lookup(const std::string &key) const {
    // could make "contains" a precondition, but want to let code rely on the exception we throw
    if (contents.contains(key)) {
        // ToDo: ask about a cleaner way to do lookup without having to create iterator?
        std::map<std::string, int>::const_iterator found = contents.find(key );
        hccs_assert(found != contents.end()); // we actually found something
        return found->second;  // second is the value, I think; see https://en.cppreference.com/w/cpp/container/map/find
    } else {
        throw "Out of luck";
    }
}

Dictionary_via_std_map Dictionary_via_std_map::checkpoint() {
    return *this;
}

void Dictionary_via_std_map::restore(const Dictionary_via_std_map &a_checkpoint) {
    *this = a_checkpoint;
}



#include <doctest.h>

// function is defined below, after the interesting part of the test
static Dictionary_via_std_map build_example_primes_3_to_31();

TEST_CASE("Dictionary insertion and lookup (imperative), simple examples")
{
    // Assume primes_3_to_31_i contains 3, 5, 7, 11, 13, 17, 19, 23, 29, 31),
    // we'll contrast this with pure-functional primes_3_to_31_f, in the other file;
    // the former has imperative operations and the latter pure-functional
    Dictionary_via_std_map primes_3_to_31_i = build_example_primes_3_to_31();

    // initially, that dictionary contains, e.g., 7, but not 9
    CHECK(      primes_3_to_31_i.contains("7"));
    CHECK_FALSE(primes_3_to_31_i.contains("9"));

    // Now, the distinction between pure and imperative ... we _change_ an object
    primes_3_to_31_i.insert("9", 9);

    // now, the imperative one should contain, e.g., 7 ... and some contain 9
    CHECK(      primes_3_to_31_i.contains("7"));
    CHECK(      primes_3_to_31_i.contains("9"));    // now this has 9 ... note the pure-functional one would _not_
}

TEST_CASE("Dictionary insertion and lookup (imperative), more complicated but more complete")
{
    Dictionary_via_std_map primes_3_to_31_i = build_example_primes_3_to_31();

    // A more exhaustive test, the simpler-but-clearer one is below
    for (int i=3; i<33; i++) { // note: all composites less than 49 have a factor of 2, 3, or 5
        CHECK(primes_3_to_31_i.contains(std::to_string(i)) ==
              (i==3 or i==5 or !((i%2 == 0) or (i%3 == 0) or (i%5==0))));
        if (primes_3_to_31_i.contains(std::to_string(i))) {         // being in the dictionary implies ..
            CHECK(primes_3_to_31_i.lookup(std::to_string(i)) == i); // ... we'll get the final value
        }
    }

    // Now, the distinction between pure and imperative ... we _change_ an object (which the "build" actually did too)
    primes_3_to_31_i.insert("9", 9);

    for (int i=3; i<33; i++) { // note: all composites less than 49 have a factor of 2, 3, or 5
        CHECK(primes_3_to_31_i.contains(std::to_string(i)) == ((i == 9) or // AFTER THE CHANGE, WE ACCEPT 9 too
              (i == 3 or i == 5 or !((i % 2 == 0) or (i % 3 == 0) or (i % 5 == 0)))));
        if (primes_3_to_31_i.contains(std::to_string(i))) {         // being in the dictionary implies ..
            CHECK(primes_3_to_31_i.lookup(std::to_string(i)) == i); // ... we'll get the final value
        }
    }
}

static Dictionary_via_std_map build_example_primes_3_to_31()
{
    Dictionary_via_std_map primes_3_to_31_i;

    // Build the example Dictionary from the comment, above: contains 3, 5, 7, 11, 13, 17, 19, 23, 29, 31.
    // Note that we do some of them in two steps, to be sure replacement doesn't create issues:

    primes_3_to_31_i.insert("11", -1); // -1 indicated we'll overwrite ...
    primes_3_to_31_i.insert("7", -1);  // ... this value in this test
    primes_3_to_31_i.insert("3", 3);
    primes_3_to_31_i.insert("5", -1);

    primes_3_to_31_i.insert("5", 5);  // update dictionary
    primes_3_to_31_i.insert("7", 7);  // again

    primes_3_to_31_i.insert("19", 19);
    primes_3_to_31_i.insert("13", 13);
    primes_3_to_31_i.insert("17", -1);
    primes_3_to_31_i.insert("29", -1);
    primes_3_to_31_i.insert("17", 17); // update
    primes_3_to_31_i.insert("23", 23);
    primes_3_to_31_i.insert("29", 29); // one more time...
    primes_3_to_31_i.insert("31", 31);

    primes_3_to_31_i.insert("11", 11);  // finally, update what was the root

    return primes_3_to_31_i;
}

