#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char username[16] = "user";

void shell(){
    char buf[128];
    char cmd[16];
    char arg[2][64];

    printString("Welcome to EorzeOS!\n");
    while (true) {
        printString(username);
        printString("> ");

        clear(buf, 128);
        readString(buf);

        clear(cmd, 16);
        clear(arg[0], 64);
        clear(arg[1], 64);

        parseCommand(buf, cmd, arg);
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


//yogurt nomor 2
    if (strcmp(cmd, "yo")) {
        printString("gurt\n");
        return;
    }
    if (strcmp(cmd, "gurt")) {
        printString("yo\n");
        return;
    }

    //ganti user nomer 2
    if(strcmp(cmd, "user")){
      if(arg[0][0] == '\0'){
        strcpy(username, "user");
        printString("username changed to user\n");
      } else{
        strcpy(username, arg[0]);
        printString("username changed to ");
        printString(username);
        printString("\n");
      }
      return;
    }

    printString(buf);
    printString("\n");
}

// Tambahkan fungsi lain nanti sesuai soal berikutnya...
