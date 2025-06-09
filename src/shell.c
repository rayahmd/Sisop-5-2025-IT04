#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char username[16] = "user";
char company_suffix[16] = "";
int current_color = 0x07;

// void updatePrompt();
// void parseCommand(char *buf, char *cmd, char arg[2][64]);
// void handleGrandCompany(char *arg);
// void handleCalculator(char *cmd, char arg[2][64]);
// void changeColor(byte color);

void shell() {
    char buf[128];
    char cmd[16];
    char arg[2][64];

    changeColor(current_color);
    printString("Welcome to EorzeOS!\r\n");
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
    int i, j, k;

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

    if (strcmp(cmd, "yo") == 0) {
        printString("gurt\r\n");
    } else if (strcmp(cmd, "gurt") == 0) {
        printString("yo\r\n");
    } else if (strcmp(cmd, "user") == 0) {
        if (arg[0][0] == '\0') {
            strcpy(username, "user");
            printString("Username reset to 'user'\r\n");
        } else {
            strcpy(username, arg[0]);
            printString("Username changed to ");
            printString(username);
            printString("\r\n");
        }
    } else if (strcmp(cmd, "grandcompany") == 0) {
        handleGrandCompany(arg[0]);
    } else if (strcmp(cmd, "clear") == 0) {
        clearScreen();
        company_suffix[0] = '\0';
        changeColor(0x07);
    } else if (strcmp(cmd, "add") == 0 || strcmp(cmd, "sub") == 0 ||
               strcmp(cmd, "mul") == 0 || strcmp(cmd, "div") == 0) {
        handleCalculator(cmd, arg);
    } else if (strcmp(cmd, "yogurt") == 0) {
        unsigned int random_value = getBiosTick();
        int r = mod(random_value, 3);
        if (r == 0) {
            printString("gurt> yo\r\n");
        } else if (r == 1) {
            printString("gurt> ts unami gng </3\r\n");
        } else {
            printString("gurt> sygau\r\n");
        }
    } else if (strcmp(cmd, "") == 0) {
        printString("Command not found: ");
        printString(buf);
        printString("\r\n");
    } else {
        printString(buf);
        printString("\r\n");
    }
}

void handleGrandCompany(char *arg) {
    int new_color;
    char new_suffix[16];
    int valid_company;

    new_color = current_color;
    valid_company = 0;

    if (strcmp(arg, "maelstrom") == 0) {
        new_color = 0x0C;
        strcpy(new_suffix, "Storm");
    } else if (strcmp(arg, "twinadder") == 0) {
        new_color = 0x0E;
        strcpy(new_suffix, "Serpent");
    } else if (strcmp(arg, "immortalflames") == 0) {
        new_color = 0x09;
        strcpy(new_suffix, "Flame");
    } else {
        printString("Invalid Grand Company. Options: maelstrom, twinadder, immortalflames\r\n");
        valid_company = 1;
    }

    if (valid_company == 0) {
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

    if (strcmp(cmd, "add") == 0) {
        result = x + y;
    } else if (strcmp(cmd, "sub") == 0) {
        result = x - y;
    } else if (strcmp(cmd, "mul") == 0) {
        result = x * y;
    } else if (strcmp(cmd, "div") == 0) {
        if (y == 0) {
            printString("Error: Division by zero\r\n");
            return;
        }
        result = x / y;
    }

    itoa(result, result_str);
    printString(result_str);
    printString("\r\n");
}

void changeColor(byte color) {
    current_color = color;
    interrupt(0x10, 0x0600, (color << 8), 0x0000, 0x184F);
}
