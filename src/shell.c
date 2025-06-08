#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char username[16] = "user";
char company_suffix[16] = "";
byte current_color = 0x07;

void updatePrompt();
void parseCommand(char *buf, char *cmd, char arg[2][64]);
void handleGrandCompany(char *arg);
void handleCalculator(char *cmd, char arg[2][64]);
void changeColor(byte color);

void shell() {
    char buf[128];
    char cmd[16];
    char arg[2][64];

    printString("Welcome to EorzeOS!\n");
    while (true) {
        updatePrompt();
        printString("> ");

        clear(buf, 128);
        readString(buf);

        clear(cmd, 16);
        clear(arg[0], 64);
        clear(arg[1], 64);

        parseCommand(buf, cmd, arg);
    }
}

void updatePrompt() {
    printString(username);
    if (company_suffix[0] != '\0') {
        printString("@");
        printString(company_suffix);
    }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
    int i, j, k, r;

    i = 0;
    j = 0;
    k = 0;

    while (buf[i] != ' ' && buf[i] != '\0' && i < 15) {
        cmd[i++] = buf[i];
    }
    cmd[i] = '\0';

    while (buf[i] == ' ') i++;
    while (buf[i] != ' ' && buf[i] != '\0' && j < 63) {
        arg[0][j++] = buf[i++];
    }
    arg[0][j] = '\0';

    while (buf[i] == ' ') i++;
    while (buf[i] != ' ' && buf[i] != '\0' && k < 63) {
        arg[1][k++] = buf[i++];
    }
    arg[1][k] = '\0';

    if (strcmp(cmd, "yo")) {
        printString("gurt\n");
    } else if (strcmp(cmd, "gurt")) {
        printString("yo\n");
    } else if (strcmp(cmd, "user")) {
        if (arg[0][0] == '\0') {
            strcpy(username, "user");
            printString("Username reset to 'user'\n");
        } else {
            strcpy(username, arg[0]);
            printString("Username changed to ");
            printString(username);
            printString("\n");
        }
    } else if (strcmp(cmd, "grandcompany")) {
        handleGrandCompany(arg[0]);
    } else if (strcmp(cmd, "clear")) {
        clearScreen();
        company_suffix[0] = '\0';
        changeColor(0x07);
    } else if (strcmp(cmd, "add") || strcmp(cmd, "sub") ||
               strcmp(cmd, "mul") || strcmp(cmd, "div")) {
        handleCalculator(cmd, arg);
    } else if (strcmp(cmd, "yogurt")) {
        r = mod(getRandom(), 3);
        if (r == 0) {
            printString("gurt> yo\n");
        } else if (r == 1) {
            printString("gurt> ts unami gng </3\n");
        } else {
            printString("gurt> sygau\n");
        }
    } else if (strcmp(cmd, "") == false) {
        printString("Command not found: ");
        printString(buf);
        printString("\n");
    }
}

void handleGrandCompany(char *arg) {
    byte new_color;
    char new_suffix[16];
    bool valid_company;

    new_color = current_color;
    valid_company = true;

    if (strcmp(arg, "maelstrom")) {
        new_color = 0x04;
        strcpy(new_suffix, "Storm");
    } else if (strcmp(arg, "twinadder")) {
        new_color = 0x0E;
        strcpy(new_suffix, "Serpent");
    } else if (strcmp(arg, "immortalflames")) {
        new_color = 0x01;
        strcpy(new_suffix, "Flame");
    } else {
        printString("Invalid Grand Company. Options: maelstrom, twinadder, immortalflames\n");
        valid_company = false;
    }

    if (valid_company) {
        clearScreen();
        strcpy(company_suffix, new_suffix);
        changeColor(new_color);
    }
}

void handleCalculator(char *cmd, char arg[2][64]) {
    int x, y, result;
    char result_str[16];

    result = 0;

    atoi(arg[0], &x);
    atoi(arg[1], &y);

    if (strcmp(cmd, "add")) {
        result = x + y;
    } else if (strcmp(cmd, "sub")) {
        result = x - y;
    } else if (strcmp(cmd, "mul")) {
        result = x * y;
    } else if (strcmp(cmd, "div")) {
        if (y == 0) {
            printString("Error: Division by zero\n");
            return;
        }
        result = x / y;
    }

    itoa(result, result_str);
    printString(result_str);
    printString("\n");
}

void changeColor(byte color) {
    current_color = color;
    interrupt(0x10, 0x0E00 + ' ', color, 0, 0);
}