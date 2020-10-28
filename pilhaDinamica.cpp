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
    int tam;

public:
    Pilha(){
        Topo=NULL;
        tam=0;
    }
    void Empilha(T element)
    {
        No<T> *Aux = new No<T>(element, this->Topo);
        this->Topo = Aux;
        tam++;
    }
    void Empilha(No<T> Novo)
    {
        Novo->Lig=Topo;
        Topo = Novo;
        tam++;
    }
    bool Desempilha(T &Elemento)
    {
        if (Topo == NULL)
            return false;
        Elemento = Topo->Chave;
        No<T> *Aux = Topo;
        Topo = Topo->Lig;
        delete Aux;
        tam--;
        return true;
    }
    bool Desempilha()
    {
        if (Topo == NULL)
            return false;
        No<T> *Aux = Topo;
        Topo = Topo->Lig;
        delete Aux;
        tam--;
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
    void Ordena(){
        Pilha<T>* aux = new Pilha<T>;
        T auxT;
        T menor = this->TopoPilha().Chave;
        int tam = this->tam;
        for(int i=tam; i>0;i--)
        {
            menor=this->TopoPilha().Chave;
            for(int j=0;j<i;j++)
            {
                this->Desempilha(auxT);
                if(auxT<menor) menor=auxT;
                aux->Empilha(auxT);
            }
            for(int j=0;j<i;j++)
            {
                aux->Desempilha(auxT);
                if(auxT!=menor)
                    this->Empilha(auxT);
            }
            aux->Empilha(menor);
        }
        for(int i=0; i<tam;i++)
        {
            aux->Desempilha(auxT);
            this->Empilha(auxT);
        }
    }
    void Mostra()
    {
        No<T>* aux=this->Topo;
        while (aux!=NULL)
        {
            cout<<aux->Chave<<"->";
            aux=aux->Lig;
        }
        cout<<"NULL\n";
    }
};

int main()
{
    Pilha<char> P;
    P.Empilha('a');
    P.Empilha('z');
    P.Empilha('v');
    P.Empilha('b');
    P.Mostra();
    P.Ordena();
    P.Mostra();



    return 0;
}