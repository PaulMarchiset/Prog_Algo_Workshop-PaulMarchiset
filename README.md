# 🌯 Paul Marchiset - Prog et algo

## 1 étoile

### Noir et Blanc

L'exercice du noir et blanc nous a permis de réutiliser une fonction vue en TD : la luminance qui nous permet de calculer pour chaque valeur rouge, verte et bleue de chaque pixel afin d'appliquer la couleur sur une échelle de gris.

Luminance :
```cpp
float luminance{0.2126f * image.pixel(x, y).r + 0.7152f * image.pixel(x, y).g + 0.0722f * image.pixel(x, y).b};
 ```

![](output/grayscale.jpg)

## 2 étoiles 

### Miroir

Pour créer un effet miroir sur l'axe vertical, il suffit de modifier la position en du premier pixel en X pour le mettre en position finale. Cette méthode peut créer un conflit car, lorsqu'on arrivera au milieu de l'image, on réécrira par dessus les pixels déjà copier. On obtiendra donc la moitié de l'image en miroir et le reste "normal" (voir images ci-dessous)

![](output/mirrorBug1.png)
![](output/mirrorBug2.png)

Pour contrer ce problème, l'utilisation du ```std::swap``` est nécessaire pour échanger les pixels entre la position x et leur position finale.

![](output/mirror.png)

### Bruit

Pour créer du bruit, il nous faut utiliser une valeur aléatoire entre plusieurs nombres. À chaque itération de boucle, c'est à dire, pour chaque pixel, on prend une valeur entre 0 et 2 (compris) et on définit une réponse à donner et à faire pour chaque pixel.


```cpp
switch (random_int(0, 3))
            {
            case 0:
                image.pixel(x, y).r = image.pixel(x, y).r + (rand() % 2) / 2.f;
                break;
            case 1:
                image.pixel(x, y).g = image.pixel(x, y).g + (rand() % 2) / 2.f;
                break;
            case 2:
                image.pixel(x, y).b = image.pixel(x, y).b + (rand() % 2) / 2.f;
                break;
            default:
                break;
            };
```

![](output/noise.png)

### Rotation

Pour cette transformation, il nous a fallu obligatoirement créer une nouvelle image. La simplicité de la transformation, nous permet de simplement récupérer l'inverser la largeur et la longueur pour la taille et ensuite d'inverser l'axe x et y sur la nouvelle image. La position x de la nouvelle image étant récupérer par la dernière position y de l'image précédente.

```cpp
new_image.pixel(new_width - 1 - y, x) = image.pixel(x, y);

```

![](output/rotate90.png)

## 3 étoiles

### cercle

Il nous faut d'abord définir la position centrale du cercle, sinon il prendra pour centre un coin de l'image.

En utilisant l'égalité mathématique : x² + y² = r² on arrive simplement à 

### animation 

### rosace

### glitch

## 4 étoiles 

### mosaïque et mosaïque miroir

### dithering

## Effets rigolos

### Matrix

### Tri

### Water effect

