/*
** EPITECH PROJECT, 2024
** MyWorld
** File description:
** Utility functions
*/

#include "../include/my_world.h"

float distance_2d(vector2_t a, vector2_t b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

float clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

int is_point_in_rect(vector2_t point, vector2_t pos, vector2_t size)
{
    return (point.x >= pos.x && point.x <= pos.x + size.x &&
            point.y >= pos.y && point.y <= pos.y + size.y);
}

void play_sound_effect(world_t *world, int sound_id)
{
    if (!world || sound_id < 0 || sound_id >= 5 || !world->sounds[sound_id])
        return;
    
    sfSound_play(world->sounds[sound_id]);
}

matrix create_identity_matrix(void)
{
    matrix m = {{{0}}};
    
    m.m[0][0] = 1.0f;
    m.m[1][1] = 1.0f;
    m.m[2][2] = 1.0f;
    m.m[3][3] = 1.0f;
    
    return m;
}

matrix multiply_matrices(matrix a, matrix b)
{
    matrix result = {{{0}}};
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                result.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    
    return result;
}

vector3_t transform_point(vector3_t point, matrix m)
{
    vector3_t result;
    
    result.x = m.m[0][0] * point.x + m.m[0][1] * point.y + 
               m.m[0][2] * point.z + m.m[0][3];
    result.y = m.m[1][0] * point.x + m.m[1][1] * point.y + 
               m.m[1][2] * point.z + m.m[1][3];
    result.z = m.m[2][0] * point.x + m.m[2][1] * point.y + 
               m.m[2][2] * point.z + m.m[2][3];
    
    return result;
}

matrix create_rotation_matrix_x(float angle)
{
    matrix m = create_identity_matrix();
    float rad = angle * PI / 180.0f;
    
    m.m[1][1] = cos(rad);
    m.m[1][2] = -sin(rad);
    m.m[2][1] = sin(rad);
    m.m[2][2] = cos(rad);
    
    return m;
}

matrix create_rotation_matrix_y(float angle)
{
    matrix m = create_identity_matrix();
    float rad = angle * PI / 180.0f;
    
    m.m[0][0] = cos(rad);
    m.m[0][2] = sin(rad);
    m.m[2][0] = -sin(rad);
    m.m[2][2] = cos(rad);
    
    return m;
}

matrix create_translation_matrix(vector3_t translation)
{
    matrix m = create_identity_matrix();
    
    m.m[0][3] = translation.x;
    m.m[1][3] = translation.y;
    m.m[2][3] = translation.z;
    
    return m;
}