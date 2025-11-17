#include<SFML\Graphics.hpp>
#include<iostream>
using namespace std;


void calculator(){
        sf::RenderWindow window(sf::VideoMode({480, 700}), "Calculator");
        sf::Image icon;
        if(!icon.loadFromFile("./assets/images/cal1.png")){
            cout<<"icon not loaded";
        }
        window.setIcon(icon);
        window.setFramerateLimit(60);
        window.setKeyRepeatEnabled(false);

        int btnsPerRows = 4;
        int btnsPerCol = 4;
        int btnWidth = 100;
        int gap = 15;
        int totalBtns = btnsPerRows * btnsPerCol;

        sf::RectangleShape calScreen(sf::Vector2f(460, 200));
        calScreen.setFillColor(sf::Color(0, 153, 255));
        calScreen.setOutlineColor(sf::Color(62, 61, 212));
        calScreen.setOutlineThickness(2);
        calScreen.setPosition(sf::Vector2f(10, 10));

        std::pair<int, int> buttonPositions[totalBtns];

            for(int i = 0; i < btnsPerRows; i++) {
                for(int j = 0; j < btnsPerCol; j++) {

                    buttonPositions[i * 4 + j] = {
                        gap + j * (btnWidth + gap),
                        gap + i * (btnWidth + gap)
                    };
    }
}       
        sf::RectangleShape buttons[totalBtns];
        for(int i = 0; i<totalBtns; i++){
            sf::RectangleShape button(sf::Vector2f(btnWidth, btnWidth));
            button.setPosition(sf::Vector2f(buttonPositions[i].first, buttonPositions[i].second+210));
            button.setFillColor(sf::Color(62, 61, 212));
            buttons[i] = button;
        }


        sf::Font font;
        if(!font.openFromFile("./assets/fonts/calfont.ttf")){
            cout<<"font not loaded";
        }

        string btnNames[] = {
            "9", "8", "7", "-",
            "6", "5", "4", "+",
            "3", "2", "1", "*",
            "0", "C", "=", "/"
        };

        vector<sf::Text> btnText;
        btnText.reserve(totalBtns);
        
        for(int i = 0; i < totalBtns; i++){
            sf::Text t(font, btnNames[i], 27);
            t.setFillColor(sf::Color::White);
            int textx = t.getGlobalBounds().size.x;
            int texty = t.getGlobalBounds().size.y;
            int tposx = (buttons[i].getPosition().x + btnWidth/2)-(textx/2);
            int tposy = (buttons[i].getPosition().y + btnWidth/2)-(texty/2);
            t.setPosition(sf::Vector2f(tposx, tposy));
            btnText.push_back(move(t));
        }

        int num1, num2;
        char op;
        string input = "";

        bool wasMouseButtonPressed = false;
        while(window.isOpen()){

            while(const std::optional event = window.pollEvent()){

                auto mouse_position = sf::Mouse::getPosition(window);

                if(event->is<sf::Event::Closed>()){
                    window.close();
                    return;
                }
            }
                
            bool isMousebuttonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
                 
                if(isMousebuttonPressed && !wasMouseButtonPressed){
                        for(int i = 0; i<totalBtns; i++){

                            auto mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

                            if(buttons[i].getGlobalBounds().contains(mouse_position)){
                                
                                try{
                                    stoi(btnNames[i]);
                                    input += btnNames[i];
                                }
                                catch(const invalid_argument& e){
                                        
                                        if(btnNames[i] == "C"){
                                            input = "";
                                        }
                                        else if(btnNames[i]== "/" || btnNames[i]== "*" || btnNames[i]== "-" || btnNames[i]== "+"){

                                            if(!input.empty()){
                                            num1 = stoi(input);
                                            input = "";
                                            }
                                            op = btnNames[i][0];
                                            
                                        } 
                                        else if(btnNames[i] == "="){
                                            num2 = stoi(input);
                                            int result;
                                            switch(op){

                                                case '+':
                                                    result = num1 + num2;
                                                    input = to_string(result);
                                                    break;

                                                case '-':
                                                    result = num1 - num2;
                                                    input = to_string(result);
                                                    break;

                                                case '/':
                                                    result = num1 / num2;
                                                    input = to_string(result);
                                                    break;

                                                case '*':
                                                    result = num1 * num2;
                                                    input = to_string(result);
                                                    break;
                                            }
                                        }
                                        
                                        }
                                    }
                            }            
                        
                };
            wasMouseButtonPressed = isMousebuttonPressed;
            
            sf::Text calDisplay(font, input, 40);
            calDisplay.setFillColor(sf::Color(62, 61, 212));
            calDisplay.setPosition(sf::Vector2f(calScreen.getPosition().x+20, calScreen.getPosition().y+140));
            calDisplay.setString(input);

            window.clear();

            window.draw(calScreen);
            for(int i=0; i < totalBtns; i++){
                window.draw(buttons[i]);
                window.draw(btnText[i]);   
            }
            window.draw(calDisplay);
            window.display();
                
            }
            
        };
