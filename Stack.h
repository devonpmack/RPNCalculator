//
// Created by Devon Mack on 4/4/2017.
//

#ifndef RPN_STACK_H
#define RPN_STACK_H

#include <iostream>
#include "Button.h"

class Stack {
    protected:
        int top;
        float data[80];
        float EPSILON;
    public:
        Stack();
        void push(float n);
        float pop();
        void print();
        ~Stack() { cout << "Unloading stack." << endl;};
};


#endif //RPN_STACK_H
