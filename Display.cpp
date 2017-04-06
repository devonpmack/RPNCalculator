//
// Created by Devon Mack on 4/4/2017.
//

#include "Display.h"
#include <iostream>
#include <sstream>

using namespace std;

Display::Display(int x1_in, int y1_in, int width, int height, ALLEGRO_COLOR color_in, float num) {
    x1 = x1_in;
    y1 = y1_in;
    w = width;
    h = height;

    color = color_in;
    margin = 2;
    number = num;

    //convert int to string
    stringstream ss;
    ss << num;
    text = ss.str();

    cout << "Initialized numpad " << number << endl;
    font = al_load_font("font.ttf",30,0);

    if (!font) {
        cout << "FAILED TO LOAD FONT" << endl;
    }

}

float Display::getNum() {
    return number;
}

void Display::setNumber(float num) {
    number = num;
    stringstream ss;
    ss << num;
    text = ss.str();
}
