#include "Gem.h"

ShatterGem::ShatterGem()
  : m_ShatteredFragmentArrays(100, sf::VertexArray(sf::Quads, 4))
{
  //x : 0 -> 408, y : 0 -> 408
  //X coordinates to shatter into
  float X1 = 0,   X2 = 41,  X3 = 123, X4 = 164, X5 = 205,
        X6 = 246, X7 = 287, X8 = 328, X9 = 369, X10 = 410;

  float Y1 = 0,   Y2 = 41,  Y3 = 123, Y4 = 164, Y5 = 205,
        Y6 = 246, Y7 = 287, Y8 = 328, Y9 = 369, Y10 = 410;

  m_ShatterPieces = {
    //x : 0 -> 410, y = 0
    { 0, 0,   41, 41 }, { 41, 0,   41, 41 }, { 82, 0,   41, 41 }, { 123, 0,   41, 41 }, { 164, 0,   41, 41 }, { 205, 0,   41, 41 }, { 246, 0,   41, 41 }, { 287, 0,   41, 41 }, { 287, 0,   41, 41 }, { 328, 0,   41, 41 }, { 369, 0,   41, 41 },
    { 0, 41,  41, 41 }, { 41, 41,  41, 41 }, { 82, 41,  41, 41 }, { 123, 41,  41, 41 }, { 164, 41,  41, 41 }, { 205, 41,  41, 41 }, { 246, 41,  41, 41 }, { 287, 41,  41, 41 }, { 287, 41,  41, 41 }, { 328, 41,  41, 41 }, { 369, 41,  41, 41 },
    { 0, 82,  41, 41 }, { 41, 82,  41, 41 }, { 82, 82,  41, 41 }, { 123, 82,  41, 41 }, { 164, 82,  41, 41 }, { 205, 82,  41, 41 }, { 246, 82,  41, 41 }, { 287, 82,  41, 41 }, { 287, 82,  41, 41 }, { 328, 82,  82, 41 }, { 369, 82,  82, 41 },
    { 0, 123, 41, 41 }, { 41, 123, 41, 41 }, { 82, 123, 41, 41 }, { 123, 123, 41, 41 }, { 164, 123, 41, 41 }, { 205, 123, 41, 41 }, { 246, 123, 41, 41 }, { 287, 123, 41, 41 }, { 287, 123, 41, 41 }, { 328, 123, 41, 41 }, { 369, 123, 41, 41 },
    { 0, 164, 41, 41 }, { 41, 164, 41, 41 }, { 82, 164, 41, 41 }, { 123, 164, 41, 41 }, { 164, 164, 41, 41 }, { 205, 164, 41, 41 }, { 246, 164, 41, 41 }, { 287, 164, 41, 41 }, { 287, 164, 41, 41 }, { 328, 164, 14, 41 }, { 369, 164, 82, 41 },
    { 0, 205, 41, 41 }, { 41, 205, 41, 41 }, { 82, 205, 41, 41 }, { 123, 205, 41, 41 }, { 164, 205, 41, 41 }, { 205, 205, 41, 41 }, { 246, 205, 41, 41 }, { 287, 205, 41, 41 }, { 287, 205, 41, 41 }, { 328, 205, 41, 41 }, { 369, 205, 41, 41 },
    { 0, 246, 41, 41 }, { 41, 246, 41, 41 }, { 82, 246, 41, 41 }, { 123, 246, 41, 41 }, { 164, 246, 41, 41 }, { 205, 246, 41, 41 }, { 246, 246, 41, 41 }, { 287, 246, 41, 41 }, { 287, 246, 41, 41 }, { 328, 246, 41, 41 }, { 369, 246, 41, 41 },
    { 0, 287, 41, 41 }, { 41, 287, 41, 41 }, { 82, 287, 41, 41 }, { 123, 287, 41, 41 }, { 164, 287, 41, 41 }, { 205, 287, 41, 41 }, { 246, 287, 41, 41 }, { 287, 287, 41, 41 }, { 287, 287, 41, 41 }, { 328, 287, 41, 41 }, { 369, 287, 41, 41 },
    { 0, 328, 41, 41 }, { 41, 328, 41, 41 }, { 82, 328, 41, 41 }, { 123, 328, 41, 41 }, { 164, 328, 41, 41 }, { 205, 328, 41, 41 }, { 246, 328, 41, 41 }, { 287, 328, 41, 41 }, { 287, 328, 41, 41 }, { 328, 328, 41, 41 }, { 369, 328, 41, 41 },
    { 0, 369, 41, 41 }, { 41, 369, 41, 41 }, { 82, 369, 41, 41 }, { 123, 369, 41, 41 }, { 164, 369, 41, 41 }, { 205, 369, 41, 41 }, { 246, 369, 41, 41 }, { 287, 369, 41, 41 }, { 287, 369, 41, 41 }, { 328, 369, 41, 41 }, { 369, 369, 41, 41 }
  };

  for (std::size_t i = 0; i < 100; ++i) {
    m_ShatteredFragmentArrays[i][0].texCoords.x = m_ShatterPieces[i].left;
    m_ShatteredFragmentArrays[i][0].texCoords.y = m_ShatterPieces[i].top;

    m_ShatteredFragmentArrays[i][1].texCoords.x = m_ShatterPieces[i].left + m_ShatterPieces[i].width;
    m_ShatteredFragmentArrays[i][1].texCoords.y = m_ShatterPieces[i].top;

    m_ShatteredFragmentArrays[i][2].texCoords.x = m_ShatterPieces[i].left + m_ShatterPieces[i].width;
    m_ShatteredFragmentArrays[i][2].texCoords.y = m_ShatterPieces[i].top  + m_ShatterPieces[i].height;

    m_ShatteredFragmentArrays[i][3].texCoords.x = m_ShatterPieces[i].left;
    m_ShatteredFragmentArrays[i][3].texCoords.y = m_ShatterPieces[i].top  + m_ShatterPieces[i].height;
  }

}

ShatterGem::~ShatterGem()
{
}

void ShatterGem::Render(std::shared_ptr<sf::RenderTarget> Target)
{
}

void ShatterGem::TickUpdate(const double & delta)
{
}

void ShatterGem::PhysicsUpdate()
{
}

void ShatterGem::OnShutDown()
{
}

void ShatterGem::OnGameStart()
{
}

void ShatterGem::OnGameEnd()
{
}

void ShatterGem::OnKilled()
{
}

void ShatterGem::OnSpawn()
{
}

void ShatterGem::Shatter()
{
}

void ShatterGem::Reassemble()
{
}

void ShatterGem::RenderShatteredFragments()
{
}

void ShatterGem::UpdateShatteredFragments()
{
}
