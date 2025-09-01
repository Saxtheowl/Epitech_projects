#!/usr/bin/env python3
"""
** EPITECH PROJECT, 2025
** Trade
** File description:
** Unit tests for trading bot
*/

import sys
import os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'src'))

import unittest
from trade import TradingBot

class TestTradingBot(unittest.TestCase):
    def setUp(self):
        self.bot = TradingBot()
    
    def test_init(self):
        """Test bot initialization"""
        self.assertEqual(self.bot.stack['USDT'], 1000.0)
        self.assertEqual(self.bot.stack['BTC'], 0.0)
        self.assertEqual(self.bot.stack['ETH'], 0.0)
        self.assertEqual(len(self.bot.price_history), 0)
    
    def test_parse_settings(self):
        """Test settings parsing"""
        self.bot.parse_settings("settings timebank 1000")
        self.assertEqual(self.bot.settings['timebank'], '1000')
    
    def test_parse_stack(self):
        """Test stack parsing"""
        self.bot.parse_stack("update game stacks ETH:10.5,BTC:2.3,USDT:500.0")
        self.assertEqual(self.bot.stack['ETH'], 10.5)
        self.assertEqual(self.bot.stack['BTC'], 2.3)
        self.assertEqual(self.bot.stack['USDT'], 500.0)
    
    def test_moving_average(self):
        """Test moving average calculation"""
        prices = [10.0, 12.0, 14.0, 16.0, 18.0]
        ma = self.bot.calculate_moving_average(prices, 3)
        self.assertAlmostEqual(ma, 16.0, places=1)
    
    def test_rsi_calculation(self):
        """Test RSI calculation"""
        prices = [44, 44.34, 44.09, 44.15, 43.61, 44.33, 44.83, 45.85, 46.08, 45.89, 46.03, 46.28, 46.28, 46.00, 46.03]
        rsi = self.bot.calculate_rsi(prices)
        self.assertTrue(0 <= rsi <= 100)
    
    def test_parse_candles(self):
        """Test candles parsing"""
        line = "update game next_candles BTC_USDT,45000.0,45100.0,44900.0,45050.0,1000.0,1634567890"
        candles = self.bot.parse_candles(line)
        self.assertEqual(len(candles), 1)
        self.assertEqual(candles[0]['pair'], 'BTC_USDT')
        self.assertEqual(candles[0]['close'], 45050.0)
    
    def test_make_trading_decision_pass(self):
        """Test trading decision when no data"""
        decision = self.bot.make_trading_decision([])
        self.assertEqual(decision, "pass")

if __name__ == '__main__':
    unittest.main()