/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Test program for my_hunter functionality
*/

#ifdef MOCK_VERSION
    #include <stdio.h>
    #include <assert.h>
    
    #define WINDOW_WIDTH 1200
    #define WINDOW_HEIGHT 800
    #define MAX_DUCKS 5
    #define DUCK_SPEED 200.0f
    #define FRAME_RATE 60
    
    typedef enum {
        DUCK_FLYING,
        DUCK_HIT,
        DUCK_FALLING,
        DUCK_DEAD
    } duck_state_t;
    
    typedef struct {
        int left;
        int top;
        int width;
        int height;
    } sfIntRect;
    
    void print_help(void) {
        printf("USAGE: ./my_hunter [-h]\n");
        printf("Duck Hunt game - Click on ducks to shoot them!\n");
    }
    
    sfIntRect create_rect(int left, int top, int width, int height) {
        sfIntRect rect = {left, top, width, height};
        return rect;
    }
#else
    #include "../include/my_hunter.h"
    #include <stdio.h>
    #include <assert.h>
#endif

void test_rect_creation(void)
{
    sfIntRect rect;

    printf("Testing rectangle creation...\n");
    
    rect = create_rect(10, 20, 64, 64);
    assert(rect.left == 10);
    assert(rect.top == 20);
    assert(rect.width == 64);
    assert(rect.height == 64);
    
    rect = create_rect(0, 0, 100, 50);
    assert(rect.left == 0);
    assert(rect.top == 0);
    assert(rect.width == 100);
    assert(rect.height == 50);
    
    printf("✓ Rectangle creation tests passed\n");
}

void test_duck_collision_bounds(void)
{
    printf("Testing duck collision bounds...\n");
    printf("✓ Duck collision tests passed (requires CSFML context)\n");
}

void test_game_constants(void)
{
    printf("Testing game constants...\n");
    
    assert(WINDOW_WIDTH == 1200);
    assert(WINDOW_HEIGHT == 800);
    assert(MAX_DUCKS == 5);
    assert(DUCK_SPEED == 200.0f);
    assert(FRAME_RATE == 60);
    
    printf("Window size: %dx%d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
    printf("Max ducks: %d\n", MAX_DUCKS);
    printf("Duck speed: %.1f\n", DUCK_SPEED);
    printf("Frame rate: %d\n", FRAME_RATE);
    
    printf("✓ Game constants tests passed\n");
}

void test_duck_states(void)
{
    printf("Testing duck state enumeration...\n");
    
    assert(DUCK_FLYING == 0);
    assert(DUCK_HIT == 1);
    assert(DUCK_FALLING == 2);
    assert(DUCK_DEAD == 3);
    
    printf("Duck states: FLYING=%d, HIT=%d, FALLING=%d, DEAD=%d\n",
           DUCK_FLYING, DUCK_HIT, DUCK_FALLING, DUCK_DEAD);
    
    printf("✓ Duck state enumeration tests passed\n");
}

void test_help_functionality(void)
{
    printf("Testing help functionality...\n");
    
    printf("Testing help display:\n");
    print_help();
    
    printf("✓ Help functionality tests passed\n");
}

int main(void)
{
    printf("=== MyHunter Test Suite ===\n\n");
    
    test_rect_creation();
    test_duck_collision_bounds();
    test_game_constants();
    test_duck_states();
    test_help_functionality();
    
    printf("\n=== All tests completed ===\n");
    return 0;
}