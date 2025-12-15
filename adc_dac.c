// adc_dac.c
// Entry function for Analog-to-Digital (ADC) and Digital-to-Analog (DAC) conversion calculator
// ADC code calculation and binary representation 
// DAC output voltage computation
// Quantisation step size

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include "menu.h"

void start_adcdac() {

    char mode[10]; 
    float vref, analog_in;
    int bits, digital_in;

    type_write("\nAight, let's get this converter module fired up", 10);
    loading_dots(2000);
    printf("===================================================================\n");
    type_write(BOLD_BLUE "                  A D C/ D A C  C O N V E R T E R\n" RESET,10);
    printf("===================================================================\n");

    while (1){
        // Ask user what mode
        type_write("Aight, what's it gonna be? 'adc' (Analog-to-Digital) or 'dac' (Digital-to-Analog)?\n", 10);
        type_write("You can also type 'back' to bail.\n", 10);

        // MODE INPUT LOOP
        while (1) {
            type_write("Enter mode: ", 10);

            fgets(mode, 9, stdin);
            mode[strcspn(mode, "\n")] = '\0';

            to_lower(mode);    // lowercase check

            if (strcmp(mode, "back") == 0) {
                type_write("Gotcha. Bouncin' back to the menu", 10);
                loading_dots(2000);
                return;
            }
            if (strcmp(mode, "adc") == 0 || strcmp(mode, "dac") == 0) {
                    break; 
            }
            type_write(BOLD_YELLOW "I didn't get that, bro. Type 'adc', 'dac', or 'back'.\n" RESET, 10);
        }   

        // ------------------ ADC MODE ------------------
        if (strcmp(mode, "adc") == 0) {
            printf("===================================================================\n");
            type_write(BOLD_RED "                          A D C  M O D E\n" RESET,10);
            printf("===================================================================\n");

            // Ask for Vref
            while (1){
            vref = get_float_input("What's the reference voltage (Vref)? (e.g., 5 or 3.3): ");
            if (vref > 0) break;
            type_write(BOLD_YELLOW "Vref must be a positive number, bro.\n" RESET, 10);
            }   

            // Ask for resolution (bits)
            while (1){
            bits = get_int_input("How many bits of resolution we workin' with? (e.g., 8, 10, 12): ");
            if (bits > 0) break;
            type_write(BOLD_YELLOW "Bits must be a positive integer, man. Try again.\n" RESET, 10);
            }

            // Analog input validation
            while (1){
            analog_in = get_float_input("Aight, what's the analog voltage you're converting?: ");
            if (analog_in >= 0 && analog_in <= vref) break;
            type_write(BOLD_YELLOW "Analog voltage must be between 0 and your Vref, bro.\n" RESET, 10);
            }

            // Max ADC code: 2^bits - 1
            int max_code = (1 << bits) - 1;

            // ADC step size = Vref / max_code
            float step = vref / max_code;

            // Convert analog to digital code
            int digital = (int)((analog_in/vref) * max_code);
            if (digital > max_code) digital = max_code;
            if (digital < 0) digital = 0;

            // Convert to binary string
            char binary[33];
            for (int i = bits - 1; i >= 0; i--) {
                binary[bits - 1 - i] = ((digital >> i) & 1) + '0';
            }
            binary[bits] = '\0';

            // Quantisation error = +/- (step/2)
            float q_error = step / 2.0f;

            type_write("Crunchin' the numbers", 10);
            loading_dots(2000);
            
            Beep(800, 100);
            Beep(1000, 100);
            Beep(1200, 150);

            printf("\n=========== ADC CONVERSION RESULTS ===========\n");
            printf(BOLD_GREEN "\nADC Step Size (Resolution): %.6f V\n" RESET, step);
            printf(BOLD_GREEN"Digital Output (decimal): %d\n" RESET, digital);
            printf(BOLD_GREEN "Digital Output (binary): %s\n" RESET, binary);
            printf(BOLD_GREEN "Quantisation Error: +/- %.6f V\n\n" RESET, q_error);
            printf("================================================\n");
        }

        // ------------------ DAC MODE ------------------
        else if (strcmp(mode, "dac") == 0) {
            printf("===================================================================\n");
            type_write(BOLD_RED "                          D A C  M O D E\n" RESET,10);
            printf("===================================================================\n");

            // Vref input
            while (1){
                vref = get_float_input("What's the reference voltage (Vref)? (e.g., 5 or 3.3): ");
                if (vref > 0) break;
                type_write(BOLD_YELLOW "Vref must be a positive number, bro.\n" RESET, 10);
            }  

            // Bit resolution
            while (1){
                bits = get_int_input("How many bits of resolution we workin' with? (e.g., 8, 10, 12): ");
                if (bits > 0) break;
                type_write(BOLD_YELLOW "Bits must be a positive integer, man. Try again.\n" RESET, 10);
            }

            // Digital input
            while (1) {
                digital_in = get_int_input("Aight, what's the digital value you're converting?: ");
                if (digital_in >= 0 && digital_in < (1 << bits)) break;
                type_write(BOLD_YELLOW "Digital input must be between 0 and max code, bro.\n" RESET, 10);
            }

            // DAC step size
            float step = vref / ( (1 << bits) - 1 );

            // Convert digital to analog
            float analog_out = step * digital_in;

            type_write("Crunchin' the numbers", 10);
            loading_dots(2000);
            
            Beep(800, 100);
            Beep(1000, 100);
            Beep(1200, 150);

            printf("\n=========== DAC CONVERSION RESULTS ===========\n");
            printf(BOLD_GREEN "DAC Step Size (Resolution): %.6f V\n" RESET, step);
            printf( BOLD_GREEN "Resulting Analog Output Voltage: %.6f V\n\n" RESET, analog_out);
            printf("================================================\n");

        }
        if (!ask_run_again()) return;
    
    }
}