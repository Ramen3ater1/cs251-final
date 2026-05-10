// LECTURE EXAMPLE:
//
// Abstract Syntax for Tiger
//
// C++ Version adapted from Andrew Appel's files by davew@cs.haverford.edu
//
// This is a collection of classes that are designed to be used in an
//  abstract syntax tree for, e.g., Andrew Appel's "tiger" language (used in CMSC 350).
//
// Part of the full CS350 class hierarchy is given below.
//
// HEIRARCHY OF AST NODE TYPES:
//
//	AST_node_
//      A_dec_
//		A_exp_
//			A_literalExp_
//				A_leafExp_
//					A_nilExp_
//					A_intExp_
//					A_boolExp_
//					A_stringExp_
//			A_varExp_	(variable use, e.g. "d" in the expression "d+1", but not "a" in "a := 2")
//			A_opExp_	(-, +, *, /, =, >=, ...)
//			A_assignExp_
//			A_letExp_
//			A_controlExp_
//				A_ifExp_
//				A_whileExp_
//				A_forExp_
//				A_breakExp_
//				A_seqExp_	(Like {} In C++)
//



#if ! defined _AST_H
#define _AST_H

#include <memory>
#include <string>

class AST_node {  // abstract class acting as a Java "interface" would
public:
	virtual std::string HERA_code() = 0;
    virtual ~AST_node() = default;  // C++ uses this but somehow can't automatically put it in as it would copy-constructor, assignment
};

class A_expression : public AST_node {
public:
	[[nodiscard]] int    result_reg() const {
		if (this->stored_result_reg < 0) this->stored_result_reg = this->init_result_reg();
		return stored_result_reg;
	}
	[[nodiscard]] std::string result_reg_s() const { // return in string form, e.g. "R2"
		return "R" + std::to_string(this->result_reg());
	}

    ~A_expression() override = default;
private:
	mutable int stored_result_reg = -1;  // Initialize to -1 to be sure it gets replaced by "if" in result_reg() above
	virtual int init_result_reg() const = 0;   // This should ONLY be called from "result_reg" above!
};

typedef std::unique_ptr<A_expression> A_exp;

class A_root : public AST_node {
public:
	explicit A_root(A_exp main_exp);

	std::string HERA_code() override;
	// std::string print_rep(int indent) override;

private:
	A_exp main_expr;
};



class A_intExp : public A_expression {
public:
	explicit A_intExp(int i);  // C++ note: "explicit" keeps us from turning int into node accidentally

	std::string HERA_code() override;

private:
	int value;
    int init_result_reg() const override;  // This should ONLY be called from "result_reg" above!
};

typedef enum {A_plusOp, A_minusOp, A_timesOp} A_oper;

class A_opExp : public A_expression {
public:
	A_opExp(A_oper oper, A_exp left, A_exp right);
	std::string HERA_code() override;

private:
	A_oper _oper;
	A_exp _left;
	A_exp _right;
    int init_result_reg() const override;  // This should ONLY be called from "result_reg" above!
};

/* Some allocation functions, these just simplify things by "wrapping" the make_unique stuff in a more concise notation */

A_exp A_IntExp(int i);
A_exp A_OpExp(A_oper, A_exp left, A_exp right);

/*
class A_letExp : public A_expression {
public:
	A_letExp(const Dictionary_Imp &decs, A_exp body);
rivate:
    Dictionary_Imp declarations;
	A_exp _body;
    virtual int init_result_reg() override;  // This should ONLY be called from "result_reg" above!
};
*/


/*
class A_ifExp : public A_expression {
public:
	A_ifExp(A_exp test, A_exp then, A_exp else_or_0_pointer_for_no_else);
private:
	A_exp _test;
	A_exp _then;
	A_exp _else_or_null;
    virtual int init_result_reg() override;  // This should ONLY be called from "result_reg" above!
};
*/



void AST_example();


#endif
