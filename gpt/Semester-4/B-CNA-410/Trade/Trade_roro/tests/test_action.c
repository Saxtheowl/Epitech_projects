/*
** EPITECH PROJECT, 2025
** Trade_roro
** File description:
** test_action.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include "trade.h"

static void fill_pair(market_t *m, const char *pair, double a, double b)
{
    memset(m, 0, sizeof(*m));
    strncpy(m->pair, pair, sizeof(m->pair) - 1);
    m->buf[0].close = a;
    m->buf[1].close = b;
    m->count = 2;
}

Test(action, buy_when_rising, .init = cr_redirect_stdout)
{
    settings_t st;
    market_t m;

    settings_init(&st);
    st.fee_percent = 0.0;
    st.stack_usdt = 1000.0;
    fill_pair(&m, "ETH_USDT", 10.0, 11.0);
    handle_action(&st, &m);
    cr_assert_stdout_eq_str("buy ETH_USDT 1\n");
}

Test(action, sell_when_falling, .init = cr_redirect_stdout)
{
    settings_t st;
    market_t m;

    settings_init(&st);
    st.fee_percent = 0.0;
    st.stack_eth = 2.0;
    fill_pair(&m, "ETH_USDT", 11.0, 10.0);
    handle_action(&st, &m);
    cr_assert_stdout_eq_str("sell ETH_USDT 1\n");
}

