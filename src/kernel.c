#include "shell.h"
#include "kernel.h"

int main() {
  clearScreen();
  shell();
}

void printString(char *str)
{
  //TODO: Implementasi fungsi untuk mencetak string
  int i = 0;
  while(str[i] != '\0'){
    char c = str[i];
    interrupt(0x10, 0x0E00 + c, 0, 0, 0);
    i++;
  }
}

void readString(char *buf)
{
  //TODO: Implementasi fungsi untuk membaca string
    int i = 0;
    char c = 0;
    while (1) {
        c = interrupt(0x16, 0x0000, 0, 0, 0);
        if (c == 0x0D) break; // Enter
        if (c == 0x08 && i > 0) { // Backspace
            i--;
            interrupt(0x10, 0x0E00 + 0x08, 0x07, 0, 0);
            interrupt(0x10, 0x0E00 + ' ', 0x07, 0, 0);
            interrupt(0x10, 0x0E00 + 0x08, 0x07, 0, 0);
        } else if (c >= 0x20 && c <= 0x7E) { // Printable characters
            buf[i++] = c;
            interrupt(0x10, 0x0E00 + c, 0x07, 0, 0);
        }
    }
    buf[i] = '\0';
    printString("\r\n");
}

void clearScreen()
{
  //TODO: Implementasi fungsi untuk membersihkan layar
  int i;
  for (i = 0; i < 80 * 25 * 2; i += 2) {
        putInMemory(0xB800, i, ' ');
        putInMemory(0xB800, i + 1, 0x07); 
  }
  interrupt(0x10, 0x0200, 0, 0, 0);
}
