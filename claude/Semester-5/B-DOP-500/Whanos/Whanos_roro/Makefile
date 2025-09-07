##
## EPITECH PROJECT, 2025
## Whanos
## File description:
## Makefile for Whanos DevOps Infrastructure
##

ANSIBLE_PLAYBOOK = ansible/deploy_whanos.yml
INVENTORY = ansible/inventory.yml
SCRIPTS_DIR = scripts
IMAGES_DIR = images
JENKINS_DIR = jenkins
TESTS_DIR = tests

.PHONY: all build-images deploy-infrastructure test clean fclean re help

all: build-images

build-images:
	@echo "Building all Whanos Docker images..."
	@for lang in c java javascript python befunge; do \
		echo "Building $$lang images..."; \
		docker build -f $(IMAGES_DIR)/$$lang/Dockerfile.base -t whanos-$$lang $(IMAGES_DIR)/$$lang/; \
		docker build -f $(IMAGES_DIR)/$$lang/Dockerfile.standalone -t whanos-$$lang-standalone $(IMAGES_DIR)/$$lang/; \
	done
	@echo "All images built successfully!"

deploy-infrastructure:
	@echo "Deploying Whanos infrastructure with Ansible..."
	@ansible-playbook -i $(INVENTORY) $(ANSIBLE_PLAYBOOK)
	@echo "Infrastructure deployed successfully!"

deploy-registry:
	@echo "Starting Docker Registry..."
	@docker run -d -p 5000:5000 --name whanos-registry registry:2
	@echo "Registry started on localhost:5000"

test:
	@echo "Running Whanos tests..."
	@$(SCRIPTS_DIR)/test_language_detection.sh
	@$(SCRIPTS_DIR)/test_containerization.sh
	@echo "All tests passed!"

test-jenkins:
	@echo "Testing Jenkins configuration..."
	@curl -f http://localhost:8080/api/json || (echo "Jenkins not accessible" && exit 1)
	@echo "Jenkins is accessible!"

clean:
	@echo "Cleaning up Docker containers and images..."
	@docker container prune -f || true
	@docker image prune -f || true

fclean: clean
	@echo "Full cleanup - removing all Whanos images..."
	@docker rmi -f $$(docker images | grep whanos | awk '{print $$3}') 2>/dev/null || true
	@docker rm -f whanos-registry 2>/dev/null || true

re: fclean all

setup-dev:
	@echo "Setting up development environment..."
	@chmod +x $(SCRIPTS_DIR)/*.sh
	@echo "Development environment ready!"

help:
	@echo "Whanos - DevOps Infrastructure Makefile"
	@echo ""
	@echo "Available targets:"
	@echo "  all              - Build all Docker images (default)"
	@echo "  build-images     - Build all Whanos base and standalone images"
	@echo "  deploy-infrastructure - Deploy full infrastructure with Ansible"
	@echo "  deploy-registry  - Start local Docker registry"
	@echo "  test             - Run all tests"
	@echo "  test-jenkins     - Test Jenkins connectivity"
	@echo "  clean            - Clean Docker containers and unused images"
	@echo "  fclean           - Full cleanup including Whanos images"
	@echo "  re               - Full rebuild (fclean + all)"
	@echo "  setup-dev        - Setup development environment"
	@echo "  help             - Show this help message"