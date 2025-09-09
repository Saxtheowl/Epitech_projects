#include "my.h"
#include <unistd.h>

int count_letter_in_text(char const *text, char letter)
{
    int count = 0;
    int i = 0;
    
    if (text == 0)
        return 0;
    
    while (text[i]) {
        if (text[i] == letter || 
            (letter >= 'a' && letter <= 'z' && text[i] == letter - 32) ||
            (letter >= 'A' && letter <= 'Z' && text[i] == letter + 32)) {
            count++;
        }
        i++;
    }
    return count;
}

int is_valid_letter(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int count_total_letters(char const *text)
{
    int count = 0;
    int i = 0;
    
    while (text[i]) {
        if (is_valid_letter(text[i]))
            count++;
        i++;
    }
    return count;
}

void print_float_with_precision(double value)
{
    int integer_part = (int)value;
    int decimal_part = (int)((value - integer_part) * 100 + 0.5);
    
    if (decimal_part >= 100) {
        integer_part++;
        decimal_part = 0;
    }
    
    my_put_nbr(integer_part);
    my_putchar('.');
    if (decimal_part < 10)
        my_putchar('0');
    my_put_nbr(decimal_part);
}

void process_step1_and_step2(char const *text, char **argv, int argc)
{
    int i;
    int count;
    
    for (i = 2; i < argc; i++) {
        if (my_strlen(argv[i]) == 1 && is_valid_letter(argv[i][0])) {
            count = count_letter_in_text(text, argv[i][0]);
            my_putchar(argv[i][0]);
            my_putchar(':');
            my_put_nbr(count);
            my_putchar('\n');
        }
    }
}

void process_step3(char const *text, char **argv, int argc)
{
    int i;
    int count;
    int total_letters = count_total_letters(text);
    double percentage;
    
    for (i = 2; i < argc; i++) {
        if (my_strlen(argv[i]) == 1 && is_valid_letter(argv[i][0])) {
            count = count_letter_in_text(text, argv[i][0]);
            percentage = total_letters > 0 ? (double)count * 100.0 / total_letters : 0.0;
            
            my_putchar(argv[i][0]);
            my_putchar(':');
            my_put_nbr(count);
            my_putstr(" (");
            print_float_with_precision(percentage);
            my_putstr("%)\n");
        }
    }
}

typedef struct {
    char letter;
    double frequency;
} language_freq_t;

language_freq_t english_freq[] = {
    {'a', 8.167}, {'b', 1.492}, {'c', 2.782}, {'d', 4.253}, {'e', 12.02}, 
    {'f', 2.228}, {'g', 2.015}, {'h', 6.094}, {'i', 6.966}, {'j', 0.153},
    {'k', 0.772}, {'l', 4.025}, {'m', 2.406}, {'n', 6.749}, {'o', 7.507},
    {'p', 1.929}, {'q', 0.095}, {'r', 5.987}, {'s', 6.327}, {'t', 9.056},
    {'u', 2.758}, {'v', 0.978}, {'w', 2.360}, {'x', 0.150}, {'y', 1.974}, {'z', 0.074}
};

language_freq_t french_freq[] = {
    {'a', 7.636}, {'b', 0.901}, {'c', 3.260}, {'d', 3.669}, {'e', 14.715},
    {'f', 1.066}, {'g', 0.866}, {'h', 0.737}, {'i', 7.529}, {'j', 0.613},
    {'k', 0.074}, {'l', 5.456}, {'m', 2.968}, {'n', 7.095}, {'o', 5.796},
    {'p', 2.521}, {'q', 1.362}, {'r', 6.693}, {'s', 7.948}, {'t', 7.244},
    {'u', 6.311}, {'v', 1.628}, {'w', 0.114}, {'x', 0.387}, {'y', 0.308}, {'z', 0.136}
};

language_freq_t german_freq[] = {
    {'a', 6.516}, {'b', 1.886}, {'c', 2.732}, {'d', 5.076}, {'e', 16.396},
    {'f', 1.656}, {'g', 3.009}, {'h', 4.577}, {'i', 6.550}, {'j', 0.268},
    {'k', 1.417}, {'l', 3.437}, {'m', 2.534}, {'n', 9.776}, {'o', 2.594},
    {'p', 0.670}, {'q', 0.018}, {'r', 7.003}, {'s', 7.270}, {'t', 6.154},
    {'u', 4.166}, {'v', 0.846}, {'w', 1.921}, {'x', 0.034}, {'y', 0.039}, {'z', 1.134}
};

language_freq_t spanish_freq[] = {
    {'a', 11.525}, {'b', 2.215}, {'c', 4.019}, {'d', 5.010}, {'e', 12.181},
    {'f', 0.692}, {'g', 1.768}, {'h', 0.703}, {'i', 6.247}, {'j', 0.493},
    {'k', 0.011}, {'l', 4.967}, {'m', 3.157}, {'n', 6.712}, {'o', 8.683},
    {'p', 2.510}, {'q', 0.877}, {'r', 6.871}, {'s', 7.977}, {'t', 4.632},
    {'u', 2.927}, {'v', 1.138}, {'w', 0.017}, {'x', 0.215}, {'y', 1.008}, {'z', 0.467}
};

double get_letter_freq(language_freq_t *lang, char letter)
{
    int i;
    char lower_letter = letter;
    
    if (letter >= 'A' && letter <= 'Z')
        lower_letter = letter + 32;
    
    for (i = 0; i < 26; i++) {
        if (lang[i].letter == lower_letter)
            return lang[i].frequency;
    }
    return 0.0;
}

double calculate_distance(char const *text, char **letters, int num_letters, language_freq_t *lang)
{
    double distance = 0.0;
    int i;
    int count;
    int total_letters = count_total_letters(text);
    double actual_freq, expected_freq, diff;
    
    for (i = 0; i < num_letters; i++) {
        if (my_strlen(letters[i]) == 1 && is_valid_letter(letters[i][0])) {
            count = count_letter_in_text(text, letters[i][0]);
            actual_freq = total_letters > 0 ? (double)count * 100.0 / total_letters : 0.0;
            expected_freq = get_letter_freq(lang, letters[i][0]);
            diff = actual_freq - expected_freq;
            if (diff < 0) diff = -diff;
            distance += diff;
        }
    }
    return distance;
}

char const *detect_language(char const *text, char **letters, int num_letters)
{
    double eng_dist = calculate_distance(text, letters, num_letters, english_freq);
    double fre_dist = calculate_distance(text, letters, num_letters, french_freq);
    double ger_dist = calculate_distance(text, letters, num_letters, german_freq);
    double spa_dist = calculate_distance(text, letters, num_letters, spanish_freq);
    
    double min_dist = eng_dist;
    char const *result = "English";
    
    if (fre_dist < min_dist) {
        min_dist = fre_dist;
        result = "French";
    }
    if (ger_dist < min_dist) {
        min_dist = ger_dist;
        result = "German";
    }
    if (spa_dist < min_dist) {
        result = "Spanish";
    }
    
    return result;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        write(2, "Usage: ./rush2 \"text\" letter1 [letter2 ...]\n", 44);
        return 84;
    }
    
    process_step3(argv[1], argv, argc);
    
    my_putstr("=> ");
    my_putstr(detect_language(argv[1], &argv[2], argc - 2));
    my_putchar('\n');
    
    return 0;
}