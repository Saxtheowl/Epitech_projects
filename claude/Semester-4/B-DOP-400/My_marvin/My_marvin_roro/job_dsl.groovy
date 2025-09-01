// Job DSL script for SEED job
job(DISPLAY_NAME) {
    description('')
    
    properties {
        githubProjectProperty {
            projectUrl("https://github.com/${GITHUB_NAME}")
        }
    }
    
    scm {
        git {
            remote {
                url("https://github.com/${GITHUB_NAME}.git")
            }
        }
    }
    
    triggers {
        scm('* * * * *')
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