#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static void write_real(float value) {
    printf("%f", value);
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

int g_x;

int main(void) {
    ;
    return 0;
}
