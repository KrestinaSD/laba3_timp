#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"
#include "modAlphaCipher.cpp"
#include <iostream>
#include <locale>
#include <codecvt>

using namespace std;
SUITE(KeyTest)
{

    TEST(LargeLetters) {
        modAlphaCipher test(L"УТИПУТИ");
        CHECK(true);
    }
    TEST(SmallLetters) {
        modAlphaCipher test(L"яустал");
        CHECK(true);
    }
    TEST(LargeAndSmallLetters) {
        modAlphaCipher test(L"ЯУСТал");
        CHECK(true);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher test(L""), cipher_error);
    }
    TEST(Key_with_a_space) {
        CHECK_THROW(modAlphaCipher test(L"я устал"), cipher_error);
    }
    TEST(Key_with_number) {
        CHECK_THROW(modAlphaCipher test(L"я3устал"), cipher_error);
    }
    TEST(Key_with_invalid_characters_special) {
        CHECK_THROW(modAlphaCipher test(L"я.устал"), cipher_error);
    }
}

struct KeyAB_fixture {
        modAlphaCipher m{L"АВ"};
    };

struct KeyAB_fixture_MAX {
    modAlphaCipher mM{L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"};
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyAB_fixture, LargeLetters) {
    	wstring open_text = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        wstring result_correct = L"АГВЕДЖЁИЗКЙМЛОНРПТСФУЦХШЧЪЩЬЫЮЭАЯ";
        CHECK_EQUAL(true, m.encrypt(open_text) == result_correct);
    }
    TEST_FIXTURE(KeyAB_fixture, SmallLetters) {
        wstring open_text = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
        wstring result_correct = L"АГВЕДЖЁИЗКЙМЛОНРПТСФУЦХШЧЪЩЬЫЮЭАЯ";
        CHECK_EQUAL(true, m.encrypt(open_text) == result_correct);
    }
    TEST_FIXTURE(KeyAB_fixture,NumberInText ) {
        wstring open_text = L"гавайская123пицца";
        CHECK_THROW(m.encrypt(open_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithSpecialSymbol) {
        wstring open_text = L"гавайская/пицаца";
        CHECK_THROW(m.encrypt(open_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithASpace ) {
        wstring open_text = L"гавайская пицца";
        CHECK_THROW(m.encrypt(open_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture_MAX, maxkluch) {
        wstring open_text = L"ГАВАЙСКАЯПИЦЦА";
        wstring result_correct = L"ГБДГНЦРЖЖШТБВМ";
        CHECK_EQUAL(true, mM.encrypt(open_text) == result_correct);
       
	}
}
SUITE(DecryptTest)
{
    TEST_FIXTURE(KeyAB_fixture, LargeLetters) {
        wstring cipher_text = L"АГВЕДЖЁИЗКЙМЛОНРПТСФУЦХШЧЪЩЬЫЮЭАЯ";
        wstring result_correct = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        CHECK_EQUAL(true, m.decrypt(cipher_text) == result_correct);
    }
    TEST_FIXTURE(KeyAB_fixture, Smallletters) {
        wstring cipher_text = L"агведжёизкймлонрптсфуцхшчъщьыюэая";
        wstring result_correct = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        CHECK_EQUAL(true, m.decrypt(cipher_text) == result_correct);
    }
    TEST_FIXTURE(KeyAB_fixture,LargeAndSmallLetters ) {
        wstring cipher_text = L"ЗДраВстуЙТЕ";
        wstring result_correct = L"ЗВРЮВПТСЙРЕ";
        CHECK_EQUAL(true, m.decrypt(cipher_text) == result_correct);
    }

    TEST_FIXTURE(KeyAB_fixture, EmptyText) {
        wstring cipher_text = L"";
        CHECK_THROW(m.decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithNumber) {
        wstring cipher_text = L"гавайская123пицца";
         CHECK_THROW(m.decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithSymbol) {
        wstring cipher_text = L"гавайская/пицаца";
        CHECK_THROW(m.decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithASpace ) {
        wstring cipher_text = L"гавайская пицца";
         CHECK_THROW(m.decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture_MAX, maxkluch) {
        wstring  cipher_text = L"ГБДГНЦРЖЖШТБВМ";
        wstring result_correct = L"ГАВАЙСКАЯПИЦЦА";
        CHECK_EQUAL(true, mM.decrypt(cipher_text) == result_correct);
       
	}
}

int main()
{
    return UnitTest::RunAllTests();
}

