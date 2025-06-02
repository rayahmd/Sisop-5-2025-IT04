#include "std_lib.h"

// Division implementation (supports negative numbers)
int div(int a, int b) {
    if (b == 0) return 0;  // Handle division by zero
    
    int sign = 1;
    if (a < 0) {
        a = -a;
        sign = -sign;
    }
    if (b < 0) {
        b = -b;
        sign = -sign;
    }
    
    int result = 0;
    while (a >= b) {
        a -= b;
        result++;
    }
    
    return sign * result;
}

// Modulo implementation (supports negative numbers)
int mod(int a, int b) {
    if (b == 0) return 0;  // Handle modulo by zero
    
    int sign = (a < 0) ? -1 : 1;
    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;
    
    while (a >= b) {
        a -= b;
    }
    
    return sign * a;
}

// String comparison
bool strcmp(char *s1, char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2) == 0;
}

// String copy
void strcpy(char *dst, char *src) {
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';
}

// Clear buffer (set to zero)
void clear(void *buf, int size) {
    char *p = (char *)buf;
    for (int i = 0; i < size; i++) {
        *p++ = 0;
    }
}

// String to integer (supports negative numbers)
int atoi(char *str) {
    int res = 0;
    int sign = 1;
    int i = 0;

    // Handle negative numbers
    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            break;
        res = res * 10 + str[i] - '0';
    }

    return sign * res;
}

// Integer to string (supports negative numbers)
void itoa(int num, char *str) {
    int i = 0;
    int is_negative = 0;

    // Handle 0 explicitly
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // Handle negative numbers
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % 10;
        str[i++] = rem + '0';
        num = num / 10;
    }

    // Append negative sign
    if (is_negative)
        str[i++] = '-';

    str[i] = '\0'; // Null-terminate string

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char tmp = str[start];
        str[start] = str[end];
        str[end] = tmp;
        start++;
        end--;
    }
}

int getRandom() {
    static unsigned int seed = 42;
    seed = seed * 1103515245 + 12345;
    return (seed / 65536) % 32768;
}
