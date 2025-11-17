#include<iostream>
#include<SFML/Graphics.hpp>
#include<fstream>
using namespace std;

void notepad(){
    sf::RenderWindow window(sf::VideoMode({480, 700}), "Notepad");
    sf::Font font;
    sf::Image icon;
    if(!font.openFromFile("./assets/fonts/lowrespixel.otf") || !icon.loadFromFile("./assets/images/notepad.png")){
        cout<<"font not loaded";
    }
    window.setIcon(icon);

    string note;
    ifstream inFile("notepadFile.txt");
    string oldNotes;
    
    while(getline(inFile, oldNotes)){
        cout<<oldNotes;
        note.append(oldNotes + "\n");
    }
    inFile.close();

    ofstream notepadFile("notepadFile.txt");

    
    int lineLength = 0;

    while(window.isOpen()){

        while(std::optional event = window.pollEvent()){ 

            if(event->is<sf::Event::Closed>()){
                window.close();
            }
            if(const auto* texts = event->getIf<sf::Event::TextEntered>()){
                if(texts->unicode >= 32 && texts->unicode < 127){
                    char character = static_cast<char>(texts->unicode);
                    note += character;
                    lineLength ++;

                    if(lineLength >= 44){
                        note += '\n';
                        lineLength = 0;
                    }
                } 
            }

            if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if(keyPressed->scancode == sf::Keyboard::Scancode::Backspace){
                    if(!note.empty()){
                            note.pop_back();
                        }
                    } 
                if(keyPressed->scancode == sf::Keyboard::Scancode::Enter){
                    note += "\n";
                }
            }
            }
           
        

        sf::Text text(font, note, 20);
        text.setString(note);
        text.setFillColor(sf::Color::Black);
        text.setPosition(sf::Vector2f(10, 10));
        
        window.clear(sf::Color(227, 227, 227));
        window.draw(text);
        window.display();
    }
    if(notepadFile.is_open()){
            cout<<"file is open\n"; 
            notepadFile<<note;
    }
    notepadFile.close();
}