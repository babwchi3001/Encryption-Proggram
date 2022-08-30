#include "NoneCipher.hpp"

NoneCipher::NoneCipher(Key key) : Cipher(key) {}

std::string NoneCipher::getCipherTypeString() const
{
  return "NONE";
}

std::string NoneCipher::encrypt(const std::string& plain_text)
{
  std::string converted_text = preparePlainText(plain_text);
  return converted_text;
}

std::string NoneCipher::decrypt(const std::string& cipher_text)
{
  return cipher_text;
}