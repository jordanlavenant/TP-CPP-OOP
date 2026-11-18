# TP1

## Partie 1

### 1.2

La fonction membre n'apporte rien de plus

### 1.3

## Partie 2

### 2.1

3 tests échouent (sauf le premier qui réussi par accident) car la fonction to_hex() renvoie une chaîne en dur "#000000".

### 2.2

La vérification de la couleur par défaut n'échoue plus par accident, car avant elle renvoyt une chaîne en dur "#000000" alors que maintenant elle calcule réellement la chaîne hexadécimale à partir des attributs par défaut de l'objet.

Les 3 autres tests échouent toujours car les constructeurs ne sont pas encore implémentés.

### 2.3

D'après ce que renvoie la valeur de la class (#2c2800), on peut donc avec "2c" deviner la valeur en base 10, qui vaut 44. Ainsi si j'injecte 300 dans to_hex() pour la couleur rouge, on obtient 44, ce qui est cohérent avec la fonction saturate() qui limite les valeurs à 255.

### 2.4

Ainsi, la nouvelle couleur devient bien "#ff2800" si la valeur injectée est supérieure à 255, et "#002800" si elle est inférieure à 0. Cela est cohérent avec la fonction saturate() qui limite les valeurs à 255 et 0.

### 2.5

La saturation permet de préserver l'invariant [0, 255], pour représenter une couleur valide, en plafonnant les valeurs supérieures à 255 à 255 et en plancher les valeurs inférieures à 0 à 0.

La chaîne hexadécimale injecter dans le constructeur a un format textuel strict, une chaîne mal formée (mauvaise longueur, pas de # ou des caractères non-hexadécimaux) ne peut pas être convertie en couleur valide, donc assert arrête immédiatement l'exécution du programme. Cela permet de préserver l'invariant [0, 255] pour représenter une couleur valide.

### 2.6

- Le type uint8_t est un entier non signé sur 8 bits, ce qui permet de représenter les valeurs de 0 à 255. Cela est cohérent avec l'invariant [0, 255] pour représenter une couleur valide.
- Ainsi les bornes entière par 16 sont 0/16 = 0 et 255/16 = 15, ce qui permet de représenter les valeurs de 0 à 15, soit 16 valeurs possibles. Cela est cohérent avec l'invariant [0, 255] pour représenter une couleur valide.
- La table digits possède bien 16 caractètres valides indexées de 0 à 15.

Le quotient est donc strictement garanti d'être compris entre 0 et 15.

## Partie 3

### 3.1

La valeur hexadécimale donnée par aggregate "#12c2800" ne décrit pas une couleur valide, car elle ne respecte pas le format textuel strict attendu par le constructeur. Le constructeur attend une chaîne de 7 caractères commençant par un '#' suivi de 6 caractères hexadécimaux (0-9, a-f). La chaîne "#12c2800" contient 8 caractères et ne respecte donc pas ce format.

### 3.2

On constate qu'en remplaçant `mix(dawn, dusk, 0.5)` par `color{before::to_hex({300, 40, 0})}`, le programme s'arrete car la valeur obtenue ne respecte plus la bonne longueur (7 caractères) par le constructeur de la classe color.

### 3.3

La réparation de before::to_hex n'a protéger que la conversion en texte au moment de l'affichage, mais l'objet bedore::color lui-même n'est toujours pas protégé, et peuvent ainsi sortir des bornes à tous les endroits où before::color est utilisé.

- A chaque instanciation directe de before::color, on peut encore écrire des valeurs hors bornes
- Les champs red, green, blue étant publics, à chaque affectation directe d'un champ, on peut encore écrire des valeurs hors bornes.
- Dans la fonction mix, on peut encore écrire des valeurs hors bornes, si on ne vérifie pas.

## Partie 4

## 4.2

```bash
dawn #00dcff
dusk #ff1c00

r -153
g 220
b 459
```

Si on met t = 2.0, alors cela donne des valeurs hors bornes.

## 4.4

EN remplaçant l'arrondi par la troncature `static_cast<int>(...)`, la partie décimale est simplement jetée, ce qui donne 127 alors que le test attend 128. Tronquer introduit un biais systématique vers le bas.

## 4.5

```
Erreur d’analyse XML : aucun élément trouvé
Emplacement : file://///wsl.localhost/Ubuntu-24.04/home/jorda/TP-CPP-OOP/lab01-from-aggregates-to-classes/build/spiro.svg
Numéro de ligne 564, Colonne 1 :
```
