#include "User.hpp"
User::User(const std::string& name, const std::string& password) :contacts_(Utils::sortContactsAlphabetically)
{
  name_ = name;
  password_ = password;
}

std::string User::getName() const
{
  return name_;
}

std::string User::getPassword() const
{
  return password_;
}

const std::map<User*, Cipher*, bool(*)(User*, User*)>& User::getContacts() const
{
  return contacts_;
}

bool User::verifyPassword(const std::string& password) const
{
  if(password == password_)
    return true;
  else
    return false;
}

bool User::hasContact(const std::string& name) const
{
for(auto contact : contacts_)
{
  if(name == contact.first->getName())
    return true;
}
  return false;
}

void User::addContact(User* contact, CipherType type, Key key)
{
  Cipher* cipher = nullptr;

  try
  {
    if(type == CipherType::ASCII_CIPHER)
      cipher = new AsciiCipher(key);
    else if(type == CipherType::CAESAR_CIPHER)
      cipher = new CaesarCipher(key);
    else if(type == CipherType::NONE_CIPHER)
      cipher = new NoneCipher(key);

  }
  catch(std::bad_alloc())
  {
    throw std::bad_alloc();
  }
contacts_[contact] = cipher;
}

std::vector<std::vector<std::string>> User::configToVector(const std::string& config_file)
{
  std::vector<std::vector<std::string>> config_to_vector;
  std::vector<std::string> vector_to_vector;
  std::string config_file_content = config_file;
  std::string delimiter = ",:;";
  size_t end = 0;
  size_t begin = 0;
  size_t line_begin = 0;
  size_t delimit_len = delimiter.size() - 2;
  std::string token;
  std::string line_token;
  std::string line_delimiter = "\n";
  size_t line_end = 0;

  while ((end = config_file_content.find_first_of(line_delimiter, begin)) != std::string::npos)
  {
    line_token = config_file_content.substr(begin, end - begin);
    begin = end + delimit_len;
    line_begin = 0;
    while((line_end = line_token.find_first_of(delimiter, line_begin)) != std::string::npos)
    {
      token = line_token.substr(line_begin, line_end - line_begin);
      line_begin = line_end + delimit_len;
      vector_to_vector.push_back(token);
    }
    config_to_vector.push_back(vector_to_vector);
    vector_to_vector.clear();
  }
  return  config_to_vector;
}

bool User::sendMessage(const std::string& recipient, const std::string& filename, const std::string& plain_text) const
{


  std::fstream text_file(filename, std::ios_base::out);
  if(!text_file)
  {
    return false;
  }

  std::string all_upper_text = Cipher::preparePlainText(plain_text);
  std::string contacts_line;
  std::string converted_text;
  Key encryption_key ;
  std::string encryption_type;
  bool count = false;

  for(auto contact : contacts_)
  {
    if(recipient == contact.first->getName())
    {
      encryption_key = contact.second->getKey();
      encryption_type = contact.second->getCipherTypeString();
      count= true;
    }
  }
  if(!count)
  {
    text_file.close();
    return false;
  }
  else
  {
   if(encryption_type == "ASCII")
   {
     AsciiCipher ascii_instance(encryption_key);
     converted_text = ascii_instance.encrypt(all_upper_text);
   }
   if(encryption_type == "CAESAR")
   {
     CaesarCipher caesar_instance(encryption_key);
     converted_text = caesar_instance.encrypt(all_upper_text);
   }
   if(encryption_type == "NONE")
   {
     NoneCipher none_instance(encryption_key);
     converted_text = all_upper_text;
   }

    converted_text = "Recipient: " + recipient + "\n"
                     + "Sender: " + getName() + "\n"
                     + converted_text;
   text_file<<converted_text;
   text_file.close();
   IO::printEncryptedMessage(converted_text);
  }
  return true;
}

bool User::readMessage(const std::string& filename) const
{
std::fstream file_text;
file_text.open(filename,std::ios_base::in | std::ios_base::out);
if(!file_text)
{
  return false;
}

std::string given_text;
std::string full_file;
size_t begin = 0;
size_t end = 0;
std::string line_delimiter = ":\n";
std::string token;
std::vector<std::string> sender_check;


  while(std::getline(file_text, given_text))
  {
    full_file = full_file + given_text + "\n";
  }

  std::string new_full_file;
  for(auto letter:full_file)
  {
    if(letter == ' ')
      continue;
    new_full_file += letter;
  }

  while ((end = new_full_file.find_first_of(line_delimiter, begin)) != std::string::npos)
  {
    token = new_full_file.substr(begin, end - begin);
    begin = end + (line_delimiter.length() - 1);
    sender_check.push_back(token);
  }

std::string encrypted_msg;
encrypted_msg = sender_check[4];

std::string decrypted_text;
bool contact_check = false;

  if(sender_check[1] == getName())
{
  for(auto sender : contacts_)
  {
    if(sender.first->getName() == sender_check[3])
    {
      contact_check = true;
      decrypted_text = sender.second->decrypt(encrypted_msg);
      IO::printDecryptedMessage(getName(),sender.first->getName(),decrypted_text);
    }
  }
}
  else
  {
    file_text.close();
    return false;
  }

  if (!contact_check)
  {
    file_text.close();
    return false;
  }
  file_text.close();
  return true;
}