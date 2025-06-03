#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char username[16] = "user";
char company_suffix[16] = "";
byte current_color = 0x07; // Default white color

void updatePrompt();
void handleGrandCompany(char *arg);
void handleCalculator(char *cmd, char arg[2][64]);
int getRandom();

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
    int i = 0, j = 0, k = 0;

    /* a) Ambil cmd (kata pertama) */
    while (buf[i] != ' ' && buf[i] != '\0' && i < 15) {
        cmd[i] = buf[i];
        i++;
    }
    cmd[i] = '\0';

    /* b) Lewati spasi, ambil arg[0] */
    if (buf[i] == ' ') i++;
    while (buf[i] != ' ' && buf[i] != '\0' && j < 63) {
        arg[0][j++] = buf[i++];
    }
    arg[0][j] = '\0';

    /* c) Lewati spasi, ambil arg[1] */
    if (buf[i] == ' ') i++;
    while (buf[i] != ' ' && buf[i] != '\0' && k < 63) {
        arg[1][k++] = buf[i++];
    }
    arg[1][k] = '\0';

    // Feature 1: The Echo (default behavior)
    if (strcmp(cmd, "") == 0) {
        return;
    }

    // Feature 2: gurt/yo
    if (strcmp(cmd, "yo") == 0) {
        printString("gurt\n");
        return;
    }
    if (strcmp(cmd, "gurt") == 0) {
        printString("yo\n");
        return;
    }

    // Feature 3: Change username
    if (strcmp(cmd, "user") == 0) {
        if (arg[0][0] == '\0') {
            strcpy(username, "user");
            printString("Username changed to user\n");
        } else {
            strcpy(username, arg[0]);
            printString("Username changed to ");
            printString(username);
            printString("\n");
        }
        return;
    }

    // Feature 4: Grand Company
    if (strcmp(cmd, "grandcompany") == 0) {
        handleGrandCompany(arg[0]);
        return;
    }

    // Feature 5: Clear command
    if (strcmp(cmd, "clear") == 0) {
        clearScreen();
        current_color = 0x07; // Reset to white
        company_suffix[0] = '\0'; // Remove company suffix
        return;
    }

    // Feature 6: Calculator commands
    if (strcmp(cmd, "add") == 0 || strcmp(cmd, "sub") == 0 || 
        strcmp(cmd, "mul") == 0 || strcmp(cmd, "div") == 0) {
        handleCalculator(cmd, arg);
        return;
    }

    // Feature 7: Yogurt command (random response)
    if (strcmp(cmd, "yogurt") == 0) {
        int r = getRandom() % 3;
        if (r == 0) {
            printString("gurt> yo\n");
        } else if (r == 1) {
            printString("gurt> ts unami gng </3\n");
        } else {
            printString("gurt> sygau\n");
        }
        return;
    }


    // Default behavior (The Echo)
    printString(buf);
    printString("\n");
}

void handleGrandCompany(char *arg) {
    if (strcmp(arg, "maelstrom") == 0) {
        clearScreen();
        current_color = 0x04; // Red
        strcpy(company_suffix, "Storm");
    } else if (strcmp(arg, "twinadder") == 0) {
        clearScreen();
        current_color = 0x0E; // Yellow
        strcpy(company_suffix, "Serpent");
    } else if (strcmp(arg, "immortalflames") == 0) {
        clearScreen();
        current_color = 0x01; // Blue
        strcpy(company_suffix, "Flame");
    } else {
        printString("Invalid Grand Company\n");
    }
    
    // Change text color for future output
    interrupt(0x10, 0x0E00 + ' ', current_color, 0, 0);
}

void handleCalculator(char *cmd, char arg[2][64]) {
    int x, y;
    atoi(arg[0], &x);
    atoi(arg[1], &y);
    int result = 0;
    char result_str[16];

    if (strcmp(cmd, "add") == 0) {
        result = x + y;
    } else if (strcmp(cmd, "sub") == 0) {
        result = x - y;
    } else if (strcmp(cmd, "mul") == 0) {
        result = x * y;
    } else if (strcmp(cmd, "div") == 0) {
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
    // Change text color for future output
    current_color = color;
    interrupt(0x10, 0x0E00 + ' ', color, 0, 0);
}
