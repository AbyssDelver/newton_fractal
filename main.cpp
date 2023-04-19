#include "complex_numbers.hpp"
#include <iostream>


int main(){
auto z1 = Complex(0,-1);
auto z2 = Complex(1, 0);
std::cout << (z1*z2).imaginary();
}