# Projet snake2024

## Utilisation des maps
Pour créer une carte utilisable il faut faire en sorte que toutes les lignes aient le même nombre de caractères

ATTENTION => TOUJOURS FINIR LE FICHIER PAR UN RETOUR A LA LIGNE (ligne finale vide)

## BUGS A CORRIGER
- Affichage d'un warning lors de la compilation qui affiche que getline() est déclaré implicitement à la ligne 105 de grid.c
	=> Remplacer getline() par fgets()
	voir : https://stackoverflow.com/questions/59014090/warning-implicit-declaration-of-function-getline
	size_t len = strlen(line);
        	if (len > 0 && line[len - 1] == '\n') {
            		line[len - 1] = '\0';
        	}

## FUITES MEMOIRE
- Fuite de mémoire de 18 octets (déjà présent lors de la V4) lors du lancement avec une option (pas d'allocation) et de 50 octets lors du lancement classique du programme => Verifier si la mémoire a été libérée de : fenêtre graphique, structure snake, police d'écriture


Commande : valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./game.out

## AMELIORATIONS POSSIBLES
- Quand on ajoute un argument après ./game.out alors le jeu se lance normalement s'il n'y a pas de - pour préciser que c'est une option, on préfèrerais le fonctionnemen>

- Centrer les écrans de victoire et de défaite

- Faire une option -d qui permet de choisir la difficulté
