//
// Created by davew on 12/1/22.
//

#include "A_simpler_tree_and_dag.h"
#include <iostream>
using namespace std;

AST_node_1class::AST_node_1class(int value, A_exp1 left, A_exp1 right) :
        _value(value),                  // initialize field from parameter
        _left(std::move(left)),      // need to use "move" here, to avoid two pointers to same node
        _right(std::move(right)) {   // likewise for right; body can be empty, nothing else to do...
}


ASD_node_1class::ASD_node_1class(int value, ASD_exp1 left, ASD_exp1 right)  :
        _value(value),                  // initialize field from parameter
        _left(std::move(left)),      // OPTIONALLY use "move" here, to avoid doing +1 and then -1
        _right(std::move(right)) {   // likewise for right; body can be empty, nothing else to do...
}


/* This won't work, due to "where" trying to be a 2nd pointer!
void AST_node_1class::print_left_children_loop() {
    cout << "found " << this->_value << endl;
    ASD_exp1 where = this->_left;
    while (where != nullptr) {
        cout << "found " << where->_value << endl;
        where = where->_left;
    }
}
*/

void AST_node_1class::print_left_children_here_and_below_rec() {
    cout << "found " << this->_value << endl;
    if (this->_left != nullptr) {
        this->_left->print_left_children_here_and_below_rec();
    }
}

void AST_node_1class::print_from_no_endl(int indent) const {
    for (int i = 0; i < indent; i++) cout << " ";
    cout << "AST(" << _value << ", /* at address " << this << "*/" << endl;
    if (_left == nullptr) {
        for (int i = 0; i < indent+4; i++) cout << " ";
        cout << "std::nullptr";
    } else {
        _left->print_from_no_endl(indent + 4);
    }
    cout << "," << endl;
    if (_right == nullptr) {  // Oops; fixed from "_left" Dec. 9
        for (int i = 0; i < indent+4; i++) cout << " ";
        cout << "std::nullptr";
    } else {
        _right->print_from_no_endl(indent + 4);
    }
    cout << ")";
}


void print_from_no_endl(ASD_exp1 node, int indent) {
    for (int i = 0; i<indent; i++) cout << " ";
    if (node == nullptr)
        cout << "std::nullptr";
    else {
        cout << "ASD(" << node->_value << ", /* at address " << node << "*/" << endl;
        print_from_no_endl(node->_left, indent+4);
        cout << "," << endl;
        print_from_no_endl(node->_right, indent+4);
        cout << ")";
    }
}


void ASD_node_1class::print_left_children_loop() {
    cout << "found " << this->_value << endl;
    ASD_exp1 where = this->_left;
    while (where != nullptr) {
        cout << "found " << where->_value << endl;
        where = where->_left;
    }
}

void ASD_node_1class::print_left_children_here_and_below_rec() {
    cout << "found " << this->_value << endl;
    if (this->_left != nullptr) {
        this->_left->print_left_children_here_and_below_rec();
    }
}

#include <logic.h>


void examples_1class() {
    // creating an AST_Node
    A_exp1 example_l = make_unique<AST_node_1class>(14, nullptr, nullptr);
    A_exp1 example_r = make_unique<AST_node_1class>(3, nullptr, nullptr);
    A_exp1 ex2 = make_unique<AST_node_1class>(12, move(example_l), move(example_r));
    // "example_l" and "example_r" not usable now that we've moved them
    hccs_assert(example_l == nullptr); // not sure if standard guarantees this, but it is true when I test it...
    hccs_assert(example_r == nullptr);
    cout << "Printing left children down to empty tree, only one approach works" << endl;
    // ex2_D->print_left_children_loop();
    ex2->print_left_children_here_and_below_rec();

    ex2->print_from_no_endl(0);

    // creating an ASD_Node
    ASD_exp1 example_D = make_unique<ASD_node_1class>(21, nullptr, nullptr);
    ASD_exp1 ex2_D = make_unique<ASD_node_1class>(10, example_D, example_D); // 10 for addition :-)
    cout << "Printing left children down to empty DAG, both options" << endl;
    ex2_D->print_left_children_loop();
    ex2_D->print_left_children_here_and_below_rec();

    print_from_no_endl(ex2_D, 0);

    cout << endl;
}
