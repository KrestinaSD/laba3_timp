#include  "coder.h"

using namespace std;

int coder::getValidKey(std::string ws_key)
{
	if (ws_key.empty())
		throw cipher_error("Empty key");
	for (char c : ws_key) {
        if (std::ispunct(c)) {
            throw cipher_error(std::string("Invalid key. Key should not contain punctuation"));
        }
    }	
	
	int key = std::stoi(ws_key);
	if (key<=0) {
		throw cipher_error(std::string("Invalid key. Enter a number > 0"));
	} 
	if (key >= 33) {
		throw cipher_error(std::string("Invalid key. Enter a number < 33"));
	}
	return key;
}

std::string coder::getValidOpenText(std::string ws_open_text)
{
	std::string tmp;
	for (auto c:ws_open_text) {
		if (isalpha(c) != 0) {
				char upper_c = toupper(c);
        		tmp.push_back(upper_c);
			}
	}
	if (tmp.empty())
		throw cipher_error("Input text is missing");
	return tmp;
}

std::string coder::getValidCipherText(const std::string & ws_cipher_text)
{
	if (ws_cipher_text.empty())
		throw cipher_error("Output text is missing");

	for (auto c:ws_cipher_text) {
		if (!isupper(c)) {
				throw cipher_error(std::string("Invalid text"));
		}
	}
	return ws_cipher_text;
}


coder::coder(std::string ws_key)
{
	key1 = getValidKey(ws_key);
}

string coder::encrypt(std::string open_text) // шифрование
{
    string tabl = getValidOpenText(open_text);
    if (tabl.length() <= key1){
    	throw cipher_error(std::string("Key > length stroka"));
    }
    string tr = tabl;
    int len, nstrok, index, x;
    len = tabl.length(); // введенный текст
    nstrok = (len - 1) / key1 + 1; // количество столбцов
    x = 0;
    for (int i = key1; i > 0; i--) { // столбцы
        for (int j = 0; j < nstrok; j++) { // строки
            index = i+key1*j;
            if (index-1 < len) {
                tr[x] = tabl[index-1];
                x++;
            }
        }
    }
    return tr;
}

string coder::decrypt(const std::string& cipher_text) // расшифрование
{
    string tabl = getValidCipherText(cipher_text);
    if (tabl.length() <= key1){
    	throw cipher_error(std::string("Key > length stroka"));
    }
    int len, nstrok, index, x;
    len = tabl.length();
    nstrok = (len - 1) / key1 + 1; // количество столбцов
    x = 0;
    for (int i = key1; i > 0; i--) { // столбцы
        for (int j = 0; j < nstrok; j++) { // строки
            index = i+key1*j;
            if (index-1 < len) {
                tabl[index-1] = cipher_text[x];
                x++;
            }
        }
    }
    return tabl;
}

