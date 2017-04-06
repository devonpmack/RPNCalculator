//
// Created by Devon Mack on 4/6/2017.
//

#ifndef RPN_OPERATORSTACK_H
#define RPN_OPERATORSTACK_H

#include "Stack.h"
#include <iostream>
#include <cmath>
#include <sstream>

class Operatorstack : public Stack{
    public:
        string operation(Button::b_event operation, string input);
};

#endif //RPN_OPERATORSTACK_H
