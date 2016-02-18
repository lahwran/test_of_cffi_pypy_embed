#include <stdio.h>

#include <plugin.h>

int main(int argc, char **argv) {
    point_t x = { .x = 1, .y = 2 };
    do_stuff(&x);
    return 0;
}
