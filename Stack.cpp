//
// Created by Devon Mack on 4/4/2017.
//

#include "Stack.h"
#include "Button.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

Stack::Stack() {
    EPSILON = 0.0000001;
    top = -1;
    for (int i = 0; i < 40; i++) {
        data[i] = 0;
    }
}

float Stack::pop() {
    float ret;
    if (top >= 0) {
        ret = data[top];
        top--;
    } else {
        cout << "[Warning] Popping from empty stack (will give 0)" << endl;
        return 0;
    }

    return ret;
}

void Stack::push(float n) {
    // Stack can't be too big
    if (top < 79) {
        data[++top] = n;
    } else {
        throw invalid_argument("Not pushing, stack too big!");
    }

}

string Stack::operation(Button::b_event operation, string input) {
    float a;
    float b;
    bool ontop;
    float toPush;
    print();
    cout << "EVENT: " << operation << endl;
    switch(operation) {
        case Button::ADD:
            push(atof(input.c_str()));
            a = pop();
            b = pop();
            toPush = a+b;

            ontop = true;
            break;
        case Button::SUBTRACT:
            push(atof(input.c_str()));
            a = pop();
            b = pop();
            toPush = b-a;
            ontop = true;
            break;
        case Button::MULTIPLY:
            push(atof(input.c_str()));
            a = pop();
            b = pop();
            push(a*b);
            ontop = true;
            break;
        case Button::DIVIDE:
            push(atof(input.c_str()));
            a = pop();
            b = pop();
            if (abs(a) < EPSILON) {
                throw invalid_argument("Divide by zero.");
            } else {
                push(b/a);
                ontop = true;
                break;
            }
        case Button::EXPONENT:
            push(atof(input.c_str()));
            a = pop();
            b = pop();
            push(pow(a,b));
            ontop = true;
            break;
        case Button::ENTER:
            push(atof(input.c_str()));
            input = "0";
            ontop = true;
            break;
        case Button::CLEAR:
            input = "0";
        case Button::POP:
            toPush = pop();
            ontop = true;
            break;
        case Button::ALLCLEAR:
            input = "0";
            top = -1;
            break;
        case Button::DEL:
            input = input.erase(input.size()-1);
            if (input == "") {
                input = "0";
            }
            break;
        case Button::DECIMAL:
            input += ".";
            break;
        default:
            string out = "Invalid operation!";
            throw invalid_argument(out);
    }
    if (ontop) {
        //convert int to string
        stringstream ss;
        ss << toPush;
        return ss.str();
    }

    return input;
}

void Stack::print() {
    int n = top;
    cout << "Stack---" << endl;
    while (n >= 0) {
        cout << data[n--] << endl;
    }
    cout << "---" << endl;
}

/*Stack::~Stack() {
	cout << "destroy";
}*/

float Stack::sTop() {
    if (top >= 0) {
        return data[top];
    } else {
        return 0;
    }

}
