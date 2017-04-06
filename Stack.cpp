//
// Created by Devon Mack on 4/4/2017.
//

#include "Stack.h"

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

