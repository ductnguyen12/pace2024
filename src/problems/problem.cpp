#include <problems/problem.h>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <stdexcept>
#include <utils/simple_timer.h>

#ifdef DEBUG_MODE

#include <thread>
#include <chrono>
#include <cstdio>

#endif

bool isNumber(std::string const& value) {
    return !value.empty() && std::all_of(value.begin(), value.end(),  ::isdigit);
}

Problem::Problem(int n0, int n1, std::vector<std::vector<int>> const& v1, int* cw, int* ord) : graph(n0, n1, v1), cw(cw), ord(ord) {

}

BipartiteGraph& Problem::getGraph() {
    return graph;
}

#ifdef DEBUG_MODE

bool canContinue;
int sleepTime;
StoppingCondition* shared;

void printProgress() {

    while (canContinue) {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        std::fprintf(stdout, "Progress: %8.4f%%\n", shared->getProgress() * 100);        
    }
}

#endif

Solution Problem::findSolution(Algorithm* algorithm, StoppingCondition* stoppingCondition) {
#ifdef DEBUG_MODE
    canContinue = true;
    sleepTime = 500; //milliseconds
    shared = stoppingCondition;
    std::thread progressThread(printProgress);
#endif
    Solution solution = algorithm->findSolution(&graph, stoppingCondition);
#ifdef DEBUG_MODE
    canContinue = false;
    progressThread.join();
    std::cout<<std::endl;
#endif
    return solution;
}

void Parser::tokenize(std::string const& filepath) {
    file = new std::ifstream(filepath);
    for (Token* token : tokens) delete token;
    tokens.clear();
}
bool Parser::fetch() {
    if (file == nullptr) {
        return false;
    }
    if (!file->is_open()) {
        throw std::runtime_error("Tokenization error: File is not open.");
    }
    std::string line;
    if (std::getline(*file, line)) {
        std::istringstream iss(line);
        std::string value;
        while (iss >> value) {
            if (value == "c" || value == "p") {
                tokens.push_back(new Token(value, Token::Type::KEYWORD));
            }
            else {
                tokens.push_back(new Token(value, isNumber(value) ? Token::Type::NUMBER : Token::Type::NON_NUMBER));
            }
        }
        tokens.push_back(new Token("\\n", Token::Type::NEWLINE));
    }
    else {
        tokens.push_back(new Token(Token::Type::END_OF_FILE));
        file = nullptr;
    }
    return true;
}

std::shared_ptr<Token> Parser::consume(Token::Type type, std::string const& value) {
    if (tokens.empty() && !fetch()) {
        throw std::runtime_error("Cannot fetch more tokens");
    }
    if (tokens.empty() || tokens.front()->type != type || tokens.front()->value != value) {
        return nullptr;
    }
    Token* front = tokens.front();
    tokens.pop_front();
    return std::shared_ptr<Token>(front);
}
std::shared_ptr<Token> Parser::consume(Token::Type type) {
    if (tokens.empty() && !fetch()) {
        throw std::runtime_error("Cannot fetch more tokens");
    }
    if (tokens.empty() || tokens.front()->type != type) {
        return nullptr;
    }
    Token* front = tokens.front();
    tokens.pop_front();
    return std::shared_ptr<Token>(front);
}
std::shared_ptr<Token> Parser::consume() {
    if (tokens.empty() && !fetch()) {
        throw std::runtime_error("Cannot fetch more tokens");
    }
    if (tokens.empty()) {
        return nullptr;
    }
    Token* front = tokens.front();
    tokens.pop_front();
    return std::shared_ptr<Token>(front);
}

Parser::Parser() {

}

Problem* Parser::parseProblem(std::string const& filepath) {
    SimpleTimer timer;
    tokenize(filepath);
    std::string comment;
    int n0, n1, m;
    int* cw = nullptr;
    int* ord = nullptr;
    parseComment(comment);
    parseDescription(n0, n1, m, cw, ord);
    std::vector<std::vector<int>> v1;
    parseConnection(n0, n1, m, v1);
    if (consume(Token::Type::END_OF_FILE) == nullptr || !tokens.empty()) {
        throw std::runtime_error("Parsing error: Expected end of file.");
    }
    std::cout << "Reading time: " << timer.count() << "\n";
    timer.start();
    Problem* problem = new Problem(n0, n1, v1, cw, ord);
    std::cout << "Preparing time: " << timer.count() << "\n";
    return problem;
}

void Parser::parseComment(std::string& comment) {
    comment = "";
    std::shared_ptr<Token> c = consume(Token::Type::KEYWORD, "c");
    if (c != nullptr) {
        while ((c = consume()) != nullptr) {
            if (c->type == Token::Type::END_OF_FILE || c->type == Token::Type::NEWLINE) {
                break;
            }
            comment.append(" " + c->value);
        }
        if (c == nullptr) {
            throw std::runtime_error("Parsing error: Out of tokens.");
        }
        else if (c->type != Token::Type::NEWLINE) {
            throw std::runtime_error("Parsing error: Expected a newline token.");
        }
    }
#ifdef DEBUG_MODE
    std::cout << "Comment: " << comment << std::endl;
#endif
}

void Parser::parseDescription(int& n0, int& n1, int& m, int*& cw, int*& ord) {
    cw = nullptr;
    ord = nullptr;
    if (consume(Token::Type::KEYWORD, "p") == nullptr) {
        throw std::runtime_error("Parsing error: Expected a keyword \"p\".");
        return;
    }
    if (consume(Token::Type::NON_NUMBER, "ocr") == nullptr) {
        throw std::runtime_error("Parsing error: Expected a num-numeric token \"ocr\".");
        return;
    }
    std::shared_ptr<Token> token;
    if ((token = consume(Token::Type::NUMBER)) == nullptr) {
        throw std::runtime_error("Parsing error: Expected a numeric token \"n0\".");
        return;
    }
    n0 = std::stoi(token->value);
    if ((token = consume(Token::Type::NUMBER)) == nullptr) {
        throw std::runtime_error("Parsing error: Expected a numeric token \"n1\".");
        return;
    }
    n1 = std::stoi(token->value);
    if ((token = consume(Token::Type::NUMBER)) == nullptr) {
        throw std::runtime_error("Parsing error: Expected a numeric token \"m\".");
        return;
    }
    m = std::stoi(token->value);
#ifdef DEBUG_MODE
    std::cout << "n0: " << n0 << " n1: " << n1 << " m: " << m;
#endif
    if ((token = consume(Token::Type::NEWLINE)) == nullptr) {
        parseCutWidth(n0, n1, m, cw, ord);
    }
#ifdef DEBUG_MODE
    std::cout << std::endl;
#endif
}
void Parser::parseCutWidth(int const& n0, int const& n1, int const& m, int*& cw, int*& ord) {
    std::shared_ptr<Token> token;
    if ((token = consume(Token::Type::NUMBER)) == nullptr) {
        throw std::runtime_error("Parsing error: Expected a numeric token \"cw\".");
        return;
    }
    if (consume(Token::Type::NEWLINE) == nullptr) {
        throw std::runtime_error("Parsing error: Expected a newline token.");
        return;
    }
    cw = new int(std::stoi(token->value));
    ord = new int[n0 + n1];
    for (int idx = 0; idx < n0 + n1; idx++) {
        if ((token = consume(Token::Type::NUMBER)) == nullptr) {
            throw std::runtime_error("Parsing error: Expected a numeric token.");
            return;
        }
        ord[idx] = std::stoi(token->value);
        if (consume(Token::Type::NEWLINE) == nullptr) {
            throw std::runtime_error("Parsing error: Expected a newline token.");
            return;
        }
    }
#ifdef DEBUG_MODE
    std::cout << *cw << " [";
    for (int i = 0; i < n0 + n1; i++) std::cout << " " << ord[i] << " ";
    std::cout << "]" << std::endl;
#endif
}
void Parser::parseConnection(int const& n0, int const& n1, int const& m, std::vector<std::vector<int>>& v1) {
    v1.resize(n1);
    std::shared_ptr<Token> token;
    for (std::vector<int>& v : v1) v.clear();
    for (int idx = 0; idx < m; idx++) {
        if ((token = consume(Token::Type::NUMBER)) == nullptr) {
            throw std::runtime_error("Parsing error: Expected a numeric token.");
            return;
        }
        int a = std::stoi(token->value);
        if ((token = consume(Token::Type::NUMBER)) == nullptr) {
            throw std::runtime_error("Parsing error: Expected a numeric token.");
            return;
        }
        int b = std::stoi(token->value);
        if ((token = consume(Token::Type::NEWLINE)) == nullptr) {
            throw std::runtime_error("Parsing error: Expected a newline token.");
            return;
        }
        v1[b - n0 - 1].push_back(a - 1);
    }
#ifdef DEBUG_MODE
    for (int i=0; i < v1.size(); i++) {
        std::cout << n0 + i + 1 << ": ";
        for (int& n : v1[i]) {
            std::cout << n + 1 << " ";
        }
        std::cout << std::endl;
    }
#endif
}