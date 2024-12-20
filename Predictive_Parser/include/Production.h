#ifndef PRODUCTION_H
#define PRODUCTION_H
#include <iostream>
#include <vector>
#include <string>

class Production {
public:
    Production(std::string rhs, std::vector<std::string> lhs);
    std::string getLhs();
    std::vector<std::string> getRhs();
    void setLhs(std::string lhs);
    void setRhs(std::vector<std::string> rhs);
    void addRhs(std::string rhs);
private:
    std::string lhs;
    std::vector<std::string> rhs;
};

#endif // PRODUCTION_H