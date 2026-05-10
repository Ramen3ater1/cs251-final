//
// Created by davew on 11/17/22.
//

#include "Dictionary_pure_via_std_map.h"
#include "logic.h"

// This is a "cheat" in which we actually have a (potentially very slow) imperative implementation
//  to fit the pure-functional approach. So, ignore the implementation here, and focus on the _tests_
//  below. In the lab, you'll implement this in a way that's true to the spirit of the paradigm.

Dictionary_pure_via_std_map Dictionary_pure_via_std_map::add(const std::string &key, int value) const {
    Dictionary_pure_via_std_map result(*this); // No idea what the complexity is, here.
    result.contents[key] = value;
    return result;
}

bool Dictionary_pure_via_std_map::contains(const std::string &key) const {
    return contents.contains(key);
}

int Dictionary_pure_via_std_map::lookup(const std::string &key) const {
    // could make "contains" a precondition, but want to let code rely on the exception we throw
    if (contents.contains(key)) {
        std::map<std::string, int>::const_iterator found = contents.find(key );
        hccs_assert(found != contents.end()); // we actually found something
        return found->second;  // second is the value, I think; see https://en.cppreference.com/w/cpp/container/map/find
    } else {
        throw "Out of luck";
    }
}



#include <doctest.h>

// function is defined below, after the interesting part of the test
static Dictionary_pure_via_std_map build_example_primes_3_to_31();

TEST_CASE("Dictionary insertion and lookup (pure), simple examples")
{
    // Assume primes_3_to_31_f contains 3, 5, 7, 11, 13, 17, 19, 23, 29, 31),
    // we'll contrast this with pure-functional primes_3_to_31_f, in the other file;
    // the former has imperative operations and the latter pure-functional
    Dictionary_pure_via_std_map primes_3_to_31_f = build_example_primes_3_to_31();

    // initially, that dictionary contains, e.g., 7, but not 9
    CHECK(      primes_3_to_31_f.contains("7"));
    CHECK_FALSE(primes_3_to_31_f.contains("9"));

    // Now, the distinction between pure and imperative ... we build a fresh object, leaving the original intact
    Dictionary_pure_via_std_map primes_3_to_31_f_9 = primes_3_to_31_f.add("9", 9);

    // now, the _new_ pure one one should contain, e.g., 7 ... and also 9, though the original is unchanged!
    CHECK(      primes_3_to_31_f.contains("7"));
    CHECK_FALSE(primes_3_to_31_f.contains("9"));    // UNLIKE the imperative "insert", pure "add" leaves this alone
    CHECK(      primes_3_to_31_f_9.contains("7"));  // We still have all the old stuff, including 7
    CHECK(      primes_3_to_31_f_9.contains("9"));  // as well as the 9, in the one with 9.
}

TEST_CASE("Dictionary insertion and lookup (pure), more complicated but more complete")
{
    Dictionary_pure_via_std_map primes_3_to_31_f = build_example_primes_3_to_31();

    // A more exhaustive test, the simpler-but-clearer one is below
    for (int i=3; i<33; i++) { // note: all composites less than 49 have a factor of 2, 3, or 5
        CHECK(primes_3_to_31_f.contains(std::to_string(i)) ==
              (i==3 or i==5 or !((i%2 == 0) or (i%3 == 0) or (i%5==0))));
        if (primes_3_to_31_f.contains(std::to_string(i))) {         // being in the dictionary implies ..
            CHECK(primes_3_to_31_f.lookup(std::to_string(i)) == i); // ... we'll get the final value
        }
    }

    // Now, the distinction between pure and imperative ... we build a fresh object, leaving the original intact
    Dictionary_pure_via_std_map primes_3_to_31_f_9 = primes_3_to_31_f.add("9", 9);

    // confirm we didn't break the original:
    for (int i=3; i<33; i++) { // note: all composites less than 49 have a factor of 2, 3, or 5
        CHECK(primes_3_to_31_f.contains(std::to_string(i)) ==
              (i==3 or i==5 or !((i%2 == 0) or (i%3 == 0) or (i%5==0))));
        if (primes_3_to_31_f.contains(std::to_string(i))) {         // being in the dictionary implies ..
            CHECK(primes_3_to_31_f.lookup(std::to_string(i)) == i); // ... we'll get the final value
        }
    }

    // confirm that the new one is like the original but with 9:
    for (int i=3; i<33; i++) { // note: all composites less than 49 have a factor of 2, 3, or 5
        CHECK(primes_3_to_31_f_9.contains(std::to_string(i)) ==
              ((i == 9) or // AFTER THE CHANGE, WE ACCEPT 9 too
               (i == 3 or i == 5 or !((i % 2 == 0) or (i % 3 == 0) or (i % 5 == 0)))));
        if (primes_3_to_31_f_9.contains(std::to_string(i))) {         // being in the dictionary implies ..
            CHECK(primes_3_to_31_f_9.lookup(std::to_string(i)) == i); // ... we'll get the final value
        }
    }
}

static Dictionary_pure_via_std_map build_example_primes_3_to_31()
{
    Dictionary_pure_via_std_map p;

    // Build the example Dictionary from the comment, above: contains 3, 5, 7, 11, 13, 17, 19, 23, 29, 31.
    // Note that we do some of them in two steps, to be sure re-adding a new value doesn't create issues:

    Dictionary_pure_via_std_map p11x = p.add("11", -1); // -1 indicated we'll later add a different ...
    Dictionary_pure_via_std_map p7x  = p11x.add("7", -1);  // ... this value in this test
    Dictionary_pure_via_std_map p3   = p7x.add("3", 3);
    Dictionary_pure_via_std_map p5x  = p3.add("5", -1);

    Dictionary_pure_via_std_map p5   = p5x.add("5", 5);  // "update" fresh dictionary ...
    Dictionary_pure_via_std_map p7   = p5.add("7", 7);   // again ...

    Dictionary_pure_via_std_map p19  = p7.add("19", 19);
    Dictionary_pure_via_std_map p13  = p19.add("13", 13);
    Dictionary_pure_via_std_map p17x = p13.add("17", -1);
    Dictionary_pure_via_std_map p29x = p17x.add("29", -1);
    Dictionary_pure_via_std_map p17  = p29x.add("17", 17); // and again ...
    Dictionary_pure_via_std_map p23  = p17.add("23", 23);
    Dictionary_pure_via_std_map p29  = p23.add("29", 29); // one more time...
    Dictionary_pure_via_std_map p31  = p29.add("31", 31);

    Dictionary_pure_via_std_map primes_3_to_31_f = p31.add("11", 11);  // finally, update what was the root

    return primes_3_to_31_f;
}
