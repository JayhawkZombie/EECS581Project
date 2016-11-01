#ifndef SFENGINE_SHADER_H
#define SFENGINE_SHADER_H

#include "../BasicIncludes.h"

namespace Engine
{

  enum class ShaderType {
    VertexShader = 0,
    FragmentShader
  };

  template<typename T>
  struct ShaderParameter {
    T value;
    std::string ID;
    ShaderType Type;
  };

  template<typename T>
  struct ShaderArrayParameter {
    T* values;
    std::string ID;
    std::size_t ArraySize;
    ShaderType Type;

    void SetValues(std::size_t i, T* vals) {
      if (values)
        delete[] values;

      values = new T[i];
      for (std::size_t _ = 0; _ < i; _++) {
        values[_] = vals[_];
      }
    }
  };

  class Shader
  {
  public:
    Shader(const std::string &file);
    ~Shader();

    void AddFloatParameter(const std::string &param);
    void AddFloatArrayParameter(const std::string &param, const std::size_t &ArraySize);
    void AddColorParameter(const std::string &param);
    void AddTextureParameter(const std::string &param);

  private:
    
    std::map<std::string, ShaderParameter<float>> FloatParameters;
    std::map<std::string, ShaderParameter<sf::Color>> ColorParameters;
    std::map<std::string, ShaderArrayParameter<float>> FloatArrayParameters;

  };

}

#endif
