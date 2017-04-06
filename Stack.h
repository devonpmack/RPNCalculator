//
// Created by Devon Mack on 4/4/2017.
//

#ifndef RPN_STACK_H
#define RPN_STACK_H

#include "Button.h"

class Stack {
    private:
        int top;
        float data[80];
        float EPSILON;
    public:
        Stack();
        void push(float n);
        float pop();
        string operation(Button::b_event operation, string input);
        void print();
        //~Stack();
};


#endif //RPN_STACK_H
