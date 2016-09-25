#ifndef SFENGINE_ENGINE_CONFIGURATION_H
#define SFENGINE_ENGINE_CONFIGURATION_H

#include <bitset>

#include "../BasicIncludes.h"

namespace Engine
{
  struct Config
  {
    /**
    * Settings pulled from ini file
    * Variable naming
    * <Category>_<type><Name>
    * ex: Diagnostc_bDisplayFrameStats
    * Category - Diagnostic, type = b (bool), Name = DisplayFrameStats
    */

    //Diagnostic ini settings
    bool           Diagnostic_bDisplayFrameStats; //Whether to display the FPS/Timing counter in the corner
    bool           Diagnostic_bBenchmarkShaders;  //Whether to benchmark increase in rendering times due to using shaders, can identify slow pipelines
    unsigned int   Diagnostic_uiLogLevel;         //How high of log levels to log
    std::string    Diagnostic_strDiagnosticFont;  //Font to use for rendered text

                                                  //Render ini settings
    bool               Render_bVsyncEnabled;
    bool               Render_bUseRenderTexture;
    bool               Render_bTextureSmoothingEnabled;
    unsigned int       Render_uiAALevel;
    bool               Render_bShadersEnabled;

    //Timing ini settings
    float              Timing_fMinTick;
    float              Timing_fMaxTick;

    //Window ini settings
    sf::Vector2f       Window_v2fWindowSize;
    bool               Window_bFullscreen;
    bool               Window_bShowSplashScreen;
    bool               Window_bPlaySplashScreenAudio;
    UINT32             Window_uiDepthBits;
    UINT32             Window_uiStencilBits;

    //Effects ini settings
    bool              Effects_bPostProcessEnabled;
    UINT32            Effects_uiMaxNumParticles;
    std::vector<std::string> Effects_strShaderPath; //Vector of paths to shaders
    std::vector<std::string> Effects_strShader;     //Vector of the names of the shaders
  };
}


#endif
