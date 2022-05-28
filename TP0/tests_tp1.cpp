/*  TP1 -- Tableau dynamique générique
 *  INF3105 | Structures de données et algorithmes
 *  UQAM | Département d'informatique
 *  http://ericbeaudry.uqam.ca/INF3105/tp1/
 *
 *  Le programme tests_tp1.cpp contient quelques tests de base pour Tableau<T>.
 *  Il comporte quelques fonctions nommées testX où X est un nombre séquentiel.
 *  La fonction main() à la toute fin appelle ces fonctions une à une.
 */

#include "tableau.h"
#include <iostream>

// La fonction test1 vérifie la fonction chercher.
bool test1(){
    int nombres[20] = {7, 2, 7, 9, 6, 3, 4, 7,  2, 47, 6, 0, 1, 5, 8, 83, 4, 105, 35, 53};
    Tableau<int> t1;
    for(int i=0;i<20;i++)
        t1.ajouter(nombres[i]);
    Tableau<int> t2 = t1;
    t2.ajouter(10000);

    for(int i=0;i<20;i++){
        if(t1.chercher(nombres[i]) < 0){
            std::cout << "Erreur test1() A !\n";
            return false;
        }
        if(t2.chercher(nombres[i]) < 0){
            std::cout << "Erreur test1() B !\n";
            return false;
        }
    }

    if(t1.chercher(10000) >= 0){
        std::cout << "Erreur test1() C !\n";
        return false;
    }
    if(t2.chercher(10000) < 0){
        std::cout << "Erreur test1() D !\n";
        return false;
    }

    if(t2.compter(0) != 1){
        std::cout << "Erreur test1() E !\n";
        return false;
    }
    if(t2.compter(7) != 3){
        std::cout << "Erreur test1() F !\n";
        return false;
    }
    if(t2.compter(10000) != 1){
        std::cout << "Erreur test1() G !\n";
        return false;
    }
    if(t2.compter(99999) != 0){
        std::cout << "Erreur test1() H !\n";
        return false;
    }
    t1.enlever(0);
    if(t1.compter(7) != 2){
        std::cout << "Erreur test1() I !\n";
        return false;
    }
    if(t2.compter(7) != 3){
        std::cout << "Erreur test1() J !\n";
        return false;
    }
    return true;
}

// La fonction test1 vérifie la fonction compter.
bool test2(){
    Tableau<int> t;
    int N=20, M=1000;
    for(int i=0;i<M;i++)
       for(int j=0;j<N;j++){
          t.ajouter(j);
       }

    for(int j=0;j<N;j++)
       if(t.compter(j) != M){
           std::cout << "Erreur test2() A !\n";
           return false;
       }

    return true;
}

// Les fonctions test3 à test5 utilisent la class A pour compter le nombre
// de comparaisons effectuées.
// Dans le présent contexte, la classe A contient uniquement un entier.
// Elle permet de passer de Tableau<int> à Tableau<A>.

int compteurAcomparaisons = 0;
class A{
  private:
    int x;
  public:
    A(int x_=0) : x(x_) {}
    bool operator < (const A& o) const{
       compteurAcomparaisons++;
       return x < o.x;
    }
    bool operator <= (const A& o) const{
       compteurAcomparaisons++;
       return x <= o.x;
    }
    bool operator == (const A& o) const{
       compteurAcomparaisons++;
       return x == o.x;
    }
    bool operator >= (const A& o) const{
       compteurAcomparaisons++;
       return x >= o.x;
    }
    bool operator > (const A& o) const{
       compteurAcomparaisons++;
       return x > o.x;
    }
};

// La fonction test3 n'appelle pas la fonction creer_index. Ainsi, les appels
// à Tableau::chercher ne sont pas efficaces. Pour chercher un élément, on
// doit parcourir séquentiellement les éléments.
// Le but de la fonction test3() est d'apprécier une amélioration le gain
// de la création d'un indexe à la fonction test4().
bool test3(){
    Tableau<A> t;
    for(int i=0;i<1000;i++)
       t.ajouter(2*i);
    for(int i=0;i<1000;i++)
       t.ajouter(2*i+1);

    compteurAcomparaisons=0;

    for(int i=0;i<2000;i++){
       // position trouvée
       int pt = t.chercher(i);
       // bonne position où le nombre i devrait être
       int bp = i/2 + (i%2==0 ? 0 : 1000);
       if(pt!=bp){
           std::cout << "Erreur test3() A : pt=" << pt << " bp=" << bp << "!\n";
           return false;
       }
    }
    std::cout << "Score test3: " << compteurAcomparaisons << "\n";
    return true;
}

// L'unique différence à la fonction test4 est l'appelle à t.creer_index().
// La fonction Tableau::creer_index crée un index interne dans Tableau pour
// accélérer les cherches. Avec un index, chaque recherche peut se faire en
// O(log n).
bool test4(){
    Tableau<A> t;
    for(int i=0;i<1000;i++)
       t.ajouter(2*i);
    for(int i=0;i<1000;i++)
       t.ajouter(2*i+1);

    compteurAcomparaisons=0;
    t.creer_index();
    std::cout << "Score test4/creer index: " << compteurAcomparaisons << "\n";
    compteurAcomparaisons=0;

    for(int i=0;i<2000;i++){
       // position trouvée
       int pt = t.chercher(i);
       // bonne position où le nombre i devrait être
       int bp = i/2 + (i%2==0 ? 0 : 1000);
       if(pt!=bp){
           std::cout << "Erreur test4() A : pt=" << pt << " bp=" << bp << "!\n";
           return false;
       }
    }
    // On devrait apprécier une baisse significative par rapport à test3.
    std::cout << "Score test4: " << compteurAcomparaisons << "\n";
    return true;
}

// La fonction test5 évalue l'efficacité de la fonction Tableau::compter lorsqu'un
// index a préalablement été créée.
bool test5(){
    Tableau<A> t;
    int N=20, M=1000;
    for(int i=0;i<M;i++)
       for(int j=0;j<N;j++){
          t.ajouter(j);
       }
    t.creer_index();
    compteurAcomparaisons=0;
    for(int j=0;j<N;j++)
       if(t.compter(j) != M){
           std::cout << "Erreur test5() A !\n";
           return false;
       }
    std::cout << "Score test5: " << compteurAcomparaisons << "\n";
    return true;
}

// Le test6 vérifie si la classe Tableau est rebuste face à quelques situations.
// Par exemple, si on crée l'index et qu'on modifie ensuite le tableau, l'index
// doit soit être invalidé ou ajusté.
bool test6(){
   Tableau<int> t;
   for(int i;i<25;i++){
      t.ajouter(i);
      t.ajouter(-i);
      t.ajouter(1000+i);
   }
   t.creer_index();
   t.ajouter(50);
   int p50 = t.chercher(50);
   if(p50 != t.taille()-1){
       std::cout << "Erreur test6() A : l'index devrait être maintenant invalide !\n";
       return false;
   }
   t[0] = 99;
   int p99 = t.chercher(99);
   if(p99 != 0){
       std::cout << "Erreur test6() B : l'index devrait être maintenant invalide !\n";
       return false;
   }
   t.creer_index();
   p50 = t.chercher(50);
   if(p50 != t.taille()-1){
       std::cout << "Erreur test6() A : l'index devrait être maintenant invalide !\n";
       return false;
   }
   p99 = t.chercher(99);
   if(p99 != 0){
       std::cout << "Erreur test6() B : l'index devrait être maintenant invalide !\n";
       return false;
   }
   return true;
}

int main(){
    bool tests_reussis =
        true // Cette ligne «true» a été insérée pour facilier la mise en commentaire de la ligne suivante.
        && test1()
        && test2()
        && test3()
        && test4()
        && test5()
        && test6()
        ;

    std::cout << std::endl << std::endl
         << "**** Sommaire ****" << std::endl;

    if(tests_reussis){
        std::cout << "=> BRAVO, tous les tests TP1 fournis ont été réussis !" << std::endl
                  << "=> Attention, ces tests ne sont pas exhaustifs !" << std::endl;
    }else{
        std::cout << "=> ATTENTION, au moins un test a échoué !" << std::endl;
    }
    return tests_reussis ? 0 : 1;
}
