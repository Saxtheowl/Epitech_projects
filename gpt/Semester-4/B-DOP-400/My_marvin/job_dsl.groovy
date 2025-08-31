/*
** EPITECH PROJECT, 2025
** my_marvin
** File description:
**   Job DSL definitions (root as required by subject)
*/

folder('Tools') {
    displayName('Tools')
    description('Folder for miscellaneous tools.')
}

job('Tools/clone-repository') {
    description('Clone arbitrary Git repository from URL')
    parameters {
        stringParam('GIT_REPOSITORY_URL', '', 'Git URL of the repository to clone')
    }
    wrappers {
        preBuildCleanup()
    }
    steps {
        shell('git clone "$GIT_REPOSITORY_URL" repo')
    }
}

job('Tools/SEED') {
    description('Create a build job from a GitHub repository and display name')
    parameters {
        stringParam('GITHUB_NAME', '', 'GitHub repository owner/repo_name (e.g.: "EpitechIT31000/chocolatine")')
        stringParam('DISPLAY_NAME', '', 'Display name for the job')
    }
    steps {
        dsl {
            external('job_dsl.groovy')
            additionalParameters([
                GITHUB_NAME: '$GITHUB_NAME',
                DISPLAY_NAME: '$DISPLAY_NAME'
            ])
        }
    }
}

def repo = binding.variables['GITHUB_NAME']
def display = binding.variables['DISPLAY_NAME']

if (repo && display) {
    job(display) {
        properties {
            githubProjectUrl("https://github.com/${repo}")
        }
        triggers {
            scm('* * * * *')
        }
        wrappers {
            preBuildCleanup()
        }
        scm {
            github(repo)
        }
        steps {
            shell('make fclean')
            shell('make')
            shell('make tests_run')
            shell('make clean')
        }
    }
}

