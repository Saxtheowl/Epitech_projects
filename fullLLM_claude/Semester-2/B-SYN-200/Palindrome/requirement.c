#include <stdlib.h>

int my_factrec_synthesis(int nb)
{
    if (nb < 0)
        return 0;
    if (nb == 0 || nb == 1)
        return 1;
    
    // Check for overflow by testing if nb * factorial(nb-1) would overflow
    int prev_factorial = my_factrec_synthesis(nb - 1);
    if (prev_factorial == 0)
        return 0;
    
    // Simple overflow check: if nb > INT_MAX/prev_factorial, overflow
    if (nb > 2147483647 / prev_factorial)
        return 0;
    
    return nb * prev_factorial;
}

int my_squareroot_synthesis(int nb)
{
    int root, square;
    
    if (nb < 0)
        return -1;
    if (nb == 0 || nb == 1)
        return nb;
    
    // Binary search for the square root
    int left = 1;
    int right = nb / 2;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Check for overflow before squaring
        if (mid > 46340)  // sqrt(INT_MAX) ≈ 46340
            right = mid - 1;
        else {
            square = mid * mid;
            if (square == nb)
                return mid;
            if (square < nb)
                left = mid + 1;
            else
                right = mid - 1;
        }
    }
    
    return -1;
}