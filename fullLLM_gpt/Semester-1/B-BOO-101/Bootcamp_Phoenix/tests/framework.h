#ifndef TESTS_FRAMEWORK_H
#define TESTS_FRAMEWORK_H

#include <stddef.h>

struct test_case {
    const char *suite;
    const char *name;
    void (*fn)(void);
};

void register_test(struct test_case *test);
void test_fail(const char *file, int line, const char *expr, const char *details);
void cr_redirect_stdout(void);
const char *test_capture_stdout_end(void);

#define Test(suite, name) \
    static void suite##_##name(void); \
    static struct test_case suite##_##name##_case = {#suite, #name, suite##_##name}; \
    static void __attribute__((constructor)) suite##_##name##_register(void) { register_test(&suite##_##name##_case); } \
    static void suite##_##name(void)

#define cr_assert(expr) \
    do { \
        if (!(expr)) { \
            test_fail(__FILE__, __LINE__, #expr, NULL); \
            return; \
        } \
    } while (0)

#include <stdio.h>
#include <string.h>

#define cr_assert_eq(a, b) \
    do { \
        long long _va = (long long)(a); \
        long long _vb = (long long)(b); \
        if (_va != _vb) { \
            char details[128]; \
            snprintf(details, sizeof(details), "%lld != %lld", _va, _vb); \
            test_fail(__FILE__, __LINE__, #a " == " #b, details); \
            return; \
        } \
    } while (0)

#define cr_assert_lt(a, b) \
    do { \
        long long _va = (long long)(a); \
        long long _vb = (long long)(b); \
        if (!(_va < _vb)) { \
            char details[128]; \
            snprintf(details, sizeof(details), "%lld >= %lld", _va, _vb); \
            test_fail(__FILE__, __LINE__, #a " < " #b, details); \
            return; \
        } \
    } while (0)

#define cr_assert_gt(a, b) \
    do { \
        long long _va = (long long)(a); \
        long long _vb = (long long)(b); \
        if (!(_va > _vb)) { \
            char details[128]; \
            snprintf(details, sizeof(details), "%lld <= %lld", _va, _vb); \
            test_fail(__FILE__, __LINE__, #a " > " #b, details); \
            return; \
        } \
    } while (0)

#define cr_assert_str_eq(a, b) \
    do { \
        const char *_sa = (a); \
        const char *_sb = (b); \
        if ((!_sa && _sb) || (_sa && !_sb) || (_sa && _sb && strcmp(_sa, _sb) != 0)) { \
            char details[256]; \
            snprintf(details, sizeof(details), "\"%s\" != \"%s\"", _sa ? _sa : "(null)", _sb ? _sb : "(null)"); \
            test_fail(__FILE__, __LINE__, #a " == " #b, details); \
            return; \
        } \
    } while (0)

#define cr_assert_null(value) \
    do { \
        if ((value) != NULL) { \
            test_fail(__FILE__, __LINE__, #value " == NULL", "value is not NULL"); \
            return; \
        } \
    } while (0)

#define cr_assert_not_null(value) \
    do { \
        if ((value) == NULL) { \
            test_fail(__FILE__, __LINE__, #value " != NULL", "value is NULL"); \
            return; \
        } \
    } while (0)

#define cr_assert_stdout_eq_str(expected) \
    do { \
        const char *_captured = test_capture_stdout_end(); \
        cr_assert_str_eq(_captured, (expected)); \
    } while (0)

#endif /* TESTS_FRAMEWORK_H */
