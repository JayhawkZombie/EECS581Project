#include "../../Headers/Lights/LightObject.h"


  void SORT2(std::vector<std::pair<KS::Vec2<float>, float>> &Vertices, const int &first, const int &last)
  {
    if (Vertices[first].second > Vertices[last].second)
      std::swap(Vertices[first], Vertices[last]);
  }

  void SORT3(std::vector<std::pair<KS::Vec2<float>, float>> &vec, const int &first, const int &last)
  {
    if (vec[first].second > vec[first + 1].second)
      std::swap(vec[first], vec[first + 1]);

    if (vec[first].second > vec[first + 2].second)
      std::swap(vec[first], vec[first + 2]);

    if (vec[last - 1].second > vec[last].second)
      std::swap(vec[last - 1], vec[last]);

  }

  void SORT4(std::vector<std::pair<KS::Vec2<float>, float>> &Vertices, const int &first, const int &last)
  {
    if (Vertices[first].second > Vertices[first + 1].second)
      std::swap(Vertices[first], Vertices[first + 1]);

    if (Vertices[first + 1].second > Vertices[last - 1].second)
      std::swap(Vertices[first + 1], Vertices[last - 1]);

    if (Vertices[last - 1].second > Vertices[last].second)
      std::swap(Vertices[last - 1], Vertices[last]);

    SORT3(Vertices, first + 1, last);
    SORT2(Vertices, first, first + 1);
    SORT2(Vertices, first + 1, first + 2);
  }

  namespace Engine
  {

  }
