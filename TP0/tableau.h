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

    bool           vide() const;
    // Retourne le nombre d'éléments dans le tableau
    int            taille() const;

    // Insère element à position index. Les éléments à partir de index sont décalés d'une position.
    void           inserer(const T& element, int index=0);

    // Enlève l'element à position index. Les éléments après index sont décalés d'une position.
    void           enlever(int index=0);
    void           enlever_dernier();

    // Cherche et retourne la position de l'élément. Si non trouvé, retourne -1.
    int            chercher(const T& element) const;
    int            contient(const T& element) const;

    const T&       operator[] (int index) const;
    T&             operator[] (int index);

    bool           operator == (const Tableau<T>& autre) const;
    Tableau<T>&    operator = (const Tableau<T>& autre);

    //Fonctionalités spécifiques au TP1
    int  compter(const T& element); // retourne le nb d'occurrences de element
    void creer_index() const; // cette fonction permet d'optimiser les fonctions chercher, contient et compter.
    void tri_fusion_algo(index_tableau* t[], int const debut, int const fin);
    void tri_fusion(index_tableau* t[],int const debut, int const milieu,int const fin);


  private:
    T*             elements;
    int            nbElements;
    int            capacite;
    //index interne à créer
    T*             index;

    struct index_tableau{
        int index;
        T element_tableau;
    };

};


// ---------- Définitions -------------


template <class T>
Tableau<T>::Tableau(int capacite_)
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
    index = new T[capacite];
}

template <class T>
Tableau<T>::~Tableau()
{
    delete[] elements;
    elements=nullptr;
    index=nullptr;
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
void Tableau<T>::enlever_dernier()
{
    nbElements--;

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

template<class T>
bool Tableau<T>::vide() const
{
    return nbElements==0;
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

template<class T>
bool Tableau<T>::contient(const T &element) const;
{
    for(int i=0; i<nbElmenents; i++){
        if(elements[i]==element){
            return true;
        }
    }
    return false;
}
template <class T>
void Tableau<T>::creer_index() const
{

    index_tableau indexer = new index_tableau[capacite];

    for(int i=0; i< nbElements; ++i){
        indexer[i].index=i;
        indexer[i].element_tableau=elements[i];
    }
    tri_fusion_algo(indexer,0, nbElements);

}

template <class T>
void Tableau<T>::tri_fusion_algo(index_tableau* t[], int debut, int fin){
    if(begin>=end){
        return;
    }

    int milieu=fin/2;
    tri_fusion_algo(index_tableau* t[], debut, milieu);
    tri_fusion_algo(index_tableau* t[],milieu +1, fin);
    tri_fusion(t[], debut, milieu, fin);

}

template <class T>
void Tableau<T>::tri_fusion(index_tableau* t[], int gauche,int milieu, int droite){
    int sous_tableau_un= milieu -gauche+1;
    int sous_tableau_deux= droite-milieu;

    index_tableau *tableau_gauche=new index_tableau[sous_tableau_un];
    index_tableau *tableau_droite=new index_tableau[sous_tableau_deux];

    for(int i=0; i<sous_tableau_un;++i){
        tableau_gauche[i].element_tableau= t[gauche+i].element_tableau;
        tableau_gauche[i].index=t[gauche+i].index;
    }
    for(int j=0; j<sous_tableau_droite;++j){
        tableau_droite[j].element_tableau= t[milieu+1+j].element_tableau;
        tableau_droite[j].index=t[milieu+1=j].index;
    }

    int index_sous_tableau_un=0,index_sous_tableau_deux=0,index_tableau_fusionne=0;

    while(index_sous_tableau_un<sous_tableau_un && index_sous_tableau_deux<sous_tableau_deux){
        if(tableau_gauche[index_sous_tableau_un].element_tableau<=tableau_droite[sous_tableau_deux].element_tableau){
            t[index_tableau_fusionne]=tableau_gauche[index_sous_tableau_un];
        }
    }
}
#endif //define _TABLEAU___H_
