#include "my_navy.h"

int main(void)
{
    ship_t ship;
    
    my_putstr("Testing ship parsing...\n");
    
    if (parse_ship_line("2:C1:C2\n", &ship)) {
        my_putstr("Ship 1 parsed successfully: length=");
        my_put_nbr(ship.length);
        my_putstr(" start=");
        my_put_nbr(ship.start_x);
        my_putstr(",");
        my_put_nbr(ship.start_y);
        my_putstr(" end=");
        my_put_nbr(ship.end_x);
        my_putstr(",");
        my_put_nbr(ship.end_y);
        my_putstr("\n");
    } else {
        my_putstr("Ship 1 parsing FAILED\n");
    }
    
    if (parse_ship_line("3:D4:F4\n", &ship)) {
        my_putstr("Ship 2 parsed successfully\n");
    } else {
        my_putstr("Ship 2 parsing FAILED\n");
    }
    
    return 0;
}