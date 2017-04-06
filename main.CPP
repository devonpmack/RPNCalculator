/**********************************************************************\
* Program name      : RPN Calculator
*       |
*       | Author            : Devon Mack
*       |
*       | Date created      : 4/4/2017
*
* Purpose           : RPN Calculator with Allegro 5
*                     https://github.com/devonpmack/RPNCalculator
*
* Known Issues      : 1. Errors are all shown in console
*                     2. Display the pop() warning a lot
*                     3. The X is really ugly with this font
*
\**********************************************************************/

/* Need if not a project */
 #include "Stack.cpp"
 #include "Numpad.cpp"
 #include "Button.cpp"
/*                       */

#include "Button.h"
#include "Stack.h"
#include "Numpad.h"

#include <iostream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <wtypes.h>
#include <sstream>

#define BLUE al_map_rgb(158, 207, 255)
#define YELLOW al_map_rgb(255,255,158)
#define GREEN al_map_rgb(207,255,158)
#define WHITE al_map_rgb(255, 255, 255)
#define RED al_map_rgb(255, 158, 158)
#define ORANGE al_map_rgb(255,176,97)

bool initializeAllegro(ALLEGRO_DISPLAY *&display);

// Constants
const int size = 90; // The size of each 'square' on the calculator, button sizing is based off this
const int margin = 2; //
const int ScreenWidth = 5*size;
const int ScreenHeight = 10*size;
const int NumButtons = 17;

ALLEGRO_EVENT_QUEUE *event_queue = NULL;

using namespace std;

int main(int argc, char **argv) {
    ALLEGRO_DISPLAY *display = NULL;

    Stack stack;

    if (!initializeAllegro(display)) {
        return false;
    }

    // --- Initialize all the buttons/displays ---
    // Numpad
    Numpad *numberPad[10];
    int counter = 0;
    int locationy = size*5;

    //Initialize the numpad buttons
    numberPad[0] = new Numpad(margin,size*4+margin+locationy,size-margin,size-margin,GREEN, 0);
    counter++;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            numberPad[counter] = new Numpad(j*size+margin,i*size+size+locationy+margin,
                                            size-margin,size-margin,GREEN, counter);
            counter++;
        }
    }

    locationy = size*5;
    Button *buttons[17];

    // SECOND LINE C AC POP POW
    buttons[0] = new Button(margin, margin+locationy, size-margin, size-margin, RED, "C",
                            Button::CLEAR);
    buttons[1] = new Button(margin+size, margin+locationy, size-margin, size-margin, RED, "AC",
                            Button::ALLCLEAR);
    buttons[2] = new Button(margin+size*2, margin+locationy, size-margin, size-margin, RED, "DEL",
                            Button::DEL);
    buttons[3] = new Button(margin+size*3, margin+locationy, size-margin, size-margin, BLUE, "POP",
                            Button::POP);
    buttons[4] = new Button(margin+size*4, margin+locationy, size-margin, size-margin, BLUE, "POW",
                            Button::EXPONENT);

    // Basic math
    buttons[5] = new Button(margin+size*3, margin+size*1+locationy, size-margin, size-margin, BLUE, "+",
                            Button::ADD);
    buttons[6] = new Button(margin+size*4, margin+size*1+locationy, size-margin, size-margin, BLUE, "-",
                            Button::SUBTRACT);
    buttons[7] = new Button(margin+size*3, margin+size*2+locationy, size-margin, size-margin, BLUE, "x",
                            Button::MULTIPLY);
    buttons[8] = new Button(margin+size*4, margin+size*2+locationy, size-margin, size-margin, BLUE, "/",
                            Button::DIVIDE);

    // BELOW NUMPAD
    buttons[9] = new Button(margin+size*3, margin+size*4+locationy, size-margin, size-margin, BLUE, ".",
                            Button::DECIMAL);
    buttons[10] = new Button(margin+size*4,margin+size*4+locationy , size-margin, size-margin, BLUE, "+/-",
                             Button::PLUSMINUS);

    //2nd from
    buttons[11] = new Button(margin+size*3, margin+size*3+locationy, size-margin, size-margin, BLUE, "SQRT",
                             Button::SQRT);
    buttons[12] = new Button(margin+size*4, margin+size*3+locationy, size-margin, size-margin, BLUE, "1/x",
                             Button::RECIPROCAL);

    // ENTER
    buttons[13] = new Button(margin+size, margin+size*4+locationy, size*2-margin, size-margin, RED, "ENTER",
                             Button::ENTER);
	
	//TRIG functions
	buttons[14] = new Button(margin, margin+locationy-size, ScreenWidth/3-margin, size-margin, YELLOW, "SIN",
                             Button::SIN);
	buttons[15] = new Button(margin+ScreenWidth/3, margin+locationy-size, ScreenWidth/3-margin, size-margin, YELLOW, "COS",
                             Button::COS);
	buttons[16] = new Button(margin+2*ScreenWidth/3, margin+locationy-size, ScreenWidth/3-margin, size-margin, YELLOW, "TAN",
                             Button::TAN);
	
    // Initialize the displays
    Numpad *calc_display[4];

    calc_display[0] = new Numpad(margin*3, margin*2, size*5-margin*6, size-margin*3, WHITE, 0);
    calc_display[1] = new Numpad(margin*3, margin*2+size, size*5-margin*6, size-margin*3, WHITE, 0);
    calc_display[2] = new Numpad(margin*3, margin*2+size*2, size*5-margin*6, size-margin*3, WHITE, 0);
    calc_display[3] = new Numpad(margin*3, margin*2+size*3, size*5-margin*6, size-margin*3, WHITE, 0);

    // --- Draw the calculator ---
    // Draw the buttons
    for (int i = 0; i < NumButtons; i++) {
        cout << "Drawing button " << i << endl;
        buttons[i]->draw();
    }

    // Draw the displays
    al_draw_filled_rectangle(0,0,ScreenWidth,margin+size*4,ORANGE);
    for (int i = 0; i < 4; i++) {
        cout << "Drawing display " << i << endl;
        calc_display[i]->draw();
    }

    // Draw the numpad
    for (int i = 0; i < 10; i++) {
        cout << "Drawing pad " << i << endl;
        numberPad[i]->draw();
    }

    al_flip_display();

    // --- Main Loop ---
    ALLEGRO_EVENT ev;
    int numPress;
    bool updateDisplay = false;
    float popThree[3];
    string input = "0";
    stringstream ss;


    while(true) {
        al_wait_for_event(event_queue, &ev); // Wait for event

            // If [x] is clicked then close game
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
            // If keyboard pressed
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                break;
            }
        }
            // Mouse clicked
        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            // Left mouse button (create cell)
            if(ev.mouse.button == 1) {
                // Find what the user clicked
                // Check numpad
                for (int i = 0; i < 10; i++) {
                    if (numberPad[i]->checkMouse(ev.mouse.x,ev.mouse.y)) {
                        // If the user pressed a numpad button, add it to the string.
                        numPress = numberPad[i]->getNum();

                        // Convert the number pressed to a string
                        ss.str("");
                        ss << numPress;

                        // Don't let the display show nothing
                        if (input == "0") {
                            input = ss.str();
                        } else {
                            // add the number to the display/string
                            input += ss.str();
                        }

                        // Update the display
                        updateDisplay = true;
                    }
                }
                // Check buttons
                for (int i = 0; i < NumButtons; i++) {
                    if (buttons[i]->checkMouse(ev.mouse.x,ev.mouse.y)) {
                        // Run the event of the button,
                        input = stack.operation(buttons[i]->getEvent(), input);
                        updateDisplay = true;
                    }
                }
            }
        }
        if (updateDisplay) {
            // Update the display to display the top 4 numbers of the stack

            //The top display is a special case since the user can modify it
            calc_display[0]->setText(input);
            calc_display[0]->draw();

            // pop the top 3 to find what they are
            for (int i = 0; i < 3; i++) {
                popThree[i] = stack.pop();
            }

            // push them back
            for (int i = 2; i >= 0; i--) {
                calc_display[i+1]->setNumber(popThree[i]);
                calc_display[i+1]->draw();
                stack.push(popThree[i]);
            }

            // finished updating the display
            updateDisplay = false;
            al_flip_display();
        }
    }

    return 0;
}

bool initializeAllegro(ALLEGRO_DISPLAY *&display) {
    if (!al_init()) {
        cerr << "failed to initialize allegro! "  << endl;
        return false;
    }
    cout << "Successfully Initialized Allegro" << endl;

    if (!al_init_primitives_addon())  {
        cerr << "failed to initialize primitives! "  << endl;
        return false;
    }
    cout << "Initialized Primitives" << endl;

    if (!al_init_font_addon())  {
        cerr << "failed to initialize primitives! "  << endl;
        return false;
    }
    cout << "Initialized font addon" << endl;

    if (!al_init_ttf_addon())  {
        cerr << "failed to initialize primitives! "  << endl;
        return false;
    }
    cout << "Initialized ttf addon" << endl;

    if (!al_install_keyboard()) {
        cerr << "failed to initialize the keyboard! "  << endl;
        return false;
    }
    cout << "Successfully Initialized keyboard" << endl;

    if(!al_install_mouse()) {
        cerr << "failed to initialize the mouse!" << endl;
        return -1;
    }
    cout << "Successfully Initialized mouse" << endl;

    al_set_new_display_flags(ALLEGRO_WINDOWED); //| ALLEGRO_RESIZABLE);
    display = al_create_display(ScreenWidth, ScreenHeight);
    cout << "Successfully Initialized display" << endl;

    al_clear_to_color(WHITE);

    event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_mouse_event_source()); //mouse clicks
    al_register_event_source(event_queue, al_get_keyboard_event_source()); //keyboard presses
    al_register_event_source(event_queue, al_get_display_event_source(display)); //click x
    cout << "Successfully Initialized All of Allegro" << endl;
    return true;
}
