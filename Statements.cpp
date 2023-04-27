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
    if (_rhsExpression == nullptr)
    {
        if (dynamic_cast<Variable *>(lhsExpression()) == nullptr)
        {
            std::cout << "AssignmentStatement::evaluate Can't assign arrays to Subscripts (Multidimensional arrays are unsupported)\n";
            exit(1);
        }
        Variable *lhs = dynamic_cast<Variable *>(lhsExpression());
        if (_rhsArray.empty())
        {
            symTab.setValueFor(lhs->token().getName(), new ArrayDescriptor());
            return;
        }
        std::vector<TypeDescriptor *> arr;
        TypeDescriptor *val = _rhsArray[0]->evaluate(symTab);
        TypeDescriptor::types arrType = val->type();
        if (arrType == TypeDescriptor::ARRAY || arrType == TypeDescriptor::NOT_SPECIFIED)
        {
            std::cout << "AssignmentStatement::evaluate Right hand side array elements are of an unsupported type\n";
            exit(1);
        }
        arr.push_back(val);
        for (int i = 1; i < _rhsArray.size(); i++)
        {
            val = _rhsArray[i]->evaluate(symTab);
            if (val->type() != arrType)
            {
                std::cout << "AssignmentStatement::evaluate Data types of all elements in the right hand side array must be the same\n";
                exit(1);
            }
            arr.push_back(val);
        }
        ArrayDescriptor *arrDesc = new ArrayDescriptor(arr, arrType);
        symTab.setValueFor(lhs->token().getName(), arrDesc);
        return;
    }
    TypeDescriptor *rhs = rhsExpression()->evaluate(symTab);
    if (dynamic_cast<Variable *>(lhsExpression()) != nullptr)
    {
        Variable *lhs = dynamic_cast<Variable *>(lhsExpression());
        symTab.setValueFor(lhs->token().getName(), rhs);
    }
    
    else
    {
        std::cout << "AssignmentStatement::evaluate Left hand side expression must be a Variable\n";
        exit(1);
    }
}

ExprNode *&AssignmentStatement::lhsExpression()
{
    return _lhsExpression;
}

ExprNode *&AssignmentStatement::rhsExpression()
{
    return _rhsExpression;
}

std::vector<ExprNode*> AssignmentStatement::rhsArray(){
    return _rhsArray;
}

void AssignmentStatement::print()
{
    std::cout << _lhsVariable << " = ";
    _rhsExpression->print();
    std::cout << std::endl;
}

void PrintStatement::print()
{
    // std::cout << varName;
}

PrintStatement::PrintStatement(std::string name)
{
    varName = name;
}

void PrintStatement::evaluate(SymTab & symTab)
{
    std::cout << symTab.getValueFor(varName) << std::endl;
}

ForLoop::ForLoop(AssignmentStatement * start, ExprNode * rel_expr, AssignmentStatement * change, Statements * body_loop)
{
    starting = start;
    expr = rel_expr;
    changer = change;
    _body = body_loop;
}

void ForLoop::print() {}

void ForLoop::evaluate(SymTab & symTab)
{
    starting->evaluate(symTab);

    while (expr->evaluate(symTab))
    {
        _body->evaluate(symTab);
        changer->evaluate(symTab);
    }
}
