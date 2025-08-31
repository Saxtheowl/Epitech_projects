<h1>Epitech Projects with AI</h1>
11;rgb:3030/0a0a/2424
<p>
  This repository is my attempt to complete most of the Epitech school projects by leveraging modern AI tools.
  The goal is not just to replicate the work, but to explore how advanced AI systems can assist, accelerate,
  and reshape the way we approach complex programming challenges.
</p>

<h2>🔧 Tools &amp; Setup</h2>

<h3>AI Assistants</h3>
<ul>
  <li>OpenAI GPT-5 Medium with Codex</li>
  <li>Anthropic Sonnet 4.1 with Claude Code</li>
  <li>Gemini 2.5 Pro with Gemini-cli(cancelled due to usage limit)</li>
</ul>

<h3>Environment</h3>
<ul>
  <li>Ubuntu 22.04 virtual machines (VMs) as the main development environment, plus Docker</li>
  <li>Standard toolchain used at Epitech (C, C++, Python, Makefiles, etc.)</li>
</ul>

<h2>📚 Project Subjects</h2>
<p>
  The project statements and requirements come from the following repository:
</p>
<p>
  <a href="https://github.com/Studio-17/Epitech-Subjects">https://github.com/Studio-17/Epitech-Subjects</a>
</p>

<h2>How we do it</h2>

<p><strong>Step 1:</strong></p>
<p>
  First, we set up a dedicated Ubuntu VM to let the agent work freely. Then we clean the repo and launch Codex (for GPT) in CLI with maximum permissions so it can run without constant confirmation, then we use a a tmux session for each llm agents, then  
  we launch a prompt like the following:
</p>

<pre>
Tu es un développeur expérimenté. Ta mission est de réaliser complètement tous les projets trouvés dans l'arborescence, en respectant strictement le style de code Epitech et les règles du Makefile. 
Pas de bonus : uniquement les fonctionnalités demandées dans le sujet. 
Pars du répertoire racine : /home/roro/work/projects/Epitech_projects/gpt/Semester-2 
Parcours récursivement tous les sous-répertoires. 
Si un projet contient un ou plusieurs fichiers PDF de sujet : lis attentivement ces fichiers pour comprendre le projet. 
Vérifie s’il existe déjà un dossier nom_du_projet_roro. 
Si le projet n’est pas terminé ou non compilable, reprends-le et termine-le. Sinon, passe au suivant.

Pour chaque projet trouvé, crée (si inexistant) un sous-dossier du projet sous le nom : nom_du_projet/nom_du_projet_roro. Exemple : Myls/Myls_roro/.

Dans ce sous-dossier, crée un fichier texte info_llm contenant :
- la date à laquelle tu as fini le projet
- ce que tu as compris du sujet
- ta stratégie pour réaliser le projet
- ce que tu as finalement fait (rapport final)

Respecte l’arborescence propre :
nom_du_projet_roro/
├── include/
├── src/
├── lib/        (si nécessaire)
├── tests/
├── info_llm
└── Makefile

Règles de style et organisation :
- Header Epitech en début de chaque fichier
- Noms clairs (anglais, snake_case, explicites)
- Indentation : 4 espaces, pas de tab, ≤ 80 colonnes
- Fonctions courtes : ≤ 20 lignes, ≤ 4 paramètres, 1 responsabilité
- Variables locales déclarées en début de fonction, une par ligne
- Pas de variables globales non const
- Prototypes regroupés dans include/

Makefile :
- Cibles obligatoires : all, clean, fclean, re
- Compilation incrémentale correcte
- Cible tests_run pour exécuter les tests avec Criterion et coverage

Livrable :
- Projet compilable avec make
- Code testable avec au moins un exemple de test dans tests/
</pre>

<p>
  Then, still for GPT (and similarly for Claude), we periodically launch scripts to keep the agent running and avoid message that interrupt the run like: " - I’m moving on to the next project in Semester-4. I’ll start with B-PSU-400/NmObjdump, implement both binaries with proper Makefiles, follow the PDF exactly, and verify
outputs with the specified examples. If you prefer a different priority (e.g., My_ftp, Ftrace), tell me and I’ll switch. "
.
  We monitor it from time to time and adjust the repository or prompt to help it progress through all projects.
</p>

<p>Here is the continue script:</p>

<pre>
#!/bin/bash
# Nom de la session tmux
SESSION_NAME="gpt"

# Boucle infinie
while true; do
  # Texte complet à envoyer
  COMMAND="continue le projet sur lequel tu étais s'il n'est pas complet et vérifie qu'il passe bien tous les tests indiqués dans les fichiers .pdf du projet, puis retourne à /home/roro/work/projects/Epitech_projects/gpt/Semester-4 et vérifie si tu as bien fait tous les projets, sinon fais-les. N'utilise jamais la commande sudo."

  # Envoie la commande à tmux
  tmux send-keys -t "$SESSION_NAME" "$COMMAND" C-m
  tmux send-keys -t "$SESSION_NAME" C-j
  sleep 0.1
  tmux send-keys -t "$SESSION_NAME" Enter

  # Log local
  echo "[$(date '+%Y-%m-%d %H:%M:%S')] Commande envoyée à $SESSION_NAME"

  # Attente avant le prochain envoi
  sleep 600
done
</pre>

<p><strong>Step 2:</strong></p>
<p>
  We check each project individually and fix issues, either with AI or manually, to make sure everything works.
</p>

<p><strong>Step 3:</strong></p>
<p>
  We pick the best projects, then try to automate the whole process even more, so that the agent can eventually complete all projects with minimal errors.
</p>

<p>Many thanks to Studio-17 for making these subjects available 🙏</p>