#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;

#define SIZE 20
int snakeSize = 1;
int score;
enum Directions {UP, DOWN, LEFT, RIGHT};
Directions dir;
bool gameOver = false;

struct Apple{
    int x, y;
};
Apple apple;

struct Snake{
    int x, y;
};
Snake snake[100];


void move(){
    for(int i = snakeSize; i > 0; i--){
        snake[i].x = snake[i-1].x;
        snake[i].y = snake[i-1].y;
    }
    switch(dir){
        case UP:
            snake[0].y --;
            break;
            
        case DOWN:
            snake[0].y ++;
            break;
            
        case LEFT:
            snake[0].x --;
            break;
            
        case RIGHT:
            snake[0].x ++;
            break;
            
    }
    if(snake[0].x == apple.x && snake[0].y == apple.y){
        snakeSize ++;
        apple.x = rand() % SIZE;
        apple.y = rand() % SIZE;
        
    }
    for(int i = 1; i < snakeSize; i++){
        if(snake[0].x == snake[i].x && snake[0].y == snake[i].y){
            snakeSize = 1;
            snake[0].x = 0;
            snake[0].y = 0;
            dir = RIGHT;
            gameOver = true;
        }
    }
    if (snake[0].x > 23) snake[0].x = 0;
    else if (snake[0].x < 0) snake[0].x = 23;
    else if (snake[0].y > 34) snake[0].y = 0;
    else if (snake[0].y < 0) snake[0].y = 34;
};

void snakeGame(){
    sf::RenderWindow window(sf::VideoMode({480, 700}), "Snake Game");
    sf::Font font;
    sf::Image icon;
    sf::Texture bg;
    sf::Clock ticker;

    

    if(!bg.loadFromFile("./assets/images/snakebg.png")){
        cout<<"background not loaded";
    };
    sf::Sprite bgSprite(bg);

    if(!font.openFromFile("./assets/fonts/ka1.ttf") || !icon.loadFromFile("./assets/images/snake.png")){
        cout<<"font || icon not loaded";
    }
    window.setIcon(icon);

    sf::RectangleShape appleShape(sf::Vector2f(SIZE, SIZE));
    appleShape.setFillColor(sf::Color::Red);

    sf::RectangleShape snakeShape(sf::Vector2f(SIZE, SIZE));
    snakeShape.setFillColor(sf::Color::Black);
    
    while(window.isOpen()){
        if(gameOver)window.close();
        
        while(std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                snakeSize = 1;
                snake[0].x = 0;
                snake[0].y = 0;
                dir = RIGHT;
                gameOver = true;
                window.close();
            }
            if(const auto key = event->getIf<sf::Event::KeyPressed>()){

                switch(key->scancode){
                    case sf::Keyboard::Scan::Up:
                        dir = UP;
                        break;

                    case sf::Keyboard::Scan::Down:
                        dir = DOWN;
                        break;

                    case sf::Keyboard::Scan::Left:
                        dir = LEFT;
                        break;

                    case sf::Keyboard::Scan::Right:
                        dir = RIGHT;
                        break;
                }
            }
        }
        score = snakeSize -1;
        string scoreStr = to_string(score);
        sf::Text textScore(font, "score: " + scoreStr, 20);
        textScore.setFillColor(sf::Color::Black);
        int scorex = textScore.getGlobalBounds().size.x;
        int scoreposx = scorex/2;
        textScore.setPosition(sf::Vector2f(240 - scoreposx, 0));

        window.clear();
        if(ticker.getElapsedTime().asMilliseconds() > 100){
            move();
            ticker.restart();
        }
        window.draw(bgSprite);

        appleShape.setPosition(sf::Vector2f(apple.x * SIZE, apple.y * SIZE));
        window.draw(appleShape);

        for(int i = 0; i < snakeSize; i++){
            snakeShape.setPosition(sf::Vector2f(snake[i].x * SIZE, snake[i].y * SIZE));
            window.draw(snakeShape);
        }
        
        window.draw(textScore);

        window.display();
    }
}