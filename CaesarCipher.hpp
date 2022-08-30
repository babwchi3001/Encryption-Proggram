#ifndef OOP1SS22_A1_227_CAESARCIPHER_HPP
#define OOP1SS22_A1_227_CAESARCIPHER_HPP

#include "Cipher.hpp"
#include "Utils.hpp"
#include <cmath>

class CaesarCipher : public Cipher {
public:

  CaesarCipher(Key key);

  ~CaesarCipher() = default;

  std::string getCipherTypeString() const override;


  std::string encrypt(const std::string &plain_text) override;


  std::string decrypt(const std::string &cipher_text) override;

};

#endif //OOP1SS22_A1_227_CAESARCIPHER_HPP
