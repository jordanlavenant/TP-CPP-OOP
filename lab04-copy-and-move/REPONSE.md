# TP4

LAVENANT Jordan - APP4 IIM

## Partie 1

### 1.1

**Erreur :**

```bash
/usr/include/c++/13/bits/stl_construct.h:96:17: error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = shape; _Dp = std::default_delete<shape>]’
   96 |     -> decltype(::new((void*)0) _Tp(std::declval<_Args>()...))
      |                 ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

la fonction supprimée est le constructeur de copie de `std::unique_ptr`.

### 1.2

La ligne compile car la classe `drawing` déclare un constructeur de déplacement. `std::move(a)` transforme `a` en `rvalue`, ce qui appelle ce constructeur au lieu du constructeur de copie.

Le vecteur peut se déplacer sans se copier car les éléments `std::unique_ptr` ne sont pas clonés, mais leurs valeurs internes sont transférer vers le nouveau.

## Partie 2

### 2.2

**Erreur :**

```bash
/home/jorda/TP-CPP-OOP/lab04-copy-and-move/include/shape.hpp:75:29: error: invalid covariant return type for ‘virtual std::unique_ptr<circle> circle::clone() const’
   75 |     std::unique_ptr<circle> clone() const override;
      |
```

Quand une méthode virtuelle est redéfinie `override`, le type de retour dérivé soit être le même. Ici, `std::unique_ptr(circle)` et `std::unique_ptr(shape)` sont 2 classes différentes, ce qui ne permet pas de surcharger la méthode virtuelle.

### 2.5

Le code affiche 9 clones, avec et sans `reserve`.

Sans le `reserve` initial, le vecteur réalloue successivement de la mémoire pour ajouter les shapes, avec le `reserve`, le vecteur alloue une seule fois un bloc mémoire de taille 9, sans aucune réallocation.

## Partie 3

### 3.3

En enlevant le `noexcept`, on remarque qu'il y a 7 clones.

### 3.4

Le constructeur par défaut du compilateur déplace les membres, il appelle donc le constructeur de déplacement de `shapes`, ce qui transfère sans copie.

Non car si tous les membres ont un constructeur de déplacement `noexcept`, la version par défaut du constructeur est implicitement marquée `noexcept`.

## Partie 4

### 4.2

Grâce à l'idiome `copy-and-swap` utilisé dans `operator=(drawing const& other)`

### 4.4

La figure est devenue incomplète car en passant par une référence `drawing& arm = motif;`, `arm` n'est plus une copie indépendante, et deviens un alias vers l'unique objet `motif`.

Ainsi à chaque tour de boucle, les facteurs d'échelle se cumulent tour après tour au lieu de repartir de la taille initiale du motif, on reprt donc du motif déjà réduit par les tours précédents, jusqu'à réduire sa taille définitivemnt.
