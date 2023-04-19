#include <cmath>
class Complex{
double a{0};
double b{0};

public:

Complex (double i1, double i2) : a(i1), b(i2) {};

double real() const{
    return a;
}

double imaginary() const{
    return b;
}

double abs_value() const{
    return(sqrt(real()*real()+imaginary()*imaginary()));
}

};

Complex operator+(Complex z1, Complex z2){
    Complex sum = Complex(z1.real() + z2.real(), z1.imaginary() + z2.imaginary());
    return sum;
}

Complex operator*(Complex z1, Complex z2){
Complex product = Complex((z1.real()*z2.real() - z1.imaginary()*z2.imaginary()) ,z1.real()*z2.imaginary() + z2.real()*z1.imaginary() );
return product;
}

Complex operator/(Complex z1, Complex z2){
    double divider = pow(z2.real(),2) +pow(z2.imaginary(),2);
    Complex quotient = Complex(((z1.real()*z2.real()+z1.imaginary()*z2.imaginary())/divider), (z1.imaginary()*z2.real() - z1.real()*z2.imaginary())/divider);
    return quotient;
}