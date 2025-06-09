#include "std_lib.h"

int div(int a, int b) {
    int sign, result; 

    sign = 1;
    result = 0;

    if (b == 0) {
        return 0;
    }

    if (a < 0) {
        a = -a;
        sign = -sign;
    }
    if (b < 0) {
        b = -b;
        sign = -sign;
    }

    while (a >= b) {
        a -= b;
        result++;
    }

    return sign * result;
}

int mod(int a, int b) {
    //int sign;

   // sign = 1;
    if (b == 0) {
        return 0;
    }

    /*if (a < 0) {
        sign = -1;
        a = -a;
    }
    if (b < 0) {
        sign = -1;
        b = -b;
    }
*/
    while (a >= b) {
        a -= b;
    }

    return a;
}

int strcmp(char *s1, char *s2) {
    while (*s1 != '\0' || *s2 != '\0') {
        if (*s1 != *s2) {
            return 1;
        }
        s1++;
        s2++;
    }
    return 0;
}

void strcpy(char *dst, char *src) {
    while (*src != '\0') {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
}

void clear(byte *buf, unsigned int size) {
    unsigned int i;
    for (i = 0; i < size; i++) {
        buf[i] = '\0';
    }
}

void atoi(char *str, int *num) {
    int res, sign, i;

    res = 0;
    sign = 1;
    i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            break;
        }
        res = res * 10 + (str[i] - '0');
    }

    *num = sign * res;
}

void itoa(int num, char *str) {
    int i, is_negative, start, end;
    char tmp;
    int rem;

    i = 0;
    is_negative = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    while (num != 0) {
        rem = mod(num, 10);
        str[i++] = rem + '0';
        num = div(num, 10);
    }

    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    // Reverse string
    start = 0;
    end = i - 1;
    while (start < end) {
        tmp = str[start];
        str[start] = str[end];
        str[end] = tmp;
        start++;
        end--;
    }
}
