union color_union {
    int color;
    struct {
        unsigned char byte0;
        unsigned char byte1;
        unsigned char byte2;
        unsigned char byte3;
    } bytes;
};

int swap_endian_color(int color)
{
    union color_union input;
    union color_union output;

    input.color = color;
    
    output.bytes.byte0 = input.bytes.byte3;
    output.bytes.byte1 = input.bytes.byte2;
    output.bytes.byte2 = input.bytes.byte1;
    output.bytes.byte3 = input.bytes.byte0;
    
    return output.color;
}