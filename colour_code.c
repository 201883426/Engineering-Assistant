#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "menu.h"

// Structure representing a single resistor colour entry
// value -> digit value for the colour
// multiplier -> what the colour multiplies the value by
// tolerance -> percentage tolerance of the band
// ansi -> terminal ANSI background colour code

typedef struct {
    char color[12];
    int value;
    float multiplier;
    float tolerance;
    int ansi;
} ColorCode;

// Full colour lookup table (digit, multiplier, tolerance data)
ColorCode table[] = {
    {"black", 0, 1, -1, 0},
    {"brown", 1, 10, 1, 94},
    {"red", 2, 100, 2, 196},
    {"orange", 3, 1000, -1, 208},
    {"yellow", 4, 10000, -1, 226},
    {"green", 5, 100000, 0.5, 46},
    {"blue", 6, 1000000, 0.25, 21},
    {"violet", 7, 10000000, 0.1, 93},
    {"grey", 8, 100000000, 0.05, 245},
    {"white", 9, 1000000000, -1, 231},
    {"gold", -1, 0.1, 5, 220},
    {"silver", -1, 0.01, 10, 7}
};
int table_size = sizeof(table) / sizeof(table[0]);

// Find a colour in the table by name and return the corresponding struct
int find_color(char *name, ColorCode *out) {
    to_lower(name);
    for (int i = 0; i < table_size; i++) {
        if (strcmp(name, table[i].color) == 0) {
            *out = table[i];
            return 1;
        }
    }
    return 0;
}

// Continually ask for a valid colour until the user enters one
void get_valid_colour(const char *prompt, ColorCode *out, int allow) {
    char input[20];
    while (1) {
        type_write(prompt, 20);
        scanf("%19s", input);
        clear_input();

        if (find_color(input, out)){
            if (!allow && out->value == -1) {
                type_write(BOLD_YELLOW "Nah bro, Gold and Silver only work for Multiplier and Tolerance. Try again.\n" RESET, 20);
                continue;
            }
            return;
        }

        type_write(BOLD_YELLOW "Whoa, never heard of that color. Check your spelling, man (and use 'grey', not 'gray').\n" RESET, 20);
    }
}

// Print resistance in ohm, k-ohm or M-ohm format
void print_resistance(float value) {
    if (value >= 1e6)
        printf(BOLD_GREEN "Resistance: %.2f Mohms\n" RESET, value / 1e6);
    else if (value >= 1e3)
        printf(BOLD_GREEN "Resistance: %.2f kohms\n" RESET, value / 1e3);
    else
        printf(BOLD_GREEN "Resistance: %.2f ohms\n" RESET, value);
}

// Print a colour band preview block
void print_band_preview(ColorCode c) {
    if (c.ansi < 0)
        printf("[??]");
    else
        printf("\033[48;5;%dm  \033[0m", c.ansi);
}

// Print a 4‑band resistor preview
void print_resistor_preview_4(ColorCode b1, ColorCode b2, ColorCode mul, ColorCode tol) {
    printf("\nResistor Preview:\n---| ");
    print_band_preview(b1);
    printf(" ");
    print_band_preview(b2);
    printf(" ");
    print_band_preview(mul);
    printf(" ");
    print_band_preview(tol);
    printf(" |---\n");
}

// Print a 5‑band resistor preview
void print_resistor_preview_5(ColorCode b1, ColorCode b2, ColorCode b3, ColorCode mul, ColorCode tol) {
    printf("\nResistor Preview:\n---| ");
    print_band_preview(b1);
    printf(" ");
    print_band_preview(b2);
    printf(" ");
    print_band_preview(b3);
    printf(" ");
    print_band_preview(mul);
    printf(" ");
    print_band_preview(tol);
    printf(" |---\n");
}

void start_colourcode() {

    int bands;
    char exp[5];
    ColorCode b1, b2, b3, mul, tol;

    // Intro animation
    type_write("\nYo, let's crack this color code", 30);
    loading_dots(2500);
    printf("===================================================================\n");
    type_write(BOLD_PURPLE "       R E S I S T O R  C O L O U R  C O D E  D E C O D E R\n" RESET,20);
    printf("===================================================================\n");

    // Ask user if they understand colour bands
    type_write("First up, you know the deal with these color bands? (yes/no)\n", 20);
    type_write("You can also type 'back' to bail:", 20);
    while (1){
        if (scanf("%9s", exp) != 1) {
            type_write(BOLD_RED "Input error, man. Bailing.\n" RESET, 20);
            return;
        }
        clear_input();
        to_lower(exp);

        if (strcmp(exp, "no") == 0) {
            // Full explanation if user doesn't know
            type_write("\nAll good, bro. Here's the lowdown:\n\n", 20);
            
            type_write("Resistor Colour Code Basics\n", 20);
            type_write("----------------------------------\n", 20);
            type_write("A resistor has coloured bands that represent numbers.\n", 20);
            type_write("The first 2 or 3 bands = digits of the resistance value.\n", 20);
            type_write("The next band = multiplier (how many zeros).\n", 20);
            type_write("The last band = tolerance (accuracy).\n\n", 20);

            type_write("  4-Band Resistor:\n", 20);
            type_write("  Band 1 -> 1st digit\n", 20);
            type_write("  Band 2 -> 2nd digit\n", 20);
            type_write("  Band 3 -> multiplier (x10, x100, etc.)\n", 20);
            type_write("  Band 4 -> tolerance (% error)\n\n", 20);

            type_write("  5-Band Resistor:\n", 20);
            type_write("  Band 1 -> 1st digit\n", 20);
            type_write("  Band 2 -> 2nd digit\n", 20);
            type_write("  Band 3 -> 3rd digit\n", 20);
            type_write("  Band 4 -> multiplier\n", 20);
            type_write("  Band 5 -> tolerance\n\n", 20);

            type_write("Aight, now you just type in your colors.\n\n", 20);
            break;

        } 
        else if (strcmp(exp, "yes") == 0) {
            type_write("\nSweet. You know what's up. Let's do this\n\n", 20);
            break;
        }
        else if (strcmp(exp, "back") == 0) {
            type_write("Gotcha. Bouncin' back", 20);
            loading_dots(2000);
            return;
        }
        else {
            type_write(BOLD_YELLOW "\nNah, just type 'yes', 'no' or 'back':" RESET, 20);
        }
    }
    
    // Main loop for decoding resistor after explanation
    while (1){
        // Ask how many bands the resistor has
        while (1) {
            bands  = get_int_input("So, we lookin' at a 4 or 5 band resistor? (or 0 to bail):");

            if (bands == 0) {
                type_write("Aight, bouncin' back", 30);
                loading_dots(2000);
                return;
            }

            if (bands != 4 && bands != 5) {
                type_write(BOLD_YELLOW "Whoa, I only do 4 or 5 band, man. Try again.\n" RESET, 20);
                continue;
            }
            break;
        }

        type_write("\nCool. Let's crack this code.\n", 25);
        type_write("Gimme the colors, one by one.\n\n", 25);
        
        // ------------------ 4 BAND ------------------
        if (bands == 4) {

            get_valid_colour("Band 1 (1st digit): ", &b1, 0);
            get_valid_colour("Band 2 (2nd digit): ", &b2, 0);
            get_valid_colour("Band 3 (Multiplier): ", &mul, 1);
            get_valid_colour("Band 4 (Tolerance): ", &tol, 1);

            float resistance = (b1.value * 10 + b2.value) * mul.multiplier;

            type_write("\nFigurin' it out", 25);
            loading_dots(2000);
            print_resistor_preview_4(b1, b2, mul, tol);

            Beep(800, 100);
            Beep(1000, 100);
            Beep(1200, 150);

            printf("\n=========== RESULT ===========\n");
            print_resistance(resistance);
            printf(BOLD_GREEN "Tolerance: +/-%.2f%%\n" RESET, tol.tolerance);
            printf("================================\n");
        }

        // ------------------ 5 BAND ------------------
        else if (bands == 5) {

            get_valid_colour("Band 1 (1st digit): ", &b1, 0);
            get_valid_colour("Band 2 (2nd digit): ", &b2, 0);
            get_valid_colour("Band 3 (3rd digit): ", &b3, 0);
            get_valid_colour("Band 4 (Multiplier): ", &mul, 1);
            get_valid_colour("Band 5 (Tolerance): ", &tol, 1);

            float resistance = (b1.value * 100 + b2.value * 10 + b3.value) * mul.multiplier;

            type_write("\nFigurin' it out", 25);
            loading_dots(2000);
            print_resistor_preview_5(b1, b2, b3, mul, tol);

            Beep(800, 100);
            Beep(1000, 100);
            Beep(1200, 150);

            printf("\n=========== RESULT ===========\n");
            print_resistance(resistance);
            printf(BOLD_GREEN "Tolerance: +/-%.2f%%\n" RESET, tol.tolerance);
            printf("================================\n");

        }
        // Ask to run again
        if (!ask_run_again()) break;

    }
}
