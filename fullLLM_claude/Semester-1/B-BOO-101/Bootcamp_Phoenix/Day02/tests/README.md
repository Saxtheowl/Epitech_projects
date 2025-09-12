# Tests unitaires pour Day02

## Prérequis
Pour exécuter ces tests, vous devez avoir Criterion installé :

```bash
# Ubuntu/Debian
sudo apt-get install libcriterion-dev

# Arch Linux
sudo pacman -S criterion

# Compilation manuelle (voir la documentation Criterion)
```

## Compilation et exécution des tests

```bash
# Test pour my_strcpy
gcc -o test_strcpy test_my_strcpy.c ../my_strcpy.c -lcriterion
./test_strcpy

# Test pour my_strncmp  
gcc -o test_strncmp test_my_strncmp.c ../my_strncmp.c -lcriterion
./test_strncmp

# Avec couverture de code (optionnel)
gcc -o test_strcpy test_my_strcpy.c ../my_strcpy.c -lcriterion --coverage
./test_strcpy
gcov my_strcpy.c
```

## Couverture requise
- Line coverage: 60% minimum
- Branch coverage: 40% minimum

Les tests couvrent les cas suivants :
- Copie de chaînes normales
- Chaînes vides
- Comparaisons identiques/différentes
- Cas limites (n=0, chaînes plus courtes que n, etc.)