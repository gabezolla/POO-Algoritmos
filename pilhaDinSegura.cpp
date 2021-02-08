// g++ pilhaDin.cpp -o pilhaDin.exe

#include <iostream>
using namespace std;

class EmptyStackError : public underflow_error {
    public:
        EmptyStackError() : underflow_error("Underflow Error: Pilha Vazia.") {}
};

class Item {    
    private:
        int chave;
        Item *proximo;

    public:
        Item(int);
        void setChave(int);
        int getChave();
        void setProximo(Item *);
        Item * getProximo();
};

class Pilha {
    private:
    Item *primeiro;
    int quantidade;

    public:
    Pilha();
    ~Pilha();
    void setPrimeiro(Item *);
    void setQuantidade(int);
    Item * getPrimeiro();
    int getQuantidade();
    bool vazia();
    void empilhar(int);
    void desempilhar();
    void printPilha();
};

Item::Item(int x) {
    this->setChave(x);
    this->setProximo(NULL);
}

Pilha::Pilha() {
    this->setPrimeiro(NULL);
    this->setQuantidade(0);
}

Pilha::~Pilha() {
    Item *atu = this->getPrimeiro(),
    *ant = NULL;

    while (atu != NULL) {
        ant = atu;
        atu = atu->getProximo();
        delete ant;
    }
}

void Item::setChave(int x) {
    this->chave = x;
}

int Item::getChave() {
    return this->chave;
}

void Item::setProximo(Item *p) {
    this->proximo = p;
}

Item * Item::getProximo() {
    return this->proximo;
}

void Pilha::setPrimeiro(Item *p) {
    this->primeiro = p;
}

void Pilha::setQuantidade(int q) {
    this->quantidade = q;
}

Item * Pilha::getPrimeiro() {
    return this->primeiro;
}

int Pilha::getQuantidade() {
    return this->quantidade;
}

bool Pilha::vazia() {
    return this->getQuantidade() == 0;
}

void Pilha::empilhar(int x) {
    Item *num = new Item(x);
    
    if(this->vazia()) {
        this->setPrimeiro(num);
        this->setQuantidade(1);
    }

    else {
        Item *atu = this->getPrimeiro();
        Item *ant = NULL;

        while(atu != NULL) {        
            ant = atu;
            atu = atu->getProximo();           
        }

        ant->setProximo(num);
        this->setQuantidade(this->getQuantidade()+1);
    }
}

void Pilha::desempilhar() {
    Item *atu = this->getPrimeiro();
    Item *ant = NULL;

    if(this->vazia()) throw EmptyStackError();

    if(atu->getProximo() == NULL) {
        cout << atu->getChave() << endl;
        atu = NULL;
        this->setQuantidade(0);
        return;
    }

    while(atu->getProximo() != NULL) {        
        ant = atu;
        atu = atu->getProximo();           
    }

    cout << atu->getChave() << endl;
    ant->setProximo(NULL);
    this->setQuantidade(this->getQuantidade()-1);
}

void Pilha::printPilha(){

    if(this->vazia()) throw EmptyStackError();

    Item *atu = this->getPrimeiro();
    int n = this->getQuantidade();
    int *v = new int[n];

    for(int i = 0; i < n; i++) {
        v[i] = atu->getChave();
        atu = atu->getProximo();
    }

    for(int j = n-1; j>=0; j--) {
        cout << v[j] << " "; 
    }

    cout << endl;
}

int main() {
    char op;
    int num;
    Pilha p1;

    while(cin >> op) {

        if(op == 'E') {
            cin >> num;
            p1.empilhar(num);            
        }

        if(op == 'M') {
            try {
                p1.printPilha();
            } catch(EmptyStackError e) {
                cout << e.what() << endl;
            }
        }

        if(op == 'D') {
            try {
                p1.desempilhar();
            } catch(EmptyStackError e) {
                cout << e.what() << endl;
            }
        }
    }

    return 0;
}

