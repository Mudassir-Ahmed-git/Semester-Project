#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;

void calendar(){
    sf::RenderWindow window(sf::VideoMode({480, 700}), "Calendar");
    sf::Image icon;
    sf::Font font;
    if(!icon.loadFromFile("./assets/images/calendar.png") || !font.openFromFile("./assets/fonts/calfont.ttf")){
        cout<<"icon not loaded";
    }
    window.setIcon(icon);

    int box_width = 50;
    int gap = 14;
    string days[7] = {"M", "T", "W", "Th", "F", "St", "S"};
    sf::RectangleShape boxes[7];
    vector<sf::Text> texts;
    texts.reserve(7);

    for(int i = 0; i < 7; i++){
        sf::RectangleShape box(sf::Vector2f(box_width, box_width));
        box.setFillColor(sf::Color::White);
        box.setOutlineColor(sf::Color::Red);
        box.setOutlineThickness(2);
        box.setPosition(sf::Vector2f(gap + (i*box_width)+(i*gap), 100));
        boxes[i] = box;
    }
    for(int i = 0; i < 7; i++){
        sf::Text text(font, days[i], 20);
        text.setFillColor(sf::Color::Black);
        int textx = text.getGlobalBounds().size.x;
        int texty = text.getGlobalBounds().size.y;
        int tposx = (boxes[i].getPosition().x + (box_width/2) - (textx/2));
        int tposy = (boxes[i].getPosition().y + (box_width/2) - (texty/2));
        text.setPosition(sf::Vector2f(tposx, tposy));
        texts.push_back(text);
    }
    while(window.isOpen()){

        while(std::optional event = window.pollEvent()){

            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color::Cyan);
        for(int i = 0; i < 7; i++){
            window.draw(boxes[i]);
            window.draw(texts[i]);
        }

        window.display();
    }
}