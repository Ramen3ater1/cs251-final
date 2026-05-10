//
// Created by davew on 12/1/22.
//

#ifndef DICTIONARY_A_SIMPLER_TREE_AND_DAG_H
#define DICTIONARY_A_SIMPLER_TREE_AND_DAG_H

// Simplified for use in lectures;
//  A binary tree that we could use for an abstract syntax tree,
//  using the classic first approach from, e.g., cs106: a single "node" class
//  that uses a pointer-to-node to refer to any tree (or null, if there is none)

#include <memory>

class AST_node_1class;  // allow forward-references, this class is declared 3 lines below
typedef std::unique_ptr<AST_node_1class> A_exp1; // requires forward ref, not shown

class AST_node_1class {
public:
    AST_node_1class(int value, A_exp1 left, A_exp1 right);

    // demo of traversal idioms, simplest version
    // void print_left_children_loop();  // print root value, it's left child value, it's left-left grandchild, etc...
    void print_left_children_here_and_below_rec();  // like the above, different implementation strategy, works

    // various other useful functions, e.g., full printing
    void print_from_no_endl(int indent) const;  // doesn't have to be a member, unlike unique_ptr code

private:
    int _value;
    A_exp1 _left;
    A_exp1 _right;
};


// Like the above, but for DAG (directed acyclic graph

class ASD_node_1class;  // allow forward-references, this class is declared 3 lines below
typedef std::shared_ptr<ASD_node_1class> ASD_exp1; // requires forward ref, not shown

class ASD_node_1class {
public:
    ASD_node_1class(int value, ASD_exp1 left, ASD_exp1 right);

    // demo of traversal idioms, simplest version
    void print_left_children_loop();  // print root value, it's left child value, it's left-left grandchild, etc...
    void print_left_children_here_and_below_rec();  // like the above, different implementation strategy

    // various useful functions, e.g. full printing of the tree
    friend void print_from_no_endl(ASD_exp1 node, int indent);  // doesn't have to be a member, unlike unique_ptr code
private:
    int _value;
    ASD_exp1 _left;
    ASD_exp1 _right;
};

void examples_1class();  // examples of the above

#endif //DICTIONARY_A_SIMPLER_TREE_AND_DAG_H
