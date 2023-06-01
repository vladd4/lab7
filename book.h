#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include "graphics.h"
using namespace sf;
using namespace std;

class Person {
private:
    std::string name;
    std::string dateOfBirth;
    std::string phoneNumber;

public:
    Person() {};
    Person(const std::string& name, const std::string& dateOfBirth, const std::string& phoneNumber)
        : name(name), dateOfBirth(dateOfBirth), phoneNumber(phoneNumber) {}

    void setName(string s) {
        name = s;
    }
    void setDate(string s) {
        dateOfBirth = s;
    }
    void setNumber(string s) {
        phoneNumber = s;
    }
    const std::string& getName() const {
        return name;
    }

    const std::string& getDateOfBirth() const {
        return dateOfBirth;
    }

    const std::string& getPhoneNumber() const {
        return phoneNumber;
    }
    void print() {
        cout << "Person: " << this->getName() << ", date of birth: " << this->getDateOfBirth() << ", number: " << this->getPhoneNumber() << endl;
    }
};

class AddressBook {
private:
    std::string fileName;

public:
    AddressBook(const std::string& fileName)
        : fileName(fileName) {}

    void addPerson(const Person& person) {
        std::ofstream file(fileName, std::ios::binary | std::ios::app);
        if (!file) {
            std::cerr << "Failed to open file: " << fileName << std::endl;
            return;
        }

        file.write(reinterpret_cast<const char*>(&person), sizeof(Person));
        file.close();
    }

    bool compareBooks(const AddressBook& otherBook, Person p1, Person p2) {
        if (p1.getName() == p2.getName() &&
            p1.getDateOfBirth() == p2.getDateOfBirth() &&
            p1.getPhoneNumber() == p2.getPhoneNumber()) {
            return true;
        }
        else {
            return false;
        }
        remove("address_book1.bin");
        remove("address_book2.bin");
    }
};

void inputFields(Person& p) {
    string n;
    cout << "Enter name: ";
    cin >> n;
    p.setName(n);
    cout << "Enter date: ";
    cin >> n;
    p.setDate(n);
    cout << "Enter number: ";
    cin >> n;
    p.setNumber(n);
}


