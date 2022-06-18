/*    UQAM / Département d'informatique                          *
 *    INF3105 - Structures de données et algorithmes             *
 *    Été 2022 / TP2                                             *
 *    AUTEUR(S): Ama SEYE + SEYA0601960 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "tableau.h"
#include "personne.h"

using namespace std;

int tp2(istream& in){
    Tableau<Personne> personnes;

    while(in){
        Personne nouvellePersonne;
        in >> nouvellePersonne;
        if(in.eof()) break;
        personnes.ajouter(nouvellePersonne);
    }

    //  À Compléter : 2 boucles imbriquées pour déterminer et afficher le type de relation entre chaque personne.
    for(int i = 0; i < personnes.taille(); i++)
        for(int j = i + 1; j < personnes.taille(); j++){
            string typeRelation = personnes[i].getTypeRelation(personnes[j]);
            if(typeRelation != "")
                cout << personnes[i].getNom() << " et " << personnes[j].getNom() <<" sont des "<< typeRelation <<"."<< endl;
    }
    return 0; // fin normale
}

int main(int argc, const char** argv)
{
    if(argc<2)
        return tp2(cin);
    else{
        ifstream fichierPresences(argv[1]);
        return tp2(fichierPresences);
    }
}
