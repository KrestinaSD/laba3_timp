#pragma once
#include <string>
#include <iostream>
#include <cctype>
#include <codecvt>

class coder
{
private:
	
	int key1;
   
    
public:
    coder()=delete; // запрет конструктора без параметров
    coder(std::string ws_key);
    std::string encrypt(std::string open_text); // зашифрование
    std::string decrypt(const std::string& cipher_text); // расшифрование
    #if _UNITTEST_ != 1
    int getKey() const { //создан для модульных тестов
        return key1;
    }
    #endif
    int getValidKey(std::string ws_key);
    std::string getValidOpenText(std::string  ws_open_text);
    std::string getValidCipherText(const std::string & ws_cipher_text);
};

class cipher_error: public std::invalid_argument {
public:
	explicit cipher_error (const std::string& what_arg):
		std::invalid_argument(what_arg) {}
	explicit cipher_error (const char* what_arg):
		std::invalid_argument(what_arg) {}
};
