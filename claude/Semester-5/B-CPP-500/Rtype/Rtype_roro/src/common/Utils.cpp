/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Common utilities
*/

#include <chrono>
#include <cmath>

namespace Utils {
    uint32_t getCurrentTimestamp() {
        return static_cast<uint32_t>(
            std::chrono::steady_clock::now().time_since_epoch().count()
        );
    }

    float distance(float x1, float y1, float x2, float y2) {
        float dx = x2 - x1;
        float dy = y2 - y1;
        return std::sqrt(dx * dx + dy * dy);
    }

    float normalize(float value, float min, float max) {
        return (value - min) / (max - min);
    }

    float lerp(float a, float b, float t) {
        return a + t * (b - a);
    }
}