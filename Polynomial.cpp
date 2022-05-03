//
//  Polynomial.cpp
//  h8Final
//
//  Created by Ty Wenrick on 5/2/22.
//

#include "Polynomial.hpp"

using namespace std;

Polynomial::Polynomial() {
    head = new PolyNode(0, 0, nullptr);
    degree = 0;
}

PolyNode::~PolyNode() {
    if (next != nullptr) {
        delete next;
    }
    next = nullptr;
}

Polynomial::Polynomial(const Polynomial& rhs) : head(nullptr){
    PolyNode** last = &head;
    degree = rhs.degree;
    for (PolyNode* curr = rhs.head; curr; curr = curr->next) {
        *last = new PolyNode(curr->coef, curr->expo, *last);
        last = &(*last)->next;
    }
}


Polynomial& Polynomial::operator=(Polynomial& rhs) {
    if (this != &rhs) {
        delete head;
        head = rhs.head;
        degree = rhs.degree;
    }
    return *this;
}

Polynomial::Polynomial(vector<int> nums) {
    degree = nums.size() - 1;
    // set constant node first
    PolyNode* constantNode = new PolyNode(nums[degree], 0, nullptr);
    PolyNode** curr = &constantNode;
    for (int i = degree + 1 - 2; i >= 0; --i) {
        *curr = new PolyNode(nums[i], nums.size() - i - 1, *curr);
    }
    head = *curr;
}

int Polynomial::evaluate(int x) {
    int result = 0;
    for(PolyNode* curr = head; curr != nullptr; curr = curr->next) {
        result = x * result + curr->coef;
    }
    return result;
}

const Polynomial& operator+(Polynomial& lhs, Polynomial& rhs) {
    return lhs += rhs;
}

Polynomial& Polynomial::operator+=(Polynomial &rhs) {
    PolyNode* ptr1 = head;
    PolyNode* ptr2 = rhs.head;
    PolyNode* resultHead = nullptr;
    PolyNode* resultTail = nullptr;
    
    if (ptr1->expo == ptr2->expo) {
        // add coef, insert new node in result
        ptr1->coef += ptr2->coef;
        PolyNode* newNode = new PolyNode(ptr1->coef, ptr1->expo, nullptr);
        resultHead = newNode;
        resultTail = resultHead;
        // increment both
        ptr1 = ptr1 -> next;
        ptr2 = ptr2 -> next;
    } else if (ptr1 -> expo > ptr2 -> expo) {
        // insert new node by ptr1 in result
        PolyNode* newNode = new PolyNode(ptr1->coef, ptr1->expo, nullptr);
        resultHead = newNode;
        resultTail = resultHead;
        // increment ptr1
        ptr1 = ptr1 -> next;
    } else {
        // insert new node by ptr2 in result
        PolyNode* newNode = new PolyNode(ptr2->coef, ptr2->expo, nullptr);
        resultHead = newNode;
        resultTail = resultHead;
        // increment ptr2
        ptr2 = ptr2 -> next;
    }
    
    while (ptr1 != nullptr && ptr2 != nullptr) {
        if (ptr1->expo == ptr2->expo) {
            // add coef, insert new node in result list
            ptr1->coef += ptr2->coef;
            PolyNode* newNode = new PolyNode(ptr1->coef, ptr1->expo, nullptr);
            resultTail->next = newNode;
            resultTail = resultTail->next;
            // increment both
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        } else if (ptr1->expo > ptr2->expo) {
            // insert new node by ptr1 in result
            PolyNode* newNode = new PolyNode(ptr1->coef, ptr1->expo, nullptr);
            resultTail->next = newNode;
            resultTail = resultTail->next;
            // increment ptr1
            ptr1 = ptr1->next;
        } else {
            // insert new node by ptr2 in result
            PolyNode* newNode = new PolyNode(ptr2->coef, ptr2->expo, nullptr);
            resultTail->next = newNode;
            resultTail = resultTail->next;
            // increment ptr2
            ptr2 = ptr2->next;
        }
        
    }
    // fill remaining
    if (ptr1 != nullptr) {
        resultTail->next = ptr1;
    } else if (ptr2 != nullptr) {
        resultTail->next = ptr2;
    }
    // set results, cleanup
    delete ptr1;
    head = resultHead;
    degree = resultHead->expo;
    return *this;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
      if (lhs.degree != rhs.degree) return false;
      for (size_t i = 0; i < lhs.degree + 1; ++i) {
        if (lhs.head != rhs.head) return false;
      }
      return true;
}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
    return !(lhs == rhs);
}


ostream& operator<<(ostream& os, const Polynomial& rhs){
    // zero poly
    if (rhs.head->expo == 0 && rhs.head->coef == 0) {
        os << "0\n";
        return os;
    }
    PolyNode* walker = rhs.head;
    while (walker != nullptr) {
        if (walker -> coef == 0 && walker -> next){
            walker = walker -> next;
        }
        if (walker -> expo > 1 && walker->coef != 1) {
            os << walker->coef << "x^" << walker->expo << " + ";
        } else if (walker->expo == 1) {
            if (walker->coef == -1) {
                os << "-x + ";
            } else if (walker->coef == 1) {
                os << "x + ";
            } else {
                os << walker->coef << "x + ";
            }
        } else {
            os << walker -> coef;
        }
        walker = walker -> next;
    }
    return os;
}
