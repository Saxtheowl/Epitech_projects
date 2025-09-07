##
## EPITECH PROJECT, 2025
## Whanos_roro
## File description:
##   Documentation (usage summary)
##

# Whanos_roro docs

- Detect repo language:
  `./src/whanos_detect.py <repo>`

- Build app image:
  `./src/whanos_build.py <repo> app:tag`
  - If repo has `Dockerfile` with `FROM whanos-<lang>`, base image is built then custom build is invoked.
  - Otherwise, standalone Dockerfile is used for the detected language.

- Generate K8s manifests from `whanos.yml`:
  `python3 ./src/whanos_k8s_gen.py whanos.yml app:tag > out.yaml`
  `kubectl apply -f out.yaml`
  - Supports `deployment.replicas`, `deployment.ports` and `deployment.resources`
    (limits/requests like cpu/memory)
  - Also supports `deployment.env` (key/value env), `deployment.namespace`,
    `deployment.service.type` (NodePort|ClusterIP|LoadBalancer), and
    `deployment.ingress.hosts` (list of hostnames; Traefik annotations are added).
    `deployment.volumes` supports PVC mounts:
    ```yaml
    deployment:
      volumes:
        - name: data
          claimName: mypvc
          mountPath: /data
          # subPath: logs
          # readOnly: true
    ```
  - Optional CLI: `--name <app>` to override app name used in resources.

- Jenkins:
  - `jenkins/Jenkinsfile.base` builds base images (param `LANG`).
  - `jenkins/Jenkinsfile.build-all` construit toutes les images de base (matrix LANG).
  - `jenkins/Jenkinsfile.link-project` crée un job de suivi (paramètres: `GIT_URL`, `BRANCH`, `CREDENTIALS_ID`, `IMAGE_TAG`, `PUSH`).
    - Clonage, build via `whanos_build.py`.
    - Si `whanos.yml` présent, génération et `kubectl apply`.
    - `PUSH=true` pousse l'image vers le registry précisé dans `IMAGE_TAG`.

- Exemple `whanos.yml` minimal:
  ```yaml
  deployment:
    replicas: 2
    ports: [80]
    resources:
      limits:
        cpu: "500m"
        memory: "256Mi"
      requests:
        cpu: "100m"
        memory: "64Mi"
  ```
  - Job DSL alternative:
    - `jenkins/jobs/base_images.groovy` crée les jobs `Whanos base images/*` et
      `Build all base images` (qui déclenche les jobs).
    - `jenkins/jobs/link_project.groovy` crée un job `link-project` qui génère un
      job sous `Projects/` pollant le SCM et déployant si `whanos.yml`.

- Images Docker livrées (base/standalone):
  `images/{c,java,javascript,python,befunge}/Dockerfile.{base,standalone}`.
