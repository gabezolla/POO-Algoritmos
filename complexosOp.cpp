// g++ complexosOp.cpp -o complexosOp.exe

#include <iostream>
using namespace std;

class Complexo {
    private:
        int real, imag;

    public:
        Complexo(int, int);
        void setReal(int);
        void setImg(int);
        int getReal();
        int getImg(); 
        Complexo operator +(Complexo); 
        Complexo operator -(Complexo); 
        Complexo operator *(Complexo); 
        Complexo operator /(Complexo);
        Complexo conjugado();
        void printComplex();
};

Complexo::Complexo(int real, int imag) {
    this->real = real;
    this->imag = imag;
}

void Complexo::setReal(int num) {
    this->real = num;
}

void Complexo::setImg(int num) {
    this->imag = num;
}

int Complexo::getReal() {
    return this->real;
}

int Complexo::getImg() {
    return this->imag;
}

Complexo Complexo::operator +(Complexo num) {
    int a, b, c, d;
    Complexo temp(0,0);
    a = this->getReal();
    b = this->getImg();
    c = num.getReal();
    d = num.getImg();
    temp.setReal(a+c);
    temp.setImg(b+d);
    return temp;
}

Complexo Complexo::operator -(Complexo num) {
    int a, b, c, d;
    Complexo temp(0,0);
    a = this->getReal();
    b = this->getImg();
    c = num.getReal();
    d = num.getImg();
    
    temp.setReal(a-c);
    temp.setImg(b-d);
    return temp;
}

Complexo Complexo::operator *(Complexo num) {
    int a, b, c, d;
    Complexo temp(0,0);
    a = this->getReal();
    b = this->getImg();
    c = num.getReal();
    d = num.getImg();
    
    temp.setReal((a*c)-(b*d));
    temp.setImg((a*d)+(b*c));
    return temp;
}

Complexo Complexo::conjugado() {
    this->setImg(-(this->getImg()));
    return *this;
}

Complexo Complexo::operator /(Complexo num) {
    Complexo numerador(this->getReal(), this->getImg());
    Complexo denominador(num.getReal(), num.getImg());
    Complexo temp(0,0);
    Complexo aux1(0,0);
    Complexo aux2(0,0);

    aux1 = numerador * num.conjugado();  
    aux2 = denominador * num;  
    /*  numerador.mult(num.conjugado());
    denominador.mult(num);
    */
    temp.setReal(aux1.getReal()/aux2.getReal());
    temp.setImg(aux1.getImg()/aux2.getReal());
    return temp;
}

void Complexo::printComplex() {
    cout << this->getReal() << " " << this->getImg() << "i" << endl; 
}

int main () {
    int a, b, c, d;
    char temp, op;

    while(cin >> a >> b >> temp >> op >> c >> d >> temp) {
        Complexo c1(a, b);
        Complexo c2(c, d);

        if(op == '+') {
            (c1+c2).printComplex();
        }

        if(op == '-') {
            (c1-c2).printComplex();
        }

        if(op == '*') {
            (c1*c2).printComplex();
        }

        if(op == '/') {
            (c1/c2).printComplex();
        }

    }
    return 0;
}
