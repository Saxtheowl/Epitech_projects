/*
** EPITECH PROJECT, 2025
** Trade
** File description:
**   Minimal Criterion tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include "trade.h"

Test(dummy, ok)
{
    cr_assert(1);
}

static void redirect_all(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(parser, settings_and_candles)
{
    settings_t st;
    market_t m;
    settings_init(&st);
    market_init(&m);
    cr_assert_eq(parse_settings_line(&st, "timebank=10000"), 0);
    cr_assert_eq(parse_next_candles(&m, "BTC_USD,1,1,2,1,2,10;ETH_USD,2,2,3,1,2,10;BTC_ETH,3,3,4,2,3,10"), 0);
    cr_assert(m.count >= (size_t)1);
    cr_assert(strlen(m.pair) > 0);
}

Test(action, pass_when_insufficient, .init = redirect_all)
{
    settings_t st;
    market_t m;
    settings_init(&st);
    market_init(&m);
    parse_next_candles(&m, "X,1,1,1,1,1,1;Y,2,1,1,1,1,1;Z,3,1,1,1,1,1");
    handle_action(&st, &m);
    cr_assert(strstr(cr_get_redirected_stdout(), "pass") != NULL);
}

Test(action, buy_or_sell, .init = redirect_all)
{
    settings_t st;
    market_t m;
    settings_init(&st);
    market_init(&m);
    /* ensure sufficient USDT for buy */
    parse_stacks_line(&st, "USDT:100000,ETH:0,BTC:0");
    parse_next_candles(&m, "X,1,1,1,1,1,1;X,2,2,2,2,2,1;X,3,3,3,3,3,1;X,4,4,4,4,4,1;X,5,5,5,5,5,1;X,6,6,6,6,6,1;X,7,7,7,7,7,1;X,8,8,8,8,8,1;X,9,9,9,9,9,1;X,10,10,10,10,10,1");
    handle_action(&st, &m);
    cr_assert(strstr(cr_get_redirected_stdout(), "buy X 1") != NULL || strstr(cr_get_redirected_stdout(), "buy ") != NULL);
}

Test(stacks, parse_stacks)
{
    settings_t st;
    settings_init(&st);
    cr_assert_eq(parse_stacks_line(&st, "ETH:1000,BTC:900,USDT:500"), 0);
    cr_assert_float_eq(st.stack_eth, 1000.0, 1e-6);
    cr_assert_float_eq(st.stack_btc, 900.0, 1e-6);
    cr_assert_float_eq(st.stack_usdt, 500.0, 1e-6);
}

Test(action, sell_case, .init = redirect_all)
{
    settings_t st;
    market_t m;
    settings_init(&st);
    market_init(&m);
    parse_stacks_line(&st, "USDT:0,ETH:0,BTC:10");
    parse_next_candles(&m, "X,1,1,1,10,1,1;X,2,2,2,9,1,1");
    handle_action(&st, &m);
    cr_assert(strstr(cr_get_redirected_stdout(), "sell X 1") != NULL || strstr(cr_get_redirected_stdout(), "sell ") != NULL);
}

Test(candle_update, single_line)
{
    market_t m;
    settings_t st;
    settings_init(&st);
    market_init(&m);
    cr_assert_eq(parse_candle_line(&m, "BTC_USD 1000,1,2,1,2,5"), 0);
    cr_assert(strcmp(m.pair, "BTC_USD") == 0);
    cr_assert_eq(m.count, (size_t)1);
}
