#include "Config.hpp"

Config::Config(const std::string &filename)
{
  file_.open(filename,std::ios_base::in | std::ios_base::out);
  filename_ = filename;
  modified_ = false;

  std::vector<std::vector<std::string>> config_check;
  std::string contacts_line;
  std::string full_file;

  while(std::getline(file_, contacts_line))
  {
    full_file = full_file + contacts_line + "\n";
  }
  config_check = User::configToVector(full_file);
  std::string name;
  std::string password;
  int count = 0;
  for(auto user : config_check)
  {
    name = user[0];
    password = user[1];
    User* new_user = new User(name,password);
    users_.push_back(new_user);
    count++;
  }
}

void Config::setConfigModified()
{
modified_ = true;
}

bool Config::isOpen() const
{
if(file_.is_open())
  return true;
else
  return false;
}

std::string Config::getFileName()
{
  return filename_;
}

bool Config::parseFile()
{
  std::fstream my_file;
  my_file.open(filename_, std::ios_base::in);
std::vector<std::vector<std::string>> config_check;
std::string contacts_line;
std::string full_file;

  while(std::getline(my_file, contacts_line))
  {
    full_file = full_file + contacts_line + "\n";
  }

config_check = User::configToVector(full_file);

bool contact_is_user = false;
for(size_t us_count = 0; us_count < config_check.size();us_count++)
{
  /// Es darf keine zwei Einträge in der Konfigurationsdatei mit dem gleichen Benutzernamen geben.
  std::string benutzer = config_check[us_count][0];
  size_t count_check = 0;
  for(auto my_user :config_check)
  {
    if(count_check == us_count)
    {
      count_check++;
      continue;
    }
    if(my_user[0] == benutzer)
    {
      //std::cout<<"HERE 1"<<std::endl;
      return false;
    }
    for(auto fuckery : config_check)
    {
      for(auto string_check : fuckery)
      {

        for(auto a:string_check)
        {
          if(!std::isalpha(a))
          {
            //std::cout<<"HERE 2"<<std::endl;
            return false;
          }        }

        break;
      }
    }

    count_check ++;
  }

  /// Ein:e Benutzer:in darf sich nicht selbst als Kontakt haben.
  bool contact_flag = false;
  for(auto contact_details : config_check[us_count])
  {
    if((config_check[us_count][0] == contact_details) && contact_flag)
    {
      //std::cout<<"HERE 3"<<std::endl;
      return false;
    }    contact_flag = true;
  }
  contact_is_user = false;
  //// FOR POSHT DUHET RREGULLUAR
  for(size_t inner_counter = 2; inner_counter < config_check[us_count].size();inner_counter += 3)
  {
    std::string cur_contact = config_check[us_count][inner_counter];

    /// Jeder Kontakt muss selbst ein:e Benutzer:in sein.
    for(auto user_check : config_check)
    {
      if(cur_contact == user_check[0])
      {
        contact_is_user = true;
        break;
      }
    }
    if(!contact_is_user)
    {
      //std::cout<<"HERE 4"<<std::endl;
      return false;
    }
    /// Jeder Kontakt darf maximal einmal pro Kontaktliste vorkommen.
    int contact_counter = 0;
    for(size_t new_inner_counter = 2 ; new_inner_counter < config_check[us_count].size(); new_inner_counter += 3)
    {
      if(new_inner_counter > 2)
      {
        if(cur_contact == config_check[us_count][new_inner_counter])
        {
          contact_counter++;
          if(contact_counter > 1)
          {
            //std::cout<<"HERE 5"<<std::endl;
            return false;
          }
        }
      }
    }
  }
}

/// Jeder Kontakt einer:eines Benutzers:Benutzerin muss die:den Benutzer:in selbst wieder als Kontakt haben. (Symmetrie)
bool symmetric = false;
size_t user_pos = 0;
for(auto users : config_check)
{
  std::string curr_user = users[user_pos];
  for(size_t contact_counter = 2; contact_counter < users.size(); contact_counter += 3)
  {
    std:: string curr_contact = users[contact_counter];
    for(auto user_contact_check : config_check)
    {
      if(curr_contact == user_contact_check[user_pos])
      {
        for(size_t new_contact_counter = 2; new_contact_counter < users.size(); new_contact_counter += 3)
        {
          if(user_contact_check[new_contact_counter] == curr_user)
          {
            symmetric = true;
            break;
          }
        }
      }
    }
  }
  if(!symmetric)
  {
   // std::cout<<"HERE 6"<<std::endl;
    return false;
  }
}
return true;
}

bool Config::containsUser(const std::string &name) const
{
bool user_found = false;
for(auto user : users_)
{
  if(user->getName() == name)
    user_found = true;

}
if(!user_found)
  return false;

return true;
}

User* Config::getUser(const std::string &name) const
{
  for(auto user : users_)
  {
    if(user->getName() == name)
      return user;
  }
  return nullptr;
}

User* Config::registerUser(const std::string &name, const std::string &password)
{
User* new_user = new User(name,password);
users_.push_back(new_user);
modified_ = true;
  return new_user;
}

User* Config::loginUser(const std::string &name, const std::string &password) const
{
  bool pass_match = false;std::fstream my_file;
  my_file.open(filename_, std::ios_base::in);
  std::vector<std::vector<std::string>> config_check;
  std::string contacts_line;
  std::string full_file;
  Key key_key = 0;
  bool nothing_checker = false;
  CipherType type;
  User* new_user;
  while(std::getline(my_file, contacts_line))
  {
    full_file = full_file + contacts_line + "\n";
  }

  config_check = User::configToVector(full_file);
  for(auto user : users_)
  {
    if(user->getName() == name)
     pass_match = user->verifyPassword(password);

  for(auto contacts : config_check)
  {
    for(size_t cont_count = 2;cont_count< contacts.size();cont_count += 3)
    {

      if(contacts[0] == user->getName())
      {
        if(contacts[cont_count+1] == "ASCII")
        {

          type = CipherType::ASCII_CIPHER;
        }
        if(contacts[cont_count+1] == "CAESAR")
        {
          type = CipherType::CAESAR_CIPHER;
        }
        if(contacts[cont_count+1] == "NONE")
        {
          type = CipherType::NONE_CIPHER;
        }
        nothing_checker = Utils::convertHexTo64BitNumber(contacts[cont_count+2],key_key);
        for(auto reg_cont: config_check)
        {
          if(reg_cont[0] == contacts[cont_count])
          {
            new_user = new User(reg_cont[0],reg_cont[1]);
          }
        }
        user->addContact(new_user,type,key_key);
      }
    }
  }
    if(pass_match)
      return user;
  }
  return nullptr;
}

bool Config::updateConfigFile()
{
  file_.open(getFileName(), std::ios_base::in | std::ios_base::out);
  if(!isOpen())
    return false;
  if(!modified_)
    return true;
  modified_ = false;

  std::string config_string;
  size_t key_length = 16;
  for(auto user : users_)
  {
    std::string user_name = user->getName();
    std::string user_password = user->getPassword();
    config_string += (user_name + ";" + user_password + ";");
    auto const& contacts_map = user->getContacts();
    for(auto contact : contacts_map)
    {
      User* contact_user = contact.first;
      Cipher* contact_cipher = contact.second;
      std::string contact_name = contact_user->getName();
      std::string cipher_type = contact_cipher->getCipherTypeString();

      Key cipher_key = contact_cipher->getKey();
      std::stringstream stringg_stream;
      stringg_stream << std::hex << cipher_key;
      std::string cipher_key_string = stringg_stream.str();
      if(cipher_key_string.size() < key_length)
        cipher_key_string = "0" + cipher_key_string;

      config_string += (contact_name + ":" + cipher_type + "," + cipher_key_string + ";");
    }
    config_string += "\n";
  }
  file_<< config_string;
  file_.close();

  return true;

}