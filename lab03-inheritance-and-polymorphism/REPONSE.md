# TP3

## Partie 1

### 1.4

**Erreur :** `/home/jorda/TP-CPP-OOP/lab03-inheritance-and-polymorphism/tests/test_shape.cpp:33:11: error: cannot declare variable ‘s’ to be of abstract type ‘shape’`

Le `= 0` déclare des fonctions virtuelles pures, sans corps dans la classe de base, ce qui rend `shape` abtraite, on ne peut donc pas faire d'instanciation directe et imposes aux classes enfants d'implémenter ces méthodes pour pouvoir êtres instanciées.

### 1.5

- **Sans `override` ni `const` (deux diagnostics) :**
  - **Avertissement :** `warning: ‘virtual std::string shape::title() const’ was hidden [-Woverloaded-virtual=]`  
    La méthode de `circle` masque celle de `shape` au lieu de la redéfinir car les signatures diffèrent (absence de `const`).
  - **Erreur :** `error: passing ‘const circle’ as ‘this’ argument discards qualifiers`  
    Dans les tests, `c` est déclaré `const` et ne peut pas appeler une méthode non-const.

- **Avec `override` (sans `const`) :**
  - **Nouvelle erreur :** `error: ‘std::string circle::title()’ marked ‘override’, but does not override`  
    Le mot-clé `override` impose au compilateur de vérifier la redéfinition : sans `const`, aucune méthode virtuelle correspondante n'existe dans la classe de base. L'avertissement de masquage reste présent.

## Partie 2

### 2.1

### 2.4

Pour ces 2 modifications, le test qui échoue est celui qui calcule l'aire du triangle.

Sur le premier remplacement, les triangles apparaissent plus petit et sur le second remplacement plus grand.

## Partie 3

### 3.1

L'image est identique et le compteur revient bien à 0.

### 3.2

Le détecteur signale un `AddressSanitizer: new-delete-type-mismatch`. Sans destructeur de base dans la classe de base, le destructeur de la classe dérivée n'est pas appelé et l'opérateur de la désallocation ne libère pas la bonne taille mémoire (taille différente entre `circle` et `shape`).

### 3.3

**Erreur :** `/usr/include/c++/13/bits/stl_construct.h:119:7: error: invalid new-expression of abstract class type ‘shape’`

La classe `shape` est une classe abstraite, ainsi ajouter un élement dans un `std::vector` nécessite d'instancier un objet `shape`, ce qui est impossible.

Si on voulait stocker une collection d'objets enfants différents, il faut obligatoirement passer par des pointeurs (ex: `std::vector<std::unique_ptr<shape>>>`).

### 3.4

En supprimant `= 0`, la classe `shape` devient concrète.

En supprimant les deux `= delete`, on autorise sa copie par valeur.

Si j'effectue un `v.push_back(circle{0.0, 0.0}, 1.0));`, le vecteur tente de stocker une instance de type `shape`, et va donc copier uniquement les attributs héritée de `shape` (centre), et ignore ceux appartenant à `circle` (le rayon).

Ainsi l'objet dans le vecteur est un objet `shape`, et donc ses méthodes appellent celles de `shape` et non celle de `circle`.
