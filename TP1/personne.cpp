/*    UQAM / Département d'informatique                          *
 *    INF3105 - Structures de données et algorithmes             *
 *    Été 2022 / TP2                                             *
 *    AUTEUR(S): Ama SEYE SEYA06019603          */

#include <algorithm>
#include "personne.h"

#define nbLieuxMinimum 2
#define nbTempsMinimum 120
#define seuilProximite 25
#define tempsMinuit 1440

std::string Personne::getNom() const{
    return nom;
}

std::string Personne::getTypeRelation(const Personne& autre) const{
    int duree_rencontre=0, nombre_de_lieux=0;
    int t1=0;
    if(t1<p.heure[1]){
        t1=p.heure[1];
        if(t1<autre.heure[1]){
            t1=autre.heure[1]
        }
    }else if(t1<autre.heure[1]){
        t1=autre.heure[1];
        if(t1<p.heure[1]){
            t1=p.heure;
        }
    }
    while
    return "?";
}

std::istream& operator >>(std::istream& is, Personne& p){
    // À compléter : ce code ne fait que lire le fichier.
    // Vous devez le compléter pour assigner les valeurs lues dans les attributs de la personne p.
    std::string nom_lue;
    Coordonnees coor;
    int heure;
    is >> nom_lue;
    p.nom=nom_lue;
    if(nom.empty() || is.eof()) return is;
    while(true){
        char c;
        is >> c;
        if(c=='-'){
            assert(is.get()=='-');
            break;
        }else{
            is.unget();
        }
        is >> coor >> heure >> c;
        assert(c==';');
    }
    return is;
}
