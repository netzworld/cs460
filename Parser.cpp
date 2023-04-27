//
// Created by Ali Kooshesh on 4/4/23.
//


#include<vector>
#include<iostream>

#include "Token.hpp"
#include "Parser.hpp"
#include "Statements.hpp"

// Parser functions

void Parser::die(std::string where, std::string message, Token &token) {
    std::cout << where << " " << message << std::endl;
    token.print();
    std::cout << std::endl;
    std::cout << "\nThe following is a list of tokens that have been identified up to this point.\n";
    tokenizer.printProcessedTokens();
    exit(1);
}

Statements *Parser::statements() {
    // This function is called when we KNOW that we are about to parse
    // a series of assignment statements.

    // This function parses the grammar rules:

    // 1. file_input : {NEWLINE | stmt} * ENDMARKER 
    // 2. stmt : simple_stmt | compound_stmt 
    // 3. simple_stmt : (print_stmt | assign_stmt) NEWLINE 
    // 4. print_stmt : ’print’ ’(’ [testlist] ’)’ 
    // 5. assign_stmt : ID ’=’ test 
    // 6. compound_stmt : for_stmt

    Statements *stmts = new Statements();
    Token tok = tokenizer.getToken();
    while(tok.eol())
        tok = tokenizer.getToken();

    while(tok.isName() || tok.isComment())
    {
        if(tok.isKeyword()){
            if (tok.isPrint())
            {           
                PrintStatement *printstatmt = print();
                stmts->addStatement(printstatmt);
            }
            else if (tok.isFor())
            {
                ForLoop *forloop = forLoop();
                stmts->addStatement(forloop);
            }
        }
        
        else if(tok.isName()) {
            tokenizer.ungetToken();
            AssignmentStatement *assignStmt = assignStatement();
            stmts->addStatement(assignStmt);
        }
        else if(tok.isComment()){
            tok = tokenizer.getToken();
            if (!tok.eol() && !tok.eof())
                die("Parser::statements", "Expected an eol token, instead got", tok);
        }
        if(!tok.eof()){
            tok = tokenizer.getToken();
            while(tok.eol())
                tok = tokenizer.getToken();
        }

        
    }
    while(tok.eol())
        tok = tokenizer.getToken();

    tokenizer.ungetToken();
    return stmts;
}

AssignmentStatement *Parser::assignStatement() {
    // Parses the following grammar rule
    //
    // 5. assign_stmt: ID ’=’ test

    Token varName = tokenizer.getToken();
    if (!varName.isName())
        die("Parser::assignStatement", "Expected a name token, instead got", varName);

    Token assignOp = tokenizer.getToken();
    if (!assignOp.isAssignmentOperator())
        die("Parser::assignStatement", "Expected an equal sign, instead got", assignOp);
    ExprNode *leftSideExpr = new Variable(varName);

    ExprNode *rightSideExpr = test();
    

    

    /* Commented out the 3 lines below because the token was reading in the next token and adding it when we didnt want it to do that
       Also the if-statement checks to see if it is a semi-coloon but we dont want that
    */

    //Token tok = tokenizer.getToken();
    //if (!tok.isSemiColon())
    //    die("Parser::assignStatement", "Expected a semicolon, instead got", tok);

    Token tok = tokenizer.getToken();
    if (!tok.eol() && !tok.eof() && !tok.isComment())
        die("Parser::assignStatement", "Expected an end of line token, instead got", tok);
    if (tok.eof())
        tokenizer.ungetToken();
    

    return new AssignmentStatement(varName.getName(), rightHandSideExpr);
}

ExprNode *Parser::test()
{
    // This function parses the grammar rule:

    // test: comparison

    return comparison();
}

ExprNode *Parser::comparison()
{
    // This function parses the grammar rules:

    // comparison: arith_expr {comp_op arith_expr}*
    // comp_op: '<'|'>'|'=='|'>='|'<='|'<>'|'!='

    ExprNode *left = arith_expr();
    Token tok = tokenizer.getToken();
    while (tok.isRelationalOp())
    {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = arith_expr();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}
// changed from expr to arith_expr
ExprNode *Parser::arith_expr() {
    // This function parses the grammar rules:

    // 12. arith_expr : term{(’+’|’-’) term} *


    ExprNode *left = term();
    Token tok = tokenizer.getToken();
    while (tok.isAdditionOperator() || tok.isSubtractionOperator()) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = term();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}



ExprNode *Parser::term() {
    // This function parses the grammar rules:

    // 13. term: factor {(’*’|’/’|’%’|’//’) factor}*
    // 

    // However, the implementation makes the <mult-op> left associate.
    ExprNode *left = factor();
    Token tok = tokenizer.getToken();

    while (tok.isMultiplicationOperator() || tok.isDivisionOperator() || 
    tok.isModuloOperator() || tok.isIntDivisionOperator() ) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = factor();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode *Parser::factor() {
    // This function parses the grammar rules:

    // 14. factor: {’-’} factor | atom


    Token tok = tokenizer.getToken();
    int hyphens = 0;
    while (tok.isSubtractionOperator())
    {
        hyphens++;
        tok = tokenizer.getToken();
    }
    Token prev = tok;
    tok = tokenizer.getToken();
    tokenizer.ungetToken();
    return atom(prev, hyphens);
   
    // if (tok.isOpenParen()) {
    //     ExprNode *p = expr();
    //     Token token = tokenizer.getToken();
    //     if (!token.isCloseParen())
    //         die("Parser::primary", "Expected close-parenthesis, instead got", token);
    //     return p;
    // }
    // die("Parser::primary", "Unexpected token", tok);

    // return nullptr;  // Will not reach this statement!
}

ExprNode *Parser::atom(Token prev, int hyphens){
    // Parses atom grammar rules:
    // 15. atom: ID | NUMBER | STRING+ | ’(’ test ’)’

    Token tok = prev;

    if(tok.isWholeNumber()){
        if(hyphens % 2 == 1) // is neg num?
            tok.setWholeNumber(-(tok.getWholeNumber()));
        return new WholeNumber(tok);
    }
    else if (tok.isName() && !tok.isKeyword())
    {
        if (hyphens % 2 == 1)
        {
            Token mult = Token();
            mult.symbol('*');
            InfixExprNode *negVar = new InfixExprNode(mult);
            Token num = Token();
            num.setWholeNumber(-1);
            negVar->left() = new WholeNumber(num);
            negVar->right() = new Variable(tok);
            return negVar;
        }
        return new Variable(tok);
    }
    else if (tok.isDouble())
    {
        if (hyphens % 2 == 1)
            tok.setDouble(-(tok.getDouble()));
        return new Double(tok);
    }
    else if (tok.isString())
    {
        if (hyphens > 0)
            die("Parser::atom", "Bad operand type for unary -: 'str':", tok);
        return new String(tok);
    }
    else if (tok.isOpenParen())
    {
        if (hyphens % 2 == 1)
        {
            Token mult = Token();
            mult.symbol('*');
            InfixExprNode *negExpr = new InfixExprNode(mult);
            Token num = Token();
            num.setWholeNumber(-1);
            negExpr->left() = new WholeNumber(num);
            negExpr->right() = test();
            tok = tokenizer.getToken();
            if (!tok.isCloseParen())
                die("Parser::atom", "Expected a close parenthesis, instead got", tok);
            return negExpr;
        }
        ExprNode *expr = test();

        tok = tokenizer.getToken();
        if (!tok.isCloseParen())
            die("Parser::atom", "Expected a close parenthesis, instead got", tok);
        return expr;
    }
    die("Parser::atom", "Expected a whole number, name, double, string, or parenthesis, instead got", tok);

    return nullptr; // Should never reach here
}

PrintStatement *Parser::print()
{
    Token tok = tokenizer.getToken();
    if(!tok.isPrint()){
        exit(1);
    }

    Token idTok = tokenizer.getToken();
    if(!idTok.isName()){
        die("Parser::print", "Expected name tok, got ", idTok);
    }
    Token nl = tokenizer.getToken();
    if(!nl.eol() || nl.eof()){
        die("Parser::print", "Expected a newline, got", nl);
    }

    PrintStatement *printstatmt = new PrintStatement(idTok.getName());
    return printstatmt;
}

ForLoop *Parser::forLoop(){
    Token tok = tokenizer.getToken();
    if(!tok.isFor()){
        exit(1);
    }
    Token parenTok = tokenizer.getToken();
    if(!parenTok.isOpenParen()){
        die("Parser::forLoop", "Expected open paren, got ", parenTok);
    }
    AssignmentStatement *starting = assignStatement(); // i, (=) 0
    
    Token semi = tokenizer.getToken(); // get ;

    if(!semi.isSemiColon()){
        die("Parser::forLoop", "Expected semicolon, got ", parenTok);
    }
    // std::cout << "Token print: ";
    // semi.print();
    // std::cout << std::endl;
    
    // std::cout << "comparison: ";
    ExprNode *comparison = arith_expr(); // gets conditional

    semi = tokenizer.getToken(); // ;
    if(!semi.isSemiColon()){
        die("Parser::forLoop", "Expected semicolon, got ", parenTok);
    }
    // std::cout << "Token: ";
    // semi.print(); 
    // std::cout << std::endl;
    Token nl = tokenizer.getToken();

    AssignmentStatement *change = assignStatement(); // gets increment or decrement assign statement
    
    parenTok = tokenizer.getToken();
    if(!parenTok.isCloseParen()){
        die("Parser::forLoop", "Expected close paren, got ", parenTok);
    }

    // std::cout << "line 219: ";
    // parenTok.print();
    // std::cout << std::endl;

    Token bracket = tokenizer.getToken();
    if(!bracket.isOpenBracket()){
        die("Parser::forLoop", "Expected open bracket, got ", parenTok);
    }

    // std::cout << "line 228: ";
    // bracket.print();
    // std::cout << std::endl;
    bracket = tokenizer.getToken();

    Statements *body_statements = statements();
    // std::cout << "trying to print statements: ";
    // body_statements->print();
   

    bracket = tokenizer.getToken();
    if(!bracket.isCloseBracket()){
        die("Parser::forLoop", "Expected closed bracket, got ", parenTok);
    } 
    bracket = tokenizer.getToken();
    ForLoop *loop = new ForLoop(starting, comparison, change, body_statements);

    return loop;
}
