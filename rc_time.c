#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <math.h>
#include "menu.h"

void start_rc(){
    float R, C, t, Vcc, V0, Vt, tau;
    char mode[20];


        type_write("\nAight, let's get this RC time constant module fired up", 10);
        loading_dots(2000);
        printf("\n===================================================================\n");
        type_write(BOLD_CYAN "       R C  T I M E  C O N S T A N T  C A L C U L A T O R\n" RESET,10);
        printf("===================================================================\n");
        
        while (1){
            // Ask charging/discharging mode
            type_write("Aight, what's it gonna be? 'charging' or 'discharging'?\n", 10);
            type_write("You can also type 'back' to bail.\n", 10);
            while (1) {
                type_write("Enter mode: ", 10);

                fgets(mode, sizeof(mode), stdin);
                mode[strcspn(mode, "\n")] = '\0';

                to_lower(mode);  // lowercase

                if (strcmp(mode, "back") == 0) {
                    type_write("Gotcha. Bouncin' back to the menu", 10);
                    loading_dots(2000);
                    return;
                }

                if (strcmp(mode, "charging") == 0 || strcmp(mode, "discharging") == 0) {
                    break;
                }
                type_write(BOLD_YELLOW "I didn't get that, bro. Type 'charging', 'discharging', or 'back'\n" RESET, 10);
            }
            
            // Resistance input
            while (1){
            R = get_float_input("Aight, what's the resistance R (in ohms)?: ");
            if (R >= 0) break;
            type_write(BOLD_YELLOW "Nah bro, R has gotta be a positive number.\n" RESET, 10);
            }  

            // Capacitance input
            while (1){
            C = get_float_input("Cool. Now what's the capacitance C (in farads)?: ");
            if (C >= 0) break;
            type_write(BOLD_YELLOW "Nah, C has gotta be a positive number.\n" RESET, 10);
            }  

            // Time constant
            tau = R * C;
            if (tau < 0.001 && tau > 0) {
             printf(BOLD_GREEN "\nSweet. Your time constant is %.3e seconds.\n" RESET, tau);
            } 
            else {
             printf(BOLD_GREEN "\nSweet. Your time constant is %.6f seconds.\n" RESET, tau);
            }
        

            // Time value
            while (1){
            t = get_float_input("Now, how long (t in seconds) are we waiting?: ");
            if (t >= 0) break;
            type_write(BOLD_YELLOW "Time can't be negative, bro. Try again.\n" RESET, 10);
            }  
            
            // ------- Charging formula -------
            if (strcmp(mode, "charging") == 0){
                while (1) {
                    Vcc = get_float_input("What's your supply voltage (Vcc)?: ");
                    if (Vcc > 0) break;
                    type_write(BOLD_YELLOW "Vcc has to be a positive voltage, bro. Try again.\n" RESET, 10);
                }
                type_write("Crunchin' the numbers", 10);
                loading_dots(2000);

                Beep(800, 100);
                Beep(1000, 100);
                Beep(1200, 150);

                // Charging formula: V(t) = Vcc * (1 - e^(-t/RC))
                Vt = Vcc * (1 - exp(-t / tau));
                printf(BOLD_GREEN "\nBoom! Voltage at t=%.2f seconds is %.4f V (charging up from 0).\n" RESET, t, Vt);
            }

            // ------- Discharging formula -------
            if (strcmp(mode, "discharging") == 0) {
                while (1) {
                    V0 = get_float_input("What's the starting voltage (V0)?: ");
                    if (V0 >= 0) break;
                    type_write(BOLD_YELLOW "V0 can't be negative, man. Try again.\n" RESET, 10);
                }
                type_write("Crunchin' the numbers", 10);
                loading_dots(2000);

                Beep(800, 100);
                Beep(1000, 100);
                Beep(1200, 150);
                
                // Discharging formula: V(t) = V0 * e^(-t/RC)
                Vt = V0 * exp(-t / tau);
                printf(BOLD_GREEN "\nBoom! Voltage at t=%.2f seconds is %.4f V (discharging from %.2f V).\n" RESET, t, Vt, V0);
            }
            printf("================================\n");
            if (!ask_run_again()) return;
        } 
}

