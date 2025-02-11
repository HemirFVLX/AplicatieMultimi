#include <iostream>

using namespace std;

struct list1
{
    int value;
    list1 *next;
};

list1 *createList()
{
    int n, x;
    cout << "Nr. elemente din lista: ";
    cin >> n;

    if (n <= 0) return NULL;

    list1 *f, *l, *c;
    f = new list1;
    cout << "Introduceti valoarea: ";
    cin >> f->value;
    f->next = NULL;
    //l=f;

    for (int i = 1; i < n; i++)
    {
        cout << "Introduceti valoarea: ";
        cin >> x;

        for(list1 *i=f; i; i=i->next) l=i;

        if(x < f->value){ // pune la inceputul listei daca elementul de adaugat este mai mic decat primul element
            c = new list1;
            c->value=x;
            c->next=f;
            f=c;
        }
        else if(x > l->value){ // pune la sfarsitul listei daca elementul de adaugat este mai mare decat ultimul
            c = new list1;
            c->value=x;
            c->next = NULL;
            l->next = c;
            l = c;
        }
        else{
            list1 *p, *r=NULL;
            for(p=f; p->value<x; p=p->next) r=p;
            c = new list1;
            c->value=x;
            c->next=p;
            r->next=c;
        }
    }
    return f;
}

void displayList(list1 *l)
{
    if(!l) cout<<"Lista vida"<<endl;
    else
    {
        for(list1 *c=l; c; c=c->next)
        {
            cout<<c->value<<" ";
        }
        cout<<endl;
    }
}

void insertInList(list1 *&l, int x, list1 *&u, bool &done) // functie pentru adaugare in lista
{
    if(!done) // la inceput
    {
        l->value=x;
        l->next=NULL;
        done=1; // marcheaza adaugarea primului element
        u=l;
    }
    else // dupa adaugarea primei valori
    {
        list1 *c=new list1;
        c->value=x;
        c->next=NULL;
        u->next=c;
        u=c;
    }
}

list1 *unite(list1 *l1, list1 *l2)
{
    list1 *result=new list1;
    list1 *u;
    bool done=0;
    list1 *f1=l1;
    list1 *f2=l2;
    while(f1 && f2){
        if(f1->value < f2->value){
            insertInList(result, f1->value, u, done);
            f1=f1->next;
        }
        else if(f1->value > f2->value){
            insertInList(result, f2->value, u, done);
            f2=f2->next;
        }
        else{ // cele doua elemente sunt egale
            insertInList(result, f1->value, u, done);
            f1=f1->next;
            f2=f2->next;
        }
    }
    while(f1){
        insertInList(result, f1->value, u, done);
        f1=f1->next;
    }
    while(f2){
        insertInList(result, f2->value, u, done);
        f2=f2->next;
    }
    return result;
}

list1 *intersect(list1 *l1, list1 *l2)
{
    list1 *result=new list1;
    list1 *u;
    bool done=0;
    for(list1 *f1=l1; f1; f1=f1->next)
        for(list1 *f2=l2; f2; f2=f2->next)
            if(f1->value == f2->value)
                insertInList(result, f1->value, u, done);
    if(!done) result=NULL;
    return result;
}

list1 *difference(list1 *l1, list1 *l2)
{
    list1 *result=new list1;
    list1 *u;
    bool done=0;
    for(list1 *f1=l1; f1; f1=f1->next)
    {
        bool ok=0;
        for(list1 *f2=l2; f2; f2=f2->next)
            if(f1->value == f2->value) ok=1;
        if(!ok)
            insertInList(result, f1->value, u, done);

    }
    if(!done) result=NULL;
    return result;
}

list1 *symmetricDifference(list1 *l1, list1 *l2){
    list1 *result=new list1;
    list1 *u;
    bool done=0;
    list1 *f1=l1;
    list1 *f2=l2;
    while(f1 && f2){
        if(f1->value < f2->value){
            insertInList(result, f1->value, u, done);
            f1=f1->next;
        }
        else if(f1->value > f2->value){
            insertInList(result, f2->value, u, done);
            f2=f2->next;
        }
        else{ // cele doua elemente sunt egale si nu vor intra in componenta listei rezultate
            f1=f1->next;
            f2=f2->next;
        }
    }
    while(f1){
        insertInList(result, f1->value, u, done);
        f1=f1->next;
    }
    while(f2){
        insertInList(result, f2->value, u, done);
        f2=f2->next;
    }
    return result;
}

int main()
{
    list1 *l1 = createList();
    list1 *l2 = createList();
    list1 *l3 = intersect(l1,l2);
    list1 *l4 = unite(l1,l2);
    list1 *l5 = difference(l1,l2);
    list1 *l6 = difference(l2,l1);
    list1 *l7 = symmetricDifference(l1,l2);
    cout<<"Lista 1: ";
    displayList(l1);
    cout<<"Lista 2: ";
    displayList(l2);
    cout<<"Intersectia celor 2 liste: ";
    displayList(l3);
    cout<<"Reuniunea celor 2 liste: ";
    displayList(l4);
    cout<<"Diferenta dinte lista 1 si lista 2: ";
    displayList(l5);
    cout<<"Diferenta dinte lista 2 si lista 1: ";
    displayList(l6);
    cout<<"Diferenta simetrica (reuniunea disjuncta) dintre cele 2 liste: ";
    displayList(l7);
    cout<<endl;
    return 0;
}
