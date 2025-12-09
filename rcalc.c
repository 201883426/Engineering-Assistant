#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include "menu.h"

// Entry function for the Resistance Calculator
void start_rcalc() {   
        char type[20];              // Stores user input: "series" / "parallel"
        int n;                      // Number of resistors
        float value;                // Temporary resistor value
        float series_sum = 0;       // Sum for series resistors
        float reciprocal_sum = 0;   // Sum of reciprocals for parallel
        float total = 0;            // Final calculated resistance

        // Intro animation
        type_write("\nAight, firing up the Resistance Calculator", 10);
        loading_dots(2000);

        printf("===================================================================\n");
        type_write(BOLD_GREEN"             R E S I S T A N C E  C A L C U L A T O R\n" RESET,10);
        printf("===================================================================\n");

        while (1){
        // Ask user for circuit type
        type_write("Aight, you got these resistors in 'series' or 'parallel'?\n", 10);
        type_write("(Hit 'back' if you wanna bail)\n", 10);

        // Loop until valid word is given
        while (1) {
        type_write("Gimme the word: ", 10);

        fgets(type, 19, stdin);
        type[strcspn(type, "\n")] = '\0';   // Strip newline

        to_lower(type);  // Convert to lowercase
        
        // Allow returning to menu
        if (strcmp(type, "back") == 0) {
            type_write("Gotcha. Bouncin' back to the menu", 10);
            loading_dots(2000);
            return;
        }

        // Accept only "series" and "parallel"
        if (strcmp(type, "series") == 0 || strcmp(type, "parallel") == 0) {
            break;
        }
        type_write(BOLD_YELLOW "Bro, I didn't get that. Just type 'series', 'parallel', or 'back'.\n" RESET, 10);
    }

        // Ask how many resistors
        type_write("Cool. How many resistors we talkin' for this ", 10);
        type_write(type, 30);
        type_write(" circuit?\n", 30);
        
        while (1) {
            n = get_int_input("Enter number: ");
            if (n <= 0) {
                type_write(BOLD_YELLOW "Nah bro, need at least 1 resistor.\n" RESET, 10);
                continue;
            }
            break;
        }

        // Reset sums for calculation
        series_sum = 0;
        reciprocal_sum = 0;
        total = 0;

        /* ==========================
               SERIES CALCULATION
           ========================== */
        if (strcmp(type, "series") == 0) {
            printf("====================================================\n");
            printf(BOLD_ORANGE "              S E R I E S  C I R C U I T            \n" RESET);
            printf("                                                    \n");
            printf("  IN ---[ R1 ]----[ R2 ]----[ R3 ]----[ R... ]--- OUT\n");
            printf("====================================================\n");
            type_write("Alright, hit me with the (ohm) values for each one.\n", 10);

            // Collect resistor values
            for (int i = 1; i <= n; i++) {
                    while (1){
                        char prompt[64];
                        sprintf(prompt, "Value for Resistor %d (in ohms): ", i);
                        value = get_float_input(prompt);
                        if (value < 0) {
                            type_write(BOLD_RED "\n Whoa, bro. Can't have negative ohms. That ain't real.\n" RESET,10);
                            Sleep(2000);
                        } 
                        else {
                            break;    // Valid value
                        }
                        }
                        series_sum += value;    // Add to total
            }

            // Output calculating animation
            type_write("Crunchin' the numbers", 10);
            loading_dots(2000);

            // Fun sound effects
            Beep(800, 100);
            Beep(1000, 100);
            Beep(1200, 150);

            // Display result
            printf(BOLD_GREEN "\nBoom! Total series resistance: %.2f ohms. Easy.\n" RESET, series_sum );
        }
        
        /* ==========================
               PARALLEL CALCULATION
           ========================== */
        else {
            printf("====================================================\n");
            printf(BOLD_ORANGE "           P A R A L L E L  C I R C U I T           \n" RESET);
            printf("                                                    \n");
            printf("                 +----[ R1 ]----+                   \n");
            printf("                 |               |                   \n");
            printf("  IN ------------+----[ R2 ]----+------------ OUT  \n");
            printf("                 |               |                   \n");
            printf("                 +----[ R... ]---+                   \n");
            printf("                                                    \n");
            printf("====================================================\n");
            type_write("Alright, hit me with the (ohm) values for each one.\n", 10);
            for (int i = 1; i <= n; i++) {
                while (1){
                    char prompt[64];
                    sprintf(prompt, "Value for Resistor %d (in ohms): ", i);
                    value = get_float_input(prompt);

                    // Validate resistor value
                    if (value == 0) {
                        type_write(BOLD_RED "\nYo, hold up! Can't use 0 in parallel, man. It breaks math (division-by-zero).\n" RESET,10);
                        continue;
                    } else if (value < 0){
                        type_write(BOLD_RED "\n Whoa, bro. Can't have negative ohms. That ain't real.\n" RESET,10);
                    } else {
                        break;
                    }
                }
                    reciprocal_sum += 1.0f / value;     // Add reciprocal
            }

            // Final parallel resistance
            total = 1.0f / reciprocal_sum;

            type_write("Crunchin' the numbers", 10);
            loading_dots(2000);

            Beep(800, 100);
            Beep(1000, 100);
            Beep(1200, 150);
            printf(BOLD_GREEN "\nDone! Total parallel resistance: %.2f ohms. Cool stuff.\n" RESET, total);
        }

        // Ask if user wants another calculation
        if (!ask_run_again()) return;
    }
}

