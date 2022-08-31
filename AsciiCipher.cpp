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
  }
  encrypted_text.pop_back();
  return encrypted_text;
}

std::string AsciiCipher::decrypt(const std::string& cipher_text)
{
  int decimal = 10;
  Key mod_key = Cipher::getKey() % decimal;
  std::string decrypt_text = "";
  std::string dec_character = "";
  std::string new_text = cipher_text;
  std::string final_text;
  int counter = 0;
  for(auto letter: new_text)
  {
    final_text+= letter;
    counter++;
    if(counter == 2)
    {
      final_text += " ";
      counter = 0;
    }
  }
  new_text.pop_back();
  for(auto text_char: new_text)
  {
    if(text_char == ' ')
    {
      //int converted = std::stoi(dec_character);
      decrypt_text += static_cast<char>(std::stoi(dec_character) - mod_key);
      //decrypt_text += static_cast<char>(converted-mod_key);
      dec_character = "";
      continue;
    }
    dec_character += text_char;
  }
  decrypt_text += static_cast<char>(std::stoi(dec_character) - mod_key);
  return decrypt_text;

}