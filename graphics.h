#pragma once
#include "book.h"
#include <sstream>
#define book1_button_hovered (sf::Mouse::getPosition(window).x>btn_book1.getGlobalBounds().left&&sf::Mouse::getPosition(window).x<btn_book1.getGlobalBounds().left+btn_book1.getGlobalBounds().width&&sf::Mouse::getPosition(window).y>btn_book1.getGlobalBounds().top&&sf::Mouse::getPosition(window).y<btn_book1.getGlobalBounds().top+btn_book1.getGlobalBounds().height)
#define book2_button_hovered (sf::Mouse::getPosition(window).x>btn_book2.getGlobalBounds().left&&sf::Mouse::getPosition(window).x<btn_book2.getGlobalBounds().left+btn_book2.getGlobalBounds().width&&sf::Mouse::getPosition(window).y>btn_book2.getGlobalBounds().top&&sf::Mouse::getPosition(window).y<btn_book2.getGlobalBounds().top+btn_book2.getGlobalBounds().height)
#define check_button_hovered (sf::Mouse::getPosition(window).x>btn_check.getGlobalBounds().left&&sf::Mouse::getPosition(window).x<btn_check.getGlobalBounds().left+btn_check.getGlobalBounds().width&&sf::Mouse::getPosition(window).y>btn_check.getGlobalBounds().top&&sf::Mouse::getPosition(window).y<btn_check.getGlobalBounds().top+btn_check.getGlobalBounds().height)

sf::Color Dark_Blue_Grey = sf::Color(33, 42, 47);
sf::Color Dark_Blue_Grey_Hover = sf::Color(27, 34, 38);
sf::Color Grey = sf::Color(128, 128, 128);

sf::RectangleShape btn_book1(sf::Vector2f(260, 50));
sf::RectangleShape btn_book2(sf::Vector2f(260, 50));
sf::RectangleShape btn_check(sf::Vector2f(260, 50));
sf::RectangleShape board_show(sf::Vector2f(441, 171));
sf::RectangleShape board_check(sf::Vector2f(441, 230));


sf::Font font;
sf::Text text_book1, text_book2, text_check, text_title1, text_title2, text_checked, text_person1, text_person2;

void validatePhoneNumber(const std::string& phoneNumber)
{
    if (phoneNumber.length() != 10)
    {
        throw std::invalid_argument("Invalid number (10-digits).");
    }
}

void validateDate(const std::string& date)
{
    if (date[2] != '.' && date[5] != '.')
    {
        throw std::invalid_argument("Invalid date (dd.mm.year).");
    }
}

class TextBox
{
public:
    TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font& font, unsigned int characterSize, sf::Color textColor, sf::Color backgroundColor, std::string placeholderText)
    {
        textbox.setPosition(position);
        textbox.setSize(size);
        textbox.setFillColor(backgroundColor);

        text.setFont(font);
        text.setCharacterSize(characterSize);
        text.setFillColor(textColor);

        cursor.setFillColor(textColor);
        cursor.setSize(sf::Vector2f(2.0f, static_cast<float>(characterSize)));

        isFocused = false;
        showCursor = true;

        placeholder.setFont(font);
        placeholder.setCharacterSize(characterSize);
        placeholder.setFillColor(sf::Color::Black);
        placeholder.setString(placeholderText);
        placeholder.setPosition(position + sf::Vector2f(5.0f, 5.0f));

        this->placeholderText = placeholderText;
    }

    void handleEvent(sf::Event event, std::string &savedText, std::string type)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
            if (textbox.getGlobalBounds().contains(mousePosition))
            {
                isFocused = true;
            }
            else
            {
                isFocused = false;
            }
        }
        else if (event.type == sf::Event::TextEntered && isFocused)
        {
            if (event.text.unicode < 128)
            {
                if (event.text.unicode == '\b' && !inputText.empty())
                {
                    inputText.pop_back();
                }
                else if (event.text.unicode != '\b')
                {
                    if (event.text.unicode == '\r' || event.text.unicode == '\n')
                    {
                        try
                        {
                            // Перевірка на правильність введення номеру телефону
                            if (type == "number") {
                                validatePhoneNumber(inputText);
                            }
                            else if (type == "date") {
                                validateDate(inputText);
                            }
                            placeholder.setCharacterSize(20);
                            placeholder.setString(placeholderText);
                            placeholder.setFillColor(sf::Color::Black);

                            // Зберігання введеного тексту
                            savedText = inputText;
                        }
                        catch (const std::exception& e)
                        {
                            // Обробка виключної ситуації - неправильний номер телефону
                            std::cout << "Error: " << e.what() << std::endl;
                            // Очищення поля введення
                            inputText.clear();
                            placeholder.setString(e.what());
                            placeholder.setCharacterSize(19);
                            placeholder.setFillColor(sf::Color::Red);
                        }
                    }
                    else
                    {
                        inputText += static_cast<char>(event.text.unicode);
                    }
                }
            }
        }
    }
    void clearInput() {
        inputText.clear();
    }
    void update(sf::Time deltaTime)
    {
        cursorTimer += deltaTime;
        if (cursorTimer.asSeconds() >= 0.5f)
        {
            cursorTimer = sf::Time::Zero;
            showCursor = !showCursor;
        }

        if (isFocused)
        {
            cursor.setPosition(text.getPosition() + sf::Vector2f(text.getLocalBounds().width, 0.0f));
        }

        
        if (inputText.empty())
        {
            placeholder.setFillColor(sf::Color::Black); 
        }
        else
        {
            placeholder.setFillColor(sf::Color::Transparent);
        }
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(textbox);

        if (inputText.empty())
        {
            placeholder.setPosition(textbox.getPosition() + sf::Vector2f(5.0f, 5.0f));
            window.draw(placeholder);
        }
        else
        {
            text.setString(inputText);
            text.setPosition(textbox.getPosition() + sf::Vector2f(5.0f, 5.0f));
            window.draw(text);
        }

        if (isFocused && showCursor && !inputText.empty())
        {
            window.draw(cursor);
        }
    }

    void setPosition(sf::Vector2f position)
    {
        textbox.setPosition(position);
        text.setPosition(position + sf::Vector2f(5.0f, 5.0f));
    }

    void setSize(sf::Vector2f size)
    {
        textbox.setSize(size);
    }

    void setText(std::string str)
    {
        inputText = str;
    }

    std::string getText()
    {
        return inputText;
    }
    friend void validatePhoneNumber(const std::string& phoneNumber);
    friend void validateDate(const std::string& date);

private:
    sf::RectangleShape textbox;
    sf::Text text;
    sf::RectangleShape cursor;
    std::string inputText;
    bool isFocused;
    bool showCursor;
    sf::Time cursorTimer;
    sf::Text placeholder;
    std::string placeholderText;
};

void drawInterface() {
	btn_book1.setFillColor(Dark_Blue_Grey);
	btn_book1.setPosition(30, 150);

	btn_book2.setFillColor(Dark_Blue_Grey);
	btn_book2.setPosition(30, 350);

	btn_check.setFillColor(Dark_Blue_Grey);
	btn_check.setPosition(30, 410);

	board_show.setFillColor(Grey);
	board_show.setPosition(325, 30);

	board_check.setFillColor(Grey);
	board_check.setPosition(325, 230);

    

	font.loadFromFile("MontserratAlternates-ExtraLight.otf");
	text_book1.setFont(font);
	text_book1.setString(L"Записати в книгу 1");
	text_book1.setCharacterSize(20);
	text_book1.setPosition(45, 160);

	text_book2.setFont(font);
	text_book2.setString(L"Записати в книгу 2");
	text_book2.setCharacterSize(20);
	text_book2.setPosition(45, 360);

	text_check.setFont(font);
	text_check.setString(L"Перевірити людей");
	text_check.setCharacterSize(20);
	text_check.setPosition(45, 420);

	text_title1.setFont(font);
	text_title1.setString(L"Книга 1:");
	text_title1.setCharacterSize(20);
	text_title1.setPosition(330, 35);

	text_title2.setFont(font);
	text_title2.setString(L"Книга 2:");
	text_title2.setCharacterSize(20);
	text_title2.setPosition(330, 105);

};



void update_textbox(TextBox textBox1, TextBox textBox2, TextBox textBox3, TextBox textBox1_1, TextBox textBox1_2, TextBox textBox1_3, sf::Time deltaTime) {
    textBox1.update(deltaTime);
    textBox2.update(deltaTime);
    textBox3.update(deltaTime);
    textBox1_1.update(deltaTime);
    textBox1_2.update(deltaTime);
    textBox1_3.update(deltaTime);
}