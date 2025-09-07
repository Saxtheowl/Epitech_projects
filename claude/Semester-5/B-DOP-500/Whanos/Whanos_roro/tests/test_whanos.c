/*
** EPITECH PROJECT, 2025
** Whanos
** File description:
** Unit tests for Whanos infrastructure
*/

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

Test(whanos_detection, test_language_detection_script_exists)
{
    int status = system("test -x scripts/detect_language.sh");
    cr_assert_eq(WEXITSTATUS(status), 0, "detect_language.sh should be executable");
}

Test(whanos_containerization, test_containerization_script_exists)
{
    int status = system("test -x scripts/containerize.sh");
    cr_assert_eq(WEXITSTATUS(status), 0, "containerize.sh should be executable");
}

Test(whanos_deployment, test_deployment_script_exists)
{
    int status = system("test -x scripts/deploy_k8s.sh");
    cr_assert_eq(WEXITSTATUS(status), 0, "deploy_k8s.sh should be executable");
}

Test(whanos_images, test_dockerfile_base_exists)
{
    cr_assert_eq(system("test -f images/c/Dockerfile.base"), 0);
    cr_assert_eq(system("test -f images/java/Dockerfile.base"), 0);
    cr_assert_eq(system("test -f images/javascript/Dockerfile.base"), 0);
    cr_assert_eq(system("test -f images/python/Dockerfile.base"), 0);
    cr_assert_eq(system("test -f images/befunge/Dockerfile.base"), 0);
}

Test(whanos_images, test_dockerfile_standalone_exists)
{
    cr_assert_eq(system("test -f images/c/Dockerfile.standalone"), 0);
    cr_assert_eq(system("test -f images/java/Dockerfile.standalone"), 0);
    cr_assert_eq(system("test -f images/javascript/Dockerfile.standalone"), 0);
    cr_assert_eq(system("test -f images/python/Dockerfile.standalone"), 0);
    cr_assert_eq(system("test -f images/befunge/Dockerfile.standalone"), 0);
}

Test(whanos_makefile, test_makefile_targets)
{
    cr_assert_eq(system("make help >/dev/null 2>&1"), 0, "Makefile should have help target");
}

Test(whanos_ansible, test_ansible_playbook_exists)
{
    cr_assert_eq(system("test -f ansible/deploy_whanos.yml"), 0);
    cr_assert_eq(system("test -f ansible/inventory.yml"), 0);
}

Test(whanos_jenkins, test_jenkins_config_exists)
{
    cr_assert_eq(system("test -f jenkins/jenkins.yml"), 0);
}