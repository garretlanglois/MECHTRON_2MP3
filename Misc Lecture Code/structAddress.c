#include <stdio.h>

struct point {
    int x;
    int y;
};

int main(void) {

    struct point array_value[5];
    array_value[0].x = 10;
    array_value[0].y = 15;

    printf("The location of point (x,y)(%d,%d)\n", array_value[0].x, array_value[0].y);
    printf("The addresses of the point (x,y) = (%p,%p)", &array_value[0].x, &array_value[0].y);

}