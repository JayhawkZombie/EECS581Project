#include "Utils\ReadIni.h"
#include "Utils\Convert.h"

#include <unordered_map>
#include <string>

/*
 * Getter methods for IniValue - Convert from the string representation to the requested value type
 **/
template<>
int Engine::Util::IniValue::Get<int>(int Default) const
{
  return Engine::Util::StringToType(m_StringValueRep, Default); 
}

template<>
unsigned int Engine::Util::IniValue::Get<unsigned int>(unsigned int Default) const
{
  return Engine::Util::StringToType(m_StringValueRep, Default);
}

template<>
float Engine::Util::IniValue::Get<float>(float Default) const
{
  return Engine::Util::StringToType(m_StringValueRep, Default);
}

template<>
double Engine::Util::IniValue::Get<double>(double Default) const
{
  return Engine::Util::StringToType(m_StringValueRep, Default);
}

template<>
bool Engine::Util::IniValue::Get<bool>(bool Default) const
{
  return Engine::Util::StringToBool(m_StringValueRep, Default);
}

template<>
sf::Vector2f Engine::Util::IniValue::Get<sf::Vector2f>(sf::Vector2f Default) const
{
  return Engine::Util::StringToVec2<float>(m_StringValueRep, Default);
}

template<>
sf::Vector2i Engine::Util::IniValue::Get<sf::Vector2i>(sf::Vector2i Default) const
{
  return Engine::Util::StringToVec2<int>(m_StringValueRep, Default);
}

template<> 
sf::Vector2u Engine::Util::IniValue::Get<sf::Vector2u>(sf::Vector2u Default) const
{
  return Engine::Util::StringToVec2<unsigned int>(m_StringValueRep, Default);
}

template<>
sf::IntRect Engine::Util::IniValue::Get<sf::IntRect>(sf::IntRect Default) const
{
  return Engine::Util::StringToRect<int>(m_StringValueRep, Default);
}

template<>
sf::FloatRect Engine::Util::IniValue::Get<sf::FloatRect>(sf::FloatRect Default) const
{
  return Engine::Util::StringToRect<float>(m_StringValueRep, Default);
}

/*
 * Setter methods for IniValue - Convert from the type to a string representation
 **/
template<>
void Engine::Util::IniValue::Set<int>(int Value)
{
  m_StringValueRep = std::to_string(Value);
}

template<>
void Engine::Util::IniValue::Set<unsigned int>(unsigned int Value)
{
  m_StringValueRep = std::to_string(Value);
}

template<>
void Engine::Util::IniValue::Set<float>(float Value)
{
  m_StringValueRep = std::to_string(Value);
}

template<>
void Engine::Util::IniValue::Set<double>(double Value)
{
  m_StringValueRep = std::to_string(Value);
}

template<>
void Engine::Util::IniValue::Set<bool>(bool Value)
{
  m_StringValueRep = Value ? "true" : "false";
}

template<>
void Engine::Util::IniValue::Set<sf::Vector2f>(sf::Vector2f Value)
{
  m_StringValueRep = "(" + std::to_string(Value.x) + "," 
                         + std::to_string(Value.y) + ")";
}

template<>
void Engine::Util::IniValue::Set<sf::Vector2i>(sf::Vector2i Value)
{
  m_StringValueRep = "(" + std::to_string(Value.x) + ","
                         + std::to_string(Value.y) + ")";
}

template<>
void Engine::Util::IniValue::Set<sf::Vector2u>(sf::Vector2u Value)
{
  m_StringValueRep = "(" + std::to_string(Value.x) + ","
                         + std::to_string(Value.y) + ")";
}

template<>
void Engine::Util::IniValue::Set<sf::IntRect>(sf::IntRect Value)
{
  m_StringValueRep = "(" + std::to_string(Value.left) + ","
                         + std::to_string(Value.top) + ","
                         + std::to_string(Value.width) + ","
                         + std::to_string(Value.height) + ")";
}

template<>
void Engine::Util::IniValue::Set<sf::FloatRect>(sf::FloatRect Value)
{
  m_StringValueRep = "(" + std::to_string(Value.left) + ","
                         + std::to_string(Value.top) + ","
                         + std::to_string(Value.width) + ","
                         + std::to_string(Value.height) + ")";
}


/*
 *
 *
 *  IniCache
 *
 **/

template<>
int Engine::Util::IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, int Default)
{
  auto ptr = Get();

  if (!ptr)
    return Default;

  int Value = Default;

  auto cache = ptr->m_SectionMap.find(Section);
  if (cache != ptr->m_SectionMap.end()) {
    Value = ptr->m_SectionMap[KeyVal].GetValue(KeyVal, Default);
  }

  return Value;
}

template<>
float Engine::Util::IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, float Default)
{
  auto ptr = Get();

  if (!ptr)
    return Default;

  float Value = Default;
  if (ptr->m_SectionMap.find(KeyVal) != ptr->m_SectionMap.end()) {
    Value = ptr->m_SectionMap[KeyVal].GetValue(KeyVal, Default);
  }
  
  return Value;
}

template<> 
double Engine::Util::IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, double Default)
{
  auto ptr = Get();

  if (!ptr)
    return Default;

  double Value = Default;
  if (ptr->m_SectionMap.find(KeyVal) != ptr->m_SectionMap.end()) {
    Value = ptr->m_SectionMap[KeyVal].GetValue(KeyVal, Default);
  }

  return Value;
}

template<> 
unsigned int Engine::Util::IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, unsigned int Default)
{
  auto ptr = Get();

  if (!ptr)
    return Default;

  unsigned int Value = Default;
  if (ptr->m_SectionMap.find(KeyVal) != ptr->m_SectionMap.end()) {
    Value = ptr->m_SectionMap[KeyVal].GetValue(KeyVal, Default);
  }

  return Value;
}

template<> 
sf::Vector2f Engine::Util::IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, sf::Vector2f Default)
{
  auto ptr = Get();

  if (!ptr)
    return Default;

  sf::Vector2f Value = Default;
  if (ptr->m_SectionMap.find(KeyVal) != ptr->m_SectionMap.end()) {
    Value = ptr->m_SectionMap[KeyVal].GetValue(KeyVal, Default);
  }

  return Value;
}

template<> 
sf::Vector2i Engine::Util::IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, sf::Vector2i Default)
{
  auto ptr = Get();

  if (!ptr)
    return Default;

  sf::Vector2i Value = Default;
  if (ptr->m_SectionMap.find(KeyVal) != ptr->m_SectionMap.end()) {
    Value = ptr->m_SectionMap[KeyVal].GetValue(KeyVal, Default);
  }

  return Value;
}

template<> 
sf::Vector2u Engine::Util::IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, sf::Vector2u Default)
{
  auto ptr = Get();

  if (!ptr)
    return Default;

  sf::Vector2u Value = Default;
  if (ptr->m_SectionMap.find(KeyVal) != ptr->m_SectionMap.end()) {
    Value = ptr->m_SectionMap[KeyVal].GetValue(KeyVal, Default);
  }

  return Value;
}

template<> 
sf::IntRect Engine::Util::IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, sf::IntRect Default)
{
  auto ptr = Get();

  if (!ptr)
    return Default;

  sf::IntRect Value = Default;
  if (ptr->m_SectionMap.find(KeyVal) != ptr->m_SectionMap.end()) {
    Value = ptr->m_SectionMap[KeyVal].GetValue(KeyVal, Default);
  }

  return Value;
}

template<> 
sf::FloatRect Engine::Util::IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, sf::FloatRect Default)
{
  auto ptr = Get();

  if (!ptr)
    return Default;

  sf::FloatRect Value = Default;
  if (ptr->m_SectionMap.find(KeyVal) != ptr->m_SectionMap.end()) {
    Value = ptr->m_SectionMap[KeyVal].GetValue(KeyVal, Default);
  }

  return Value;
}


/*
 *
 *  IniSectionCache
 *
 *
 **/

template<> 
int Engine::Util::IniSectionCache::GetValue<int>(const std::string &Key, int Default) const
{
  for (auto & val : m_Values) {
    if (val.GetKey() == Key)
      return val.Get(Default);
  }

  return Default;
}

template<> 
float Engine::Util::IniSectionCache::GetValue<float>(const std::string &Key, float Default) const
{
  for (auto & val : m_Values) {
    if (val.GetKey() == Key)
      return val.Get(Default);
  }

  return Default;
}

template<> 
double Engine::Util::IniSectionCache::GetValue<double>(const std::string &Key, double Default) const
{
  for (auto & val : m_Values) {
    if (val.GetKey() == Key)
      return val.Get(Default);
  }

  return Default;
}

template<> 
unsigned int Engine::Util::IniSectionCache::GetValue<unsigned int>(const std::string &Key, unsigned int  Default) const
{
  for (auto & val : m_Values) {
    if (val.GetKey() == Key)
      return val.Get(Default);
  }

  return Default;
}

template<> 
sf::Vector2f Engine::Util::IniSectionCache::GetValue<sf::Vector2f>(const std::string &Key, sf::Vector2f  Default) const
{
  for (auto & val : m_Values) {
    if (val.GetKey() == Key)
      return val.Get(Default);
  }

  return Default;
}

template<>
sf::Vector2u Engine::Util::IniSectionCache::GetValue<sf::Vector2u>(const std::string &Key, sf::Vector2u  Default) const
{
  for (auto & val : m_Values) {
    if (val.GetKey() == Key)
      return val.Get(Default);
  }

  return Default;
}

template<> 
sf::Vector2i Engine::Util::IniSectionCache::GetValue<sf::Vector2i>(const std::string &Key, sf::Vector2i  Default) const
{
  for (auto & val : m_Values) {
    if (val.GetKey() == Key)
      return val.Get(Default);
  }

  return Default;
}

template<> 
sf::IntRect Engine::Util::IniSectionCache::GetValue<sf::IntRect>(const std::string &Key, sf::IntRect  Default) const
{
  for (auto & val : m_Values) {
    if (val.GetKey() == Key)
      return val.Get(Default);
  }

  return Default;
}

template<> 
sf::FloatRect Engine::Util::IniSectionCache::GetValue<sf::FloatRect>(const std::string &Key, sf::FloatRect Default) const
{
  for (auto & val : m_Values) {
    if (val.GetKey() == Key)
      return val.Get(Default);
  }

  return Default;
}
