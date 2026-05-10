//
// Created by davew on 10/12/21.
//

#define DEMO_2022_LECTURE_EXAMPLES false

#include <iostream>  // access to I.O. Streams library, for std::cout and std::endl
#include "Dictionary.h"
#include "A_simpler_tree_and_dag.h"  // "1class" versions of AST and ASD, for slides
#include "AST.h"
#include "ASD.h"
using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT  // keeps the doctests in other files from giving errors even if we're not running them
#include <doctest.h>
// above two lines copied from https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
// as are various "doctest" related things below

int main(int argc, char **argv)
{
    // ===================== Run tests, copied from doctest main.md cited above ======================
    doctest::Context context;
    context.applyCommandLine(argc, argv);                // let doctest consider command-line arguments
    // might want the following, not sure?
    // context.setOption("no-breaks", true);             // don't break in the debugger when assertions fail
    int res = context.run();                             // run the tests
    if(context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;          // return the result of the test, rather than continuing code below, if appropriate
    // ===================== End of test-running boilerplate ==========================================

    cout << "Hello, world ... running some examples" << endl;

    dict_exammple_imp();
    dict_example_pure();
    dict_examples_interactive();

    cout << "dictionary examples done." << endl;

    // Some examples used in class 2022, run if you want to see them
#if DEMO_2022_LECTURE_EXAMPLES
    examples_1class();  // lecture versions of AST and ASD
    cout << endl;

    AST_example();
    cout << endl;

    ASD_example();
    cout << endl;
#endif

    cout << "Bye, bye" << endl;
    return 0; // success
}