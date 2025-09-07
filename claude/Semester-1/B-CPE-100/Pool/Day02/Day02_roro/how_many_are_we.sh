#!/bin/bash

if [ $# -eq 0 ]; then
    # Si aucun paramètre, afficher le nombre total d'étudiants
    tail -n +2 | wc -l
else
    # Afficher le nombre d'étudiants pour une ville donnée
    tail -n +2 | grep ",$1," | wc -l
fi