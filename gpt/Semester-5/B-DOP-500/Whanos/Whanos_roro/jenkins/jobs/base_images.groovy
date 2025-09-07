//
// EPITECH PROJECT, 2025
// Whanos_roro
// File description:
//   Jenkins Job DSL: base images + build-all
//

folder('Whanos base images')

def langs = ['c','java','javascript','python','befunge']

langs.each { l ->
  job("Whanos base images/whanos-${l}") {
    description("Build base image for ${l}")
    steps {
      shell("""
      set -e
      cd ${WORKSPACE}/..
      docker build -f images/${l}/Dockerfile.base -t whanos-${l} . || true
      """.stripIndent())
    }
  }
}

job('Whanos base images/Build all base images') {
  description('Trigger all base image build jobs')
  steps {
    downstreamParameterized {
      trigger(langs.collect { "Whanos base images/whanos-${it}" }) {
        block { buildStepFailure('FAILURE'); failure('FAILURE'); unstable('UNSTABLE') }
      }
    }
  }
}

