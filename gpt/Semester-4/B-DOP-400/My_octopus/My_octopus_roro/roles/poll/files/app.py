#
# EPITECH PROJECT, 2025
# Minimal Flask app placeholder for poll
#

from flask import Flask
app = Flask(__name__)

@app.route('/')
def index():
    return 'Poll service running'  # placeholder

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

