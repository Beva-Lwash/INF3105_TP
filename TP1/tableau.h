/* UQAM / Département d'informatique
   INF3105 - Structures de données et algorithmes
   Squelette pour classe générique Tableau<T> pour le TP1 et Lab3.
   AUTEUR(S): ÉCRIVEZ ICI VOTRE NOM + CODE PERMANENT
*/

// Ces deux lignes permettent d'éviter d'inclure 2 fois ce .h à la compilation.
#if !defined(__TABLEAU_H__)
#define __TABLEAU_H__

template <class T>
class Tableau
{
  public:
    Tableau(int capacite_initiale=8);
    Tableau(const Tableau&);
    ~Tableau();

    // Ajouter un element à la fin
    void           ajouter(const T& element);
    // Vider le tableau
    void           vider();
    bool           vide() const;
    // Retourne le nombre d'éléments dans le tableau
    int            taille() const;

    // Insère element à position index. Les éléments à partir de index sont décalés d'une position au préalable.
    void           inserer(const T& element, int index=0);
    // Enlève l'element à position index. Les éléments après index sont décalés d'une position après.
    void           enlever(int index=0);
    void           enlever_dernier();
    // Cherche et retourne la position de l'élément. Si non trouvé, retourne -1.
    // Voir la méthode "trouver" dans les notes de cours. Il suffit de l'adapter pour retourner la position au lieu d'un booléen
    int            trouver(const T& element);
    bool           contient(const T& element) const;

    T&             operator[] (int index);
    const T&       operator[] (int index) const;


    Tableau<T>&    operator = (const Tableau<T>& autre);

    bool           operator == (const Tableau<T>& autre) const;

  private:
    T*             elements;
    int            capacite;
    int            nbElements;
};

/*
 Puisque Tableau<T> est une classe générique, toutes ses définitions doivent être
 inclues après les déclarations. On peut quand même séparer les déclarations et
 les définitions en deux fichiers (tableau.h et tableau.hcc), à condition d'inclure le
 deuxième (tableau.hcc) à la fin du premier (tableau.h). Ainsi, un fichier source
 (.cc, .cpp, c++) qui inclut tableau.h inclura indirectement aussi tableau.hcc.

*/

//#include "tableau.hcc"
/**** Début des définitions pouvant être mises dans tableau.hcc. ****/
#include <assert.h>

template <class T>
Tableau<T>::Tableau(int capacite_initiale)
{
  capacite=capacite_;
  nbElements=0;
  elements= new T[capacite];
  index= new T[capacite];

}

template <class T>
Tableau<T>::Tableau(const Tableau& autre)
{
    capacite=autre.capacite;
    nbElements=autre.nbElements;
    elements= new T[capacite];
    for(int i=0;i<nbElements;i++){
        elements[i]=autre.elements[i];
    }
}

template <class T>
Tableau<T>::~Tableau()
{
    delete[] elements;
    elements=nullptr;
}

template <class T>
int Tableau<T>::taille() const
{
    return nbElements;
}

template <class T>
void Tableau<T>::ajouter(const T& item)
{
    assert(nbElements <= capacite);
    if(nbElements == capacite){
        capacite=capacite*2;
        T* temp= new T[capacite];
        for(int i=0;i<nbElements;i++){
            temp[i]=elements[i];
        }
        delete[] elements;
        elements=temp;
    }
    elements[nbElements++]=item;
}

template <class T>
void Tableau<T>::inserer(const T& element, int index)
{
    if(index>=0&&index<nbElements){
        if(nbElements == capacite){
            capacite=capacite*2;
            T* temp= new T[capacite];
            for(int i=0;i<nbElements;i++){
                temp[i]=elements[i];
            }
            delete[] elements;
            elements=temp;
        }
        for(int i=nbElements; i>index;--i){
            elements[i]=elements[i-1];
        }
        elements[index]=element;
        nbElements++;
    }
}

template <class T>
void Tableau<T>::enlever(int index)
{
    if(index>=0&&index<nbElements){
        nbElements--;
        for(int i= index; i<nbElements; ++i){
            elements[i]=elements[i+1];
        }
    }
}

template <class T>
int Tableau<T>::trouver(const T& element)
{
    for(int i=0; i<nbElements;i++){
        if(elements[i]==element){
            return i;
        }
    }
    return -1;
}

template <class T>
void Tableau<T>::vider()
{
    nbElements=0;
}

template <class T>
T& Tableau<T>::operator[] (int index)
{
    asssert(index<nbElements);
    return elements[index];
}

template <class T>
const T& Tableau<T>::operator[] (int index) const
{
    assert(index<nbElements);
    return elements[index];
}

template <class T>
Tableau<T>& Tableau<T>::operator = (const Tableau<T>& autre)
{
    if(this==&autre) return *this;
    nbElements=autre.nbElements;
    if(capacite<autre.nbElements){
        delete[] elements;
        capacite = autre.capacite;
        elements = new T[capacite];
    }
    for(int i=0; i<nbElements;i++){
        elements[i]=autre.elements[i];
    }
    return *this;

}

template <class T>
bool Tableau<T>::operator == (const Tableau<T>& autre) const
{
    if(this==&autre) return true;
    if(nbElements!=autre.nbElements) return false;
    for(int i=0;i<nbElements;i++){
        if(elements[i] != autre.elements[i]){
            return false;
        }
    }
    return true;
}

template <class T>
bool Tableau<T>::contient(const T& element)const
{
    return trouver(element)!=-1;
}

template<class T>
void Tableau<T>::enlever_dernier(){
    if(!vide()){
        nbElements--;
    }
}

template<class T>
bool Tableau<T>::vide() const{
    return nbElements==0;
}


#endif
