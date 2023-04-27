#ifndef EXPRINTER_TYPEDESCRIPTOR_HPP
#define EXPRINTER_TYPEDESCRIPTOR_HPP

#include <string>
#include <iostream>
#include <vector>

class TypeDescriptor
{
public:
    enum types
    {
        INTEGER,
        DOUBLE,
        STRING
    };

    TypeDescriptor(types type) : _type{type} {}

    types &type() { return _type; }

    virtual ~TypeDescriptor() {}

    virtual void print() = 0;

private:
    types _type;
};

class IntegerDescriptor : public TypeDescriptor
{
public:
    IntegerDescriptor(int value) : TypeDescriptor(INTEGER), _value(value) {}
    int value() { return _value; }
    void print() { std::cout << value(); }

private:
    int _value;
};

class DoubleDescriptor : public TypeDescriptor
{
public:
    DoubleDescriptor(double value) : TypeDescriptor(DOUBLE), _value(value) {}
    double value() { return _value; }
    void print() { std::cout << value(); }

private:
    double _value;
};

class StringDescriptor : public TypeDescriptor
{
public:
    StringDescriptor(std::string value) : TypeDescriptor(STRING), _value(value) {}
    std::string value() { return _value; }
    void print() { std::cout << value(); }

private:
    std::string _value;
};

#endif // EXPRINTER_TYPEDESCRIPTOR_HPP
