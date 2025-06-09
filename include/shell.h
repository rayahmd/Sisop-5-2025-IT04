#ifndef __SHELL_H__
#define __SHELL_H__

#include "std_type.h"

void shell();
void parseCommand(char *buf, char *cmd, char arg[2][64]);
void updatePrompt();
void handleGrandCompany(char *arg);
void handleCalculator(char *cmd, char arg[2][64]);
void changeColor(byte color);

// Tambahkan fungsi bila perlu

#endif // __SHELL_H__
