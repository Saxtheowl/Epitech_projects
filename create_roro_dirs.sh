#!/usr/bin/env bash
# ───────────────────────────────────────────────────────────────
# create_roro_dirs.sh – Ajoute un dossier  _roro  à côté de tout
# projet possédant son PDF, en ignorant les bootstrap.
# ───────────────────────────────────────────────────────────────

set -euo pipefail
shopt -s nullglob    # pour que les jokers vides ne passent rien
shopt -s nocaseglob  # pour que *.pdf soit insensible à la casse

# Parcours récursif avec find :
#   * on « prune » (ignore) tout chemin contenant /Bootstrap/
#   * on ne garde que les fichiers *.pdf
while IFS= read -r -d '' pdf_path; do
    project_dir="$(dirname "$pdf_path")"       # dossier qui contient le PDF
    project_name="$(basename "$project_dir")"  # nom du dossier projet
    parent_dir="$(dirname "$project_dir")"     # dossier parent

    roro_dir="${parent_dir}/${project_name}_roro"

    if [[ ! -e "$roro_dir" ]]; then
        mkdir "$roro_dir"
        echo "Création de : $roro_dir"
    fi
done < <(
    find . \
         -type d -iname '*bootstrap*' -prune -o \
         -type f -iname '*.pdf' -print0
)
