/*    UQAM / Département d'informatique                          *
 *    INF3105 - Structures de données et algorithmes             *
 *    Été 2022 / TP2                                             *
 *    AUTEUR(S): ÉCRIVEZ ICI VOTRE NOM + CODE PERMANENT          */

#include <algorithm>
#include "personne.h"

#define nbLieuxMinimum 2
#define nbTempsMinimum 120
#define seuilProximite 25


std::string Personne::getNom() const{
    return "";
}

std::string Personne::getTypeRelation(const Personne& autre) const{
    //À Compléter
    return "?";
}

std::istream& operator >>(std::istream& is, Personne& p){
    // À compléter : ce code ne fait que lire le fichier.
    // Vous devez le compléter pour assigner les valeurs lues dans les attributs de la personne p.
    std::string nom;
    Coordonnees coor;
    int heure;
    is >> nom;
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

