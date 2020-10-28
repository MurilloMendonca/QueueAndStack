#include <iostream>
#include <random>
#include<unistd.h>
using namespace std;
template <typename T>
struct No
{
    T Chave;
    No *Lig;
    No()
    {
        Lig = NULL;
    }
    No(T valor)
    {
        Chave = valor;
        Lig = NULL;
    }
    No(T valor, No *prox)
    {
        Chave = valor;
        Lig = prox;
    }
};
template <typename T>
struct Fila
{
private:
    No<T> *Com;
    int Nro;
    No<T> *Fim;

public:
    Fila(){
        Com=NULL;
        Fim=NULL;
        Nro=0;
    }
    int getTam()
    {
        return Nro;
    }
    void Insere(T Novo)
    {
        No<T> *P = new No<T>(Novo);
        if (this->Nro == 0)
            this->Com = this->Fim = P;
        else
        {
            this->Fim->Lig = P;
            this->Fim = P;
        }
        this->Nro++;
    }
    bool Retira(T &Valor)
    {
        if (this->Nro == 0)
            return false;
        else
        {
            No<T>* P = this->Com;
            Valor = P->Chave;
            this->Com = P->Lig;
            this->Nro--;
            if (this->Nro == 0)
                this->Fim = NULL;
            delete P;
            return true;
        }
    }
    bool Retira()
    {
        if (this->Nro == 0)
            return false;
        else
        {
            No<T>* P = this->Com;
            this->Com = P->Lig;
            this->Nro--;
            if (this->Nro == 0)
                this->Fim = NULL;
            delete P;
            return true;
        }
    }
    No<T> FrenteFila()
    {
        return *Com;
    }
    T MenorElemento()
    {
        No<T>* atual = this->Com;
        T menor=atual->Chave;
        while (atual!=NULL)
        {
            if(atual->Chave<menor) menor = atual->Chave;
            atual=atual->Lig;
        }
        return menor;
    }
    void RetiraElemento(T elemento)
    {
        Fila<T>* aux = new Fila<T>;
        T elemAux;
        while (this->Retira(elemAux))
        {
            if(elemAux!=elemento)
                aux->Insere(elemAux);
        }
        this->Com=aux->Com;
        this->Nro = aux->Nro;
        delete aux;
        
    }
    void Ordena()
    {
        Fila<T>* aux = new Fila<T>;
        int n = this->Nro;
        int menor;
        for(int i=0;i<n;i++)
        {
            menor=this->MenorElemento();
            aux->Insere(menor);
            this->RetiraElemento(menor);
        }
        this->Com = aux->Com;
        this->Nro = aux->Nro;
        delete aux;
    }
    void Mostra()
    {
        No<T>* aux=this->Com;
        while (aux!=NULL)
        {
            cout<<aux->Chave<<"->";
            aux=aux->Lig;
        }
        cout<<"NULL\n";
    }
};
/*Fila<char> P;
    P.Insere('b');
    P.Insere('a');
    P.Insere('d');
    P.Insere('f');
    P.Insere('e');
    P.Mostra();
    P.Ordena();
    P.Mostra();
    P.Retira();
    P.Mostra();*/
int main(){
    //Precisa de biblioteca random
    random_device rd;                                       //Distribuicao uniforme de probabilidade
    mt19937 gen (rd());                                     //para gerar os tempos aleatorios
    uniform_int_distribution<int> tempoDeAtendimento(1, 4); //de atendimento
    uniform_int_distribution<int> tempoDeChegada(1, 3);     //e de chegada do proximo cliente
    
    int chegada = tempoDeChegada(gen);
    Fila<int> fila;
    int cliente =1;
    int atendendo=0;
    int atendTempo=0;
    int filaMax =0;
    for(int minuto=0;minuto<720;minuto++)
    {
        system("clear");
        printf("Minuto: %i", minuto);
        printf("\nTempo de atendimento restante: %i", atendTempo);
        printf("\nProxima chegada: %i", chegada);
        if(atendendo!=0)atendTempo--;                       //Se esta atendendo->subtrai o tempo de atendimento
        if(atendTempo<0)                                    //Se acabou o tempo para aquele atendimento
        {
            atendendo=0;                                    //Libera o caixa
            if(fila.getTam()==0)                            //Se não tiver ninguem na fila
                printf("\nAguardando proximo cliente...");
            else                                            //Se tiver alguem na fila
            {
                atendendo=fila.FrenteFila().Chave;          //Atualiza qual cliente esta sendo atendido
                fila.Retira();                              //Tira da fila
                atendTempo=tempoDeAtendimento(gen);         //Gera tempo de atendimento aleatorio para este cliente

            }
        }
        printf("\nAtendendo cliente %i", atendendo);

        if(minuto==chegada){                    //Se alguem chegou
            if(atendendo==0)                    //Se esta livre
            {
                atendendo=cliente;              //Atualiza qual cliente esta sendo atendido
                atendTempo=tempoDeAtendimento(gen);           //Gera tempo de atendimento aleatorio para este cliente
                chegada=tempoDeChegada(gen)+minuto;//Gera tempo de chegada do proximo
                cliente++;                      //Atualiza numero do cliente
            }
            else                                //Se não esta livre
            {
                fila.Insere(cliente);           //Entra na fila
                cliente++;                      //atualiza o numero do cliente
                chegada=tempoDeChegada(gen)+minuto;//Gera tempo de chegada do proximo
            }
        }
        printf("\nFila: ");
        fila.Mostra();

        //Precisa da biblioteca do SO, windows.h ou unistd.h
        //sleep(2);             //sleep para poder acompalhar a entrada e saida de cada cliente

        if(fila.getTam()>filaMax) filaMax=fila.getTam();//Atualiza maior fila
    }
    printf("Tamanho maximo de fila: %i", filaMax);                  
    return 0;
}
