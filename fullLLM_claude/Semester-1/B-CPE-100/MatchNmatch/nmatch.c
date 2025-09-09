int nmatch(char const *s1, char const *s2)
{
    if (s1 == 0 || s2 == 0)
        return 0;
    
    if (*s2 == '\0')
        return (*s1 == '\0') ? 1 : 0;
    
    if (*s2 == '*') {
        int count = 0;
        int i = 0;
        
        while (s1[i] != '\0') {
            count += nmatch(s1 + i, s2 + 1);
            i++;
        }
        count += nmatch(s1 + i, s2 + 1);
        
        return count;
    }
    
    if (*s1 == '\0')
        return 0;
    
    if (*s1 == *s2)
        return nmatch(s1 + 1, s2 + 1);
    
    return 0;
}