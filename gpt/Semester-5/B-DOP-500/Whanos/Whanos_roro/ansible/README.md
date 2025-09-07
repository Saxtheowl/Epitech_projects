##
## EPITECH PROJECT, 2025
## Whanos_roro
## File description:
##   Ansible deployment (skeleton)
##

# Ansible deployment (skeleton)

This is a minimal, idempotent skeleton to provision:
- Docker engine
- Jenkins (with optional JCasC)
- Kubernetes tooling (kubectl)
- Optional local Docker registry

Usage example:
- Copy `inventory.sample` to `inventory` and edit hosts/vars
- Run: `ansible-playbook -i inventory playbook.yml`

Notes:
- Some tasks require privilege escalation (become). Adjust as needed.
- This skeleton avoids hard-coding secrets; use Ansible Vault for credentials.

