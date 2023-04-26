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

    // <statement> -> <assignStatement> <statement>
    // <statement> -> Epsilon


    Statements *stmts = new Statements();
    Token tok = tokenizer.getToken();

    while(tok.isName() || tok.isKeyword() ){
        if(tok.isPrint()){
            tokenizer.ungetToken();
            PrintStatement *printstatmt = print();
            stmts->addStatement(printstatmt);
        }
        else if (tok.isFor()){
            tokenizer.ungetToken();
            ForLoop *forloop = forLoop();
            stmts->addStatement(forloop);
        }
        else {
            tokenizer.ungetToken();
            AssignmentStatement *assignStmt = assignStatement();
            stmts->addStatement(assignStmt);
        }
        tok = tokenizer.getToken();
    }


    tokenizer.ungetToken();
    return stmts;
}

AssignmentStatement *Parser::assignStatement() {
    // Parses the following grammar rule
    //
    // <assign-stmtement> -> <id> = <expr>

    Token varName = tokenizer.getToken();
    if (!varName.isName())
        die("Parser::assignStatement", "Expected a name token, instead got", varName);

    Token assignOp = tokenizer.getToken();
    if (!assignOp.isAssignmentOperator())
        die("Parser::assignStatement", "Expected an equal sign, instead got", assignOp);

    ExprNode *rightHandSideExpr = expr();

    /* Commented out the 3 lines below because the token was reading in the next token and adding it when we didnt want it to do that
       Also the if-statement checks to see if it is a semi-coloon but we dont want that
    */

    //Token tok = tokenizer.getToken();
    //if (!tok.isSemiColon())
    //    die("Parser::assignStatement", "Expected a semicolon, instead got", tok);

    Token tok = tokenizer.getToken();
    if(!tok.eol() || tok.eof())
        die("Parse::assignStatement", "Expected a newline, instead got", tok);
    
    return new AssignmentStatement(varName.getName(), rightHandSideExpr);
}

ExprNode *Parser::expr() {
    // This function parses the grammar rules:

    // <expr> -> <term> { <add_op> <term> }
    // <add_op> -> + | -

    // However, it makes the <add_op> left associative.

    ExprNode *left = term();
    Token tok = tokenizer.getToken();
    while (tok.isAdditionOperator() || tok.isSubtractionOperator() || tok.isEqualRelation()) {
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

    // <term> -> <primary> { <mult_op> <primary> }
    // <mult_op> -> * | / | %

    // However, the implementation makes the <mult-op> left associate.
    ExprNode *left = primary();
    Token tok = tokenizer.getToken();

    while (tok.isMultiplicationOperator() || tok.isDivisionOperator() || 
    tok.isModuloOperator() || tok.isRelationalOp() ) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = primary();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode *Parser::primary() {
    // This function parses the grammar rules:

    // <primary> -> [0-9]+
    // <primary> -> [_a-zA-Z]+
    // <primary> -> (<expr>)

    Token tok = tokenizer.getToken();

    if (tok.isWholeNumber() )
        return new WholeNumber(tok);
    else if( tok.isName() )
        return new Variable(tok);
    else if (tok.isOpenParen()) {
        ExprNode *p = expr();
        Token token = tokenizer.getToken();
        if (!token.isCloseParen())
            die("Parser::primary", "Expected close-parenthesis, instead got", token);
        return p;
    }
    die("Parser::primary", "Unexpected token", tok);

    return nullptr;  // Will not reach this statement!
}

PrintStatement *Parser::print() {
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
    ExprNode *comparison = expr(); // gets conditional

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