[![NPM version](https://img.shields.io/badge/QT-5.8-green.svg)](http://doc.qt.io/qt-5/index.html)

# Sara_UI
Application de l'interface graphique du robot SARA.
Développé grace au framework Qt (5.8), en C++.

**Pour lancer l'interface graphique:**
```shell
rosrun sara_ui sara_ui
```
*Pour fermer la fenêtre en plein écran, il faut ce rendre dans l'onglet "**Power Mode**"*

**Pour lancer l'interface graphique en mode debuguage :**
```shell
rosrun sara_ui sara_ui --debug
```

# Node Principale 

**Il faut le lancer sur l'ordinateur qui éxécute Roscore, sans quoi ni le monitoring ni le lancement de scenarios ne fonctionneront**

Il faut lancer le node **sara_ui_helper** sur l'ordinateur qui execute le roscore. Il permet de reccuperer des informations de diagnostique sur celui-ci et de lancer les scenarios. :
```shell
rosrun sara_ui sara_ui_helper
```
- Pour réccuperé les diagnostics du robot le topic */diagnostics* est utilisé.
- Pour executer les scenarios, c'est le topic */sara_launch* qui est utilisé. */-Supposément--\\*

# Lanceur de scenarios
Afin de simplifier la compétition et le développement de Sara, il est possible de lancer des scénarios directement depuis cette interface utilisateur.
Les scénarios sont sauvegarder dans un fichier .scenario utilisant la structure YAML, dont voici un exemple:
```YAML
by: Lucas Maurice                       #nom de la dernière personne à avoir modifié le fichier
date: 2017-05-20                        #date de la dernière modification
Scenarios:
  - name: Teleop1                       #le nom du scenario qui sera affiché dans l'interface
    command: roslaunch teleop1.launch   #la commande linux à éxécuter pour lancer le scenario
    uses: 125                           #le nombde de fois que le scenario à été lancé
  - name: Follow Me
    command: roslaunch FollowMe.launch
    uses: 23
  - name: Hear Me
    command: roslaunch teleop3.launch
    uses: 10
```
