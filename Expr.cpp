//
// Created by Ali Kooshesh on 4/4/23.
//


#include<iostream>
#include "Expr.hpp"

void die(std::string where, std::string op, TypeDescriptor::types lType, TypeDescriptor::types rType)
{
    std::cout << where << " Unsupported operand types for " << op << ": ";

    if (lType == TypeDescriptor::INTEGER)
    {
        std::cout << "Integer";
    }
    else if (lType == TypeDescriptor::DOUBLE)
    {
        std::cout << "Double";
    }
    else if (lType == TypeDescriptor::STRING)
    {
        std::cout << "String";
    }


    std::cout << " and ";

    if (rType == TypeDescriptor::INTEGER)
    {
        std::cout << "Integer";
    }
    else if (rType == TypeDescriptor::DOUBLE)
    {
        std::cout << "Double";
    }
    else if (rType == TypeDescriptor::STRING)
    {
        std::cout << "String";
    }

    std::cout << std::endl;
    exit(1);
}

// ExprNode
ExprNode::ExprNode(Token token): _token{token} {}

Token ExprNode::token() { return _token; }

// InfixExprNode functions
InfixExprNode::InfixExprNode(Token tk) : ExprNode{tk}, _left(nullptr), _right(nullptr) {}

ExprNode *&InfixExprNode::left() { return _left; }

ExprNode *&InfixExprNode::right() { return _right; }

TypeDescriptor *InfixExprNode::evaluate(SymTab &symTab)
{
    
    TypeDescriptor *lValue = left()->evaluate(symTab);
    TypeDescriptor::types lType = lValue->type();
    TypeDescriptor *rValue = right()->evaluate(symTab);
    TypeDescriptor::types rType = rValue->type();

    if (token().isAdditionOperator())
    {
        if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() +
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::DOUBLE)
            return new DoubleDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() +
                                        dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::INTEGER)
            return new DoubleDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() +
                                        dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::DOUBLE)
            return new DoubleDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() +
                                        dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::STRING && rType == TypeDescriptor::STRING)
            return new StringDescriptor(dynamic_cast<StringDescriptor *>(lValue)->value() +
                                        dynamic_cast<StringDescriptor *>(rValue)->value());
        // If op types are unsupported
        die("InfixExprNode::evaluate", "+", lType, rType);
    }
    else if (token().isSubtractionOperator())
    {
        if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() -
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::DOUBLE)
            return new DoubleDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() -
                                        dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::INTEGER)
            return new DoubleDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() -
                                        dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::DOUBLE)
            return new DoubleDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() -
                                        dynamic_cast<DoubleDescriptor *>(rValue)->value());
        // If op types are unsupported
        die("InfixExprNode::evaluate", "-", lType, rType);
    }
    else if (token().isMultiplicationOperator())
    {
        if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() *
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::DOUBLE)
            return new DoubleDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() *
                                        dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::INTEGER)
            return new DoubleDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() *
                                        dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::DOUBLE)
            return new DoubleDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() *
                                        dynamic_cast<DoubleDescriptor *>(rValue)->value());
        // If op types are unsupported
        die("InfixExprNode::evaluate", "*", lType, rType);
    }
    else if (token().isDivisionOperator())
    {
        if ((rType == TypeDescriptor::INTEGER && dynamic_cast<IntegerDescriptor *>(rValue)->value() == 0) ||
            (rType == TypeDescriptor::DOUBLE && dynamic_cast<DoubleDescriptor *>(rValue)->value() == 0))
        {
            std::cout << "InfixExprNode::evaluate: divide by zero error\n";
            exit(2);
        }
        if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::INTEGER)
            return new DoubleDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() /
                                        (double)dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::DOUBLE)
            return new DoubleDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() /
                                        dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::INTEGER)
            return new DoubleDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() /
                                        dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::DOUBLE)
            return new DoubleDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() /
                                        dynamic_cast<DoubleDescriptor *>(rValue)->value());
        // If op types are unsupported
        die("InfixExprNode::evaluate", "/", lType, rType);
    }
    else if (token().isModuloOperator())
    {
        if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() %
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        // If op types are unsupported
        die("InfixExprNode::evaluate", "%", lType, rType);
    }
    else if (token().isIntDivisionOperator())
    {
        if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() /
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::DOUBLE)
            return new DoubleDescriptor((int)(dynamic_cast<IntegerDescriptor *>(lValue)->value() /
                                              dynamic_cast<DoubleDescriptor *>(rValue)->value()));
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::INTEGER)
            return new DoubleDescriptor((int)(dynamic_cast<DoubleDescriptor *>(lValue)->value() /
                                              dynamic_cast<IntegerDescriptor *>(rValue)->value()));
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::DOUBLE)
            return new DoubleDescriptor((int)(dynamic_cast<DoubleDescriptor *>(lValue)->value() /
                                              dynamic_cast<DoubleDescriptor *>(rValue)->value()));
        // If op types are unsupported
        die("InfixExprNode::evaluate", "//", lType, rType);
    }

    // Rel Ops
    if (token().isGreaterThanOperator())
    {
        if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() >
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::DOUBLE)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() >
                                         dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() >
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::DOUBLE)
            return new IntegerDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() >
                                         dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::STRING && rType == TypeDescriptor::STRING)
            return new IntegerDescriptor(dynamic_cast<StringDescriptor *>(lValue)->value() >
                                         dynamic_cast<StringDescriptor *>(rValue)->value());
        // If op types are unsupported
        die("RelExprNode::evaluate", ">", lType, rType);
    }
    else if (token().isGreaterEqualOperator())
    
    {
        if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() >=
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::DOUBLE)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() >=
                                         dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() >=
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::DOUBLE)
            return new IntegerDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() >=
                                         dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::STRING && rType == TypeDescriptor::STRING)
            return new IntegerDescriptor(dynamic_cast<StringDescriptor *>(lValue)->value() >=
                                         dynamic_cast<StringDescriptor *>(rValue)->value());
        // If op types are unsupported
        die("RelExprNode::evaluate", ">=", lType, rType);
    }
    else if (token().isLessThanOperator())
    {
        if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() <
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::DOUBLE)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() <
                                         dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() <
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::DOUBLE)
            return new IntegerDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() <
                                         dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::STRING && rType == TypeDescriptor::STRING)
            return new IntegerDescriptor(dynamic_cast<StringDescriptor *>(lValue)->value() <
                                         dynamic_cast<StringDescriptor *>(rValue)->value());
        // If op types are unsupported
        die("RelExprNode::evaluate", "<", lType, rType);
    }
    else if (token().isLessEqualOperator())
    {
        if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() <=
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::DOUBLE)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() <=
                                         dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() <=
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::DOUBLE)
            return new IntegerDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() <=
                                         dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::STRING && rType == TypeDescriptor::STRING)
            return new IntegerDescriptor(dynamic_cast<StringDescriptor *>(lValue)->value() <=
                                         dynamic_cast<StringDescriptor *>(rValue)->value());
        // If op types are unsupported
        die("RelExprNode::evaluate", "<=", lType, rType);
    }
    else if (token().isEqualRelationalOperator())
    {
        if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() ==
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::DOUBLE)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() ==
                                         dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() ==
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::DOUBLE)
            return new IntegerDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() ==
                                         dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::STRING && rType == TypeDescriptor::STRING)
            return new IntegerDescriptor(dynamic_cast<StringDescriptor *>(lValue)->value() ==
                                         dynamic_cast<StringDescriptor *>(rValue)->value());
        // If op types are unsupported
        die("RelExprNode::evaluate", "==", lType, rType);
    }
    else if (token().isNotEqualRelationalOperator() || token().isAltInequalityOperator())
    {
        if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() !=
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::INTEGER && rType == TypeDescriptor::DOUBLE)
            return new IntegerDescriptor(dynamic_cast<IntegerDescriptor *>(lValue)->value() !=
                                         dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::INTEGER)
            return new IntegerDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() !=
                                         dynamic_cast<IntegerDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::DOUBLE && rType == TypeDescriptor::DOUBLE)
            return new IntegerDescriptor(dynamic_cast<DoubleDescriptor *>(lValue)->value() !=
                                         dynamic_cast<DoubleDescriptor *>(rValue)->value());
        else if (lType == TypeDescriptor::STRING && rType == TypeDescriptor::STRING)
            return new IntegerDescriptor(dynamic_cast<StringDescriptor *>(lValue)->value() !=
                                         dynamic_cast<StringDescriptor *>(rValue)->value());
        // If op types are unsupported
        die("RelExprNode::evaluate", "!=", lType, rType);
    }

    else
    {
        std::cout << "InfixExprNode::evaluate: don't know how to evaluate this operator\n";
        token().print();
        std::cout << std::endl;
        exit(2);
    }

    return nullptr; // Will never reach here
}

void InfixExprNode::print() {
    _left->print();
    token().print();
    _right->print();
}

// WHoleNumber
WholeNumber::WholeNumber(Token token): ExprNode{token} {}

void WholeNumber::print() {
    token().print();
}

TypeDescriptor *WholeNumber::evaluate(SymTab &symTab)
{
    if (debug)
    {
        std::cout << "WholeNumber::evaluate: returning " << token().getWholeNumber() << std::endl;
    }
    return new IntegerDescriptor(token().getWholeNumber());
}

// Variable

Variable::Variable(Token token): ExprNode{token} {}

void Variable::print() {
    token().print();
}

TypeDescriptor* Variable::evaluate(SymTab &symTab) {
    if( ! symTab.isDefined(token().getName())) {
        std::cout << "Use of undefined variable, " << token().getName() << std::endl;
        exit(1);
    }
    if(debug)
        std::cout << "Variable::evaluate: returning " << symTab.getValueFor(token().getName()) << std::endl;
   
    return symTab.getValueFor(token().getName());
}

String::String(Token token) : ExprNode{token} {}

void String::print()
{
    token().print();
}

TypeDescriptor *String::evaluate(SymTab &symTab)
{
    if (debug)
    {
        std::cout << "String::evaluate: returning " << token().getString() << std::endl;
    }
    return new StringDescriptor(token().getString());
}

Double::Double(Token token) : ExprNode{token} {}

void Double::print()
{
    token().print();
}
