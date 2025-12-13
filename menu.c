// menu.c
// Displays the main menu and handles navigation
// Includes all user interface functionality for the Engineering Assistant.

#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include "menu.h"

// Prints characters one-by-one with a small delay for typing effect.
void type_write(const char *text, int delay_ms) {
    while (*text) {
        putchar(*text++);   // Print next character
        fflush(stdout);     // Flush to show immediately
        Sleep(delay_ms);    // Delay for typing effect
    }
}

// Displays the main menu with color formatting and typing effect.
void show_menu() {
    printf("\n=================================================================================\n");
    type_write(BOLD_YELLOW "                   E N G I N E E R I N G  A S S I S T A N T              \n" RESET,10);
    printf("=================================================================================\n");
    type_write(BOLD_GREEN "     O P T I O N  1:  R E S I S T A N C E  C A L C U L A T O R\n" RESET, 10);
    type_write(BOLD_BLUE "     O P T I O N  2:  A D C/ D A C  C O N V E R T E R\n" RESET,10);
    type_write(BOLD_PURPLE "     O P T I O N  3:  R E S I S T O R  C O L O U R  C O D E  D E C O D E R\n" RESET,10);
    type_write(BOLD_CYAN "     O P T I O N  4:  R C  T I M E  C O N S T A N T  C A L C U L A T O R\n" RESET,10);
    type_write(BOLD_RED "     O P T I O N  0:  E X I T\n" RESET, 10);
    printf("=================================================================================\n");
}

// Clears leftover characters from stdin until newline.
void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Checks if a string represents a valid integer (with optional + or - sign).
int is_integer(const char *s) {
    if (!s || !*s) return 0;    // Empty string

    if (*s == '+' || *s == '-') {
        s++;
        if (!*s) return 0;     // Sign alone is invalid
    }

    while (*s) {
        if (!isdigit((unsigned char)*s))
            return 0;          // Non-digit found
        s++;
    }
    return 1;
}

// Reads an integer safely with validation.
int get_int_input(const char *prompt) {
    char buf[64];
    int value;

    while (1) {
        type_write(prompt, 20);
        if (!fgets(buf, sizeof(buf), stdin)) continue;

        buf[strcspn(buf, "\n")] = '\0';     // Remove newline

        if (!is_integer(buf)) {
            type_write(BOLD_YELLOW "Yo, gimme a real number.\n" RESET, 10);
            continue;
        }

        value = atoi(buf);                  // Convert to integer
        return value;
    }
}

// Reads a floating‑point number safely.
float get_float_input(const char *prompt)
{
    char buf[128];
    float f;
    while (1) {
        type_write(prompt, 20);

        if (!fgets(buf, sizeof(buf), stdin)) {
            printf("Input error\n");
            exit(1);
        }

        char *end;
        f = strtof(buf, &end);          // Convert to float

        if (end != buf && *end == '\n' || *end == '\0')
            return f;                   // Valid number

        type_write(BOLD_YELLOW "Not a number bro. Try again.\n" RESET, 10);
    }
}


// Gets a validated menu choice from the user.
int get_choice() {
    char buf[128];
    int value = 0;
    int valid = 0;

    enum { MENU_ITEMS = 5 };   // 0..4 (0 = exit)

    do {
        type_write("Please select an option: ", 10);

        if (!fgets(buf, sizeof(buf), stdin)) {
            type_write("Input error. Exiting...\n", 10);
            exit(1);
        }

        buf[strcspn(buf, "\r\n")] = '\0';   // Remove newline

        if (!is_integer(buf)) {
            type_write(BOLD_YELLOW "Yo, gimme a whole number, not that gobbledygook.\n" RESET, 10);
            valid = 0;
            continue;
        }

        value = (int)strtol(buf, NULL, 10);


        if (value >= 0 && value <= 4) {
            valid = 1;
        } else {
            type_write(BOLD_YELLOW "That's not on the list, chief. Try again.\n" RESET, 10);
            valid = 0;
        }

    } while (!valid);

    return value;
}


// Prints dots (...) with delay for loading animation.
void loading_dots(int duration_ms) {
    int cycles = duration_ms / 500;

    for (int i = 0; i < cycles; i++) {
        printf(".");
        fflush(stdout);
        Sleep(500);  // 500 ms
    }

    printf("\n");
}

// Converts all characters in a string to lowercase. Used for normalizing user input.
void to_lower(char *s) {
    for (int i = 0; s[i]; i++){
        s[i] = tolower(s[i]);
    }
}


// Asks user if they want to run the calculation again.
int ask_run_again() {
    char choice[10];

    type_write("\n-------------------------------------------------\n", 3);
    type_write("Aight, calculation done. Wanna run another? (yes/no): ", 10);

    while (1) {
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0'; // Remove newline
        to_lower(choice);                     // Normalize input

        if (strcmp(choice, "yes") == 0)
            return 1;   

        if (strcmp(choice, "no") == 0 || strcmp(choice, "back") == 0) {
            type_write("Gotcha. Bouncin' back to the menu", 10);
            loading_dots(2000);
            return 0;   
        }
        // Invalid response
        type_write(BOLD_YELLOW "Bro, it's a 'yes' or 'no' question: " RESET, 10);
    }
}

