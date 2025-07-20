# Documentation Complète - Projet Arcade

## Table des Matières
1. [Vue d'ensemble](#vue-densemble)
2. [Architecture du Projet](#architecture-du-projet)
3. [Interfaces](#interfaces)
4. [Bibliothèques Graphiques](#bibliothèques-graphiques)
5. [Jeux Implémentés](#jeux-implémentés)
6. [Système de Chargement Dynamique](#système-de-chargement-dynamique)
7. [Gestion des Scores](#gestion-des-scores)
8. [Compilation et Utilisation](#compilation-et-utilisation)
9. [Structure des Fichiers](#structure-des-fichiers)

## Vue d'ensemble

Le projet Arcade est une plateforme de jeux modulaire développée en C++ qui permet de jouer à différents jeux avec différentes bibliothèques graphiques. Le système utilise un chargement dynamique de bibliothèques pour permettre le changement de rendu graphique et de jeux en temps réel.

### Fonctionnalités principales :
- Support de 3 bibliothèques graphiques : SFML, SDL2, NCurses
- 2 jeux implémentés : Snake et Nibbler
- Chargement dynamique des modules
- Système de scores persistant
- Interface utilisateur avec menu de navigation

## Architecture du Projet

Le projet suit une architecture modulaire basée sur des interfaces abstraites :

```
Arcade Core
├── IDisplay (Gestionnaire principal)
├── IGraphic (Interface graphique)
│   ├── SFML
│   ├── SDL2
│   └── NCurses
└── IGame (Interface jeux)
    ├── Snake
    └── Nibbler
```

## Interfaces

### IGraphic (Interface Graphique)

**Fichier :** `include/Interface/IGraphic.hpp`

Interface abstraite définissant les méthodes communes à toutes les bibliothèques graphiques :

```cpp
class IGraphic {
public:
    virtual ~IGraphic() = default;
    virtual void init() = 0;
    virtual void clearScreen() = 0;
    virtual void drawText(const std::string &text, int x, int y, int id) = 0;
    virtual void drawSprite(int x, int y, const std::string &sprite) = 0;
    virtual void refreshScreen() = 0;
    virtual int getInput() = 0;
    virtual bool isOpen() const = 0;
    virtual void close() = 0;
    virtual int *showMenu(const std::vector<std::string>& gameList, 
                         const std::vector<std::string>& gamelib, 
                         int scr1, int scr2) = 0;
};
```

### IGame (Interface Jeux)

**Fichier :** `include/Interface/IGames.hpp`

Interface abstraite pour tous les jeux :

```cpp
class IGame {
public:
    virtual ~IGame() = default;
    virtual void init() = 0;
    virtual std::vector<std::string> loadMap(const std::string &filename) = 0;
    virtual void update() = 0;
    virtual void handleInput(int key) = 0;
    virtual bool isGameOver() const = 0;
    virtual void reset() = 0;
    virtual int game(IGraphic *module, int *bestscore) = 0;
    virtual std::string getGameName() const = 0;
    virtual int getScore() const = 0;
};
```

### IDisplay (Gestionnaire Principal)

**Fichier :** `include/Interface/IDisplay.hpp`

Classe principale qui gère l'interface utilisateur, le chargement des modules et la coordination entre les jeux et les bibliothèques graphiques.

**Fonctionnalités :**
- Affichage du menu principal
- Gestion des entrées utilisateur
- Chargement dynamique des bibliothèques
- Coordination jeu/graphique

## Bibliothèques Graphiques

### 1. SFML

**Fichiers :** `include/Graphics/sfml.hpp`, `src/SFML/sfml.cpp`

**Caractéristiques :**
- Fenêtre 1920x1080
- Support des textures et polices
- Gestion complète des événements clavier
- Rendu 2D optimisé

**Initialisation :**
```cpp
void Sfml::init() {
    _window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Arcade-SFML");
    _font = new sf::Font();
    _font->loadFromFile("resources/font.ttf");
}
```

### 2. SDL2

**Fichiers :** `include/Graphics/sdl.hpp`, `src/SDL/sdl.cpp`

**Caractéristiques :**
- Fenêtre 1920x1080
- Support SDL_TTF pour le texte
- Support SDL_Image pour les sprites
- Rendu accéléré matériellement

**Initialisation :**
```cpp
void Sdl::init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    _window = SDL_CreateWindow("Arcade-SDL2", SDL_WINDOWPOS_CENTERED, 
                              SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}
```

### 3. NCurses

**Fichiers :** `include/Graphics/ncurses.hpp`, `src/ncurses/ncurses.cpp`

**Caractéristiques :**
- Interface textuelle en terminal
- Mapping des sprites vers des caractères ASCII
- Gestion des entrées clavier
- Affichage optimisé pour le terminal

**Mapping des sprites :**
- Mur (`wall`) → `#`
- Joueur (`player`) → `@`
- Pomme (`apple`) → `o`

## Jeux Implémentés

### 1. Snake

**Fichiers :** `include/Games/snake.hpp`, `src/games/snake.cpp`

**Gameplay :**
- Serpent qui grandit en mangeant des pommes
- Collision avec les murs = Game Over
- Collision avec soi-même = Game Over
- Score : +10 points par pomme

**Contrôles :**
- Pavé numérique : 2 (bas), 4 (gauche), 6 (droite), 8 (haut)

**Structure de données :**
```cpp
typedef struct pos {
    int x;
    int y;
} pos;
pos snake[100];  // Corps du serpent
int snakeSize;   // Taille actuelle
int direction;   // Direction courante
```

### 2. Nibbler

**Fichiers :** `include/Games/nibbler.hpp`, `src/games/nibbler.cpp`

**Gameplay :**
- Similaire à Snake mais avec rebond sur les murs
- Le serpent change de direction en touchant un mur
- Objectif : manger toutes les pommes

**Différences avec Snake :**
- Pas de Game Over sur collision mur
- Rotation automatique de direction
- Logique de rebond implémentée

## Système de Chargement Dynamique

### DLLoader

**Fichier :** `include/Interface/DLLoader.hpp`

Template générique pour le chargement dynamique de bibliothèques :

```cpp
template <typename T>   
class DLLoader {
private:
    void *handle;
    T *(*createFunc)();
    void (*destroyFunc)(T *);

public:
    DLLoader(const std::string &libPath);
    ~DLLoader();
    T *getInstance();
    void destroyInstance(T *instance);
};
```

**Utilisation :**
```cpp
// Chargement d'une bibliothèque graphique
DLLoader<IGraphic> loader("./lib/arcade_sfml.so");
IGraphic *module = loader.getInstance();

// Chargement d'un jeu
DLLoader<IGame> gameLoader("./lib/arcade_snake.so");
IGame *game = gameLoader.getInstance();
```

### Bibliothèques Compilées

Les modules sont compilés en bibliothèques partagées :
- `lib/arcade_sfml.so`
- `lib/arcade_sdl2.so`
- `lib/arcade_ncurses.so`
- `lib/arcade_snake.so`
- `lib/arcade_nibbler.so`

## Gestion des Scores

### ScoreManager

**Fichier :** `include/Interface/ScoreManager.hpp`

**Fonctionnalités :**
- Sauvegarde persistante dans le fichier "Score"
- Format : `NomJeu NomJoueur Score`
- Affichage dans le menu principal

```cpp
class ScoreManager {
public:
    void saveScore(const std::string &gameName, 
                  const std::string &playerName, 
                  int score);
};
```

## Compilation et Utilisation

### Makefile

**Cibles principales :**
```makefile
all: core graphicals games
core: $(NAME)                    # Exécutable principal
graphicals: $(GRAPHICAL_LIBS)    # Bibliothèques graphiques
games: $(GAME_LIBS)              # Bibliothèques de jeux
```

**Compilation :**
```bash
make all
```

**Flags de compilation :**
- `-Wall -Wextra -Werror -std=c++20 -fPIC`
- SFML : `-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system`
- SDL2 : `-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer`
- NCurses : `-lncurses`

### Utilisation

**Lancement :**
```bash
./arcade <library_path>
```

**Exemples :**
```bash
./arcade ./lib/arcade_sfml.so
./arcade ./lib/arcade_sdl2.so
./arcade ./lib/arcade_ncurses.so
```

**Contrôles en jeu :**
- `F1` : Quitter le jeu
- `F2/F3` : Changer de bibliothèque graphique
- `F6/F7` : Changer de jeu
- `P` : Pause
- `R` : Reset
- `Esc` : Fermer l'application

## Structure des Fichiers

```
B-OOP-400-COT-4-1-arcade-andy.sagbo-main/
├── Makefile                    # Configuration de compilation
├── README.md                   # Informations de base
├── doc/                        # Documentation
│   ├── B-OOP-400_arcade.pdf   # Spécifications du projet
│   └── Documentation Arcade.pdf
├── include/                    # Fichiers d'en-tête
│   ├── Games/
│   │   ├── nibbler.hpp
│   │   └── snake.hpp
│   ├── Graphics/
│   │   ├── ncurses.hpp
│   │   ├── sdl.hpp
│   │   └── sfml.hpp
│   └── Interface/
│       ├── DLLoader.hpp        # Chargement dynamique
│       ├── Error.hpp           # Gestion d'erreurs
│       ├── IDisplay.hpp        # Interface principale
│       ├── IGames.hpp          # Interface jeux
│       ├── IGraphic.hpp        # Interface graphique
│       └── ScoreManager.hpp    # Gestion des scores
├── lib/                        # Bibliothèques compilées
│   └── lib_arcade
├── resources/                  # Ressources du jeu
│   ├── assets/                 # Images et sprites
│   │   ├── apple.png
│   │   ├── arcade.png
│   │   ├── background.png
│   │   ├── ground.png
│   │   ├── image_arcade.png
│   │   ├── player.png
│   │   └── wall.png
│   ├── font.ttf               # Police de caractères
│   ├── nibbler.txt            # Carte Nibbler
│   └── snake.txt              # Carte Snake
└── src/                       # Code source
    ├── IDisplay.cpp           # Implémentation principale
    ├── main.cpp               # Point d'entrée
    ├── SDL/
    │   └── sdl.cpp
    ├── SFML/
    │   └── sfml.cpp
    ├── games/
    │   ├── nibbler.cpp
    │   └── snake.cpp
    └── ncurses/
        └── ncurses.cpp
```

## Gestion des Erreurs

### Classe Error

**Fichier :** `include/Interface/Error.hpp`

Classe d'exception personnalisée héritant de `std::exception` :

```cpp
class Error : public std::exception {
private:
    std::string message;
public:
    Error(std::string const& error = "Error");
    virtual const char *what() const throw();
    virtual ~Error() throw() {};
};
```

**Utilisation :**
- Validation des arguments de ligne de commande
- Vérification de l'existence des bibliothèques
- Gestion des erreurs de chargement dynamique

## Ressources et Assets

### Images (PNG)
- `apple.png` : Sprite de la pomme/nourriture
- `player.png` : Sprite du joueur/serpent
- `wall.png` : Sprite des murs
- `background.png` : Arrière-plan
- `image_arcade.png` : Logo/image du menu

### Cartes de Jeu
- `snake.txt` : Niveau pour Snake
- `nibbler.txt` : Niveau pour Nibbler

**Format des cartes :**
- `#` : Mur
- `o` : Nourriture
- ` ` : Espace vide

### Police
- `font.ttf` : Police utilisée pour l'affichage du texte

## Conclusion

Ce projet Arcade démontre une architecture modulaire robuste utilisant :
- **Polymorphisme** via les interfaces abstraites
- **Chargement dynamique** pour la modularité
- **Séparation des responsabilités** entre rendu et logique
- **Extensibilité** pour ajouter de nouveaux jeux/bibliothèques

L'architecture permet d'ajouter facilement de nouvelles bibliothèques graphiques ou de nouveaux jeux en implémentant simplement les interfaces correspondantes.