**compilation cairo :**

make

cd bin

./main grilles/<Nom de grille>

**compilation en mode texte :**

make MODE=TEXTE

cd bin

./main_txt grilles/<Nom de grille>

**attention :** il faut mettre le dossier grilles se trouvant dans Master dans le dossier bin afin de pouvoir effectuer la compilation.


**make docs :** génère la documentation

**make clean :** permet d'effacer les dossiers/fichiers générés

**make dist :** permet de générer un format compressé.



**Touches de contrôle:**

**v :** permet d'activer/désactiver le vieillissement 

**c :** permet d'activer/désactiver le mode cyclique

**n :** permet de charger une nouvelle grille en respectant le chemin grilles/<Nom de grille>

**o :** permet de savoir si la colonie est oscillante ou non

**clic gauche de souris :** fait évoluer la grille

**clic droit de souris :** quitte le jeu