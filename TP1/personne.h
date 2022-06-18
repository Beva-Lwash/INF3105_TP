/*    UQAM / Département d'informatique                          *
 *    INF3105 - Structures de données et algorithmes             *
 *    Été 2022 / TP2                                             *
 *    AUTEUR(S): Ama SEYE + SEYA06019603          */

#if !defined(__PERSONNE_H__)
#define __PERSONNE_H__

#include <iostream>
#include <string>
#include "coordonnees.h"
#include "tableau.h"

class Personne{
  public:
    //Vous pouvez ajouter autant de fonctions publiques que vous le désirez.
    Personne();
    std::string getNom() const;
    std::string getTypeRelation(const Personne& autre) const;



  private:
    std::string nom;
    std::string TypeRelation;
    friend std::istream& operator >>(std::istream&, Personne&);
};

Personne::Personne(){
    nom="";
    TypeRelation="";
}

#endif
