//
// Created by Devon Mack on 4/4/2017.
//

#ifndef RPN_NUMPAD_H
#define RPN_NUMPAD_H
#include "Button.h"
#include "Stack.h"

class Display : public Button {
    private:
        float number;

    public:
        Display(int x1_in, int y1_in, int width, int height, ALLEGRO_COLOR color_in, float num);
        float getNum();
        void setNumber(float num);
};


#endif //RPN_NUMPAD_H
