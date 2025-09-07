#!/bin/bash

# Extraire les noms d'utilisateurs (5ème champ) et compter ceux qui commencent par le paramètre
cut -d: -f5 | grep "^$1" | wc -l