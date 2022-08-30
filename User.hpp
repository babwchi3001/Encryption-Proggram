
#ifndef OOP1SS22_A1_227_USER_HPP
#define OOP1SS22_A1_227_USER_HPP
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "Cipher.hpp"
#include "AsciiCipher.hpp"
#include "CaesarCipher.hpp"
#include "NoneCipher.hpp"
#include "Utils.hpp"
#include "IO.hpp"

class User{
private:
  std::string name_;
  std::string password_;
  std::map<User*, Cipher*, bool(*)(User*, User*)> contacts_;
public:

  User(const std::string& name, const std::string& password);

  ~User();

  std::string getName() const;

  std::string getPassword() const;

  const std::map<User*, Cipher*, bool(*)(User*, User*)>& getContacts() const;

  bool verifyPassword(const std::string& password) const;

  bool hasContact(const std::string& name) const;

  void addContact(User* contact, CipherType type, Key key);

  static std::vector<std::vector<std::string>>  configToVector(const std::string& config_file_content);

  bool sendMessage(const std::string& recipient, const std::string& filename, const std::string& plain_text) const;

  bool readMessage(const std::string& filename) const;

};

#endif //OOP1SS22_A1_227_USER_HPP
