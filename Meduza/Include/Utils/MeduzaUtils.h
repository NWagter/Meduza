#pragma once
namespace Me
{
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
        static const Colour MAGENTA = Colour(0, 1.0f, 0, 1.0f);
        static const Colour ROYAL_PURPLE = Colour(0.47f, 0.32f, 0.66f, 1.0f);
        static const Colour CELESTIAL_BLUE = Colour(0.29f, 0.59f, 0.82f, 1.0f);
    }
}