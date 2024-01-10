#ifndef PROBLEM_H
#define PROBLEM_H

#include <graph/bipartite_graph.h>
#include <algorithms/algorithm.h>
#include <algorithms/solution.h>
#include <initializer_list>
#include <string>
#include <list>
#include <memory>

class Problem {
private:
    BipartiteGraph graph;
    int *cw, *ord;
public:
    Problem(int n0, int n1, std::vector<std::vector<int>> const& v1, int* cw, int* ord);
    Solution findSolution(Algorithm& algorithm);
};

class Token {
public:
    enum Type { KEYWORD, NUMBER, NON_NUMBER, NEWLINE, END_OF_FILE };
    Type const type;
    std::string const value;
    Token(std::string const& value, Type const type) : value(value), type(type) { }
    Token(Type const type) : type(type) { }
};

class Parser {
private:
    std::list<Token*> tokens;
public:
    Parser();

    void tokenize(std::string const& filepath);
    std::shared_ptr<Token> consume(Token::Type type, std::string const value);
    std::shared_ptr<Token> consume(Token::Type type);
    std::shared_ptr<Token> consume();
    void parseComment(std::string& comment);
    void parseDescription(int& n0, int& n1, int& m, int*& cw, int*& ord);
    void parseCutWidth(int const& n0, int const& n1, int const& m, int*& cw, int*& ord);
    void parseConnection(int const& n0, int const& n1, int const& m, std::vector<std::vector<int>>& v1);
    Problem* parseProblem(std::string const& filepath);
};

#endif