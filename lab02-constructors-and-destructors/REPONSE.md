# TP2

LAVENANT Jordan - APP4 IIM

## Partie 1

### 1.2

La balise `</svg>` apparaitra dans le flux lorsque l'objet `canvas` sera détruit, lorsque le destructeeur sera appelé.

### 1.4

```
<svg width="900" height="900">
<svg width="900" height="900">
</svg>
```

Le premier en tete `<svg>` provient de canvas `sheet = file` qui convertit implcitement le flux `file` en `canvas`.

Le second en tete `<svg>` provient de l'appel à la fonction prenant un `canvas` en lui passant `file`, le compilateur fait une seconde conversion implicite en créant silencieusement un objet `canvas`. A la sortie de la fonction, l'objet est détruit, et son destructeur écrit la base fermante `</svg>`.

### 1.5

- Avant toute construction, `alive` vaut 0
- Après la seconde construction, `alive` vaut 2
- Après la sortie de la portée , `alive` vaut 1

## Partie 2

### 2.1

En ignorant les avertissements, et initialisant un `canvas` avec les attributs membres, la vérification qui échoue est : `"le centre est au bon endroit"`.

Le compilateur signale aussi que l'ordre réel d'initialisation ne correspond pas à l'ordre écrit dans la liste d'initialisation du constructeur.

### 2.2

**Règle :** Les attributs membres d'une classe sont toujours initiéalisés dans l'ordre de leur déclaration dans la classe.

On a retenu cet ordre afin que l'ordre de construction soit unique et déterministe, et l'ordre de destruction soit toujours l'ordre inverse.

### 2.3

#### Erreur 1

`error: uninitialized reference member in ‘std::ostream&’ {aka ‘class std::basic_ostream<char>&’} [-fpermissive]`

#### Erreur 2

`error: use of deleted function ‘std::basic_ostream<...>::operator=(const std::basic_ostream<...>&)’`

La liste d'initialisation permet d'initialiser les références et les constantes, qui doivent obligatoirement êtres liées dès la création de l'objet.

## Partie 3

### 3.2

Si la copie était autorisée, on aurai une même référence vers le même `canvas`. Ainsi, à la destruction, les 2 destructeurs s'éxécuteraient et appelleraient `close_group()`, alors qu'il n'y a qu'une seule balise `<g>` ouvrante, et produirait un SVG invalide car on aurai 2 balises `</g>`.

### 3.3

La dernière balise ouvrante est :

`<g transform="translate(0,-150) rotate(31) scale(0.74)">`

Et est suivi de 12 balises `</g>` fermante puis de la balise fermante `</svg>`.

### 3.4

Message d'erreur :

`/home/jorda/TP-CPP-OOP/lab02-constructors-and-destructors/src/canvas.cpp:34:5: error: increment of member ‘canvas::strokes_’ in read-only object`

Cela compile car `out_` fait référence vers un objet externe, ainsi elle ne rend pas le flux constant, car seulement les membres de `canvas` deviennent constant. Comme on a retiré `++strokes;`, aucun membre de `canvas` n'est modifié, donc le code est valide pour le compilateur.

## Partie 4

### 4.1

J'ai bel et bien 400 balise ouvrante avec `strokes`.
