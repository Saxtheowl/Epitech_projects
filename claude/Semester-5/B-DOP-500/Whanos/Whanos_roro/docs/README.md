# Whanos - DevOps Infrastructure

Whanos is an advanced DevOps infrastructure that automatically deploys applications using Docker, Jenkins, Ansible, and Kubernetes.

## Architecture

The Whanos infrastructure consists of:

- **Docker Images**: Base and standalone images for supported languages
- **Jenkins**: CI/CD pipeline with automatic project linking
- **Kubernetes**: Multi-node cluster for application deployment
- **Ansible**: Infrastructure deployment and configuration management

## Supported Languages

- C (GCC 11.2)
- Java (OpenJDK 17)
- JavaScript (Node.js 14.17.5)
- Python (3.10)
- Befunge (Befunge-93)

## Quick Start

1. Build all Docker images:
   ```bash
   make build-images
   ```

2. Deploy infrastructure:
   ```bash
   make deploy-infrastructure
   ```

3. Start local registry:
   ```bash
   make deploy-registry
   ```

4. Run tests:
   ```bash
   make test
   ```

## Language Detection

Projects are automatically detected based on these criteria:

- **C**: Has a `Makefile` at repository root
- **Java**: Has `app/pom.xml` file
- **JavaScript**: Has `package.json` file
- **Python**: Has `requirements.txt` file
- **Befunge**: Has `app/main.bf` file

## Deployment Configuration

Applications can be configured for Kubernetes deployment using a `whanos.yml` file:

```yaml
deployment:
  replicas: 2
  resources:
    limits:
      memory: "512Mi"
      cpu: "0.5"
  ports:
    - 8080
    - 3000
```

## Jenkins Jobs

The infrastructure creates the following Jenkins jobs:

- **Whanos base images**: Folder containing base image build jobs
- **Projects**: Folder for application projects
- **link-project**: Job to link new projects to the infrastructure

## Infrastructure Components

### Docker Registry
- Runs on port 5000
- Stores all built application images

### Kubernetes Cluster
- Minimum 2 nodes (1 master, 1+ workers)
- Flannel networking
- NodePort services for external access

### Jenkins Server
- Configuration as Code enabled
- Automatic project detection and linking
- SCM polling every minute

## Testing

The project includes comprehensive tests:

```bash
# Run all tests
make test

# Test language detection
./scripts/test_language_detection.sh

# Test containerization
./scripts/test_containerization.sh

# Test Jenkins connectivity
make test-jenkins
```

## Deployment Guide

### Prerequisites

- Ansible installed
- SSH access to target machines
- Docker installed on all nodes

### Configuration

1. Update `ansible/inventory.yml` with your server IPs
2. Set environment variables in Ansible
3. Run deployment playbook

### Environment Variables

- `JENKINS_ADMIN_PASSWORD`: Jenkins admin password
- `JENKINS_URL`: Jenkins external URL
- `ssh_key_path`: Path to SSH private key

## File Structure

```
Whanos_roro/
├── images/                    # Docker images for each language
├── scripts/                   # Utility scripts
├── ansible/                   # Ansible playbooks and inventory
├── jenkins/                   # Jenkins configuration
├── tests/                     # Test files
├── docs/                      # Documentation
├── Makefile                   # Build and deployment targets
└── info_llm                   # Project information
```

## Troubleshooting

### Common Issues

1. **Docker permission denied**: Ensure user is in docker group
2. **Jenkins not accessible**: Check firewall and service status
3. **Kubernetes pods not starting**: Verify network plugin installation
4. **Registry push fails**: Ensure registry is running and accessible

### Logs

- Jenkins logs: `/var/log/jenkins/jenkins.log`
- Kubernetes logs: `kubectl logs <pod-name>`
- Docker logs: `docker logs <container-name>`

## Contributing

1. Follow Epitech coding standards
2. Add tests for new features
3. Update documentation
4. Ensure Makefile targets work correctly

## License

This project is part of the Epitech curriculum (B5 - Advanced DevOps).