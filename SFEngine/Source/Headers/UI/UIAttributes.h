#ifndef SFENGINE_UI_ATTRIBUTES_H
#define SFENGINE_UI_ATTRIBUTES_H

#include <cinttypes>
#include <bitset>

#include "../BasicIncludes.h"
#include "../EngineTypes.h"


namespace Engine
{
  namespace UI
  {
    /**
     * Values used in the biset for the UI element attributes
     */
    const std::uint32_t Visible = 1;                    // "0000 0000 0000 0000 0000 0000 0000 0001"
    const std::uint32_t Enabled = 2;                    // "0000 0000 0000 0000 0000 0000 0000 0010"
    const std::uint32_t Clickable = 3;                  // "0000 0000 0000 0000 0000 0000 0000 0100"
    const std::uint32_t Dragable = 4;                   // "0000 0000 0000 0000 0000 0000 0000 1000"

    const std::uint32_t CollisionAuto = 5;              // "0000 0000 0000 0000 0000 0000 0001 0000"
    const std::uint32_t CollisionManual = 6;            // "0000 0000 0000 0000 0000 0000 0010 0000"

    const std::uint32_t Textured = 7;                   // "0000 0000 0000 0000 0000 0000 0100 0000"
    const std::uint32_t Animated = 8;                   // "0000 0000 0000 0000 0000 0000 1000 0000"
    const std::uint32_t Static = 9;                     // "0000 0000 0000 0000 0000 0001 0000 0000"
    const std::uint32_t Active = 10;                    // "0000 0000 0000 0000 0000 0010 0000 0000"

    const std::uint32_t CaptureMouseOver = 11;          // "0000 0000 0000 0000 0000 0100 0000 0000"
    const std::uint32_t CaptureMouseExit = 12;          // "0000 0000 0000 0000 0000 1000 0000 0000"
    const std::uint32_t CaptureMouseMovement = 13;      // "0000 0000 0000 0000 0001 0000 0000 0000"
    const std::uint32_t CaptureMouseClickLeft = 14;     // "0000 0000 0000 0000 0010 0000 0000 0000"
    const std::uint32_t CaptureMouseClickRight = 15;    // "0000 0000 0000 0000 0100 0000 0000 0000"
    const std::uint32_t CaptureTextInput = 16;          // "0000 0000 0000 0000 1000 0000 0000 0000"
    const std::uint32_t CaptureMouseDown = 17;          // "0000 0000 0000 0001 0000 0000 0000 0000"
    const std::uint32_t CaptureMouseRelease = 18;       // "0000 0000 0000 0010 0000 0000 0000 0000"

    const std::uint32_t MouseCurrentlyOver = 19;        // "0000 0000 0000 0100 0000 0000 0000 0000"
    const std::uint32_t MouseWasOver = 20;              // "0000 0000 0000 1000 0000 0000 0000 0000"
    const std::uint32_t MouseCurrentlyDownRight = 21;   // "0000 0000 0001 0000 0000 0000 0000 0000"
    const std::uint32_t MouseCurrentlyDownLeft = 22;    // "0000 0000 0010 0000 0000 0000 0000 0000"
    const std::uint32_t MouseWasDownRight = 23;         // "0000 0000 0100 0000 0000 0000 0000 0000"
    const std::uint32_t MouseWasDownLeft = 24;          // "0000 0000 1000 0000 0000 0000 0000 0000"

    const std::string DefaultState = "00000000000000111111110010010111";
    const std::bitset<32> DefaultBisetState = std::bitset<32>(DefaultState);
  }
}


#endif