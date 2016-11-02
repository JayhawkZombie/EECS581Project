#ifndef SFENGINE_READINI_H
#define SFENGINE_READINI_H

#include <fstream>
#include <string>
#include <iostream>

#include <SFML\Graphics.hpp>

#include "../Utils/Convert.h"

namespace Engine
{
  namespace Util
  {
    /**
     <summary>Retrieve the boolean value for a given key</summary>
     <param name="category">The category in which a key is expected to appear in</param>
     <param name="key">The key to retrieve the value from</param>
     <param name="default">The default value to return in the case of a parse failure/malformed file</param>
     <param name="inifile">The file path for the ini file to parse</param>
     <param name="in">A reference to a file stream with the ini file opened</param>
     <returns>Return true if the value in the ini file is "true", returns false otherwise</returns>
     <example>
        [Window]
        WindowSize=(800,800)
        bUseVSync=false
        <code>
        std::ifstream inifile("Engine.ini");
        bool vsyncEnabled = Config::GetBooleanConfig("Window", "bUseVSync", false, "Enfine.ini", infile);
        </code>
     </example>
     */
    bool GetBooleanConfig(const std::string &category, const std::string &key, const bool &defaultValue, const std::string &inifile, std::ifstream &in);

    /**
    <summary>Retrieve the unsigned integer value for a given key</summary>
    <param name="category">The category in which a key is expected to appear in</param>
    <param name="key">The key to retrieve the value from</param>
    <param name="default">The default value to return in the case of a parse failure/malformed file</param>
    <param name="inifile">The file path for the ini file to parse</param>
    <param name="in">A reference to a file stream with the ini file opened</param>
    <returns>Return the interpretation of the string in the file to an unsigned integer. Returns default if it fails to parse or the value is negative</returns>
    <example>
      [Render]
      LayersToUse=5
      <code>
      std::ifstream inifile("Engine.ini");
      unsigned int numlevels = Config::GetUnsignedIntConfig("Render", "LayerstoUse", 1, "Engine.ini", infile);
      </code>
    </example>
    */
    unsigned int GetUnsignedIntConfig(const std::string &category, const std::string &key, const unsigned int &defaultValue, const std::string &inifile, std::ifstream &in);

    /**
    <summary>Retrieve the sf::Vector2f value for a given key</summary>
    <param name="category">The category in which a key is expected to appear in</param>
    <param name="key">The key to retrieve the value from</param>
    <param name="default">The default value to return in the case of a parse failure/malformed file</param>
    <param name="inifile">The file path for the ini file to parse</param>
    <param name="in">A reference to a file stream with the ini file opened</param>
    <returns>Return a vector2f with .x from the first string in the ordered pair, .y from the second. Returns default if it failed to parse</returns>
    <example>
      [Window]
      WindowSize=(800,800)
      bUseVSync=false
      <code>
      std::ifstream inifile("Engine.ini");
      sf::Vector2f winsize = Config::GetBooleanConfig("Window", "bUseVSync", false, "Enfine.ini", infile);
      </code>
    </example>
    */
    sf::Vector2f GetVec2fConfig(const std::string &category, const std::string &key, const sf::Vector2f &defaultValue, const std::string &inifile, std::ifstream &in);

    sf::FloatRect GetFloatRectConfig(const std::string &category, const std::string &key, const sf::FloatRect &defaultValue, const std::string &inifile, std::ifstream &in);

    /**
    <summary>Retrieve the float value for a given key</summary>
    <param name="category">The category in which a key is expected to appear in</param>
    <param name="key">The key to retrieve the value from</param>
    <param name="default">The default value to return in the case of a parse failure/malformed file</param>
    <param name="inifile">The file path for the ini file to parse</param>
    <param name="in">A reference to a file stream with the ini file opened</param>
    <returns>Return the interpretation of the string associated with the given key as a float. Returns default if it failed to parse</returns>
    <example>
      [Time]
      MinTickTime=0.1
      <code>
      std::ifstream inifile("Engine.ini");
      float MinTickTime = Config::GetFloatConfig("Time", "MinTickTime", 0.05, "Enfine.ini", infile);
      </code>
    </example>
    */
    float GetFloatConfig(const std::string &category, const std::string &key, const float &defaultValue, const std::string &inifile, std::ifstream &in);

    /**
    <summary>Retrieve the double value for a given key</summary>
    <param name="category">The category in which a key is expected to appear in</param>
    <param name="key">The key to retrieve the value from</param>
    <param name="default">The default value to return in the case of a parse failure/malformed file</param>
    <param name="inifile">The file path for the ini file to parse</param>
    <param name="in">A reference to a file stream with the ini file opened</param>
    <returns>Return the interpretation of the string associated with the given key as a double. Returns default if it failed to parse</returns>
    <example>
      [Time]
      TimeFactor=0.0002342342
      <code>
      std::ifstream inifile("Engine.ini");
      double TimeFactor = Config::GetDoubleConfig("Time", "TimeFactor", 0.0003, "Engine.ini", infile);
      </code>
    </example>
    */
    double GetDoubleConfig(const std::string &category, const std::string &key, const bool &defaultValue, const std::string &inifile, std::ifstream &in);

    /**
    <summary>Retrieve the string value for a given key</summary>
    <param name="category">The category in which a key is expected to appear in</param>
    <param name="key">The key to retrieve the value from</param>
    <param name="default">The default value to return in the case of a parse failure/malformed file</param>
    <param name="inifile">The file path for the ini file to parse</param>
    <param name="in">A reference to a file stream with the ini file opened</param>
    <returns>Return the interpretation of the string associated with the given key as a double. Returns default if it failed to parse</returns>
    <example>
      [Level]
      InitialLevel=./SomeLevel.level
      <code>
      std::ifstream inifile("Engine.ini");
      std::string levelpath = Config::GetStringValue("Level", "InitialLevel", "./DefaultLEvel.level", "Engine.ini", infile);
      </code>
    </example>
    */
    std::string GetStringConfig(const std::string &category, const std::string &key, const std::string &defaultValue, const std::string &infile, std::ifstream &in);

    std::string GetBracedConfig(const std::string &category, const std::string &key, const std::string &defaultValue, const std::string &infile, std::ifstream &in);
    std::pair<std::string, std::string> GetStringPair(const std::string &category, const std::string &key, const std::pair<std::string, std::string> &defaultValue, const std::string &infile, std::ifstream &in);
    std::pair<std::string, std::string> GetPairText(const std::string &line, std::size_t &curroffset);

    std::vector<std::pair<std::string, std::string>> ParsePairedText(const std::string &str, const std::size_t &paircount);
    
    /** 
     * Visual studio does not like it when template methods are defined in a different file
     * Visual studio ie fucking stupid like that, so we have to define it here, even though this is a header file
     */
    template<typename T>
    std::vector<sf::Rect<T>> ParseSFRectConfig(const std::string &str, const std::size_t &paircount) {
      std::vector<sf::Rect<T>> V;
      std::size_t beg{ 0 }, end{ std::string::npos }, currentpos{ 0 };
      for (std::size_t i = 0; i < paircount; ++i) {
        beg = str.find_first_of("(", currentpos);
        end = str.find_first_of(")", beg + 1);
        std::string substr = str.substr(beg, end - beg + 1);
        V.push_back(Util::StringToRect<T>(substr));
        currentpos = str.find_first_of("(", end + 1);
      }

      return V;
    }

    void WriteBooleanConfig(const std::string &category, const std::string &key, const bool &value, const std::string &inifile, std::ifstream &in);
    void WriteBooleanConfig(const std::string &category, const std::string &key, const bool &value, const std::string &inifile, std::ifstream &in);
    void WriteUnsignedIntConfig(const std::string &category, const std::string &key, const unsigned int &value, const std::string &inifile, std::ifstream &in);
    void WriteVec2fConfig(const std::string &category, const std::string &key, const sf::Vector2f &value, const std::string &inifile, std::ifstream &in);
    void WriteFloatConfig(const std::string &category, const std::string &key, const float &value, const std::string &inifile, std::ifstream &in);
    void WriteDoubleConfig(const std::string &category, const std::string &key, const bool &value, const std::string &inifile, std::ifstream &in);
    void WriteStringValue(const std::string &category, const std::string &key, const std::string &value, const std::string &infile, std::ifstream &in);
  }
}


#endif
