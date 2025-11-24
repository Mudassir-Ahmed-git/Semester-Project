#include<iostream>
#include<SFML/Graphics.hpp>
#include<ctime>
using namespace std;

int first_day(int year, int month){
    // month is 0-based (0=January, 11=December)
    // Use time functions to get the day of week for the first of the month
    struct tm timeinfo = {};
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month;
    timeinfo.tm_mday = 1;
    timeinfo.tm_isdst = -1;
    
    mktime(&timeinfo);
    
    // tm_wday: 0=Sunday, 1=Monday, ..., 6=Saturday
    return timeinfo.tm_wday;
}

void calendar(){
    sf::RenderWindow window(sf::VideoMode({480, 700}), "Calendar");
    sf::Image icon;
    sf::Font font;
    if(!icon.loadFromFile("./assets/images/calendar.png") || !font.openFromFile("./assets/fonts/calfont.ttf")){
        cout<<"icon not loaded";
    }
    window.setIcon(icon);
    
    int day, month, year;
    int cur_day;
    int days_month[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    string months[12] {"January", "Febuary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};


    //Getting Current MONTH
    time_t current_time = time(NULL);
    struct tm *localTime = localtime(&current_time);
    month = localTime->tm_mon;
    year = localTime->tm_year + 1900;
    
    if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
        days_month[1] = 29;
    }
    day = first_day(year, month);
    cur_day = localTime->tm_mday;
    cout<<"Day of Month: "<<cur_day;
    string strCurDay = to_string(cur_day);
    string yearStr = to_string(year);

    sf::Text myName(font, months[month] + ", " + yearStr, 27);
    myName.setFillColor(sf::Color::Blue);
    int myx = myName.getGlobalBounds().size.x;
    int myposx = 240 - myx/2;
    myName.setPosition(sf::Vector2f(myposx, 100));

    int box_width = 50;
    int gap = 14;
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    sf::RectangleShape boxes[7];
    vector<sf::Text> texts;
    texts.reserve(7);

    sf::RectangleShape day_boxes[42];
    vector<sf::Text> day_texts;
    day_texts.reserve(days_month[month]);

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 7; j++){
            sf::RectangleShape box(sf::Vector2f(box_width, box_width));
            box.setFillColor(sf::Color::White);
            box.setOutlineColor(sf::Color(7, 35, 156));
            box.setOutlineThickness(2);
            box.setPosition(sf::Vector2f(65 + (box_width * j), i * box_width + (150 + box_width)));
            day_boxes[j + (i*7)]  = box;
        }
    }

    for(int i = 0; i < 7; i++){
        sf::RectangleShape box(sf::Vector2f(box_width, box_width));
        box.setFillColor(sf::Color(39, 77, 245));
        box.setOutlineColor(sf::Color(7, 35, 156));
        box.setOutlineThickness(2);
        box.setPosition(sf::Vector2f(65 + (i * box_width), 150));
        boxes[i] = box;
    }
    for(int i = 0; i < 7; i++){
        sf::Text text(font, days[i], 14);
        text.setFillColor(sf::Color::White);
        int textx = text.getGlobalBounds().size.x;
        int texty = text.getGlobalBounds().size.y;
        int tposx = (boxes[i].getPosition().x + (box_width/2) - (textx/2));
        int tposy = (boxes[i].getPosition().y + (box_width/2) - (texty/2));
        text.setPosition(sf::Vector2f(tposx, tposy));
        texts.push_back(text);
    }

    for(int i = 0; i < 42; i++){
        string dayStr = to_string(i - day + 1);
        if(i >= day && i - day < days_month[month]){
            sf::Text text(font, dayStr, 14);
            text.setFillColor(sf::Color::Black);
            int textx = text.getGlobalBounds().size.x;
            int texty = text.getGlobalBounds().size.y;
            int tposx = day_boxes[i].getPosition().x + (box_width/2) - (textx/2);
            int tposy = day_boxes[i].getPosition().y + (box_width/2) - (texty/2);
            text.setPosition(sf::Vector2f(tposx, tposy));
            day_texts.push_back(text);
        }
    }

    while(window.isOpen()){

        while(std::optional event = window.pollEvent()){

            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color(187, 199, 252));
        for(int i = 0; i < 7; i++){
            window.draw(boxes[i]);
            window.draw(texts[i]);
        }
        for(int i = 0; i < 42; i++){
            window.draw(day_boxes[i]);
        }
        for(size_t i = 0; i < day_texts.size(); i++){
            if(day_texts[i].getString() == strCurDay){
                day_texts[i].setFillColor(sf::Color::Blue);
                window.draw(day_texts[i]);
            } else{
                window.draw(day_texts[i]);
            }
        }
        window.draw(myName);
        window.display();
    }
}
