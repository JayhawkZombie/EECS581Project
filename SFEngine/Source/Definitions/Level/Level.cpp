#include "../../Headers/Level/Level.h"
#include "../../Headers/Physics/PhysicsEngineInterface.h"
#include "../../../ThirdParty/Physics/vec2d.h"
#include "../../../ThirdParty/json/json.h"
#include "../../../ThirdParty/chaiscript/chaiscript.hpp"

namespace
{
  std::string PROJECT_PATH = "";
}

namespace Engine
{
  Level* CurrentLevel;

  Level::Level(const sf::Vector2u &LevelSize, const sf::FloatRect &DefaultView, bool showlines, const sf::Vector2f &GridSpacing)
    : ShowGridLines(showlines), Size(LevelSize), GridBlockSize(GridSpacing), CurrentView(DefaultView),
    LightTexture(std::make_shared<sf::RenderTexture>()),
    SceneBlendTexture(std::make_shared<sf::RenderTexture>()),
    Gravity(new ::vec2d())
  {
    auto seg = BuildSegmentMesh('L', { 100, 300 }, { 550, 500 });
    TestSegments.push_back(seg);

    LightTexture->create(__UINT_FROM_FLOAT__(WindowSize.x), __UINT_FROM_FLOAT__(WindowSize.y));
    LightTexture->clear(sf::Color::Transparent);

    SceneBlendTexture->create(__UINT_FROM_FLOAT__(WindowSize.x), __UINT_FROM_FLOAT__(WindowSize.y));
    SceneBlendTexture->clear(sf::Color::Transparent);
    
    if (ShowGridLines) {
      GenerateGrid();
    }
    CurrentLevel = this;
  }

  Level::Level(const std::string &lvl)
  {
    Handler.BindCallback(Events::KeyPressed, [this](const sf::Keyboard::Key &k) -> void { this->HandleKeyPress(k); } );
    Handler.BindCallback(Events::KeyReleased, [this](const sf::Keyboard::Key &k) ->void { this->HandleKeyRelease(k); } );
  }

  Level::~Level()
  {
    SceneTarget.reset();
    for (auto & tex : Textures)
      tex.second.reset();

    Textures.clear();
    for (auto & sheet : TileSheets)
      sheet.second.reset();
    TileSheets.clear();
    for (auto & anim : Animations)
      anim.second.reset();
    Animations.clear();
    for (auto & buff : SoundBuffers)
      buff.second.reset();
    SoundBuffers.clear();
    for (auto & sys : LightSystems)
      sys.second.reset();
    LightSystems.clear();
    for (auto & light : Lights)
      light.second.reset();
    Lights.clear();

    LightTexture.reset();
  }

  void Level::BindMethods(chaiscript::ModulePtr mptr)
  {
    mptr->add(chaiscript::fun(&GetObjectByName), "GetObjectByID");
  }

  void Level::HandleKeyPress(const sf::Keyboard::Key &key)
  {

  }

  void Level::HandleKeyRelease(const sf::Keyboard::Key &key)
  {

  }

  void Level::GenerateGrid()
  {
    float xpos = 0, ypos = 0;
    sf::VertexArray hline = sf::VertexArray(sf::Lines, 2);
    sf::VertexArray vline = sf::VertexArray(sf::Lines, 2);

    while (ypos < Size.y) {
      hline[0].position = { 0, ypos }; hline[0].color = sf::Color(0, 123, 137);
      hline[1].position = { static_cast<float>(Size.x), ypos }; hline[1].color = sf::Color(0, 123, 137);

      GridLines.push_back(hline);
      ypos += GridBlockSize.y;
    }

    while (xpos < Size.x) {
      vline[0].position = { xpos, 0 }; vline[0].color = sf::Color(0, 123, 137);
      vline[1].position = { xpos, static_cast<float>(Size.y) }; vline[1].color = sf::Color(0, 123, 137);

      GridLines.push_back(vline);
      xpos += GridBlockSize.y;
    }
  }

  void Level::LoadLevel(const std::string &lvlfile)
  {
    LoadFromFile(lvlfile);
    
  }

  void Level::OnShutDown()
  {

  }

  void Level::HandleWindowResized()
  {

  }

  std::shared_ptr<LevelObject> Level::GetObjectByName(const std::string & ID)
  {
    if (!CurrentLevel) {
      std::cerr << "CurrentLevel is NULL" << std::endl;
      return nullptr;
    }

    for (auto & obj : CurrentLevel->Objects) {
      if (obj->ItemID == ID)
        return obj;
    }

    return nullptr;
  }

  void Level::LoadFromFile(const std::string &file)
  {
    Json::Value ProjectFile;

    std::ifstream in(file);
    if (!in) {
      std::cerr << "Unable to open project file" << std::endl;
      return;
    }

    in >> ProjectFile;

    try
    {
      PROJECT_PATH = ProjectFile["Project"]["Info"]["PROJECT_PATH"].asString();
      LoadAssets(ProjectFile["Project"]["Data"]);
    }
    catch (EngineRuntimeError &err)
    {

    }

  }
  void Level::SpawnBall(char BallType, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, unsigned int Radius, float Mass, float CoeffecientOfRest, const sf::Color & Color)
  {
    //auto ball = BuildBallMesh(BallType, InitialPosition, InitialVelocity, Radius, Mass, CoeffecientOfRest, Color);
    TestObjects.push_back((BuildBallMesh(BallType, InitialPosition, InitialVelocity, Radius, Mass, CoeffecientOfRest, Color)));
  }

  void Level::SpawnSquare(float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
  {
    //auto sq = BuildPolygonMesh(4, radius, 0, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
    TestObjects.push_back((BuildPolygonMesh(4, radius, 0, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color)));
  }

  void Level::SpawnRect(float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
  {
    //auto sq = BuildPolygonMesh(4, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
    TestObjects.push_back((BuildPolygonMesh(4, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color)));
  }

  void Level::SpawnTriangle(float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
  {
    auto tri = BuildPolygonMesh(3, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
  }

  void Level::SpawnNPoly(unsigned int num_sides, float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
  {
    //auto poly = BuildPolygonMesh(num_sides, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
    TestObjects.push_back((BuildPolygonMesh(num_sides, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color)));
    auto ptr = TestObjects.back().get();
  }

  void Level::SpawnWave(char type, const sf::Vector2i & TopLeftCorner, const sf::Vector2i & BottomRightCorner, float radius, bool IsHard, unsigned int NumWavePts, float ampRight, float waveLenRight, float rFreqRight, float ampLeft, float waveLenLeft, float rFreqLeft, float elev, float airDen, float depth, float fluidDen)
  {
    auto ptr = BuildWaveSegment(type, TopLeftCorner, BottomRightCorner, radius, IsHard, NumWavePts, ampRight, waveLenRight, rFreqRight, ampLeft, waveLenLeft, rFreqLeft, elev, airDen, depth, fluidDen);
    TestSegments.push_back(ptr);
    Waves.push_back(ptr);
  }

  void Level::LoadAssets(const Json::Value & value)
  {
    //textures
    LoadTextures(value["Textures"]);
    LoadAudio(value["Audio"]);
    LoadTileSheets(value["Sheets"]);
    LoadAnimations(value["Animations"]);
  }
  void Level::LoadAudio(const Json::Value & value)
  {
    std::string name{ "" };
    std::string path{ "" };

    for (auto & file : value) {
      name = file["Name"].asString();
      path = PROJECT_PATH + file["Path"].asString();

      SoundBuffers[name] = std::make_shared<sf::SoundBuffer>();
      if (!SoundBuffers[name]->loadFromFile(path)) {
        std::cerr << "Failed to load audio file: " << path << std::endl;
      }


    }
  }
  void Level::LoadTextures(const Json::Value & value)
  {
    std::string texname{ "" };
    std::string path{ "" };

    for (auto & tex : value) {
      texname = tex["Name"].asString();
      path = PROJECT_PATH + tex["Path"].asString();
      Textures[texname] = std::make_shared<sf::Texture>();
      if (!Textures[texname]->loadFromFile(path)) {
        std::cerr << "Unable to load texture: " << path << std::endl;
      }
    }

  }
  void Level::LoadTileSheets(const Json::Value & value)
  {
    for (auto & sheet : value)
      LoadSheet(sheet);
  }
  void Level::LoadSheet(const Json::Value & value)
  {
    try
    {
      auto texname = value["Name"].asString();
      auto sheet_data = value["Sheet"];
      auto frames = sheet_data["Frames"];

      TileSheets[texname] = std::make_shared<TileSheet>();

      Json::Value rect;
      std::string tilename{ "" };
      sf::IntRect IRect{ 0, 0, 0, 0 };

      for (auto & frame : frames) {
        tilename = frame["Name"].asString();
        rect = frame["Rect"];

        IRect.left = rect[0].asInt();
        IRect.top = rect[1].asInt();
        IRect.width = rect[2].asInt();
        IRect.height = rect[3].asInt();

        TileSheets[texname]->AddTile(texname, IRect);
        TileSheets[texname]->SetTexture(Textures[sheet_data["Texture"].asString()]);
      }
    }
    catch (Json::Exception &err)
    {

    }
  }
  void Level::LoadAnimations(const Json::Value & value)
  {
    for (auto & anim : value) {

      std::string name = anim["Name"].asString();
      std::string texture = anim["Texture"].asString();
      float time = anim["FrameTime"].asFloat();
      bool bPingPong = anim["PingPong"].asBool();
      bool looping = anim["Looping"].asBool();

      auto it = Textures.find(texture);
      if (it == Textures.end())
        return;

      auto tex = it->second;
      Animations[name] = std::make_shared<Engine::Animation>();
      EditorGraphAnimations[name] = std::make_shared<Engine::Animation>();

      Animations[name]->SetSpriteSheet(tex, "Anim" + name + "sheet");
      EditorGraphAnimations[name]->SetSpriteSheet(tex, "AssetGraph" + name + "sheet");
      Animations[name]->SetFrameTime(time);
      EditorGraphAnimations[name]->SetFrameTime(time);

      std::vector<sf::IntRect> Frames = {};
      auto frames = anim["Frames"];
      sf::IntRect framerect = {};

      for (auto & frame : frames) {
        framerect.left = frame[0].asInt();
        framerect.top = frame[1].asInt();
        framerect.width = frame[2].asInt();
        framerect.height = frame[3].asInt();

        Animations[name]->AddFrame(framerect);
        EditorGraphAnimations[name]->AddFrame(framerect);
      }

      Animations[name]->MakePingPong(bPingPong);
      EditorGraphAnimations[name]->MakePingPong(bPingPong);
      Animations[name]->MakeLooped(looping);
      EditorGraphAnimations[name]->MakeLooped(looping);
    }
  }
}