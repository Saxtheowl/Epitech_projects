##
## EPITECH PROJECT, 2025
## Area
## File description:
## Makefile for Area project
##

COMPOSE_FILE = docker-compose.yml

all: build

build:
	@echo "Building Area services..."
	docker-compose -f $(COMPOSE_FILE) build

up: build
	@echo "Starting Area services..."
	docker-compose -f $(COMPOSE_FILE) up -d

down:
	@echo "Stopping Area services..."
	docker-compose -f $(COMPOSE_FILE) down

logs:
	docker-compose -f $(COMPOSE_FILE) logs -f

clean:
	@echo "Cleaning Docker containers..."
	docker-compose -f $(COMPOSE_FILE) down -v
	docker system prune -f

fclean: clean
	@echo "Full cleanup of Docker images..."
	docker-compose -f $(COMPOSE_FILE) down -v --rmi all
	docker system prune -af

re: fclean all

tests_run:
	@echo "Running Area tests..."
	docker-compose -f $(COMPOSE_FILE) exec server npm test || true
	docker-compose -f $(COMPOSE_FILE) exec client_web npm test -- --watchAll=false || true

install:
	@echo "Installing dependencies in containers..."
	docker-compose -f $(COMPOSE_FILE) exec server npm install
	docker-compose -f $(COMPOSE_FILE) exec client_web npm install
	docker-compose -f $(COMPOSE_FILE) exec client_mobile npm install

dev: up
	@echo "Area development environment started."
	@echo "Server: http://localhost:8080"
	@echo "Web Client: http://localhost:8081"
	@echo "Mobile Client: http://localhost:19000"

.PHONY: all build up down logs clean fclean re tests_run install dev