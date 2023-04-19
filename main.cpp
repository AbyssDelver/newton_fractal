#include "complex_numbers.hpp"
#include <iostream>
#include <vector>
#include <cmath> 
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//----- constanti -----
const double grid_num = 1000; // number of elements in the grid
const double window_size = 1000;
const int iterations = 300; //how many times to iterate the newton's method?
const double scale_complexplane = 0.000001; //scales complex plane viewed by factor
const double approximation = 0.00001; // how close to the root must it be for. must be positive
std::vector<Complex> roots = {Complex(1.31368, 0.42105), Complex(1.31368,-0.42105), Complex(-2.6273650, 0)}; //list of roots of the function, not const beccause weirtdly deosn't work
const std::vector<sf::Color> colors ={sf::Color(98,0,234), sf::Color(25, 118, 210), sf::Color(0, 105, 92)}; //list of colors assigned to each root(in order)
const sf::Color no_color = sf::Color(0,0,0); //color for non converging points
//---------------------

Complex function(Complex& z)
{ // the function to which Newton's method is to be applied
    return z * z * z + Complex(-5,0)*z + Complex(5,0); 
}

Complex derivative(Complex& z)
{ // the derivative of function
    Complex complex_three = Complex(3, 0);
    return complex_three * z * z + Complex(-5,0);
}

Complex approximate(Complex & z1)
{ // function
    Complex complex_minus = Complex(-1, 0);
    Complex quotient = function(z1) / derivative(z1); // non molto ottimale dividere in quotient e z2, quando funzione farlo ritornare ad una sola linea
    Complex z2 = z1 + complex_minus * quotient;
    return z2;
}

sf::Color find_root(Complex z)
{
    Complex z_next = z;

    for(int j = 0; j < iterations; ++j){
            z_next = approximate(z_next);
        }

    for(int i = 0; i < roots.size(); ++i){
        if(abs(z_next.real() - roots[i].real()) < approximation && abs(z_next.imaginary() - roots[i].imaginary()) < approximation){
            std::cout << "------- " << "\n";
            std::cout << "real- " << z.real() << "\n";
            std::cout <<"img- " << z.imaginary() << "\n";
            return colors[i];
        }
    }
    return no_color;
}

sf::RectangleShape draw_rectangle(std::vector<double> & pos, Complex z){
    sf::RectangleShape rectangle(sf::Vector2f(window_size/sqrt(grid_num),window_size/sqrt(grid_num)));
    rectangle.setPosition(pos[0], pos[1]);
    rectangle.setFillColor(find_root(z));
    return rectangle;
}

int main()
{
    // gestione finestra
    sf::RenderWindow window;
    window.create(sf::VideoMode(window_size, window_size), "frattale di newton",
                  sf::Style::Default);

    // loop principale. si esce dal loop quando si chiude la finestra
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);  //fa ritornare la finestra nera

        Complex z = Complex(-window_size/2*scale_complexplane, -window_size/2*scale_complexplane);
        std::vector<double> pos = {0, 0};

    
        for (int i = 0; i < grid_num; ++i)
        {
            pos[1] = i * (window_size/grid_num);
            z = z + Complex(0, scale_complexplane*window_size/grid_num);

            for (int j = 0; j < grid_num; ++j)
            {
                pos[0] = j * (window_size/grid_num);
                z = z + Complex(scale_complexplane*window_size/grid_num, 0);
                window.draw(draw_rectangle(pos, z));
                
            }
            z = Complex(-window_size/2*scale_complexplane, z.imaginary());
        }
    

        window.display();               // aggiorna la finestra
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1000ms);
    }
}