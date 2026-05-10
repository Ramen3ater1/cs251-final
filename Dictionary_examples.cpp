//
// Created by davew on 11/28/22.
//

#include "Dictionary.h"
#include <logic.h>


void dict_example_pure()
{
    std::cout<< "Starting Dictionary_Pure Example code" << std::endl;

    const Dictionary_Pure d1_a;
    const Dictionary_Pure d1_b = d1_a.add("Steven", 1989);
    const Dictionary_Pure d1 = d1_b.add("Dave", 1995).add("Sorelle", 2016).add("Sara", 2019);

    hccs_assert(d1.contains("Sorelle"));
    hccs_assert(d1.contains("Dave"));
    hccs_assert(d1.contains("Sara"));
    hccs_assert(d1.contains("Steven"));
    hccs_assert(!d1.contains("Jeova"));

    hccs_assert(d1.lookup("Sorelle") == 2016);
    hccs_assert(d1.lookup("Dave") == 1995);
    hccs_assert(d1.lookup("Sara") == 2019);
    hccs_assert(d1.lookup("Steven") == 1989);
    try {
        int unused = d1.lookup("Jeova");  // this should fail
        std::cerr << "Oops, shouldn't even get here" << std::endl;
        hccs_assert(false); // cause assertion failure
        if (unused) return; // unnecessary, but I couldn't figure out how to disable warning for this one line
    } catch (...) {
        ; // do nothing, we just wanted to be sure we got here instead of that "print"
    }

    const Dictionary_Pure d1_old = d1;  // never need to deep-copy, in pure-functional approach

    const Dictionary_Pure d2 = d1.add("Jeova", 2021).add("Dave", 1892);
    // Note "Dave" has value 1892 in d2, but not d1 or d1_old.

    hccs_assert(d2.contains("Jeova"));
    hccs_assert(d2.lookup("Jeova") == 2021);
    hccs_assert(d2.contains("Dave"));
    hccs_assert(d2.lookup("Dave") == 1892);

    // No need to explicitly restore here, just keep using d1 or d1_old, neither has changed!bbb

    hccs_assert(d1.lookup("Sorelle") == 2016);
    hccs_assert(d1.lookup("Dave") == 1995);
    hccs_assert(d1.lookup("Sara") == 2019);
    hccs_assert(d1.lookup("Steven") == 1989);

    hccs_assert(d1.contains("Sorelle"));
    hccs_assert(d1.contains("Dave"));
    hccs_assert(d1.contains("Sara"));
    hccs_assert(d1.contains("Steven"));
    hccs_assert(!d1.contains("Jeova"));

    hccs_assert(d1_old.lookup("Sorelle") == 2016);
    hccs_assert(d1_old.lookup("Dave") == 1995);
    hccs_assert(d1_old.lookup("Sara") == 2019);
    hccs_assert(d1_old.lookup("Steven") == 1989);

    hccs_assert(d1_old.contains("Sorelle"));
    hccs_assert(d1_old.contains("Dave"));
    hccs_assert(d1_old.contains("Sara"));
    hccs_assert(d1_old.contains("Steven"));
    hccs_assert(!d1_old.contains("Jeova"));

    std::cout<< "Finished Dictionary_Pure Example" << std::endl;
    std::cout << std::endl;
}


void dict_exammple_imp()
{
    std::cout<< "Starting Dictionary_Imp Example use code" << std::endl;

    Dictionary_Imp d1;
    d1.insert("Steven", 1989);
    d1.insert("Dave", 1995);
    d1.insert("Sorelle", 2016);
    d1.insert("Sara", 2019);

    hccs_assert(d1.contains("Sorelle"));
    hccs_assert(d1.contains("Dave"));
    hccs_assert(d1.contains("Sara"));
    hccs_assert(d1.contains("Steven"));
    hccs_assert(!d1.contains("Jeova"));

    hccs_assert(d1.lookup("Sorelle") == 2016);
    hccs_assert(d1.lookup("Dave") == 1995);
    hccs_assert(d1.lookup("Sara") == 2019);
    hccs_assert(d1.lookup("Steven") == 1989);
    try {
        int unused = d1.lookup("Jeova");  // this should fail
        std::cerr << "Oops, shouldn't even get here" << std::endl;
        hccs_assert(false); // cause assertion failure
        if (unused) return; // unnecessary, but I couldn't figure out how to disable warning for this one line
    } catch (...) {
        ; // do nothing, we just wanted to be sure we got here instead of that "print"
    }

    Dictionary_Imp_backup d1_old = d1.checkpoint();

    d1.insert("Jeova", 2021);
    d1.insert("Dave", 1892); // replaces original Dave value

    hccs_assert(d1.contains("Jeova"));
    hccs_assert(d1.lookup("Jeova") == 2021);
    hccs_assert(d1.contains("Dave"));
    hccs_assert(d1.lookup("Dave") == 1892);

    d1.restore(d1_old);

    hccs_assert(d1.lookup("Sorelle") == 2016);
    hccs_assert(d1.lookup("Dave") == 1995);
    hccs_assert(d1.lookup("Sara") == 2019);
    hccs_assert(d1.lookup("Steven") == 1989);

    hccs_assert(d1.contains("Sorelle"));
    hccs_assert(d1.contains("Dave"));
    hccs_assert(d1.contains("Sara"));
    hccs_assert(d1.contains("Steven"));
    hccs_assert(!d1.contains("Jeova"));

    std::cout<< "Finished Dictionary_Imp Example" << std::endl;
    std::cout << std::endl;
}

static void dict_examples_interactive_continue(const Dictionary_Pure &pure, Dictionary_Imp &imp) {
    std::cout << std::endl << "enter ? to look something up, or ! to quit, or a name you'd like to define: ";
    std::string answer;
    std::cin >> answer;
    if (!std::cin || answer.length() == 0 || answer == "!")
        return;  // base case, we're done
    else if (answer == "?") {  // look somethin' up
        std::cout << "Great, lets look something up. What? ";
        std::cin >> answer;
        if (!std::cin) {
            std::cout << "Oops, couldn't read your answer, giving up." << std::endl;
            return;
        } else {
            if (pure.contains(answer)) {
                std::cout << "Found " << answer << " in pure dictionary, looking it up ...";
                std::cout << " got " << pure.lookup(answer) << std::endl;
            } else {
                std::cout << "Did NOT find " << answer
                          << " in pure dictionary, maybe you should check under the sofa?" << std::endl;
            }

            if (imp.contains(answer)) {
                std::cout << "Found " << answer << " in imperative dictionary, looking it up ...";
                std::cout << " got " << imp.lookup(answer) << std::endl;
            } else {
                std::cout << "Did NOT find " << answer
                          << " in imperative dictionary, do you remember where you put it down?" << std::endl;
            }
            dict_examples_interactive_continue(pure, imp);
        }
    } else { // want to insert and add:
        std::cout << "Great, let's add \"" << answer << "\", give me the associated int value: ";
        int val;
        std::cin >> val;
        if (!std::cin) {
            std::cout << "Oops, couldn't read your answer, giving up." << std::endl;
            return;
        } else {
            std::cout << "Adding (\"" << answer << "\", " << val << ") to make new pure ...";
            Dictionary_Pure pure2 = pure.add(answer, val);
            std::cout << " and inserting (\"" << answer << "\", " << val << ") to change imp ...";
            imp.insert(answer, val);
            std::cout << std::endl;
            dict_examples_interactive_continue(pure2, imp);
        }
    }
}


void dict_examples_interactive()
{
    std::cout << std::endl << "==== Welcome to the interactive dictionary examples interface. ===" << std::endl;

    Dictionary_Imp change_me;
    dict_examples_interactive_continue(Dictionary_Pure(), change_me);

    std::cout << std::endl << "==== The interactive dictionary examples are done, thanks for playing. ===" << std::endl;
}