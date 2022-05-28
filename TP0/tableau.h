/* Squelette pour classe générique Tableau<T>.
 * Lab3 -- Tableau dynamique générique
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * http://ericbeaudry.uqam.ca/INF3105/lab3/
 */

#if !defined(_TABLEAU___H_)
#define _TABLEAU___H_

#include <assert.h>

template <class T>
class Tableau{

  public:
    Tableau(int capacite_initiale=4);
    Tableau(const Tableau&);
    ~Tableau();

    // Ajouter un element à la fin
    void           ajouter(const T& element);
    // Vider le tableau
    void           vider();
    // Retourne le nombre d'éléments dans le tableau
    int            taille() const;

    // Insère element à position index. Les éléments à partir de index sont décalés d'une position.
    void           inserer(const T& element, int index=0);

    // Enlève l'element à position index. Les éléments après index sont décalés d'une position.
    void           enlever(int index=0);

    // Cherche et retourne la position de l'élément. Si non trouvé, retourne -1.
    int            chercher(const T& element) const;

    const T&       operator[] (int index) const;
    T&             operator[] (int index);

    bool           operator == (const Tableau<T>& autre) const;
    Tableau<T>&    operator = (const Tableau<T>& autre);

    //Fonctionalités spécifiques au TP1
    int  compter(const T& element); // retourne le nb d'occurrences de element
    void creer_index() const; // cette fonction permet d'optimiser les fonctions chercher, contient et compter.

  private:
    T*             elements;
    int            nbElements;
    int            capacite;
    //index interne à créer
    T*             index;
};


// ---------- Définitions -------------


template <class T>
Tableau<T>::Tableau(int capacite_)
{
    capacite=capacite_;
    nbElements=0;
    elements= new T[capacite];
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

template <class T>
void Tableau<T>::enlever(int index)
{
    nbElements--;
    for(int i= index; i<nbElements; ++i){
        elements[i]=elements[i+1];
    }
}

template <class T>
int Tableau<T>::chercher(const T& element) const
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
const T& Tableau<T>::operator[] (int index) const
{
    assert(index<nbElements);
    return elements[index];
}

template <class T>
T& Tableau<T>::operator[] (int index)
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
int Tableau<T>::compter(const T& element)
{
    int compteur=0;
    for(int i =0; i< nbElements; ++i){
        if(elements[i]==element){
            compteur++;
        }
    }

    return compteur;

}
/*
template <class T>
void Tableau<T>::creer_index() const
{
    index=new T[capacite];



}
*/
#endif //define _TABLEAU___H_
