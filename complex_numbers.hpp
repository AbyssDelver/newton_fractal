
class Complex{
double a{0};
double b{0};

public:

Complex (double i1, double i2) : a(i1), b(i2) {};

double real(){
    return a;
}

double imaginary(){
    return b;
}

};

Complex operator+(Complex & z1, Complex z2){
    Complex sum = Complex(z1.real() + z2.real(), z1.imaginary() + z2.imaginary());
    return sum;
}

Complex operator*(Complex & z1, Complex &z2){
Complex product = Complex((z1.real()*z2.real() - z1.imaginary()*z2.imaginary()) ,z1.real()*z2.imaginary() + z2.real()*z1.imaginary() );
return product;
}