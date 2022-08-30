#ifndef OOP1SS22_A1_227_CONFIG_HPP
#define OOP1SS22_A1_227_CONFIG_HPP
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "User.hpp"

class Config{
private:
  std::fstream file_;
  std::string filename_;
  bool modified_;
  std::vector<User*> users_;
public:
  Config(const std::string& filename);

  ~Config() = default;

  void setConfigModified();

  std::string getFileName();

  bool isOpen() const;

  bool parseFile();

  bool containsUser(const std::string& name) const;

  User* getUser(const std::string& name) const;

  User* registerUser(const std::string& name, const std::string& password);

  User* loginUser(const std::string& name, const std::string& password) const;

  bool updateConfigFile();



};
#endif //OOP1SS22_A1_227_CONFIG_HPP
