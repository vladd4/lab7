#include "book.h"
#include "graphics.h"

int main()
{
    string input1, input2, input3, input1_1, input1_2, input1_3;
    RenderWindow window(VideoMode(800, 500), L"Записна книга", Style::Default);
    window.setVerticalSyncEnabled(true);
    TextBox textBox1(sf::Vector2f(30.0f, 30.0f), sf::Vector2f(260.0f, 30.0f), font, 20, sf::Color::Black, sf::Color::White, "Enter name: ");
    TextBox textBox2(sf::Vector2f(30.0f, 70.0f), sf::Vector2f(260.0f, 30.0f), font, 20, sf::Color::Black, sf::Color::White, "Enter date: ");
    TextBox textBox3(sf::Vector2f(30.0f, 110.0f), sf::Vector2f(260.0f, 30.0f), font, 20, sf::Color::Black, sf::Color::White, "Enter number: ");
  
    TextBox textBox1_1(sf::Vector2f(100.0f, 100.0f), sf::Vector2f(260.0f, 30.0f), font, 20, sf::Color::Black, sf::Color::White, "Enter name: ");
    textBox1_1.setPosition(sf::Vector2f(30.0f, 230.0f));
    TextBox textBox1_2(sf::Vector2f(100.0f, 100.0f), sf::Vector2f(260.0f, 30.0f), font, 20, sf::Color::Black, sf::Color::White, "Enter date: ");
    textBox1_2.setPosition(sf::Vector2f(30.0f, 270.0f));
    TextBox textBox1_3(sf::Vector2f(100.0f, 100.0f), sf::Vector2f(260.0f, 30.0f), font, 20, sf::Color::Black, sf::Color::White, "Enter number: ");
    textBox1_3.setPosition(sf::Vector2f(30.0f, 310.0f));
    sf::Clock clock;

    while (window.isOpen())
    {
        AddressBook book1("address_book1.bin");
        AddressBook book2("address_book2.bin");

        Person person1;
        Person person2;

        book1.addPerson(person1);
        book2.addPerson(person2);
        drawInterface();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else {
                textBox1.handleEvent(event, input1, "name");
                textBox2.handleEvent(event, input2, "date");
                textBox3.handleEvent(event, input3, "number");
                textBox1_1.handleEvent(event, input1_1, "name");
                textBox1_2.handleEvent(event, input1_2, "date");
                textBox1_3.handleEvent(event, input1_3, "number");
            }
            if (book1_button_hovered)
                btn_book1.setFillColor(Dark_Blue_Grey_Hover);
            else
                btn_book1.setFillColor(Dark_Blue_Grey);
            if (book2_button_hovered)
                btn_book2.setFillColor(Dark_Blue_Grey_Hover);
            else
                btn_book2.setFillColor(Dark_Blue_Grey);
            if (check_button_hovered)
                btn_check.setFillColor(Dark_Blue_Grey_Hover);
            else
                btn_check.setFillColor(Dark_Blue_Grey);

            
        }

        sf::Time deltaTime = clock.restart();
    
        update_textbox(textBox1, textBox2, textBox3, textBox1_1, textBox1_2, textBox1_3, deltaTime);

        window.clear(Color(220, 220, 220));
    
        window.draw(btn_book1);
        window.draw(btn_book2);
        window.draw(btn_check);
        window.draw(board_show);
        window.draw(board_check);
        window.draw(text_book1);
        window.draw(text_book2);
        window.draw(text_check);
        window.draw(text_title1);
        window.draw(text_title2);
        window.draw(text_person1);
        window.draw(text_person2);
        window.draw(text_checked);

        textBox1.draw(window);
        textBox2.draw(window);
        textBox3.draw(window);
        textBox1_1.draw(window);
        textBox1_2.draw(window);
        textBox1_3.draw(window);
        
        person1.setName(input1);
        person1.setDate(input2);
        person1.setNumber(input3);

        person2.setName(input1_1);
        person2.setDate(input1_2);
        person2.setNumber(input1_3);
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (book1_button_hovered) {
                    text_person1.setFont(font);
                    std::stringstream s;
                    s << input1 << ", " << input2 << ", " << input3;
                    text_person1.setString(s.str());
                    text_person1.setCharacterSize(20);
                    text_person1.setPosition(330, 65);
                    textBox1.clearInput();
                    textBox2.clearInput();
                    textBox3.clearInput();
                }
                if (book2_button_hovered) {
                    text_person2.setFont(font);
                    std::stringstream s1;
                    s1 << input1_1 << ", " << input1_2 << ", " << input1_3;
                    text_person2.setString(s1.str());
                    text_person2.setCharacterSize(20);
                    text_person2.setPosition(330, 135);
                    textBox1_1.clearInput();
                    textBox1_2.clearInput();
                    textBox1_3.clearInput();
                }
                if (check_button_hovered) {
                    text_checked.setFont(font);
                    std::stringstream s2;
                    bool ch = false;
                    ch = book1.compareBooks(book2, person1, person2);
                    if (ch) {
                        s2 << "Person found:" << endl << person1.getName() << ", " << person1.getDateOfBirth() << ", " << person1.getPhoneNumber();
                    }
                    else {
                        s2 << "People not found!";
                    }
                    text_checked.setString(s2.str());
                    text_checked.setCharacterSize(20);
                    text_checked.setPosition(335, 245);
                }
            }
        }
        window.display();
    }
    
    
    return 0;
}

