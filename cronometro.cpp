// g++ cronometro.cpp -o cronometro.exe
#include <iostream>
using namespace std;

class Cronometro {
    private:
        int hora, min, seg;

    public:
        Cronometro();
        int getHora();
        int getMin();
        int getSeg();
        void setHora(int);
        void setMin(int);
        void setSeg(int);
        void operator ++(int);
        void printTime();
};

Cronometro::Cronometro() {
    this->setHora(0);
    this->setMin(0);
    this->setSeg(0);
}

int Cronometro::getHora() {
    return this->hora;
}

int Cronometro::getMin() {
    return this->min;
}

int Cronometro::getSeg() {
    return this->seg;
}

void Cronometro::setHora(int h) {
    this->hora = h;
}

void Cronometro::setMin(int m) {
    this->min = m;
}

void Cronometro::setSeg(int s) {
    this->seg = s;
}

void Cronometro::operator++ (int a) {
    this->setSeg(this->getSeg()+1);

    if(this->getSeg() == 60) {
        
        this->setMin(this->getMin()+1);
        this->setSeg(0);
        
        if(this->getMin() == 60) {
            this->setMin(0);
            this->setHora(this->getHora()+1);
        }
    }
}

void Cronometro::printTime() {
    cout << this->getHora() << ":" << this->getMin() << ":" << this->getSeg() << endl;
}

int main() {
    string a;
    Cronometro c;
    
    while(cin >> a) {
        if(a == "tic") c++;
    }

    c.printTime();    
    return 0;
}

