#!/bin/bash

# Chemin vers l'exécutable
EXEC="cub3d"
LOGFILE="log.txt"

# Couleurs ANSI (fonctionnent dans un terminal compatible)
RED="\033[0;31m"
GREEN="\033[0;32m"
BLUE="\033[0;34m"
NC="\033[0m" # No Color

# Vide le log au début
> "$LOGFILE"

# Vérifie que l'exécutable existe
if [ ! -x "$EXEC" ]; then
	echo "Erreur : exécutable '$EXEC' introuvable ou non exécutable." | tee -a "$LOGFILE"
	exit 1
fi

# Fonction pour détecter la couleur et le label à afficher dans le log
get_log_header() {
	local map_file="$1"
	local header=""
	if [[ "$map_file" == *"/bad/"* ]]; then
		header="${RED}BAD MAP: $map_file${NC}"
	elif [[ "$map_file" == *"/good/"* ]]; then
		header="${GREEN}GOOD MAP: $map_file${NC}"
	else
		header="${BLUE}MAP: $map_file${NC}"
	fi
	echo -e "$header"
}

# Fonction pour lancer valgrind
run_valgrind() {
	local map_file="$1"

	# Affichage console
	echo "⏳ Testing: $map_file"

	# En-tête coloré dans le log
	get_log_header "$map_file" >> "$LOGFILE"

	# Exécution de valgrind
	valgrind --leak-check=full ./"$EXEC" "$map_file" >> "$LOGFILE" 2>&1

	echo -e "\n" >> "$LOGFILE"
}

# Recherche et traitement de toutes les maps
find maps/ maps/good maps/bad -type f -name "*.cub" | while read -r map; do
	run_valgrind "$map"
done

echo -e "\n✅ Terminé ! Consulte le fichier ${BLUE}$LOGFILE${NC}"
