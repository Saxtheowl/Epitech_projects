#!/bin/bash

# Nom de la session tmux
SESSION_NAME="gpt"

# Boucle infinie
while true; do
  # Texte complet à envoyer
COMMAND="continue le projet sur lequel tu étais s'il n'est pas complet et vérifie qu'il passe bien tous les tests indiqués dans les fichiers .pdf du projet, puis retourne à /home/roro/work/projects/Epitech_projects/gpt/Semester-5 et vérifie si tu as bien fait tous les projets, sinon fais-les. Si tu bloques trop sur le sujet en cours ou si tu as besoins de mon intervention pour continuer passe à un autre projet, n'utilise jamais la commande sudo, dans tous les cas avance sur un projet ou continue un autre"


  # Place le texte dans un buffer tmux pour éviter les coupures
#  tmux set-buffer -b force_cmd "$COMMAND"
#  tmux paste-buffer -t "$SESSION_NAME"

  # Envoie le "Enter" attendu (Ctrl+J + Enter)
  tmux send-keys -t "$SESSION_NAME" "$COMMAND" C-m
  tmux send-keys -t "$SESSION_NAME" C-j
  sleep 0.1
  tmux send-keys -t "$SESSION_NAME" Enter

  # Log local
  echo "[$(date '+%Y-%m-%d %H:%M:%S')] Commande envoyée à $SESSION_NAME"

  # Attente avant le prochain envoi
  sleep 1200
done
