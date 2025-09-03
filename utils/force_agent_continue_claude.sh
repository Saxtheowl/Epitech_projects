#!/bin/bash

# Nom de la session tmux
SESSION_NAME="claude"

# Boucle infinie
while true; do
    COMMAND="Objectif :
- Parcourir récursivement le dossier :
  /home/roro/work/projects/Epitech_projects/claude/Semester-1
- Identifier chaque projet.
- Pour chaque projet, analyser :
  1. Le ou les fichiers PDF du sujet (priorité absolue)
  2. Le code et/ou README pour évaluer l’état d’avancement
- Chaque projet doit être réalisé dans son dossier <nom_du_projet>_roro.

Règles d'action :
1. Le PDF est la source de vérité pour savoir quoi faire dans le projet.
2. Si un projet non terminé est détecté :
   - Le continuer dans le dossier <nom_du_projet>_roro et le créer s’il n’existe pas, en suivant strictement les instructions du PDF.
3. Si le projet en cours est terminé ou bloqué sans mon intervention :
   - Passer au projet suivant non terminé.
4. Vérifier pour chaque projet :
   - Toutes les parties obligatoires du PDF sont réalisées
   - Les bonus doivent être ignorés
5. Ne jamais utiliser la commande sudo.
6. Pour chaque projet, un fichier info_llm doit être présent à la racine du dossier <nom_du_projet>_roro.
   Ce fichier doit contenir :
   - La date complète de fin du projet (AAAA-MM-JJ HH:MM:SS)
   - Ce que tu as compris du sujet
   - Ta stratégie pour le réaliser
   - Ce que tu as finalement fait (rapport final)
   - Les commandes exactes pour compiler, exécuter et tester le projet
7. Tu dois décider toi-même des actions à entreprendre sans demander ma confirmation.

Format de réponse attendu :
- **Projet sélectionné :** Nom du projet
- **État actuel :** Description claire de ce qui est fait ou non
- **Étapes suivantes :** Liste détaillée des prochaines actions basées sur le PDF
- **Dossier _roro :** État du dossier (créé, mis à jour, ou déjà existant)
- **info_llm :** Statut (créé, mis à jour, ou déjà complet)"




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
  sleep 3600
done
