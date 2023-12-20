#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include "coder.h"
#include "coder.cpp"
#include <locale>
#include <codecvt>
#include <string>


SUITE (KeyTest)
{
    TEST (ValidKey) {
    	std::string validKey = "4";
    	coder test(validKey);
    	CHECK_EQUAL(4, test.getKey());
    }
    TEST(EmptyKey) {
    	std::string emptyKey = "";
        CHECK_THROW(coder test(emptyKey), cipher_error);
    }
    TEST(NegativeKey) {
    	std::string negaKey = "-5";
        CHECK_THROW(coder test(negaKey), cipher_error);
    }
    TEST(LargeKey) {
    	std::string megaKey = "55";
        CHECK_THROW(coder test(megaKey), cipher_error);
    }
    TEST(SmallKey) {
    	std::string maloKey = "0";
        CHECK_THROW(coder test(maloKey), cipher_error);
    }
    TEST(BadKey) {
    	std::string verybadKey = "1!!";
        CHECK_THROW(coder test(verybadKey), cipher_error);
    }
}

SUITE(EncryptTest)
{
    TEST(Valid_Eng_Text) {
        std::string validKey = "4";
    	coder c(validKey);
    	std::string open_text = "HELLO WORLD";
    	std::string expected_encrypted_text = "LRLOEWDHOL";
    	std::string encrypted_text = c.encrypt(open_text);
    	CHECK_EQUAL(expected_encrypted_text, encrypted_text);
    }
    
    TEST(LowText) {
    	std::string validKey = "4";
    	coder c(validKey);
    	std::string open_text = "hello world";
    	std::string expected_encrypted_text = "LRLOEWDHOL";
    	std::string encrypted_text = c.encrypt(open_text);
    	CHECK_EQUAL(expected_encrypted_text, encrypted_text); 
    }

    TEST(EmptyText) {
    	std::string validKey = "4";
    	coder c(validKey);
    	std::string open_text = ""; 	
        CHECK_THROW(c.encrypt(open_text), cipher_error);
    }
    
    TEST(WithoutLetters) {
    	std::string validKey = "4";
    	coder c(validKey);
    	std::string open_text = "!*><?/,.123"; 	
        CHECK_THROW(c.encrypt(open_text), cipher_error);
    }
    TEST(WithNumber) {
    	std::string validKey = "4";
    	coder c(validKey);
    	std::string open_text = "HELL21O";  	
        std::string expected_encrypted_text = "LLEHO";
    	std::string encrypted_text = c.encrypt(open_text);
    	CHECK_EQUAL(expected_encrypted_text, encrypted_text);
    }   
    TEST(WithBadKey) {
    	std::string validKey = "6";
    	coder c(validKey);
    	std::string open_text = "HELLO";  
    	CHECK_THROW(c.encrypt(open_text), cipher_error);
    } 
}

SUITE(DecryptText)
{
    TEST(ValidTEXTeng) {
    	std::string validKey = "4";
    	coder c(validKey);
    	std::string cipher_text ="LRLOEWDHOL";
    	std::string expected_decrypted_text = "HELLOWORLD";
    	std::string decrypted_text = c.decrypt(cipher_text);
    	CHECK_EQUAL(expected_decrypted_text, decrypted_text);
    }
  
    TEST(LowTEXT) {
    	std::string validKey = "4";
    	coder c(validKey);
    	std::string cipher_text = "lrloewdhol";
    	CHECK_THROW(c.decrypt(cipher_text), cipher_error);
    }
    
    TEST(SpaceTEXT) {
        std::string validKey ="4";
    	coder c(validKey);
    	std::string cipher_text = "HEMDKN BJHFN";
    	CHECK_THROW(c.decrypt(cipher_text), cipher_error);
    }
    TEST(EmptyTEXT) {
        std::string validKey = "4";
    	coder c(validKey);
    	std::string cipher_text = "";
    	CHECK_THROW(c.decrypt(cipher_text), cipher_error);
    }
    
    TEST(TextNumberText) {
        std::string validKey = "4";
    	coder c(validKey);
    	std::string cipher_text = "HEL123LO";
    	CHECK_THROW(c.decrypt(cipher_text), cipher_error);
    }
    TEST(TextSymbolText) {
        std::string validKey = "4";
    	coder c(validKey);
    	std::string cipher_text = "HELLO!!!";
    	CHECK_THROW(c.decrypt(cipher_text), cipher_error);
    }
    TEST(WithBadKey) {
    	std::string validKey = "6";
    	coder c(validKey);
    	std::string open_text = "HELLO";  
    	CHECK_THROW(c.decrypt(open_text), cipher_error);
    }
}


int main()
{
    return UnitTest::RunAllTests();
}
