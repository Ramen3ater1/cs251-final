#include "ASD.h"
#include <logic.h>

// Abstract Syntax for Tiger

// C++ note: the notation value(i) initializes value to be i
ASD_intExp::ASD_intExp(int i) : value(i) {
}

std::string ASD_intExp::HERA_code() {
    return "SET(" + this->result_reg_s() + ", " + std::to_string(value) + ")\n";
}


// Note: below, std::move, for _shared_ pointers, gives up the original pointer again and thus leaves the count alone
//       we could just omit it, and the count would go up and then down again when the parameters go away
ASD_opExp::ASD_opExp(ASD_oper oper, ASD_exp left, ASD_exp right) : _oper(oper), _left(std::move(left)), _right(std::move(right)) {
}

static std::string HERA_op(ASD_oper oper) {
    switch (oper) {
        case ASD_plusOp:   return "ADD";
        case ASD_timesOp:  return "MUL";
        case ASD_minusOp:  return "SUB";
        default:
            throw "This shouldn't happen unless we treat our \"enum\" as an integer.";
    }
}

std::string ASD_opExp::HERA_code() {
    std::string op = HERA_op(this->_oper);
    return (_left->HERA_code() +
            "MOVE(" + this->result_reg_s() + ", " + _left->result_reg_s() + ")\n" +
            _right->HERA_code() +
            op + "(" + this->result_reg_s() + ", " + this->result_reg_s() + ", " + _right->result_reg_s() + ")\n"
    );
}


ASD_root::ASD_root(ASD_exp main) : main_expr(std::move(main)){
}

std::string ASD_root::HERA_code() {
    return "SETCB()\n" + main_expr->HERA_code();
}



/////////////////// Result register stuff

int ASD_intExp::init_result_reg() const {
    return 1;
}

int ASD_opExp::init_result_reg() const {
    return 1+std::max(_left->result_reg(), _right->result_reg());
}



/////////////////// Simplify the allocation stuff...

ASD_exp ASD_IntExp(int i) {
    return std::make_shared<ASD_intExp>(i);
}

ASD_exp ASD_OpExp(ASD_oper oper, ASD_exp left, ASD_exp right) {
    return std::make_shared<ASD_opExp>(oper, std::move(left), std::move(right));
}


#include <iostream>
using namespace std;

void ASD_example()
{
    cout << "Testing ASD class, build (3*7)+(3*7), with only one 3*7 subtree" << endl;

    ASD_exp ths  = ASD_OpExp(ASD_timesOp, ASD_IntExp(3), ASD_IntExp(7));
    cout << "  Code for the twice-used operand of * is..." << endl;
    cout << ths->HERA_code() << endl;

    // NOTE: no "move" is needed below, _both_ left _and_ right can point to that 3*7
    ASD_exp all  = ASD_OpExp(ASD_plusOp, ths, ths);

    // The "move" below is optional, but we're done with "all" anyway, so...
    cout << "  ** AND NOW, Code for our ASD is..." << endl;
    cout << ASD_root(std::move(all)).HERA_code() << endl;
    cout << "ASD test concluded" << endl;
}
