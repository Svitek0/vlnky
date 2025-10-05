#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
using namespace sf;
using namespace std::chrono_literals; 

int main() {
    const int ResX = 800;
    const int ResY = 800;

    RenderWindow okno(VideoMode({ResX, ResY}), "Vlnky");
    float t = 0.f;

    float x01 = 200;
    float y01 = 200;
    float lambda1 = 100;
    float k1 = 2 * M_PI / lambda1;
    float freq1 = 0.05f;
    float omega1 = 2 * M_PI * freq1;

    float x02= 600;
    float y02= 600;
    float lambda2 = 300;
    float k2 = 2 * M_PI / lambda2;
    float freq2 = 0.1f;
    float omega2 = 2 * M_PI * freq2;

    //cout << "napiš pozici zdroje 1 : ";
    //cin >> x01 >> y01;

    Image img({ResX, ResY}, Color::White);
    Texture textur({ResX, ResY});
    Sprite sprt(textur);

    while (okno.isOpen()) {
        while (const optional event = okno.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
              okno.close(); 
              break; 
            }
        }

        t += 0.15f;
        okno.clear(Color::White);
        for (int y = 0; y < ResY; ++y) {
            for (int x = 0; x < ResX; ++x) {


                float dx1 = x - x01;
                float dy1 = y - y01;
                float r1 = sqrt(dx1*dx1 + dy1*dy1);

                float dx2 = x - x02;
                float dy2 = y - y02;
                float r2= sqrt(dx2*dx2 + dy2*dy2);

                float hod1 = (100.f / (r1 + 0.0001f)) * sin(k1 * r1 - omega1 * t);
                float hod2 = 1*(100.f / (r2 + 0.0001f)) * sin(k2 * r2 - omega2 * t);
                float hod12 = hod1 + hod2;


                int value = int(((hod12 + 2.f) / 4.f) * 255);
                value = clamp(value, 0, 255);
                Color barva(value, 0, 255 - value);
                img.setPixel({x, y}, Color(barva));
                
            }
                
        }
        textur.update(img);
        okno.clear();
        okno.draw(sprt);
        okno.display();

    }
}

