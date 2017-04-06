//
// Created by Devon Mack on 4/4/2017.
//

#include "Stack.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

Stack::Stack() {
    EPSILON = 0.000000001;
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
        cerr << "[Warning] Not pushing, stack too big." << endl;
    }

}

string Stack::operation(Button::b_event operation, string input) {
    float a;
    float b;
    bool pushResult = false;
    float toPush = 0;
    cout << "EVENT: " << operation << endl;
    switch(operation) {
        case Button::ADD:
            a = atof(input.c_str());
            b = pop();
            toPush = a+b;

            pushResult = true;
            break;
        case Button::SUBTRACT:
            a = atof(input.c_str());
            b = pop();
            toPush = b-a;
            pushResult = true;
            break;
        case Button::MULTIPLY:
            a = atof(input.c_str());
            b = pop();
            toPush = a*b;
            pushResult = true;
            break;
        case Button::DIVIDE:
            a = atof(input.c_str());
            b = pop();
            // If the divisor is 0
            if (abs(a) < EPSILON) {
            	cerr << "[ERROR] Divide by zero!" << endl;
            } else {
                toPush = b/a;
                pushResult = true;
            }
            break;
        case Button::EXPONENT:
            a = atof(input.c_str());
            b = pop();
            toPush = pow(a,b);
            pushResult = true;
            break;
        case Button::ENTER:
            push(atof(input.c_str()));
            input = "0";
            pushResult = true;
            break;
        case Button::CLEAR:
            input = "0";
            break;
        case Button::POP:
            toPush = pop();
            pushResult = true;
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
        case Button::SQRT:
            a = atof(input.c_str());
        	if (a < 0) {
        		cerr << "[ERROR] Can't square root a negative number!" << endl;
			} else {
				toPush = sqrt(a);
        		pushResult = true;
			}
        	break;
        case Button::SIN:
        	toPush = sinf(atof(input.c_str()));
        	pushResult = true;
        	break;
        case Button::COS:
        	toPush = cosf(atof(input.c_str()));
        	pushResult = true;
        	break;
        case Button::TAN:
        	a = atof(input.c_str());
        	if (abs(270-a) < EPSILON || abs(90-a) < EPSILON) {
        		cerr << "[ERROR] Can't tan that number!" << endl;
			} else {
				toPush = tanf(pop());
        		pushResult = true;
			}
        	break;
        case Button::PLUSMINUS:
        	toPush = atof(input.c_str())*-1;
        	pushResult = true;
        	break;
        case Button::RECIPROCAL:
        	toPush = 1/atof(input.c_str());
        	pushResult = true;
        	break;
        default:
            string out = "Invalid operation!";
            throw invalid_argument(out);
    }
    
    if (pushResult) {
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

