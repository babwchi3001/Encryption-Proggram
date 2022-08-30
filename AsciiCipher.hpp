#ifndef OOP1SS22_A1_227_ASCIICIPHER_HPP
#define OOP1SS22_A1_227_ASCIICIPHER_HPP
#include "Cipher.hpp"

class AsciiCipher : public Cipher{
public:
  AsciiCipher(Key key);

  ~AsciiCipher() = default;

  std::string getCipherTypeString() const override;

  std::string encrypt(const std::string& plain_text) override;


  std::string decrypt(const std::string& cipher_text) override;

};

#endif //OOP1SS22_A1_227_ASCIICIPHER_HPP
