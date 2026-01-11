# JEU-DU-PLANTAMITZ

## Description du projet
Plantamitz est un **jeu de plateau interactif** développé en C, combinant **programmation informatique** et **gestion de contrat** inspirée des jeux de type "match-3". Le joueur doit remplir un **contrat de collecte d’items** en un nombre limité de coups, en manipulant un plateau composé de différents fruits et légumes.

Le projet respecte un cahier des charges précis et met en œuvre des fonctionnalités de **génération aléatoire du plateau**, de **gestion des alignements interdits**, de **collecte d’items**, et de **suivi des objectifs du contrat**.

---

## Objectifs du jeu
- Le plateau est une **matrice de 25 lignes x 45 colonnes**, remplie aléatoirement avec les items suivants :  
  - `S` : Soleil  
  - `F` : Fraise  
  - `P` : Pomme  
  - `O` : Oignon  
  - `M` : Mandarine  

- Le joueur doit **atteindre les objectifs du contrat** qui varient selon le niveau :
  - Exemple niveau 1 : 20 fraises, 50 oignons, 20 mandarines en 30 coups maximum
  - Exemple niveau 2 : 55 soleils, 35 pommes, 30 fraises, 45 oignons en 40 coups maximum  

- Les **alignements interdits** (horizontal, vertical, rectangle 2x2, figure en H) sont contrôlés dès la génération du plateau pour garantir un plateau stable.

---

## Fonctionnalités principales
1. **Génération du plateau**
   - Remplit le plateau aléatoirement tout en empêchant les alignements interdits dès le départ.
2. **Affichage coloré**
   - Chaque item a une couleur spécifique pour une meilleure lisibilité.
3. **Gestion du contrat**
   - Initialisation du contrat selon le niveau choisi.
   - Suivi du nombre d’items restants à collecter.
   - Gestion du nombre de coups restants.
   - Vérification automatique de l’état du contrat (réussi, en cours, échoué).
4. **Collecte d’items**
   - Décrémentation des objectifs et du nombre de coups lors de la collecte d’un item.

---

## Structure du code
- `main.c` : logique principale du jeu, génération du plateau, simulation de la collecte et affichage.
- `sousP.c` : fonctions de génération du plateau , remplissage du plateau, affichage des items et colour.
- `header.h` : définition des structures, énumérations et prototypes des fonctions.
- `curseur.c` : fonction de détection des alignements en utilisant les touches d'alignement 'Z'(gauche), 'S'(droites), 'Q'(haut), 'D'(bas) .
- 'gestion_contrat.c' : fonctions liées à la **gestion du contrat** (initialisation, collecte)
- 'progression.c' : fonction liés  aux suivi et vérification
- 'musique.c' : fonction bonus pour intergrer un musique lors du début du jeu
- 'items_speciaux.c': fonction bonus pour un effet speciales sur l'alignement des items (bombes)

---

## Technologies utilisées
- **Langage** : C  
- **OS** : Windows (utilisation de `conio.h` et `windows.h` pour la couleur console)  
- **Outils** : compilateur C (ex : GCC ou Visual Studio)  

---

## Comment jouer
1. Compiler le projet avec un compilateur C.
2. Lancer l’exécutable.
3. Observer le plateau généré et le contrat affiché.
4. Simuler la collecte d’items (exemples déjà présents dans le code).
5. Vérifier l’avancement du contrat après chaque action.

---

## Perspectives d’évolution
- Intégrer la **logique complète du plateau** : permutations, détection automatique des alignements, suppression et chute des items.
- Ajouter une **interface graphique** pour remplacer la console.
- Créer plusieurs niveaux avec **contrats dynamiques** pour augmenter la difficulté.
- Sauvegarde et chargement de la progression du joueur.
