//
// EPITECH PROJECT, 2025
// Whanos_roro
// File description:
//   Jenkins Job DSL: link-project to create a project job
//

folder('Projects')

job('link-project') {
  parameters {
    stringParam('GIT_URL', '', 'Repository URL')
    stringParam('BRANCH', 'main', 'Default branch')
    stringParam('JOB_NAME', 'my-project', 'Project job name')
    stringParam('IMAGE_TAG', 'app:latest', 'Built image tag')
  }
  steps {
    dsl {
      text('''
        job("Projects/${JOB_NAME}") {
          scm {
            git {
              remote { url("${GIT_URL}") }
              branch("${BRANCH}")
            }
          }
          triggers { scm('* * * * *') }
          steps {
            shell('python3 ${WORKSPACE}/../Whanos_roro/src/whanos_build.py ${WORKSPACE} ${IMAGE_TAG} || true')
            shell(''' + "'" + '''
              if [ -f whanos.yml ]; then
                python3 ${WORKSPACE}/../Whanos_roro/src/whanos_k8s_gen.py whanos.yml ${IMAGE_TAG} > k8s_out.yaml || true
                if command -v kubectl >/dev/null 2>&1; then kubectl apply -f k8s_out.yaml || true; fi
              fi
            ''' + "'" + ''')
          }
        }
      '''.stripIndent())
    }
  }
}

