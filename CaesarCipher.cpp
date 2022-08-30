#include "CaesarCipher.hpp"

CaesarCipher::CaesarCipher(Key key) : Cipher(key) {}

std::string CaesarCipher::getCipherTypeString() const {
  return "CAESAR";
}

std::string CaesarCipher::encrypt(const std::string &plain_text)
{
  std::string text_to_convert = preparePlainText(plain_text);

  Key key_value = Cipher::getKey();
  int devision_value = 14;
  int alphabet_letter = 26;
  Key new_key_value = 0;
  Key prev_key = 0;
  Key prev_key_value = 0;
  int count = 0;
  std::string converted_text;
  for(auto letter : text_to_convert)
  {
    if(count == 8)
    {
      new_key_value = key_value;
      devision_value = 14;
      count = 0;
    }

    if(count != 7)
      new_key_value = key_value / (pow(10,devision_value));
    else
      new_key_value = key_value;

    if(!count)
      prev_key = new_key_value;
    else
      prev_key = new_key_value - prev_key_value;

    letter += (prev_key % alphabet_letter);

    if(static_cast<int>(letter) > 90)
      letter -= 26;

    converted_text += letter;
    count++;
    prev_key_value = new_key_value*100;
    devision_value -= 2;
  }

  return converted_text;
}

std::string CaesarCipher::decrypt(const std::string &cipher_text)
{
  std::string text_to_convert = cipher_text;
  Key key_value = Cipher::getKey();
  int devision_value = 14;
  int alphabet_letter = 26;
  Key new_key_value = 0;
  int prev_key = 0;
  Key prev_key_value = 0;
  int count = 0;
  std::string converted_text;
  for(auto& letter : text_to_convert)
  {
    if(count == 8)
    {
      new_key_value = key_value;
      devision_value = 14;
      count = 0;
    }

    if(count != 7)
      new_key_value = key_value / (pow(10,devision_value));
    else
      new_key_value = key_value;

    if(!count)
      prev_key = new_key_value;
    else
      prev_key = new_key_value - prev_key_value;

    letter -= (prev_key % alphabet_letter);

    if(letter < 65)
      letter += 26;

    converted_text += letter;
    count++;
    prev_key_value = new_key_value*100;
    devision_value -= 2;
  }

  return converted_text;
}