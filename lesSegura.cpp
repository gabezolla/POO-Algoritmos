// g++ les.cpp -o les.exe

#include <iostream>
using namespace std;

class ExistLogicError : public logic_error{
    public:
        ExistLogicError() : logic_error("Logic Error: Chave existente na lista.") {    }
};

class InexistLogicError : public logic_error {
    public:
        InexistLogicError() : logic_error("Logic Error: Chave inexistente na lista.") {    }

};

class FullListError : public runtime_error {
    public:
        FullListError() : runtime_error("Runtime Error: Lista cheia.") {     }
};

class EmptyListError : public runtime_error {
    public:
        EmptyListError() : runtime_error("Runtime Error: Lista Vazia.") {     }
};

class PositionListError : public runtime_error {
    public:
        PositionListError() : runtime_error("Runtime Error: Posicao da lista inexistente.") {     }
};

class Lista {
    private: 
        int *lista;
        int tamanho;
        int quantidade;

    public:
        Lista(int);
        ~Lista();
        void setTamanho(int);
        void setQtd(int);
        void setItem(int, int);
        int getTamanho();
        int getQtd();
        int getItem(int);
        int busca(int);
        void buscaIndex(int);
        void insert(int);
        void remover(int);
        void print();
};

Lista::Lista(int size) {
    this->setTamanho(size);
    this->setQtd(0);
    this->lista = new int[this->getTamanho()];
}

Lista::~Lista() {
    delete[] this->lista;
}

void Lista::setTamanho(int size) {
    this->tamanho = size;
}

void Lista::setQtd(int qtd) {
    this->quantidade = qtd;
}

void Lista::setItem(int num, int pos) {
    this->lista[pos] = num;
}

int Lista::getTamanho() {
    return this->tamanho;
}

int Lista::getQtd() {
    return this->quantidade;
}

int Lista::getItem(int pos) {
    return this->lista[pos];
}

int Lista::busca(int num) {

    if(this->getQtd() == 0) throw EmptyListError();

    for(int i=0; i < this->getQtd(); i++) {
        if(this->getItem(i) == num) return i;
    }

    return -1;
}

void Lista::buscaIndex(int index) {
    if(index > this->getQtd()-1 || index < 0) throw PositionListError();    
    cout << "<" << this->getItem(index) << ">" << endl;    
}

void Lista::insert(int num) {
    int i = 0;

    if(this->getQtd() == this->getTamanho()) throw FullListError();

    if(this->getQtd() == 0) {
        this->setQtd(1);
        this->setItem(num, 0);
    }

    else {
        while(num > this->getItem(i) && i < this->getQtd()) {
            i++;
        }        

        if(num == this->getItem(i)) throw ExistLogicError();

        if(i == this->getQtd()) {
            this->setItem(num, i);
            this->setQtd(this->getQtd()+1);
        }

        else if(num != this->getItem(i)){

            for(int j = this->getQtd()-1; j >= i; j--) {
                this->setItem(this->getItem(j), j+1);
            }

            this->setQtd(this->getQtd()+1);
            this->setItem(num, i);
        }        
    }
}

void Lista::remover(int num) {
    int index = this->busca(num);

    if(this->getQtd() == 0) throw EmptyListError();

    if(index == -1) throw InexistLogicError();

    if(index != -1) {

        if(index == getQtd()-1) {
            this->setQtd(this->getQtd()-1);
        }

        else {
            for(int j = index; j < this->getQtd()-1; j++) {
                this->setItem(this->getItem(j+1), j);        
            }
            this->setQtd(this->getQtd()-1);
        }
    }
}

void Lista::print() {

    if(this->getQtd()==0) throw EmptyListError();

    for(int i = 0; i < this->getQtd(); i++) {
        if(this->getItem(i) != 0) cout << this->getItem(i) << " ";
    }
    cout << endl;
}
 
int main() {
    int q, num;
    char temp;
    cin >> q;
    Lista l1(q);

    while(cin >> temp) {

        if(temp == 'I') {
            cin >> num;
            try{
                l1.insert(num); 
            } catch(FullListError e) {
                cout << e.what() << endl;
            } catch(ExistLogicError e) {
                cout << e.what() << endl;
            }                      
        } 

        if(temp == 'E') {
            cin >> num;
            try{
                l1.remover(num);
            } catch(EmptyListError e) {
                cout << e.what() << endl;
            } catch(InexistLogicError e) {
                cout << e.what() << endl;
            }
        }

        if(temp == 'B') {
            cin >> num;
            try {
                if(l1.busca(num) != -1) cout << "SIM" << endl;
                else cout << "NAO" << endl;
            } catch(EmptyListError e) {
                cout << e.what() << endl;
            }
        }

        if(temp == 'M') {
            try {
                l1.print();
            } catch(EmptyListError e) {
                cout << e.what() << endl;
            }
        }

        if(temp == 'C') {
            cin >> num;
            try{
                l1.buscaIndex(num);
            } catch(PositionListError e) {
                cout << e.what() << endl;
            }
        }

    }
}