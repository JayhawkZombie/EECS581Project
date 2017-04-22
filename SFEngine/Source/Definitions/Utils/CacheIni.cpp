#include "Utils\CacheIni.h"

#include <istream>
#include <ostream>
#include <sstream>

namespace
{

  void ReadKey(std::stringstream &in, std::string &KeyAccum) {
    //Accumulate up to the '='
    char c = '\0';

    in.get(c);
    while (in && c != '=' && c != '\n') {
      KeyAccum += c;
      in.get(c);
    }
  }

  void ReadValue(std::stringstream &in, std::string &ValAccum) {
    //Assuming we've still got the '=' character in the stream
    if (in.peek() == '=')
      in.ignore(1);

    char c = '\0';
    in.get(c);

    while (in && c != ';' && c != '\n') {
      ValAccum += c;
      in.get(c);
    }


  }

}

Engine::Util::IniCache* Engine::Util::IniCache::m_Cache = nullptr;

namespace Engine
{

  namespace Util
  {

    bool IniValue::Read(std::stringstream &in)
    {
      static std::stringstream line_str;
      line_str.str("");


      std::string line;
      std::getline(in, line);

      if (line.find('=') == std::string::npos) {
        in.write(line.data(), line.size()); //write the line back and return
        return false;
      }

      line_str.str(line.data());
      ReadKey(line_str, m_KeyRep);
      ReadValue(line_str, m_StringValueRep);

      return true;
    }

    void IniValue::Write(std::stringstream &out)
    {
      out.write(m_KeyRep.data(), m_KeyRep.size());
      out.put('=');
      out.write(m_StringValueRep.data(), m_StringValueRep.size());
      out.put('\n');
    }

    std::string IniValue::GetKey() const
    {
      return m_KeyRep;
    }

    int IniValue::AsInt(const IniValue & VRef, int Default)
    {
      if (VRef.m_PossibleTypes.find(IniValueType::Int) != VRef.m_PossibleTypes.end())
        return VRef.Get(Default);
      return Default;
    }

    float IniValue::AsFloat(const IniValue & VRef, float Default)
    {
      if (VRef.m_PossibleTypes.find(IniValueType::Float) != VRef.m_PossibleTypes.end())
        return VRef.Get(Default);
      return Default;
    }

    double IniValue::AsDouble(const IniValue & VRef, double Default)
    {
      if (VRef.m_PossibleTypes.find(IniValueType::Double) != VRef.m_PossibleTypes.end())
        return VRef.Get(Default);
      return Default;
    }

    unsigned int IniValue::AsUnsignedInt(const IniValue & VRef, unsigned int Default)
    {
      if (VRef.m_PossibleTypes.find(IniValueType::UnsignedInt) != VRef.m_PossibleTypes.end())
        return VRef.Get(Default);
      return Default;
    }

    bool IniValue::AsBool(const IniValue & VRef, bool Default)
    {
      if (VRef.m_PossibleTypes.find(IniValueType::Bool) != VRef.m_PossibleTypes.end())
        return VRef.Get(Default);
      return Default;
    }

    sf::Vector2f IniValue::AsVector2f(const IniValue & VRef, sf::Vector2f Default)
    {
      if (VRef.m_PossibleTypes.find(IniValueType::Vector2f) != VRef.m_PossibleTypes.end())
        return VRef.Get(Default);
      return Default;
    }

    sf::Vector2i IniValue::AsVector2i(const IniValue & VRef, sf::Vector2i Default)
    {
      if (VRef.m_PossibleTypes.find(IniValueType::Vector2i) != VRef.m_PossibleTypes.end())
        return VRef.Get(Default);
      return Default;
    }

    sf::Vector2u IniValue::AsVector2u(const IniValue & VRef, sf::Vector2u Default)
    {
      if (VRef.m_PossibleTypes.find(IniValueType::Vector2u) != VRef.m_PossibleTypes.end())
        return VRef.Get(Default);
      return Default;
    }

    sf::IntRect IniValue::AsIntRect(const IniValue & VRef, sf::IntRect Default)
    {
      if (VRef.m_PossibleTypes.find(IniValueType::IntRect) != VRef.m_PossibleTypes.end())
        return VRef.Get(Default);
      return Default;
    }

    sf::FloatRect IniValue::AsFloatRect(const IniValue & VRef, sf::FloatRect Default)
    {
      if (VRef.m_PossibleTypes.find(IniValueType::FloatRect) != VRef.m_PossibleTypes.end())
        return VRef.Get(Default);
      return Default;
    }

    /*
     * IniSectionCache
     **/
    void IniSectionCache::Read(std::stringstream &in)
    {
      std::string Section{ "" };
      char c = '\0';

      in.get(c);
      if (c == '[') {

        in.get(c);
        while (in && c != ']' && c != '\n') {
          Section += c;
          in.get(c);
        }

        m_SectionRep = Section;
      }
    }

    void IniSectionCache::Write(std::stringstream &out)
    {
      out.put('[');
      out.write(m_SectionRep.data(), m_SectionRep.size());
      out.put(']'); out.put('\n');

      for (auto & value : m_Values)
        value.Write(out);
    }

    /*
     * Inicache
     **/
    void IniCache::Init()
    {
      if (!m_Cache)
        m_Cache = new IniCache;
    }

    void IniCache::Cleanup()
    {
      if (m_Cache)
        delete m_Cache;
    }

    IniCache* IniCache::Get()
    {
      return m_Cache;
    }

  } //namespace util

}
