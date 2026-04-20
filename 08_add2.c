#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static void write_real(double value) {
    char buffer[64];
    char *exp = NULL;
    int exponent = 0;
    char sign;
    if (snprintf(buffer, sizeof(buffer), " %.16E", value) < 0) {
        return;
    }
    exp = strchr(buffer, 'E');
    if (exp == NULL) {
        printf("%s", buffer);
        return;
    }
    sign = exp[1];
    for (char *p = exp + 2; *p != '\0'; ++p) {
        if (*p >= '0' && *p <= '9') {
            exponent = exponent * 10 + (*p - '0');
        }
    }
    *exp = '\0';
    printf("%sE%c%03d", buffer, sign, exponent);
}

static bool read_bool(bool *out_value) {
    char buffer[16];
    if (scanf("%15s", buffer) != 1) {
        return false;
    }
    if (strcmp(buffer, "true") == 0 || strcmp(buffer, "1") == 0) {
        *out_value = true;
        return true;
    }
    if (strcmp(buffer, "false") == 0 || strcmp(buffer, "0") == 0) {
        *out_value = false;
        return true;
    }
    return false;
}

static void write_bool(bool value) {
    printf("%s", value ? "true" : "false");
}

int16_t g_a;
int16_t g_b;

int main(void) {
    g_a = 10;
    g_b = -1;
    printf("%d", (int)g_a + g_b);
    ;
    return 0;
}
