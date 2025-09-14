// Job DSL script for creating CI/CD jobs from SEED job parameters
def githubName = build.buildVariableResolver.resolve('GITHUB_NAME')
def displayName = build.buildVariableResolver.resolve('DISPLAY_NAME')

freeStyleJob(displayName) {
    description("CI/CD job for ${githubName}")
    
    properties {
        githubProjectProperty {
            projectUrl("https://github.com/${githubName}")
        }
    }
    
    scm {
        git {
            remote {
                url("https://github.com/${githubName}.git")
            }
        }
    }
    
    triggers {
        scm('* * * * *')  // Poll SCM every minute
    }
    
    wrappers {
        preBuildCleanup()
    }
    
    steps {
        shell('make fclean')
        shell('make')
        shell('make tests_run')
        shell('make clean')
    }
}