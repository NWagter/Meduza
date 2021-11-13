#pragma once
namespace Me
{

#define RUN_GAME 1
#define RUN_EDITOR 2
#define RUN_PAUSED 4

namespace Utils
{
    class Utilities
    {
    public:
        static uint16_t GetHashedID(std::string);
    };     

    Math::Vec4 TextureSlice(Math::Vec2 a_textureSize, Math::Vec2 a_sliceBegin, Math::Vec2 a_sliceSize);
}

  
  namespace Colours
  {
    static const Colour BLACK = Colour(0, 0, 0, 1.0f);
    static const Colour WHITE = Colour(1.0f, 1.0f, 1.0f, 1.0f);
    static const Colour RED = Colour(1.0f, 0, 0, 1.0f);
    static const Colour BLUE = Colour(0, 0, 1.0f, 1.0f);
    static const Colour GREEN = Colour(0, 1.0f, 0, 1.0f);

    static const Colour RESENE_DARK_OAK = Colour(0.33f, 0.20f, 0.16f, 1.0f);
    static const Colour TAUBMANS_WINTER_OAK = Colour(0.66f, 0.54f, 0.37f, 1.0f);
    static const Colour AZURE_WHITE = Colour(0.95, 1.0f, 1.0f, 1.0f);

    static const Colour MAGENTA = Colour(1.0f, 0.0f, 1.0f, 1.0f);
    static const Colour ROYAL_PURPLE = Colour(0.47f, 0.32f, 0.66f, 1.0f);
    static const Colour CELESTIAL_BLUE = Colour(0.29f, 0.59f, 0.82f, 1.0f);
  }

  namespace Animation
  {
    static Me::Math::Vec4 GetUV(Me::Math::Vec4 a_texture, Me::Math::Vec2 a_textureSize)
    {
      Me::Math::Vec4 uv;

      if (a_texture.m_x != 0 || a_texture.m_z != 1)
      {
        uv.m_x = (1 / a_textureSize.m_x) * (a_texture.m_x);
        uv.m_z = (1 / a_textureSize.m_x) * (a_texture.m_z);
      }
      if (a_texture.m_y != 0 || a_texture.m_w != 1)
      {
        uv.m_y = (1 / a_textureSize.m_y) * (a_texture.m_y + 0.5f);
        uv.m_w = (1 / a_textureSize.m_y) * (a_texture.m_w - 0.5f);
      }

      return uv;
    }
  }
}