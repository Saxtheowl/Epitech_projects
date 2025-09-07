int get_color(unsigned char red, unsigned char green, unsigned char blue)
{
    int color = 0;

    color = (red << 16) | (green << 8) | blue;
    return color;
}