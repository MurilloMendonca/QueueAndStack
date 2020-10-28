#include <iostream>
#define TAM 100
using namespace std;
template <typename T>
struct No
{
    T Chave;
    No(T valor)
    {
        Chave=valor;
    }
    No(){

    }
};

template <typename T>
struct Pilha
{
private:
    No<T> Dados[TAM];
    int Tamanho;

public:
    Pilha(){
        Tamanho=0;;
    }
    bool Empilha(No<T> Novo)
    {
        if (Tamanho == TAM - 1)
            return false;
        for(int i=Tamanho-1;i>=0;i--)
        {
            Dados[i+1] = Dados[i];
        }
        Dados[0] = Novo;
        Tamanho++;
        
        return true;
    }
    bool Empilha(T Novo)
    {
        No<T> NovoNo=No<T>(Novo);
        if (Tamanho == TAM - 1)
            return false;
        for(int i=Tamanho-1;i>=0;i--)
        {
            Dados[i+1] = Dados[i];
        }
        Dados[0] = NovoNo;
        Tamanho++;
        
        return true;
    }
    bool Desempilha(No<T> &Novo)
    {
        if (Tamanho == 0)
            return false;
        Novo = Dados[0];
        for(int i=0;i<Tamanho;i++)
        {
            Dados[i]=Dados[i+1] ;
        }
        Tamanho--;
        return true;
    }
    bool Desempilha()
    {
        if (Tamanho == 0)
            return false;
        for(int i=0;i<Tamanho;i++)
        {
            Dados[i]=Dados[i+1];
        }
        Tamanho--;
        return true;
    }

    No<T> TopoPilha()
    {
        return Dados[0];
    }
    bool PilhaVazia()
    {
        return ((Tamanho == 0) ? true : false);
    }
    bool PilhaCheia()
    {
        return ((Tamanho == TAM-1) ? true : false);
    }
};

int main()
{
    Pilha<char> P;
    P.Empilha('a');
    cout<<P.TopoPilha().Chave;
    P.Empilha('b');
    cout<<P.TopoPilha().Chave;
    P.Desempilha();
    cout<<P.TopoPilha().Chave;
    return 0;
}