#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
using namespace std;
#include<calculator.hpp>
#include<snakegame.hpp>
#include<calendar.hpp>
#include<notepad.hpp>

// Getting Formatted Time for Display
string gettime(){
    time_t current_time = time(0);
        tm* localTime = localtime(&current_time);

        char buffer[12];
        strftime(buffer, sizeof(buffer), "%I:%M:%S %p", localTime);
        string timeStr(buffer);
        return timeStr;

};

int main(){

    //Window Settings
    sf::RenderWindow window(sf::VideoMode({480, 700}), "miniPhone (Phone Simulator)");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    //Loading Assets BG & Font
    sf::Texture bg("./assets/images/bg1.png");
    sf::Sprite backg(bg);
    sf::Font timeFont;
    if(!timeFont.openFromFile("./assets/fonts/ka1.ttf")){
        cout<<"font not loaded";
    }

    //Text for Time Display
    sf::Text timeText(timeFont, "", 30);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(sf::Vector2f(240.f, 420.f));
    
    //Loading App icon Textures and Making their Sprites
    string appAddr[4] = {"./assets/images/cal1.png", "./assets/images/snake.png", "./assets/images/calendar.png", "./assets/images/notepad.png"};
    sf::Texture appTextures[4];
    vector<sf::Sprite> appSprites; 
    appSprites.reserve(4);

    //App icon Textures
    for(int i = 0; i < 4; i++){
        sf::Texture appIcon(appAddr[i]);
        appTextures[i] = appIcon;
    }
    //Sprites of Textures
    for(int i = 0; i < 4; i++){
        sf::Sprite appSprite(appTextures[i]);
        appSprites.push_back(appSprite);
    }


    float padding = 40;
    // Position ICONS on Screen
    appSprites[0].setPosition(sf::Vector2f(padding , 570.f));
    appSprites[1].setPosition(sf::Vector2f(padding + appTextures[1].getSize().x, 570.f));
    appSprites[2].setPosition(sf::Vector2f(padding + appTextures[1].getSize().x + appTextures[2].getSize().x, 570.f));
    appSprites[3].setPosition(sf::Vector2f(padding + appTextures[1].getSize().x + appTextures[2].getSize().x + appTextures[3].getSize().x, 570.f));

    //Function Calls of each APP
    void (*apps[4])() = {calculator, snakeGame, calendar, notepad};

    //GAME LOOP
    while (window.isOpen())
    {   
        //Positioning Text for Time
        sf::FloatRect textbounds = timeText.getLocalBounds();
        timeText.setOrigin(sf::Vector2f(textbounds.size.x/2.f, textbounds.size.y/2.f));
        timeText.setString(gettime());
        
        //Loop For polling Events
        while (const std::optional event = window.pollEvent())
        {

            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // HANLDING MOUSE HOVERING OR CLICKS ON APP ICONS
            auto mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));
            
            for(int i = 0; i < 4; i++){
                appSprites[i].setColor(sf::Color(255, 255, 255));
            }
            for(int i = 0; i < 4; i++){
                if(appSprites[i].getGlobalBounds().contains(mouse_position)){
                    
                    appSprites[i].setColor(sf::Color(204, 204, 204));
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        if(i == 1){
                            gameOver = false;
                            apps[i]();
                        }
                        else{
                            apps[i]();
                        }
                        
                    }
                }
            }

            
        window.clear();


        window.draw(backg);
        for(int i = 0; i < 4; i++){
            window.draw(appSprites[i]);
        }
        window.draw(timeText);

        window.display();
    }
}