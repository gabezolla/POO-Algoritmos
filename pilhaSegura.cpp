// g++ pilha.cpp -o pilha.exe

#include <iostream>
using namespace std;

class FullStackError : public runtime_error {
    public:
        FullStackError() : runtime_error("Runtime Error: Pilha Cheia.") {  } 
};

class EmptyStackError : public runtime_error {
    public:
        EmptyStackError() : runtime_error("Runtime Error: Pilha Vazia.") {  } 
};

class Pilha {
    private:
        int *pilha;
        int tamanho;
        int topo;

    public:
        Pilha (int);
        void setNum(int, int);
        void setQtd(int);
        void setTopo(int);
        int getNum(int);
        int getQtd();
        int getTopo();
        void empilhar(int);
        void desempilhar();
        void printBottomUp();
        void printTopDown();
};

Pilha::Pilha(int size) {
    this->setQtd(size);
    this->setTopo(-1);
    this->pilha = new int[size];
}

void Pilha::setNum(int num, int topo) {
    this->pilha[topo] = num;
}

void Pilha::setQtd(int size) {
    this->tamanho = size;
}

void Pilha::setTopo(int topo) {
    this->topo = topo;
}

int Pilha::getQtd() {
    return this->tamanho; 
}

int Pilha::getNum(int index) {
    return this->pilha[index];
}

int Pilha::getTopo() {
    return this->topo;
}

void Pilha::empilhar(int num) {
    
    if(this->getTopo() == this->getQtd()-1) {
        throw FullStackError();
    }

    this->setTopo(this->getTopo()+1);
    this->setNum(num, this->getTopo());
}

void Pilha::desempilhar() {

    if(this->getTopo() == -1) {
        throw EmptyStackError();
    }

    this->setTopo(this->getTopo()-1);
}

void Pilha::printBottomUp() {
    if(this->getTopo() == -1) throw EmptyStackError();

    for(int i = 0; i <= this->getTopo(); i++) {
        cout << this->getNum(i) << endl;
    }
}

void Pilha::printTopDown() {
    if(this->getTopo() == -1) throw EmptyStackError();

    for(int i = this->getTopo(); i>=0; i--) {
        cout << this->getNum(i) << endl;
    }
}

int main() {
    int n, num;
    char temp;
    cin >> n;
    Pilha p1(n);

    while (cin >> temp) {        

        if(temp == 'E') { 
            cin >> num;
            try {
                p1.empilhar(num); 
            } catch(FullStackError e) {
                cout << e.what() << endl;
            }            
        }

        if(temp == 'D') { 
            try {
                p1.desempilhar();
            } catch(EmptyStackError e) {
                cout << e.what() << endl;
            }   
        }

        if(temp == 'T') {
            try {
                p1.printTopDown();
            } catch(EmptyStackError e) {
                cout << e.what() << endl;
            }
        } 

        if(temp == 'B') {
            try { 
                p1.printBottomUp();
            } catch(EmptyStackError e) {
                cout << e.what() << endl;
            }
        }
    }

    return 0;
}