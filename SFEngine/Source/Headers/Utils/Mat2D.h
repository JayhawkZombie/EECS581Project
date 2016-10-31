#ifndef SFENGINE_MAT2D_H
#define SFENGINE_MAT2D_H


namespace Engine
{

  template<typename T>
  class Matrix
  {
  public:
    Matrix()
      : MatHeight(0), MatWidth(0), Mat(nullptr) {}
    ~Matrix()
    {
      for (size_t i = 0; i < MatHeight; ++i)
        delete[] Mat[i];
      delete[] Mat;
    }

    void Create(std::size_t N, std::size_t M) {
      MatHeight = N;
      MatWidth = M;
      Mat = new T*[N];
      for (size_t i = 0; i < MatHeight; ++i)
        Mat[i] = new T[MatWidth]{};
    }

    Matrix& operator[](const std::size_t &N) {
      return &Mat[N];
    }

    T* operator() (const std::size_t &N, const std::size_t &M) {
      if (N >= MatHeight || M >= MatWidth)
        return nullptr;

      return &Mat[N][M];
    }

    void Assign(const std::size_t &N, const std::size_t &M, const T &value) {
      if (N >= MatHeight || M >= MatWidth)
        return;
      else {
        Mat[N][M] = value;
      }
    }

    T **Mat;
    std::size_t MatHeight, MatWidth;

  };

}


#endif
