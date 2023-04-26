//
// Created by Ali Kooshesh on 4/4/23.
//

#include "Statements.hpp"

// Statement
Statement::Statement() {}

// Statements

Statements::Statements() {}

void Statements::addStatement(Statement *statement) { _statements.push_back(statement); }

void Statements::print() {
    for (auto s: _statements)
        s->print();
}

void Statements::evaluate(SymTab &symTab) {
    for (auto s: _statements)
        s->evaluate(symTab);
}

// AssignmentStatement

AssignmentStatement::AssignmentStatement() : _lhsVariable{""}, _rhsExpression{nullptr} {}

AssignmentStatement::AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr):
        _lhsVariable{lhsVar}, _rhsExpression{rhsExpr} {}

void AssignmentStatement::evaluate(SymTab &symTab) {
    int rhs = rhsExpression()->evaluate(symTab);
    symTab.setValueFor(lhsVariable(), rhs);
}

std::string &AssignmentStatement::lhsVariable() {
    return _lhsVariable;
}

ExprNode *&AssignmentStatement::rhsExpression() {
    return _rhsExpression;
}

void AssignmentStatement::print() {
    std::cout << _lhsVariable << " = ";
    _rhsExpression->print();
    std::cout << std::endl;
}

void PrintStatement::print(){
    //std::cout << varName;

}

PrintStatement::PrintStatement(std::string name){
    varName = name;
}

void PrintStatement::evaluate(SymTab &symTab){
   std::cout << symTab.getValueFor(varName) << std::endl;
}

ForLoop::ForLoop(AssignmentStatement *start, ExprNode *rel_expr, AssignmentStatement *change, Statements *body_loop){
    starting = start;
    expr = rel_expr;
    changer = change;
    _body = body_loop;

}

void ForLoop::print(){}

void ForLoop::evaluate(SymTab &symTab){
    starting->evaluate(symTab);
 
  while(expr->evaluate(symTab)){
    _body->evaluate(symTab);
    changer->evaluate(symTab);
  }
  
}

// a samurai and a spartan
