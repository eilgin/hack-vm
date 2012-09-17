# Machine virtuelle Hack
=====

## A propos
=====

Ce projet est une impl�mentation possible de compilateur *back-end* pour la machine virtuelle [Hack](http://www1.idc.ac.il/tecs/).
Il traduit le *bytecode* Jack en instruction assembleur pour le syst�me virtuel *hack*.
Le but est de proposer une solution possible au projet du chap�tre 7 du livre "The elements of Computing Elements" :)

## Pr�-requis
=====

le *back-end* � �t� �crit en C++ et utilise la biblioth�que [Boost 1.50.0](http://www.boost.org/) (notamment Boost::filesystem).
Le projet est regroup� au sein d'une solution [Visual Studio 2010](http://www.microsoft.com/visualstudio/eng/downloads#d-2010-express).

## Utilisation
=====

Les fichiers sources se trouvent � la racine. La solution *VS* se trouve dans le dossier **VMTranslator**.
Les batteries de *test* se trouvent dans le dossier �ponyme (vous trouverez un fichier HTML en anglais qui vous guidera).
A noter que le chemin vers les tests devrait se trouver dans les propri�t�s du projet
(Une fois la solution ouverte, faites un clic droit sur le projet *VMTranslator* puis `Propri�t�s` > `Propri�t�s de configuration` > `D�bogage`).
Vous pouvez y mettre par exemple dans `R�pertoire de travail` ceci `$(ProjectDir)..\test\` et dans `Arguments de la commande` cela `FunctionCalls\SimpleFunction\SimpleFunction.vm`
Par ailleurs, n'oubliez pas de pr�ciser le chemin vers la librairie boost (Include et Librairies) dans les `Propri�t�s de configuration` (`R�pertoires VC++`).