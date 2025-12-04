#include <stdio.h>
#include <windows.h>
#include "menu.h"
#include "funcs.h"

// Entry point of the Engineering Assistant program.
// Displays menu, gets user choice, and switches to the requested feature.

int main() {
    int choice;
    // Intro message with typing effect
    type_write("\nYo, system's on. I'm your engineering buddy. Check out what I can do:\n", 30);

    while (1) {
        // Show main menu and get user's choice
        show_menu();
        choice = get_choice();

        // Execute the selected option
        switch (choice) {
            case 1:
                start_rcalc();          // Resistance calculator
                break;
            case 2:
                start_adcdac();         // ADC/DAC converter
                break;
            case 3:
                start_colourcode();     // Resistor colour code decoder
                break;
            case 4:
                start_rc();             // RC time constant calculator
                break;
            case 0:
                // Exit program
                type_write(BOLD_RED "Aight, peace out. Shutting down" RESET, 30);
                loading_dots(3000);
                return 0;
            default:
                // Error sound + invalid message
                Beep(400, 120);
                Beep(300, 120);
                Beep(200, 150);
                type_write(BOLD_YELLOW "Nah bro, that's not an option. Pick one from the list." RESET, 30);
                Sleep(2000);
        }
    }

    return 0;
}
