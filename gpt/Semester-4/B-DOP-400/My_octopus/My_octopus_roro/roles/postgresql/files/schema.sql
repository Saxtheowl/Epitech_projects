--
-- EPITECH PROJECT, 2025
-- My_octopus - PostgreSQL schema for poll app (placeholder)
--

-- Create votes table if it does not exist
CREATE TABLE IF NOT EXISTS votes (
    id SERIAL PRIMARY KEY,
    choice TEXT NOT NULL,
    created_at TIMESTAMP NOT NULL DEFAULT NOW()
);

