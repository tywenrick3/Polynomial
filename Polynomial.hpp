//
//  Polynomial.hpp
//  h8Final
//
//  Created by Ty Wenrick on 5/2/22.
//

#ifndef Polynomial_hpp
#define Polynomial_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

struct PolyNode {
    PolyNode(int coef, int expo, PolyNode* next)
            : coef(coef), expo(expo), next(next) {}
    ~PolyNode();
    int coef;
    int expo;
    PolyNode* next;
};

class Polynomial {
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
    friend bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
    friend const Polynomial& operator+(Polynomial& lhs, Polynomial& rhs);
public:
    Polynomial();
    Polynomial(std::vector<int> nums);
    Polynomial(const Polynomial& rhs);
    Polynomial& operator=(Polynomial& rhs);
    int evaluate(int x);
    Polynomial& operator+=(Polynomial& rhs);
    void append(const PolyNode* node);
    
private:
    int degree;
    PolyNode* head;
};

#endif /* Polynomial_hpp */
