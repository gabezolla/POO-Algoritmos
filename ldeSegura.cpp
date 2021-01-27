// g++ lista.cpp -o lista.exe

#include <iostream>
using namespace std;

class ExistKeyError : public logic_error {
    public:
        ExistKeyError() : logic_error("Logic Error: Chave ja existe na Lista.") {}
};

class InexistKeyError : public logic_error {
    public:
        InexistKeyError() : logic_error("Logic Error: Chave inexistente na Lista.") {}
};

class EmptyListError : public underflow_error {
    public:
        EmptyListError() : underflow_error("Underflow Error: Lista Vazia.") {}
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

class Lista {
    private:
    Item *primeiro;
    int quantidade;

    public:
    Lista();
    ~Lista();
    void setPrimeiro(Item *);
    void setQuantidade(int);
    Item * getPrimeiro();
    int getQuantidade();
    bool vazia();
    void imprimirLista();
    void inserir(int);
    Item * buscar(int);
    Item * remover(int);
};

Item::Item(int x) {
    this->setChave(x);
    this->setProximo(NULL);
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

Lista::Lista () {
    this->setPrimeiro(NULL);
    this->setQuantidade(0);
}

Lista::~Lista() {
    Item *atu = this->getPrimeiro(),
    *ant = NULL;

    while (atu != NULL) {
        ant = atu;
        atu = atu->getProximo();
        delete ant;
    }
}

void Lista::setPrimeiro(Item *p) {
    this->primeiro = p;
}

void Lista::setQuantidade(int q) {
    this->quantidade = q;
}

Item * Lista::getPrimeiro() {
    return this->primeiro;
}

int Lista::getQuantidade() {
    return this->quantidade;
}

bool Lista::vazia() {
    return this->getQuantidade() == 0;
}

Item * Lista::buscar(int num) {
    Item *atu = this->getPrimeiro();
    Item *ant = NULL;

    if(atu == NULL) throw EmptyListError();

    while(atu!= NULL && num != atu->getChave()) {
        ant = atu;
        atu = atu->getProximo();
    }

    if(atu==NULL) throw InexistKeyError();

    return atu;
}

void Lista::inserir(int num) {
    Item *novo = new Item(num);

    if(this->vazia()) {
        this->setPrimeiro(novo);
        this->setQuantidade(1);
    }

    else {
        Item *atu = this->getPrimeiro();
        Item *ant = NULL;

        while(atu != NULL && atu->getChave() < num) {        
            ant = atu;
            atu = atu->getProximo();           
        }

        if(atu == NULL) {
            ant->setProximo(novo);
            this->setQuantidade(this->getQuantidade()+1);
        }

        else if(atu->getChave() != num) {

            if(ant == NULL) {
                novo->setProximo(this->getPrimeiro());
                this->setPrimeiro(novo);
            }

            else {
                ant->setProximo(novo);
                novo->setProximo(atu);
            }
        
            this->setQuantidade(this->getQuantidade()+1);
        }

        else { 
            delete novo;
            throw ExistKeyError();
        }
    }
}

Item * Lista::remover(int num) {
    Item *atu = this->getPrimeiro();
    Item *ant = NULL;

    if(atu == NULL) throw EmptyListError();

    while(atu != NULL && atu->getChave() < num) {
        ant = atu;
        atu = atu->getProximo();
    }

    if(atu != NULL && atu->getChave() == num) {

        if(ant == NULL) {
            this->setPrimeiro(atu->getProximo());
        }

        else {
            ant->setProximo(atu->getProximo());
        }

        this->setQuantidade(this->getQuantidade()-1);
        return atu;
    }

    else {
        throw InexistKeyError();
    }

    return NULL;
}

void Lista::imprimirLista() {
    Item *atu = this->getPrimeiro();

    if(atu == NULL) throw EmptyListError();

    int n = this->getQuantidade();
    for (int i = 0; i < n-1; i++) {
        cout << atu->getChave() << " ";
        atu = atu->getProximo();
    }
    if (n > 0) {
        cout << atu->getChave() << endl;
    }
}

int main() {
    char op;
    int num;
    Lista *lista = new Lista();

    while(cin >> op) {  
        Item *temp = NULL;

        if(op == 'I') {
            cin >> num;
            try {
            lista->inserir(num);
            } catch(ExistKeyError e) {
                cout << e.what() << endl;
            }
        }

        if(op == 'R') {
            cin >> num;
            try{                
                temp = lista->remover(num);
                cout << "REMOVIDO: " << temp->getChave() << endl;
                delete temp;
            } catch(InexistKeyError e) {
                cout << e.what() << endl;
            } catch(EmptyListError e) {
                cout << e.what() << endl;
            }
        }

        if(op == 'B') {
            cin >> num;
            try{
                if(lista->buscar(num)) cout << "SIM" << endl;                
            } catch(EmptyListError e) {
                cout << e.what() << endl;
            } catch(InexistKeyError e) {
                cout << e.what() << endl;
            }
        }

        if(op == 'M') {
            try {
                lista->imprimirLista();
            } catch(EmptyListError e) {
                cout << e.what() << endl;
            }
        }
    }
    
    delete lista;
    return 0;
}