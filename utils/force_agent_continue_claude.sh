#!/bin/bash

# Nom de la session tmux
SESSION_NAME="claude"

# Boucle infinie
while true; do
  # Texte complet à envoyer
  COMMAND="continue le projet sur lesquel tu etais si il est pas complet et verifie que il passe bien tous les test indiqué dans le ou les fichiers .pdf du projet puis retourne a /home/roro/work/projects/Epitech_projects/claude/Semester-2 et verifie si tu as bien fais tous les projets sinon fais les, n'utilise jamais la commande sudo"

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
  sleep 1800
done
