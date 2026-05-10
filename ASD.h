// LECTURE EXAMPLE:
//
// Abstract Syntax for Tiger, DAG (directed acyclyc graph) version
//
// C++ Version adapted from Andrew Appel's files by davew@cs.haverford.edu
//
// This is a collection of classes that are designed to be used in an
//  abstract syntax tree for, e.g., Andrew Appel's "tiger" language (used in CMSC 350).
//
// HEIRARCHY OF AST NODE TYPES is what it was in AST.h


#if ! defined _ASD_H
#define _ASD_H

#include <memory>
#include <string>

class ASD_node {  // abstract class with some common data
public:
	virtual std::string HERA_code() = 0;
    virtual ~ASD_node() = default;  // C++ uses this but somehow can't automatically put it in as it would copy-constructor, assignment
};

class ASD_expression : public ASD_node {
public:
	[[nodiscard]] int    result_reg() const {
		if (this->stored_result_reg < 0) this->stored_result_reg = this->init_result_reg();
		return stored_result_reg;
	}
	[[nodiscard]] std::string result_reg_s() const { // return in string form, e.g. "R2"
		return "R" + std::to_string(this->result_reg());
	}

    ~ASD_expression() override = default;
private:
	mutable int stored_result_reg = -1;  // Initialize to -1 to be sure it gets replaced by "if" in result_reg() above
	virtual int init_result_reg() const = 0;   // This should ONLY be called from "result_reg" above!
};

// For our DAG's, we can use shared_ptr,
//   which implements the "object on the heap knows how many arrows there are to it" idiom, a.k.a. "count pointers"
typedef std::shared_ptr<ASD_expression> ASD_exp;

class ASD_root : public ASD_node {
public:
	explicit ASD_root(ASD_exp main_exp);

	std::string HERA_code() override;
	// std::string print_rep(int indent) override;

private:
	ASD_exp main_expr;
};



class ASD_intExp : public ASD_expression {
public:
	explicit ASD_intExp(int i);  // C++ note: "explicit" keeps us from turning int into node accidentally

	std::string HERA_code() override;

private:
	int value;
    int init_result_reg() const override;  // This should ONLY be called from "result_reg" above!
};

typedef enum {ASD_plusOp, ASD_minusOp, ASD_timesOp} ASD_oper;

class ASD_opExp : public ASD_expression {
public:
	ASD_opExp(ASD_oper oper, ASD_exp left, ASD_exp right);
	std::string HERA_code() override;

private:
	ASD_oper _oper;
	ASD_exp _left;
	ASD_exp _right;
    int init_result_reg() const override;  // This should ONLY be called from "result_reg" above!
};

/* Some allocation functions, these just simplify things by "wrapping" the allocation stuff in a more concise notation */

ASD_exp ASD_IntExp(int i);
ASD_exp ASD_OpExp(ASD_oper, ASD_exp left, ASD_exp right);

/*
class ASD_letExp : public ASD_expression {
public:
	ASD_letExp(const Dictionary_Imp &decs, ASD_exp body);
rivate:
    Dictionary_Imp declarations;
	ASD_exp _body;
    virtual int init_result_reg() override;  // This should ONLY be called from "result_reg" above!
};
*/


/*
class ASD_ifExp : public ASD_expression {
public:
	ASD_ifExp(ASD_exp test, ASD_exp then, ASD_exp else_or_0_pointer_for_no_else);
private:
	ASD_exp _test;
	ASD_exp _then;
	ASD_exp _else_or_null;
    virtual int init_result_reg() override;  // This should ONLY be called from "result_reg" above!
};
*/



void ASD_example();


#endif
