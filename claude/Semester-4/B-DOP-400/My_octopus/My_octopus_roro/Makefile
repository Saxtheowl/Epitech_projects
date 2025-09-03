##
## EPITECH PROJECT, 2025
## Octopus
## File description:
## Makefile for Ansible project
##

VAULT_PASSWORD_FILE = /tmp/.vault_pass
INVENTORY = production
PLAYBOOK = playbook.yml

all: deploy

deploy:
	@echo "Setting up vault password..."
	@echo "verySecretPassword" > $(VAULT_PASSWORD_FILE)
	@export ANSIBLE_VAULT_PASSWORD_FILE=$(VAULT_PASSWORD_FILE) && \
	ansible-playbook -i $(INVENTORY) $(PLAYBOOK)

check:
	@echo "Checking Ansible syntax..."
	@ansible-playbook --syntax-check -i $(INVENTORY) $(PLAYBOOK)

dry-run:
	@echo "Running in check mode (dry-run)..."
	@echo "verySecretPassword" > $(VAULT_PASSWORD_FILE)
	@export ANSIBLE_VAULT_PASSWORD_FILE=$(VAULT_PASSWORD_FILE) && \
	ansible-playbook --check -i $(INVENTORY) $(PLAYBOOK)

clean:
	@echo "Cleaning temporary files..."
	@rm -f $(VAULT_PASSWORD_FILE)

fclean: clean

re: clean all

help:
	@echo "Available targets:"
	@echo "  all       - Deploy the application"
	@echo "  deploy    - Same as all"
	@echo "  check     - Check Ansible syntax"
	@echo "  dry-run   - Run playbook in check mode"
	@echo "  clean     - Remove temporary files"
	@echo "  fclean    - Same as clean"
	@echo "  re        - Clean and redeploy"
	@echo "  help      - Show this help"

.PHONY: all deploy check dry-run clean fclean re help