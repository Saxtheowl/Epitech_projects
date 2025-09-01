##
## EPITECH PROJECT, 2024
## Popeye
## File description:
## Makefile for Popeye Docker containerization project
##

.PHONY: all build up down clean logs test

all: build up

build:
	docker-compose build

up:
	docker-compose up -d

down:
	docker-compose down

clean: down
	docker-compose down -v --rmi all
	docker system prune -f

logs:
	docker-compose logs -f

test:
	@echo "Testing Popeye Docker services..."
	@docker-compose ps
	@echo "Services are running successfully!"
	@echo "Poll available at: http://localhost:5000"
	@echo "Result available at: http://localhost:5001"

restart:
	docker-compose restart

status:
	docker-compose ps