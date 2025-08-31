#!/bin/bash

# Nom de la session tmux
SESSION_NAME="gpt"

# Boucle infinie
while true; do
  # Génère une commande shell pour créer un fichier avec date/heure dans tmux
  COMMAND="cree un nouveau fichier appelé test et met la date jusquau seconde dans le nom du fichier"

  # Envoie la commande dans la session tmux
  tmux send-keys -t "$SESSION_NAME" "$COMMAND" C-m
  tmux send-keys -t "$TARGET" C-j   # ← Codex shows “Ctrl+J newline”
  sleep 0.1
  tmux send-keys -t "$TARGET" C-m   # ← fallback “Enter”



  # Affiche un log local dans le terminal
  echo "[$(date '+%Y-%m-%d %H:%M:%S')] Commande envoyée à $SESSION_NAME"

  # Attente de 60 secondes
  sleep 20
done
