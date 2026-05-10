#include "AST.h"
#include <logic.h>

// Abstract Syntax for Tiger

// C++ note: the notation value(i) initializes value to be i
A_intExp::A_intExp(int i) : value(i) {
}

std::string A_intExp::HERA_code() {
    return "SET(" + this->result_reg_s() + ", " + std::to_string(value) + ")\n";
}


// Note: below, std::move means we give up the parameter (e.g. left) to build data field (e.g. _left)
A_opExp::A_opExp(A_oper oper, A_exp left, A_exp right) : _oper(oper), _left(std::move(left)), _right(std::move(right)) {
}

static std::string HERA_op(A_oper oper) {
    switch (oper) {
        case A_plusOp:   return "ADD";
        case A_timesOp:  return "MUL";
        case A_minusOp:  return "SUB";
        default:
            throw "This shouldn't happen unless we treat our \"enum\" as an integer.";
    }
}

std::string A_opExp::HERA_code() {
    std::string op = HERA_op(this->_oper);
    return (_left->HERA_code() +
            "MOVE(" + this->result_reg_s() + ", " + _left->result_reg_s() + ")\n" +
            _right->HERA_code() +
            op + "(" + this->result_reg_s() + ", " + this->result_reg_s() + ", " + _right->result_reg_s() + ")\n"
    );
}


A_root::A_root(A_exp main) : main_expr(std::move(main)){
}

std::string A_root::HERA_code() {
    return "SETCB()\n" + main_expr->HERA_code();
}



/////////////////// Result register stuff

int A_intExp::init_result_reg() const {
    return 1;
}

int A_opExp::init_result_reg() const {
    return 1+std::max(_left->result_reg(), _right->result_reg());
}



/////////////////// Simplify the whole make_unique<T> stuff...

A_exp A_IntExp(int i) {
    return std::make_unique<A_intExp>(i);
}

A_exp A_OpExp(A_oper oper, A_exp left, A_exp right) {
    return std::make_unique<A_opExp>(oper, std::move(left), std::move(right));
}


#include <iostream>
using namespace std;

void AST_example()
{
    cout << "Testing AST class, build (5+1)*(3+4)" << endl;
    A_exp five = A_IntExp(5);
    A_exp one  = A_IntExp(1);
    A_exp lhs  = A_OpExp(A_plusOp, std::move(five), std::move(one));
    cout << "  Code for the left operand of * is..." << endl;
    cout << lhs->HERA_code() << endl;

    A_exp rhs  = A_OpExp(A_plusOp, A_IntExp(3), A_IntExp(4));
    cout << "  Code for the right operand of * is..." << endl;
    cout << rhs->HERA_code() << endl;

    A_exp all  = A_OpExp(A_timesOp, std::move(lhs), std::move(rhs));

    cout << "  ** AND NOW, Code for our AST is..." << endl;
    cout << A_root(std::move(all)).HERA_code() << endl;
    cout << "AST test concluded" << endl;
}
