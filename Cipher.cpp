#include "Cipher.hpp"

Cipher::Cipher(Key key):key_(key){}

Key Cipher::getKey()
{
  return key_;
}

std::string Cipher::preparePlainText(const std::string& plain_text)
{
  std::string converted_text;
  char current_char = 0;
for(auto &a : plain_text)
{
  if(a ==' ')
    continue;

  current_char = toupper(a);
  converted_text += current_char;
}
  return converted_text;
}

CipherType Cipher::getCipherType(const std::string& type)
{
  if(type == "NONE")
    return CipherType::NONE_CIPHER;
  else if(type == "ASCII")
    return CipherType::ASCII_CIPHER;
  else if(type == "CAESAR")
    return CipherType::CAESAR_CIPHER;
  else
    return CipherType::INVALID;
}