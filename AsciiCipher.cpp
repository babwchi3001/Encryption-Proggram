#include "AsciiCipher.hpp"

AsciiCipher::AsciiCipher(Key key): Cipher(key) {}

std::string AsciiCipher::getCipherTypeString() const
{
  return "ASCII";
}

std::string AsciiCipher::encrypt(const std::string& plain_text)
{

std::string converted_text = preparePlainText(plain_text);
Key mod_key = Cipher::getKey() % 10;
std::string encrypted_text = "";
for(auto letter: converted_text)
{
  Key new_key = static_cast<Key>(letter)+mod_key;
  std::string chart_str = std::to_string(new_key);
  encrypted_text += chart_str + " ";
 // std::cout<<mod_key<<std::endl;
}
encrypted_text.pop_back() ;
return encrypted_text;
}

std::string AsciiCipher::decrypt(const std::string& cipher_text)
{
  int decimal = 10;
  Key mod_key = Cipher::getKey() % decimal;
  std::string decrypt_text = "";
  std::string dec_character = "";
  for(char text_char: cipher_text)
  {
    if(text_char == ' ')
    {
      decrypt_text += static_cast<char>(std::stoi(dec_character) - mod_key);
      dec_character = "";
      continue;
    }
    dec_character += text_char;
  }
  decrypt_text += static_cast<char>(std::stoi(dec_character) - mod_key);
  return decrypt_text;

}
