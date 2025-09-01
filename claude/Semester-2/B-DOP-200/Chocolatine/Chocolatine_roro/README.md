# Chocolatine - GitHub Actions CI/CD Workflow

A comprehensive GitHub Actions workflow for Epitech projects implementing automated testing, coding style checks, compilation verification, and repository mirroring.

## Overview

This workflow provides a complete CI/CD pipeline with the following features:
- Automated coding style verification using Epitech's coding style checker
- Program compilation testing with timeout protection
- Automated test execution
- Repository mirroring for deployment

## Workflow Jobs

### 1. check_coding_style
- **Container**: `ghcr.io/epitech/coding-style-checker:latest`
- **Purpose**: Validates code against Epitech coding standards
- **Features**: Automatic error annotations for style violations

### 2. check_program_compilation
- **Container**: `epitechcontent/epitest-docker:latest`
- **Purpose**: Verifies project compiles successfully
- **Timeout**: 2 minutes
- **Depends on**: coding style check

### 3. run_tests
- **Container**: `epitechcontent/epitest-docker:latest`
- **Purpose**: Executes project test suite
- **Timeout**: 2 minutes
- **Depends on**: compilation check

### 4. push_to_mirror
- **Purpose**: Mirrors repository to deployment target
- **Trigger**: Only on push events
- **Depends on**: test execution
- **Uses**: SSH key authentication

## Environment Variables

- `MIRROR_URL`: Target repository URL for mirroring
- `EXECUTABLES`: List of executable names (if needed)

## Secrets Required

- `GIT_SSH_PRIVATE_KEY`: SSH private key for repository mirroring

## Branch Configuration

The workflow ignores branches with the prefix `ga-ignore-` to allow for testing without triggering the CI/CD pipeline.

## Usage

1. Place this workflow in `.github/workflows/chocolatine.yml`
2. Configure the required secrets in your repository settings
3. Ensure your project has proper Makefile with `make`, `make clean`, and `make tests_run` targets
4. Push changes to trigger the workflow

## Requirements

- Makefile with standard Epitech targets
- Test suite accessible via `make tests_run`
- Proper Epitech coding style compliance
- SSH key configured for repository mirroring