##
## EPITECH PROJECT, 2025
## Bernstein
## File description:
## Makefile for Kubernetes deployment
##

KUBECTL = kubectl

all: deploy

deploy: deploy-cadvisor deploy-postgres deploy-redis deploy-apps deploy-traefik

deploy-cadvisor:
	@echo "Deploying cAdvisor monitoring..."
	$(KUBECTL) apply -f cadvisor.daemonset.yaml

deploy-postgres:
	@echo "Deploying PostgreSQL database..."
	$(KUBECTL) apply -f postgres.secret.yaml
	$(KUBECTL) apply -f postgres.configmap.yaml
	$(KUBECTL) apply -f postgres.volume.yaml
	$(KUBECTL) apply -f postgres.deployment.yaml
	$(KUBECTL) apply -f postgres.service.yaml

deploy-redis:
	@echo "Deploying Redis queue..."
	$(KUBECTL) apply -f redis.configmap.yaml
	$(KUBECTL) apply -f redis.deployment.yaml
	$(KUBECTL) apply -f redis.service.yaml

deploy-apps:
	@echo "Deploying application services..."
	$(KUBECTL) apply -f poll.deployment.yaml
	$(KUBECTL) apply -f worker.deployment.yaml
	$(KUBECTL) apply -f result.deployment.yaml
	$(KUBECTL) apply -f poll.service.yaml
	$(KUBECTL) apply -f result.service.yaml
	$(KUBECTL) apply -f poll.ingress.yaml
	$(KUBECTL) apply -f result.ingress.yaml

deploy-traefik:
	@echo "Deploying Traefik load balancer..."
	$(KUBECTL) apply -f traefik.rbac.yaml
	$(KUBECTL) apply -f traefik.deployment.yaml
	$(KUBECTL) apply -f traefik.service.yaml

init-db:
	@echo "Initializing database..."
	@echo "Waiting for PostgreSQL to be ready..."
	@sleep 30
	@echo "CREATE TABLE votes (id text PRIMARY KEY, vote text NOT NULL);" | \
	$(KUBECTL) exec -i deployment/postgres -- psql -U postgres

status:
	@echo "Checking deployment status..."
	$(KUBECTL) get pods --all-namespaces
	$(KUBECTL) get services --all-namespaces
	$(KUBECTL) get ingress

clean:
	@echo "Cleaning up deployments..."
	$(KUBECTL) delete -f traefik.service.yaml || true
	$(KUBECTL) delete -f traefik.deployment.yaml || true
	$(KUBECTL) delete -f traefik.rbac.yaml || true
	$(KUBECTL) delete -f result.ingress.yaml || true
	$(KUBECTL) delete -f poll.ingress.yaml || true
	$(KUBECTL) delete -f result.service.yaml || true
	$(KUBECTL) delete -f poll.service.yaml || true
	$(KUBECTL) delete -f result.deployment.yaml || true
	$(KUBECTL) delete -f worker.deployment.yaml || true
	$(KUBECTL) delete -f poll.deployment.yaml || true
	$(KUBECTL) delete -f redis.service.yaml || true
	$(KUBECTL) delete -f redis.deployment.yaml || true
	$(KUBECTL) delete -f redis.configmap.yaml || true
	$(KUBECTL) delete -f postgres.service.yaml || true
	$(KUBECTL) delete -f postgres.deployment.yaml || true
	$(KUBECTL) delete -f postgres.volume.yaml || true
	$(KUBECTL) delete -f postgres.configmap.yaml || true
	$(KUBECTL) delete -f postgres.secret.yaml || true
	$(KUBECTL) delete -f cadvisor.daemonset.yaml || true

fclean: clean

re: fclean all

tests_run:
	@echo "Running Kubernetes configuration tests..."
	@echo "Validating YAML syntax..."
	@for file in *.yaml; do \
		echo "Validating $$file..."; \
		$(KUBECTL) apply --dry-run=client -f $$file > /dev/null; \
	done
	@echo "All YAML files are valid!"

.PHONY: all deploy deploy-cadvisor deploy-postgres deploy-redis deploy-apps deploy-traefik init-db status clean fclean re tests_run