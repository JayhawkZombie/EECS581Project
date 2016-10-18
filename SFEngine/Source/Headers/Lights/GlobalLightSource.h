#ifndef SFENGINE_GLOBAL_LIGHT_SOURCE
#define SFENGINE_GLOBAL_LIGHT_SOURCE

#include "GenericLightSource.h"

namespace Engine
{

  /**
   * Global light source is just a light that illuminates everything equally
   *
   */
  class GlobalLightSource : public GenericLightSource
  {
  public:
    GlobalLightSource();
    GlobalLightSource(const GlobalLightSource &src);
    ~GlobalLightSource();


  protected:

  };

}
#endif
