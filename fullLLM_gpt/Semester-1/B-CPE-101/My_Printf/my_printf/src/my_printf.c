#include "../include/my_printf.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <float.h>

#define DIGITS_LOWER "0123456789abcdefghijklmnopqrstuvwxyz"
#define DIGITS_UPPER "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

static size_t pf_strlen(const char *str)
{
    size_t len = 0;

    if (!str)
        return 0;
    while (str[len] != '\0')
        ++len;
    return len;
}

static size_t pf_strnlen(const char *str, size_t max_len)
{
    size_t len = 0;

    if (!str)
        return 0;
    while (len < max_len && str[len] != '\0')
        ++len;
    return len;
}

static void *pf_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;

    for (size_t i = 0; i < n; ++i)
        d[i] = s[i];
    return dst;
}

static void *pf_memset(void *dst, int value, size_t n)
{
    unsigned char *d = (unsigned char *)dst;
    for (size_t i = 0; i < n; ++i)
        d[i] = (unsigned char)value;
    return dst;
}

static char *pf_strdup(const char *str)
{
    size_t len = pf_strlen(str);
    char *dup = malloc(len + 1);

    if (!dup)
        return NULL;
    pf_memcpy(dup, str, len);
    dup[len] = '\0';
    return dup;
}

static char *pf_strndup(const char *str, size_t len)
{
    char *dup = malloc(len + 1);

    if (!dup)
        return NULL;
    pf_memcpy(dup, str, len);
    dup[len] = '\0';
    return dup;
}

static ssize_t pf_write(const char *data, size_t len)
{
    size_t written = 0;

    while (written < len) {
        ssize_t ret = write(1, data + written, len - written);
        if (ret < 0)
            return -1;
        written += (size_t)ret;
    }
    return (ssize_t)len;
}

static ssize_t pf_write_pad(char c, size_t count)
{
    char buffer[64];
    pf_memset(buffer, c, sizeof(buffer));
    size_t remaining = count;
    ssize_t total = 0;

    while (remaining > 0) {
        size_t chunk = remaining < sizeof(buffer) ? remaining : sizeof(buffer);
        ssize_t ret = pf_write(buffer, chunk);
        if (ret < 0)
            return -1;
        total += ret;
        remaining -= chunk;
    }
    return total;
}

typedef enum {
    PF_LEN_NONE,
    PF_LEN_HH,
    PF_LEN_H,
    PF_LEN_L,
    PF_LEN_LL,
    PF_LEN_CAPL
} pf_length_t;

typedef struct {
    bool flag_minus;
    bool flag_plus;
    bool flag_space;
    bool flag_zero;
    bool flag_hash;
    bool width_from_arg;
    bool precision_from_arg;
    int width;
    bool precision_specified;
    int precision;
    pf_length_t length;
    char spec;
} pf_format;

static void pf_init_format(pf_format *fmt)
{
    fmt->flag_minus = false;
    fmt->flag_plus = false;
    fmt->flag_space = false;
    fmt->flag_zero = false;
    fmt->flag_hash = false;
    fmt->width_from_arg = false;
    fmt->precision_from_arg = false;
    fmt->width = 0;
    fmt->precision_specified = false;
    fmt->precision = 0;
    fmt->length = PF_LEN_NONE;
    fmt->spec = '\0';
}

static bool pf_is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static const char *pf_parse_flags(const char *p, pf_format *fmt)
{
    while (*p == '-' || *p == '+' || *p == ' ' || *p == '0' || *p == '#') {
        if (*p == '-')
            fmt->flag_minus = true;
        else if (*p == '+')
            fmt->flag_plus = true;
        else if (*p == ' ')
            fmt->flag_space = true;
        else if (*p == '0')
            fmt->flag_zero = true;
        else if (*p == '#')
            fmt->flag_hash = true;
        ++p;
    }
    return p;
}

static const char *pf_parse_width(const char *p, pf_format *fmt)
{
    if (*p == '*') {
        fmt->width_from_arg = true;
        return p + 1;
    }
    int width = 0;
    while (pf_is_digit(*p)) {
        width = width * 10 + (*p - '0');
        ++p;
    }
    fmt->width = width;
    return p;
}

static const char *pf_parse_precision(const char *p, pf_format *fmt)
{
    if (*p != '.')
        return p;
    ++p;
    fmt->precision_specified = true;
    if (*p == '*') {
        fmt->precision_from_arg = true;
        return p + 1;
    }
    int precision = 0;
    while (pf_is_digit(*p)) {
        precision = precision * 10 + (*p - '0');
        ++p;
    }
    fmt->precision = precision;
    return p;
}

static const char *pf_parse_length(const char *p, pf_format *fmt)
{
    if (p[0] == 'h' && p[1] == 'h') {
        fmt->length = PF_LEN_HH;
        return p + 2;
    }
    if (p[0] == 'h') {
        fmt->length = PF_LEN_H;
        return p + 1;
    }
    if (p[0] == 'l' && p[1] == 'l') {
        fmt->length = PF_LEN_LL;
        return p + 2;
    }
    if (p[0] == 'l') {
        fmt->length = PF_LEN_L;
        return p + 1;
    }
    if (p[0] == 'L') {
        fmt->length = PF_LEN_CAPL;
        return p + 1;
    }
    return p;
}

static const char *pf_parse_format(const char *p, pf_format *fmt)
{
    p = pf_parse_flags(p, fmt);
    p = pf_parse_width(p, fmt);
    p = pf_parse_precision(p, fmt);
    p = pf_parse_length(p, fmt);
    fmt->spec = *p;
    if (*p != '\0')
        ++p;
    return p;
}

static unsigned long long pf_get_unsigned_arg(pf_format *fmt, va_list *ap)
{
    switch (fmt->length) {
    case PF_LEN_HH:
        return (unsigned long long)(unsigned char)va_arg(*ap, unsigned int);
    case PF_LEN_H:
        return (unsigned long long)(unsigned short)va_arg(*ap, unsigned int);
    case PF_LEN_L:
        return (unsigned long long)va_arg(*ap, unsigned long);
    case PF_LEN_LL:
        return (unsigned long long)va_arg(*ap, unsigned long long);
    default:
        return (unsigned long long)va_arg(*ap, unsigned int);
    }
}

static long long pf_get_signed_arg(pf_format *fmt, va_list *ap)
{
    switch (fmt->length) {
    case PF_LEN_HH:
        return (long long)(signed char)va_arg(*ap, int);
    case PF_LEN_H:
        return (long long)(short)va_arg(*ap, int);
    case PF_LEN_L:
        return (long long)va_arg(*ap, long);
    case PF_LEN_LL:
        return (long long)va_arg(*ap, long long);
    default:
        return (long long)va_arg(*ap, int);
    }
}

static char *pf_convert_unsigned_base(unsigned long long value, unsigned base, bool uppercase)
{
    char tmp[65];
    size_t len = 0;
    const char *digits = uppercase ? DIGITS_UPPER : DIGITS_LOWER;

    if (value == 0) {
        tmp[len++] = '0';
    } else {
        while (value > 0 && len < sizeof(tmp)) {
            tmp[len++] = digits[value % base];
            value /= base;
        }
    }
    char *out = malloc(len + 1);
    if (!out)
        return NULL;
    for (size_t i = 0; i < len; ++i)
        out[i] = tmp[len - 1 - i];
    out[len] = '\0';
    return out;
}

static char *pf_apply_precision(const char *digits, size_t len, int precision)
{
    if (precision <= (int)len)
        return pf_strndup(digits, len);
    size_t total = (size_t)precision;
    char *out = malloc(total + 1);
    if (!out)
        return NULL;
    size_t pad = total - len;
    pf_memset(out, '0', pad);
    pf_memcpy(out + pad, digits, len);
    out[total] = '\0';
    return out;
}

static int pf_emit(const pf_format *fmt, const char *prefix, size_t prefix_len,
                   char *content, size_t content_len, bool free_content)
{
    size_t total = prefix_len + content_len;
    char pad_char = ' ';
    size_t padding = 0;

    if (fmt->width > (int)total)
        padding = (size_t)fmt->width - total;

    if (fmt->flag_zero && !fmt->flag_minus && !fmt->precision_specified &&
        fmt->spec != 's' && fmt->spec != 'c' && fmt->spec != '%')
        pad_char = '0';

    ssize_t written = 0;
    bool prefix_written = false;

    if (!fmt->flag_minus) {
        if (pad_char == '0') {
            if (prefix_len) {
                written = pf_write(prefix, prefix_len);
                if (written < 0) {
                    if (free_content)
                        free(content);
                    return -1;
                }
            }
            prefix_written = true;
            if (padding) {
                written = pf_write_pad('0', padding);
                if (written < 0) {
                    if (free_content)
                        free(content);
                    return -1;
                }
            }
        } else if (padding) {
            written = pf_write_pad(' ', padding);
            if (written < 0) {
                if (free_content)
                    free(content);
                return -1;
            }
        }
    }

    int total_written = 0;
    if (!fmt->flag_minus && pad_char == '0')
        total_written += (int)prefix_len + (int)padding;

    if (!prefix_written && prefix_len) {
        written = pf_write(prefix, prefix_len);
        if (written < 0) {
            if (free_content)
                free(content);
            return -1;
        }
        total_written += (int)prefix_len;
    }

    if (content_len) {
        written = pf_write(content, content_len);
        if (written < 0) {
            if (free_content)
                free(content);
            return -1;
        }
        total_written += (int)content_len;
    }

    if (fmt->flag_minus && padding) {
        written = pf_write_pad(' ', padding);
        if (written < 0) {
            if (free_content)
                free(content);
            return -1;
        }
        total_written += (int)padding;
    }

    if (!fmt->flag_minus && pad_char == '0' && prefix_len && prefix_written)
        total_written += (int)prefix_len;

    if (free_content)
        free(content);
    return total_written;
}

static int pf_print_string(const pf_format *fmt, va_list *ap)
{
    const char *src = va_arg(*ap, const char *);
    if (!src)
        src = "(null)";
    size_t len = fmt->precision_specified ? pf_strnlen(src, (size_t)fmt->precision)
                                          : pf_strlen(src);
    char *copy = pf_strndup(src, len);
    if (!copy)
        return -1;
    return pf_emit(fmt, NULL, 0, copy, len, true);
}

static int pf_print_char(const pf_format *fmt, va_list *ap)
{
    char c = (char)va_arg(*ap, int);
    char buf[1] = {c};
    char *dup = pf_strndup(buf, 1);
    if (!dup)
        return -1;
    return pf_emit(fmt, NULL, 0, dup, 1, true);
}

static int pf_print_percent(const pf_format *fmt)
{
    char *dup = pf_strndup("%", 1);
    if (!dup)
        return -1;
    return pf_emit(fmt, NULL, 0, dup, 1, true);
}

static int pf_adjust_integer_prefix(const pf_format *fmt, bool is_negative,
                                    unsigned long long value, char spec,
                                    char prefix[3])
{
    size_t idx = 0;

    if (is_negative) {
        prefix[idx++] = '-';
    } else if (fmt->flag_plus && (spec == 'd' || spec == 'i' || spec == 'f' || spec == 'F' || spec == 'e' || spec == 'E' || spec == 'g' || spec == 'G')) {
        prefix[idx++] = '+';
    } else if (fmt->flag_space && (spec == 'd' || spec == 'i' || spec == 'f' || spec == 'F' || spec == 'e' || spec == 'E' || spec == 'g' || spec == 'G')) {
        prefix[idx++] = ' ';
    }

    if (spec == 'p') {
        prefix[idx++] = '0';
        prefix[idx++] = 'x';
    } else if ((spec == 'x' || spec == 'X') && fmt->flag_hash && value != 0) {
        prefix[idx++] = '0';
        prefix[idx++] = (spec == 'x') ? 'x' : 'X';
    }

    return (int)idx;
}

static char *pf_build_integer_digits(const pf_format *fmt, unsigned long long value,
                                     unsigned base, bool uppercase,
                                     bool value_is_zero)
{
    char *raw = pf_convert_unsigned_base(value, base, uppercase);
    if (!raw)
        return NULL;

    size_t raw_len = (fmt->precision_specified && fmt->precision == 0 && value_is_zero) ? 0 : pf_strlen(raw);

    char *digits = NULL;
    if (fmt->precision_specified) {
        digits = pf_apply_precision(raw, raw_len, fmt->precision);
    } else {
        digits = pf_strndup(raw, raw_len);
    }
    free(raw);
    if (!digits)
        return NULL;

    if (fmt->spec == 'o' && fmt->flag_hash) {
        if (!(digits[0] == '0' && digits[1] == '\0')) {
            size_t len = pf_strlen(digits);
            char *tmp = malloc(len + 2);
            if (!tmp) {
                free(digits);
                return NULL;
            }
            tmp[0] = '0';
            pf_memcpy(tmp + 1, digits, len + 1);
            free(digits);
            digits = tmp;
        }
    }
    return digits;
}

static int pf_print_integer(const pf_format *fmt, unsigned long long value,
                            bool is_negative, unsigned base, bool uppercase)
{
    bool value_is_zero = (value == 0);
    char prefix[3] = {0};
    int prefix_len = pf_adjust_integer_prefix(fmt, is_negative, value, fmt->spec, prefix);

    char *digits = pf_build_integer_digits(fmt, value, base, uppercase, value_is_zero);
    if (!digits)
        return -1;
    size_t digits_len = pf_strlen(digits);

    /* Adjust for alternate form when value is zero */
    if (fmt->spec == 'o' && fmt->flag_hash && value_is_zero && digits_len == 0) {
        free(digits);
        digits = pf_strdup("0");
        if (!digits)
            return -1;
        digits_len = 1;
    }

    if (fmt->spec == 'p' && value_is_zero && fmt->precision_specified && fmt->precision == 0) {
        free(digits);
        digits = pf_strdup("0");
        if (!digits)
            return -1;
        digits_len = 1;
    }

    return pf_emit(fmt, prefix, (size_t)prefix_len, digits, digits_len, true);
}

static char *pf_convert_fixed(long double value, int precision, bool alt_form)
{
    long double rounding = 0.5L;
    for (int i = 0; i < precision; ++i)
        rounding /= 10.0L;
    long double rounded = value + rounding;
    unsigned long long int_part = (unsigned long long)rounded;
    long double frac_part = rounded - (long double)int_part;

    char *int_str = pf_convert_unsigned_base(int_part, 10, false);
    if (!int_str)
        return NULL;
    size_t int_len = pf_strlen(int_str);

    size_t total = int_len;
    if (precision > 0 || alt_form)
        total += 1 + (size_t)precision;

    char *res = malloc(total + 1);
    if (!res) {
        free(int_str);
        return NULL;
    }
    pf_memcpy(res, int_str, int_len);
    size_t pos = int_len;
    free(int_str);

    if (precision > 0 || alt_form)
        res[pos++] = '.';

    for (int i = 0; i < precision; ++i) {
        frac_part *= 10.0L;
        int digit = (int)frac_part;
        res[pos++] = (char)('0' + digit);
        frac_part -= digit;
    }
    res[pos] = '\0';
    return res;
}

static char *pf_convert_scientific(long double value, int precision, bool alt_form, bool uppercase, int *exp_out)
{
    long double mantissa = value;
    int exponent = 0;

    if (mantissa == 0.0L) {
        exponent = 0;
    } else {
        while (mantissa >= 10.0L) {
            mantissa /= 10.0L;
            ++exponent;
        }
        while (mantissa > 0.0L && mantissa < 1.0L) {
            mantissa *= 10.0L;
            --exponent;
        }
    }

    char *mant_str = pf_convert_fixed(mantissa, precision, alt_form);
    if (!mant_str)
        return NULL;

    char exp_buf[8];
    size_t exp_len = 0;
    int abs_exp = exponent < 0 ? -exponent : exponent;

    do {
        exp_buf[exp_len++] = (char)('0' + (abs_exp % 10));
        abs_exp /= 10;
    } while (abs_exp > 0);
    while (exp_len < 2)
        exp_buf[exp_len++] = '0';

    size_t mant_len = pf_strlen(mant_str);
    char exp_char = uppercase ? 'E' : 'e';
    size_t total = mant_len + 1 + 1 + exp_len;
    char *res = malloc(total + 1);
    if (!res) {
        free(mant_str);
        return NULL;
    }
    size_t pos = 0;
    pf_memcpy(res + pos, mant_str, mant_len);
    pos += mant_len;
    res[pos++] = exp_char;
    res[pos++] = (exponent < 0) ? '-' : '+';
    while (exp_len-- > 0)
        res[pos++] = exp_buf[exp_len];
    res[pos] = '\0';
    free(mant_str);
    if (exp_out)
        *exp_out = exponent;
    return res;
}

static char *pf_trim_trailing_zeros(char *str, bool alt_form)
{
    if (alt_form)
        return str;
    size_t len = pf_strlen(str);
    size_t i = len;
    bool seen_dot = false;
    while (i > 0) {
        if (str[i - 1] == '.') {
            seen_dot = true;
            break;
        }
        if (str[i - 1] != '0')
            break;
        --i;
    }
    if (seen_dot) {
        if (i > 0 && str[i - 1] == '.')
            --i;
    }
    str[i] = '\0';
    return str;
}

static int pf_print_float(const pf_format *fmt, va_list *ap)
{
    int precision = fmt->precision_specified ? fmt->precision : 6;
    if (precision < 0)
        precision = 6;
    long double value = (fmt->length == PF_LEN_CAPL) ? va_arg(*ap, long double)
                                                     : (long double)va_arg(*ap, double);

    bool negative = false;
    if (value < 0.0L || (value == 0.0L && (1.0L / value) < 0)) {
        negative = true;
        value = -value;
    }

    char *digits = NULL;
    bool uppercase = (fmt->spec == 'F' || fmt->spec == 'E' || fmt->spec == 'G');

    if (value != value) {
        digits = pf_strdup(uppercase ? "NAN" : "nan");
        negative = false;
    } else if (value > LDBL_MAX) {
        digits = pf_strdup(uppercase ? "INF" : "inf");
    } else {
        switch (fmt->spec) {
        case 'f':
        case 'F':
            digits = pf_convert_fixed(value, precision, fmt->flag_hash);
            break;
        case 'e':
        case 'E':
            digits = pf_convert_scientific(value, precision, fmt->flag_hash, uppercase, NULL);
            break;
        case 'g':
        case 'G': {
            int p = precision;
            if (p == 0)
                p = 1;
            int exp = 0;
            char *sci = pf_convert_scientific(value, p - 1, fmt->flag_hash, uppercase, &exp);
            if (!sci)
                return -1;
            if (exp < -4 || exp >= p) {
                digits = pf_trim_trailing_zeros(sci, fmt->flag_hash);
            } else {
                int frac_prec = p - (exp + 1);
                if (frac_prec < 0)
                    frac_prec = 0;
                free(sci);
                digits = pf_convert_fixed(value, frac_prec, fmt->flag_hash);
                if (!digits)
                    return -1;
                digits = pf_trim_trailing_zeros(digits, fmt->flag_hash);
                uppercase = (fmt->spec == 'G');
                if (uppercase) {
                    for (size_t i = 0; digits[i]; ++i)
                        if (digits[i] >= 'a' && digits[i] <= 'z')
                            digits[i] = (char)(digits[i] - ('a' - 'A'));
                }
            }
            break;
        }
        default:
            digits = pf_convert_fixed(value, precision, fmt->flag_hash);
            break;
        }
    }

    if (!digits)
        return -1;

    if (fmt->spec == 'F' || fmt->spec == 'E') {
        for (size_t i = 0; digits[i]; ++i)
            if (digits[i] >= 'a' && digits[i] <= 'z')
                digits[i] = (char)(digits[i] - ('a' - 'A'));
    }

    char prefix[3] = {0};
    int prefix_len = pf_adjust_integer_prefix(fmt, negative, 1, fmt->spec, prefix);
    return pf_emit(fmt, prefix, (size_t)prefix_len, digits, pf_strlen(digits), true);
}

static int pf_print_pointer(const pf_format *fmt, va_list *ap)
{
    void *ptr = va_arg(*ap, void *);
    unsigned long long value = (unsigned long long)(uintptr_t)ptr;
    if (value == 0) {
        char *nil = pf_strdup("(nil)");
        if (!nil)
            return -1;
        return pf_emit(fmt, NULL, 0, nil, pf_strlen(nil), true);
    }
    pf_format converted = *fmt;
    converted.spec = 'p';
    converted.flag_hash = true;
    converted.precision_specified = fmt->precision_specified;
    return pf_print_integer(&converted, value, false, 16, false);
}

static int pf_handle_format(const pf_format *fmt, va_list *ap)
{
    switch (fmt->spec) {
    case 'c':
        return pf_print_char(fmt, ap);
    case 's':
        return pf_print_string(fmt, ap);
    case '%':
        return pf_print_percent(fmt);
    case 'd':
    case 'i': {
        long long value = pf_get_signed_arg((pf_format *)fmt, ap);
        bool negative = value < 0;
        unsigned long long abs_value = negative ? (unsigned long long)(-value)
                                                : (unsigned long long)value;
        return pf_print_integer(fmt, abs_value, negative, 10, false);
    }
    case 'u': {
        unsigned long long value = pf_get_unsigned_arg((pf_format *)fmt, ap);
        return pf_print_integer(fmt, value, false, 10, false);
    }
    case 'o': {
        unsigned long long value = pf_get_unsigned_arg((pf_format *)fmt, ap);
        return pf_print_integer(fmt, value, false, 8, false);
    }
    case 'x':
    case 'X': {
        unsigned long long value = pf_get_unsigned_arg((pf_format *)fmt, ap);
        return pf_print_integer(fmt, value, false, 16, fmt->spec == 'X');
    }
    case 'p':
        return pf_print_pointer(fmt, ap);
    case 'f':
    case 'F':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
        return pf_print_float(fmt, ap);
    default: {
        char buf[2] = {'%', fmt->spec};
        char *dup = pf_strndup(buf, 2);
        if (!dup)
            return -1;
        return pf_emit(fmt, NULL, 0, dup, 2, true);
    }
    }
}

int vmy_printf(const char *format, va_list ap)
{
    int total = 0;

    while (format && *format) {
        if (*format != '%') {
            if (pf_write(format, 1) < 0)
                return -1;
            ++format;
            ++total;
            continue;
        }
        ++format;
        pf_format spec;
        pf_init_format(&spec);
        format = pf_parse_format(format, &spec);
        if (spec.width_from_arg) {
            int width = va_arg(ap, int);
            if (width < 0) {
                spec.flag_minus = true;
                spec.width = -width;
            } else {
                spec.width = width;
            }
        }
        if (spec.precision_from_arg) {
            int precision = va_arg(ap, int);
            if (precision >= 0) {
                spec.precision_specified = true;
                spec.precision = precision;
            } else {
                spec.precision_specified = false;
            }
        }
        if (spec.spec == '\0')
            break;
        if (spec.spec == 'n') {
            void *ptr = va_arg(ap, void *);
            if (!ptr)
                continue;
            switch (spec.length) {
            case PF_LEN_HH:
                *(signed char *)ptr = (signed char)total;
                break;
            case PF_LEN_H:
                *(short *)ptr = (short)total;
                break;
            case PF_LEN_L:
                *(long *)ptr = (long)total;
                break;
            case PF_LEN_LL:
                *(long long *)ptr = (long long)total;
                break;
            default:
                *(int *)ptr = total;
                break;
            }
            continue;
        }
        va_list working;
        va_copy(working, ap);
        int written = pf_handle_format(&spec, &working);
        if (written < 0)
        {
            va_end(working);
            return -1;
        }
        va_copy(ap, working);
        va_end(working);
        total += written;
    }
    return total;
}

int my_printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int result = vmy_printf(format, ap);
    va_end(ap);
    return result;
}
