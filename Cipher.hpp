

#ifndef OOP1SS22_A1_227_CIPHER_HPP
#define OOP1SS22_A1_227_CIPHER_HPP

#include <cstdint>
#include <iostream>
#include <string>

enum class CipherType { INVALID, NONE_CIPHER, ASCII_CIPHER, CAESAR_CIPHER };

typedef uint64_t Key;

class Cipher{
private:
  Key key_;
public:
  Cipher(Key key);

  virtual ~Cipher() = default;

  Key getKey();

  virtual std::string getCipherTypeString() const = 0;

  static std::string preparePlainText(const std::string& plain_text) ;

  virtual std::string encrypt(const std::string& plain_text) = 0;

  virtual std::string decrypt(const std::string& cipher_text) = 0;

  static CipherType getCipherType(const std::string& type);
};
#endif //OOP1SS22_A1_227_CIPHER_HPP
