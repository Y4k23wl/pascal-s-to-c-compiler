#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static void write_real(double value) {
    char buffer[64];
    char formatted[64];
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
    snprintf(formatted, sizeof(formatted), "%sE%c%03d", buffer, sign, exponent);
    printf("%s", formatted);
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

const int c_a = 10;
const int c_b = 3;
int16_t g_i;
int16_t g_x;
double g_y;

int main(void) {
    g_x = c_a + c_b * 2;
    g_y = 3.1400000000000001;
    if (g_x > 10)
    {
        printf("%d", (int)g_x);
    }
    else
    {
        printf("%d", (int)c_b);
    }
    {
        int __for_end_1 = 5;
        for (g_i = 1; g_i <= __for_end_1; ++g_i)
        {
            printf("%d", (int)g_i);
        }
    }
    scanf("%hd", (&(g_x)));
    write_real(g_y);
    return 0;
}
