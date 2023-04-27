//
// Created by Ali Kooshesh on 4/4/23.
//

#ifndef APYTHONINTERPRETER_TOKEN_HPP
#define APYTHONINTERPRETER_TOKEN_HPP

#include<string>

class Token {

public:
    Token();

    bool &eof()  { return _eof; }
    bool &eol()  { return _eol; }

    bool eof() const { return _eof; }
    bool eol() const  { return _eol; }

    bool isOpenParen() const    { return _symbol == '('; }
    bool isCloseParen() const   { return _symbol == ')'; }

    bool isOpenBracket() const  { return _symbol == '{'; }
    bool isCloseBracket() const { return _symbol == '}'; }

    void symbol(char c) { _symbol = c; }
    char symbol() { return _symbol; }

    void setRelationalOp(std::string op) { relationalOp = op;   }
    std::string getRelationalOp()        { return relationalOp; }

    bool isSemiColon() const              { return _symbol == ';'; }
    bool isAssignmentOperator() const     { return _symbol == '='; }
    bool isMultiplicationOperator() const { return _symbol == '*'; }
    bool isAdditionOperator() const       { return _symbol == '+'; }
    bool isSubtractionOperator() const    { return _symbol == '-'; }
    bool isModuloOperator() const         { return _symbol == '%'; }
    bool isDivisionOperator() const       { return _symbol == '/'; }
    bool isIntDivisionOperator() const    { return relationalOp == "//"; }
    bool isArithmeticOperator() const {
        return isMultiplicationOperator() ||
               isAdditionOperator() ||
               isSubtractionOperator() ||
               isModuloOperator() ||
               isDivisionOperator();
    }
    bool isLessThanOperator() const { return _symbol == '<';  }
    bool isLessEqualOperator() const { return relationalOp == "<="; }
    bool isGreaterThanOperator() const { return _symbol == '>'; }
    bool isGreaterEqualOperator() const { return relationalOp == ">="; }
    bool isEqualRelationalOperator() const { return relationalOp == "==";  }
    bool isNotEqualRelationalOperator() const { return relationalOp == "!="; }
    bool isAltInequalityOperator() const { return relationalOp == "<>"; }
    bool isRelationalOp()
    {
        return isLessEqualOperator() ||
               isLessThanOperator() ||
               isGreaterEqualOperator() ||
               isGreaterThanOperator() ||
               isEqualRelationalOperator() ||
               isNotEqualRelationalOperator() ||
               isAltInequalityOperator();
    }
  
    bool isPeriod() const { return _symbol == '.'; }

    bool isName() const                   { return _name.length() > 0; }
    std::string getName() const                  { return _name; }
    void setName(std::string n) { _name = n; }
    bool isPrint() const { return _name == "print"; }
    bool isFor() const { return _name == "for"; }
    bool isKeyword() const { return isPrint() || isFor(); }

    bool &isWholeNumber() { return _isWholeNumber; }
    bool isWholeNumber() const { return _isWholeNumber; }
    int getWholeNumber() const { return _wholeNumber; }
    void setWholeNumber(int n) {
        _wholeNumber = n;
        isWholeNumber() = true;
    }

    bool &isDouble() { return _isDouble; }
    bool isDouble() const { return _isDouble; }
    double getDouble() const { return _double; }
    void setDouble(double f)
    {
        _double = f;
        isDouble() = true;
    }

    bool &isString() { return _isString; }
    bool isString() const { return _isString; }
    std::string getString() const { return _str; }
    void setString(std::string s)
    {
        _str = s;
        isString() = true;
    }

    bool &isComment() { return _isComment; }
    bool isComment() const { return _isComment; }
    std::string getComment() const { return _comment; }
    void setComment(std::string s)
    {
        _comment = s;
        isComment() = true;
    }

    bool isKeyword() {
        return isPrint() || isFor();

    }
    

  

   
    

    void print() const;

private:
    std::string _name;
    std::string relationalOp;
    bool _eof, _eol;
    bool _isWholeNumber;
    bool _isDouble;
    bool _isString;
    bool _isComment;
    char _symbol;
    int _wholeNumber;
    double _double;
    std::string _str;
    std::string _comment;
};


#endif //APYTHONINTERPRETER_TOKEN_HPP
