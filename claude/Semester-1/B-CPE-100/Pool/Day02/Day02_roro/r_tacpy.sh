#!/bin/bash

# Prendre les lignes 2 sur 2, extraire les logins (1er champ), les renverser, 
# trier en ordre inverse, prendre entre MY_LINE1 et MY_LINE2, formater avec virgules et point final
sed -n '2~2p' | cut -d: -f1 | rev | sort -r | sed -n "${MY_LINE1},${MY_LINE2}p" | tr '\n' ',' | sed 's/,$/.\n/'