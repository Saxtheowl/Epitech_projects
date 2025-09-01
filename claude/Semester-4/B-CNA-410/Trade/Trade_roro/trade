#!/usr/bin/env python3
"""
** EPITECH PROJECT, 2025
** Trade
** File description:
** Trading bot main file
*/

import sys
import re
from typing import Dict, List, Optional, Tuple

class TradingBot:
    def __init__(self):
        self.stack = {'ETH': 0.0, 'BTC': 0.0, 'USDT': 1000.0}
        self.price_history = []
        self.settings = {}
        
    def parse_settings(self, line: str) -> None:
        """Parse settings line from server"""
        parts = line.strip().split()
        if len(parts) >= 3 and parts[0] == 'settings':
            key = parts[1]
            values = ' '.join(parts[2:])
            self.settings[key] = values
    
    def parse_candles(self, line: str) -> List[Dict]:
        """Parse candles data from server"""
        if not line.startswith('update game next_candles'):
            return []
        
        candles = []
        parts = line.replace('update game next_candles ', '').split(';')
        
        for part in parts:
            if '_' in part:
                pair, prices = part.split(',', 1)
                price_values = [float(x) for x in prices.split(',')]
                if len(price_values) == 6:
                    candles.append({
                        'pair': pair,
                        'open': price_values[0],
                        'high': price_values[1],
                        'low': price_values[2],
                        'close': price_values[3],
                        'volume': price_values[4],
                        'timestamp': price_values[5]
                    })
        return candles
    
    def parse_stack(self, line: str) -> None:
        """Parse stack information from server"""
        if not line.startswith('update game stacks'):
            return
        
        stack_data = line.replace('update game stacks ', '')
        currencies = stack_data.split(',')
        
        for currency_info in currencies:
            if ':' in currency_info:
                currency, amount = currency_info.split(':')
                self.stack[currency] = float(amount)
    
    def calculate_moving_average(self, prices: List[float], window: int) -> float:
        """Calculate simple moving average"""
        if len(prices) < window:
            return sum(prices) / len(prices) if prices else 0
        return sum(prices[-window:]) / window
    
    def calculate_rsi(self, prices: List[float], period: int = 14) -> float:
        """Calculate Relative Strength Index"""
        if len(prices) < period + 1:
            return 50.0
        
        gains = []
        losses = []
        
        for i in range(1, len(prices)):
            diff = prices[i] - prices[i-1]
            if diff > 0:
                gains.append(diff)
                losses.append(0)
            else:
                gains.append(0)
                losses.append(abs(diff))
        
        if len(gains) < period:
            return 50.0
            
        avg_gain = sum(gains[-period:]) / period
        avg_loss = sum(losses[-period:]) / period
        
        if avg_loss == 0:
            return 100.0
        
        rs = avg_gain / avg_loss
        rsi = 100 - (100 / (1 + rs))
        return rsi
    
    def make_trading_decision(self, candles: List[Dict]) -> str:
        """Make trading decision based on market data"""
        if not candles:
            return "pass"
        
        # Simple strategy based on moving averages and RSI
        for candle in candles:
            pair = candle['pair']
            close_price = candle['close']
            
            # Store price history for analysis
            pair_history = [c['close'] for c in self.price_history if c['pair'] == pair]
            pair_history.append(close_price)
            
            if len(pair_history) < 10:
                continue
                
            # Calculate indicators
            ma_short = self.calculate_moving_average(pair_history, 5)
            ma_long = self.calculate_moving_average(pair_history, 10)
            rsi = self.calculate_rsi(pair_history)
            
            # Trading logic
            if pair == 'BTC_USDT':
                # Buy signal: short MA crosses above long MA and RSI < 70
                if ma_short > ma_long and rsi < 70 and self.stack['USDT'] > close_price:
                    buy_amount = min(self.stack['USDT'] * 0.1, 100.0)
                    if buy_amount >= close_price:
                        return f"buy BTC_USDT {buy_amount:.2f}"
                
                # Sell signal: short MA crosses below long MA and RSI > 30
                if ma_short < ma_long and rsi > 30 and self.stack['BTC'] > 0.01:
                    sell_amount = min(self.stack['BTC'] * 0.5, 1.0)
                    return f"sell BTC_USDT {sell_amount:.6f}"
            
            elif pair == 'ETH_USDT':
                # Similar strategy for ETH
                if ma_short > ma_long and rsi < 65 and self.stack['USDT'] > close_price:
                    buy_amount = min(self.stack['USDT'] * 0.1, 50.0)
                    if buy_amount >= close_price:
                        return f"buy ETH_USDT {buy_amount:.2f}"
                
                if ma_short < ma_long and rsi > 35 and self.stack['ETH'] > 0.1:
                    sell_amount = min(self.stack['ETH'] * 0.5, 10.0)
                    return f"sell ETH_USDT {sell_amount:.4f}"
        
        return "pass"
    
    def run(self):
        """Main bot loop"""
        try:
            while True:
                line = input().strip()
                
                if line.startswith('settings'):
                    self.parse_settings(line)
                
                elif line.startswith('update game next_candles'):
                    candles = self.parse_candles(line)
                    self.price_history.extend(candles)
                    
                    # Keep only recent history to avoid memory issues
                    if len(self.price_history) > 1000:
                        self.price_history = self.price_history[-500:]
                
                elif line.startswith('update game stacks'):
                    self.parse_stack(line)
                
                elif line.startswith('action order'):
                    decision = self.make_trading_decision(self.price_history[-10:] if self.price_history else [])
                    print(decision)
                    sys.stdout.flush()
                    
        except EOFError:
            pass
        except KeyboardInterrupt:
            pass

if __name__ == "__main__":
    bot = TradingBot()
    bot.run()