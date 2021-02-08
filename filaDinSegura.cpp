// g++ pilhaDin.cpp -o pilhaDin.exe

#include <iostream>
using namespace std;

class EmptyLineError : public underflow_error {
    public:
        EmptyLineError() : underflow_error("Underflow Error: Fila Vazia.") {}
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

class Fila {
    private:
    Item *primeiro;
    int quantidade;

    public:
    Fila();
    ~Fila();
    void setPrimeiro(Item *);
    void setQuantidade(int);
    Item * getPrimeiro();
    int getQuantidade();
    bool vazia();
    void enfileirar(int);
    void desenfileirar();
    void printFila();
};

Item::Item(int x) {
    this->setChave(x);
    this->setProximo(NULL);
}

Fila::Fila() {
    this->setPrimeiro(NULL);
    this->setQuantidade(0);
}

Fila::~Fila() {
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

void Fila::setPrimeiro(Item *p) {
    this->primeiro = p;
}

void Fila::setQuantidade(int q) {
    this->quantidade = q;
}

Item *Fila::getPrimeiro() {
    return this->primeiro;
}

int Fila::getQuantidade() {
    return this->quantidade;
}

bool Fila::vazia() {
    return this->getQuantidade() == 0;
}

void Fila::enfileirar(int x) {
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

void Fila::desenfileirar() {
    Item *atu = this->getPrimeiro();
    
    if(this->vazia()) throw EmptyLineError();
    this->setPrimeiro(atu->getProximo());
    cout << "<" << atu->getChave() << ">" << endl;
    atu->setProximo(NULL);    
    this->setQuantidade(this->getQuantidade()-1);
}

void Fila::printFila(){
    if(this->vazia()) throw EmptyLineError();
    Item *atu = this->getPrimeiro();
    int n = this->getQuantidade();

    for(int i = 0; i < n; i++) {
        cout << atu->getChave() << " ";
        atu = atu->getProximo();
    }
    cout << endl;
}

int main() {
    char op;
    int num;
    Fila p1;

    while(cin >> op) {

        if(op == 'E') {
            cin >> num;
            p1.enfileirar(num);          
        }

        if(op == 'M') {
            try {
                p1.printFila();
            } catch (EmptyLineError e) {
                cout << e.what() << endl;

            }
        }

        if(op == 'D') {
            try{
                p1.desenfileirar(); 
            } catch (EmptyLineError e) {
                cout << e.what() << endl;
            } 
        }
    }

    return 0;
}