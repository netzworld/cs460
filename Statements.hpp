//
// Created by Ali Kooshesh on 4/4/23.
//

#ifndef APYTHONINTERPRETER_STATEMENTS_HPP
#define APYTHONINTERPRETER_STATEMENTS_HPP

#include <iostream>
#include <vector>

#include "Expr.hpp"
#include "SymTab.hpp"

// The Statement (abstract) class serves as a super class for all statements that
// are defined in the language. Ultimately, statements have to be evaluated.
// Therefore, this class defines evaluate, a pure-virtual function to make
// sure that all subclasses of Statement provide an implementation for this
// function.

class Statement {
public:
    Statement();

    virtual void print() = 0;
    virtual void evaluate(SymTab &symTab) = 0;

};


// Statements is a collection of Statement. For example, all statements in a function
// can be represented by an instance of Statements.

class Statements {
public:
    Statements();

    void addStatement(Statement *statement);
    void evaluate(SymTab &symTab);

    void print();

private:
    std::vector<Statement *> _statements;
};

// AssignmentStatement represents the notion of an lValue having been assigned an rValue.
// The rValue is an expression.

class AssignmentStatement : public Statement {
public:
    AssignmentStatement();
    AssignmentStatement(ExprNode* lhsVar, ExprNode *rhsExpr);
    AssignmentStatement(ExprNode *lhsExpr, std::vector<ExprNode *> rhsArray);

    ExprNode *&lhsExpression();
    ExprNode *&rhsExpression();
    std::vector<ExprNode *> rhsArray();

    virtual void evaluate(SymTab &symTab);
    virtual void print();
    

private:
    ExprNode *_lhsVariable;
    ExprNode *_rhsExpression;
    std::vector<ExprNode*> _rhsArray;
};


class PrintStatement : public Statement {
public:
    PrintStatement();
    PrintStatement(std::string varName);

    virtual void print();
    virtual void evaluate(SymTab &symTab);

private:
    std::string varName;


};

class ForLoop : public Statement,public Statements {
public:
    ForLoop();
    ForLoop(AssignmentStatement *start, 
            ExprNode *rel_expr, AssignmentStatement *change, Statements *body_loop);

    virtual void print();
    virtual void evaluate(SymTab &symTab);

private:
    AssignmentStatement* starting;
    ExprNode* expr;
    AssignmentStatement* changer;
    Statements *_body;   

};

#endif //APYTHONINTERPRETER_STATEMENTS_HPP
