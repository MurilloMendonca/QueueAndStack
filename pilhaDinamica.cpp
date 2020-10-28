#include <iostream>

using namespace std;
template <typename T>
struct No
{
    T Chave;
    No* Lig;
    No(){
        Lig=NULL;
    }
    No(T valor)
    {
        Chave=valor;
        Lig=NULL;
    }
    No(T valor, No* prox)
    {
        Chave=valor;
        Lig=prox;
    }
};

template <typename T>
struct Pilha
{
private:
    No<T> *Topo;

public:
    Pilha(){
        Topo=NULL;
    }
    void Empilha(T element)
    {
        No<T> *Aux = new No<T>(element, this->Topo);
        this->Topo = Aux;
    }
    void Empilha(No<T> Novo)
    {
        Novo->Lig=Topo;
        Topo = Novo;
    }
    bool Desempilha(T &Elemento)
    {
        if (Topo == NULL)
            return false;
        Elemento = Topo->Chave;
        No<T> *Aux = Topo;
        Topo = Topo->Lig;
        delete Aux;
        return true;
    }
    bool Desempilha()
    {
        if (Topo == NULL)
            return false;
        No<T> *Aux = Topo;
        Topo = Topo->Lig;
        delete Aux;
        return true;
    }

    No<T> TopoPilha()
    {
        return *Topo;
    }
    bool PilhaVazia()
    {
        return ((Topo == NULL)?true:false);
    }
    void Inverte()
    {
        Pilha<T>* aux = new Pilha<T>;
        T NoAux;
        while(this->Desempilha(NoAux))
        {
            aux->Empilha(NoAux);
        }
        this->Topo=aux->Topo;
        delete aux;
    }
    void InverteComFila()
    {
        Fila<T>* aux = new Fila<T>;
        T NoAux;
        while(this->Desempilha(NoAux))
        {
            aux->Insere(NoAux);
        }
        while(aux->Remove(NoAux))
        {
            this->Empilha(NoAux);
        }
        delete aux;
    }

};

int main()
{
    Pilha<char> P;
    P.Empilha('a');
    cout<<P.TopoPilha().Chave;
    P.Empilha('b');
    cout<<P.TopoPilha().Chave;
    P.Inverte();
    cout<<P.TopoPilha().Chave;
    P.Desempilha();
    cout<<P.TopoPilha().Chave;


    return 0;
}