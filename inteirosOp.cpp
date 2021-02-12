// g++ inteirosPOO.cpp -o inteirosPOO.exe

#include <iostream>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class BigNum {
    private:
        string num;

    public:
        BigNum(std::string);
        BigNum();
        string getBig();
        void setBig(string a); 
        BigNum operator +(BigNum);
        BigNum operator -(BigNum); 
        BigNum operator *(BigNum); 
        void printNum();
};

BigNum::BigNum(string a) {
    this->setBig(a);
}

BigNum::BigNum() {
    this->setBig(" ");
}

void BigNum::setBig(string a) {
    this->num = a;
}

string BigNum::getBig() {
    return this->num;
}
 
BigNum BigNum::operator +(BigNum aux) {
    string a = this->getBig();
    string b = aux.getBig();
    
    if(a.size() < b.size()) swap(a, b);
    int j = a.size()-1;

    for(int i=b.size()-1; i>=0; i--, j--) a[j] += (b[i]-'0');

    for(int i=a.size()-1; i>0; i--) {
        if(a[i] > '9'){
            int temp = a[i] - '0';
            a[i-1] = ((a[i-1]-'0') + temp/10) + '0';
            a[i] = (temp%10)+'0';
        }
    }

    if(a[0] > '9') {
        string aux;
        aux += a[0];
        a[0] = ((a[0]-'0')%10) + '0';
        aux[0] = ((aux[0] - '0')/10)+'0';
        a = aux+a;
    }

    BigNum temp(a);    
    return temp;
}

BigNum BigNum::operator -(BigNum aux) {
    string a = this->getBig();
    string b = aux.getBig();

    if(a.size() < b.size()) swap(a, b);
    int j = a.size()-1;
    int h = 0;

    for(int i=b.size()-1; i>=0; i--) {
        if(a[j] - '0' < b[i] - '0') {
            a[j-1]--;
            a[j] += 10;
        }
        a[j] -= (b[i]-'0'); 
        j--;
    }
    if(a[0] == '0') a.erase(a.begin());

    BigNum temp(a);    
    return temp;
}

BigNum BigNum::operator *(BigNum aux) {
    string r, r2, raux;
    string b = aux.getBig();
    string a = this->getBig();
    r = "";
    int i, j;

    for (j = b.length()-1; j >= 0; j--) {
        char adc = 0;
        raux = "";
        for (i = 0; i < (b.length()-1)-j; i++) {
            raux += '0';
        }
        for (i = a.length()-1; i >= 0; i--) {
            char temp = (a[i] - '0') * (b[j] - '0') + adc;
            raux += (temp % 10) + '0';
            adc = temp / 10;
        }
        if (adc) {
            raux += adc + '0';
        }
        r2 = "";
        for (i = raux.length()-1; i >= 0 ; i--) {
            r2 += raux[i];
        }
        r = r + r2;
    }
    if(r[0] == '0') {
        BigNum aux2("0");
        return aux2;
    }     
    BigNum temp(r);   
    return temp;
}

void BigNum::printNum() {
    cout << this->num << endl;
}

int main() {
    string a, b;
    char temp;
    
    while(cin >> a >> temp >> b) {
        BigNum d(a);
        BigNum e(b);
        if(temp == '+') {
            (d+e).printNum();
        }

        if(temp == '-') {
            (d-e).printNum();
        }

        if(temp == '*') {
            (d*e).printNum();
        }
    }

    return 0;
}
