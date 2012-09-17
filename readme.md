# Machine virtuelle Hack
=====

## A propos
=====

Ce projet est une implémentation possible de compilateur *back-end* pour la machine virtuelle [Hack](http://www1.idc.ac.il/tecs/).
Il traduit le *bytecode* Jack en instruction assembleur pour le système virtuel *hack*.
Le but est de proposer une solution possible au projet du chapître 7 du livre "The elements of Computing Elements" :)

## Pré-requis
=====

le *back-end* à été écrit en C++ et utilise la bibliothèque [Boost 1.50.0](http://www.boost.org/) (notamment Boost::filesystem).
Le projet est regroupé au sein d'une solution [Visual Studio 2010](http://www.microsoft.com/visualstudio/eng/downloads#d-2010-express).

## Utilisation
=====

Les fichiers sources se trouvent à la racine. La solution *VS* se trouve dans le dossier **VMTranslator**.
Les batteries de *test* se trouvent dans le dossier éponyme (vous trouverez un fichier HTML en anglais qui vous guidera).
A noter que le chemin vers les tests devrait se trouver dans les propriétés du projet
(Une fois la solution ouverte, faites un clic droit sur le projet *VMTranslator* puis `Propriétés` > `Propriétés de configuration` > `Débogage`).
Vous pouvez y mettre par exemple dans `Répertoire de travail` ceci `$(ProjectDir)..\test\` et dans `Arguments de la commande` cela `FunctionCalls\SimpleFunction\SimpleFunction.vm`
Par ailleurs, n'oubliez pas de préciser le chemin vers la librairie boost (Include et Librairies) dans les `Propriétés de configuration` (`Répertoires VC++`).