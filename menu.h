#ifndef MENU_H
#define MENU_H

#define BOLD_CYAN "\e[1;36m"
#define BOLD_BLUE "\e[1;34m"
#define BOLD_PURPLE "\e[35m"
#define BOLD_WHITE "\e[0;37m"
#define BOLD_INDIGO "\e[94m"
#define BOLD_RED "\e[31m"
#define BOLD_GREEN "\e[32m"
#define BOLD_YELLOW "\e[33m"
#define BOLD_ORANGE "\e[91m"
#define RESET "\033[0m"

void show_menu();
int get_choice();
int ask_run_again();
int is_integer(const char *s);
int get_int_input(const char *prompt);
void type_write(const char *text, int delay_ms);
void clear_input();
void loading_dots(int duration_ms);
void to_lower(char *s);
float get_float_input(const char *prompt);

#endif