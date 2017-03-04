#include "../../Headers/Lights/LightingSystem.h"

namespace Engine
{

#define ____PI 3.141592653
#define COSPIBY4 0.25

#define MAX_CIRCLE_ANGLE 512
#define HALF_MAX_CIRCLE_ANGLE (MAX_CIRCLE_ANGLE >> 1)
#define QUARTER_MAX_CIRCLE_ANGLE (MAX_CIRCLE_ANGLE >> 2)
#define MASK_MAX_CIRCLE_ANGLE (MAX_CIRCLE_ANGLE - 1)
#define PI 3.141592653589793238f

#define USE_LOOKUP_TABLE

  float CosineTable[MAX_CIRCLE_ANGLE];

  inline void FtoInt(int *int_ptr, float f) {
    __asm fld f
    __asm mov edx, int_ptr
    __asm FRNDINT
    __asm fistp dword ptr[edx];
  }

  inline float fastcos(float n) {
    float f = n * HALF_MAX_CIRCLE_ANGLE / PI;
    int i;
    FtoInt(&i, f);
    return(
      i < 0 ?
      CosineTable[((-i) + QUARTER_MAX_CIRCLE_ANGLE) & MASK_MAX_CIRCLE_ANGLE] :
      CosineTable[(i + QUARTER_MAX_CIRCLE_ANGLE) & MASK_MAX_CIRCLE_ANGLE]);
  }

  inline float fastsin(float n) {
    float f = n * HALF_MAX_CIRCLE_ANGLE / PI;
    int i;
    FtoInt(&i, f);
    return(
      i < 0 ?
      CosineTable[(-((-i)&MASK_MAX_CIRCLE_ANGLE)) + MAX_CIRCLE_ANGLE] :
      CosineTable[i & MASK_MAX_CIRCLE_ANGLE]);
  }

  LightSystem::LightSystem()
  {
    Edges.push_back({});
    Edges.push_back({});
    Edges.push_back({});
    Edges.push_back({});

    //Load the shaders
    LightShader = std::make_unique<sf::Shader>();
    LightShader->loadFromFile("./SFEngine/Source/CoreFiles/Shaders/LightShader.fsh", sf::Shader::Fragment);

    BlendShader = std::make_unique<sf::Shader>();
    BlendShader->loadFromFile("./SFEngine/Source/CoreFiles/Shaders/LightBlendShader.fsh", sf::Shader::Fragment);

#ifdef USE_LOOKUP_TABLE
    //pre-compute all of our sin/cos values  
    for (int i = 0; i < MAX_CIRCLE_ANGLE; ++i) {
      CosineTable[i] = (float)(std::sin((double)i * PI / HALF_MAX_CIRCLE_ANGLE));
    }
#endif
  }

  LightSystem::~LightSystem()
  {
  }

  void LightSystem::SetBoundaries(const sf::Vector2f & TopLeft, const sf::Vector2f & TopRight, const sf::Vector2f & BottomRight, const sf::Vector2f & BottomLeft)
  {
    Edges[0].Start = TopLeft; Edges[0].End = TopRight;
    Edges[1].Start = TopRight; Edges[1].End = BottomRight;
    Edges[2].Start = BottomRight; Edges[2].End = BottomLeft;
    Edges[3].Start = BottomLeft; Edges[3].End = TopLeft;
  }

  void LightSystem::AddLightObject(std::shared_ptr<LightObject> Object)
  {
    LightObjects[Object->ID] = Object;

    Edges.insert(Edges.end() - 0, Object->Edges.begin(), Object->Edges.end());
    std::cerr << "Light system now has: " << Edges.size() << " edges " << std::endl;
  }

  void LightSystem::AddComplexObject(const std::vector<sf::Vector2f>& positions)
  {
    for (std::size_t i = 1; i < positions.size(); ++i) {
      Edges.push_back({}); Edges.back().Start = positions[i - 1]; Edges.back().End = positions[i];

      //Segments.push_back(sf::VertexArray(sf::Lines, 2));
      //Segments.back()[0].position = positions[i - 1];
      //Segments.back()[1].position = positions[i];
      //Segments.back()[0].color = sf::Color::Yellow;
      //Segments.back()[1].color = sf::Color::Yellow;
    }
  }

  void LightSystem::RenderLightToTexture(std::shared_ptr<Light> light, std::shared_ptr<sf::RenderTexture> Target)
  {
    auto texSize = Target->getSize();

    LightShader->setUniform("color", sf::Glsl::Vec4(light->Color.r, light->Color.g, light->Color.b, light->Color.a));
    LightShader->setUniform("center", sf::Glsl::Vec2(WindowSize.x / 2.f, WindowSize.y / 2.f));
    LightShader->setUniform("radius", light->Radius);
    LightShader->setUniform("expand", 0.2f);
    LightShader->setUniform("windowHeight", (float)WindowSize.y);

    light->Circle.setRadius(light->Radius);
    light->Circle.setOrigin(light->Circle.getRadius(), light->Circle.getRadius());
    light->Circle.setPosition(sf::Glsl::Vec2(WindowSize.x / 2.f, WindowSize.y / 2.f));
    light->Circle.setFillColor(sf::Color::Transparent);

    Target->clear(sf::Color(0, 0, 0));
    Target->draw(light->Circle, LightShader.get());
    Target->display();
  }

  void LightSystem::BlurLightTexture(std::shared_ptr<Light> light)
  {
  }

  void LightSystem::BlendLightMapWithScene(std::shared_ptr<Light> light, std::shared_ptr<sf::RenderTexture> SceneTexture, std::shared_ptr<sf::RenderTexture> OutputTexture)
  {
    static sf::RectangleShape rect;
    rect.setSize(static_cast<sf::Vector2f>(SceneTexture->getSize()));
    state.shader = BlendShader.get();
    state.blendMode = sf::BlendAdd;

    BlendShader->setUniform("MaskTexture", LightMaps[light->ID]->getTexture());
    BlendShader->setUniform("SceneTexture", SceneTexture->getTexture());
    BlendShader->setUniform("MinimumIntensity", 1.f);
    BlendShader->setUniform("LightHue", sf::Glsl::Vec4(light->Color.r, light->Color.g, light->Color.b, light->Color.a));
    BlendShader->setUniform("HueIntensity", 0.3f);
    BlendShader->setUniform("MaximumIntensity", 10.f);

    OutputTexture->draw(rect, state);
  }

  void LightSystem::AddLight(std::shared_ptr<Light> light)
  {
    try
    {
      Lights[light->ID] = light;

      LightTextures[light->ID] = std::make_shared<sf::RenderTexture>();
      LightTextures[light->ID]->create(WindowSize.x, WindowSize.y);
      LightTextures[light->ID]->clear(sf::Color::Transparent);
      RenderLightToTexture(Lights[light->ID], LightTextures[light->ID]);
      LightTextures[light->ID]->display();
      LightMaps[light->ID] = std::make_shared<sf::RenderTexture>();
      LightMaps[light->ID]->create(WindowSize.x, WindowSize.y);
      auto image = LightTextures[light->ID]->getTexture().copyToImage();
      image.saveToFile("LIGHT_TEXTURE_IMAGE.png");
    }
    catch (IDException &err)
    {
      throw;
    }
  }

  void LightSystem::UpdateLight(std::shared_ptr<Light> light)
  {
    auto it = Lights.find(light->ID);
    if (it != Lights.end()) {
      it->second->Attenuation = light->Attenuation;
      it->second->Color = light->Color;
      it->second->Expand = light->Expand;
      it->second->Position = light->Position;
      it->second->Radius = light->Radius;

      RenderLightToTexture(light, LightTextures[light->ID]);
    }
  }

  void LightSystem::SweepLight(std::shared_ptr<Light> light)
  {
    //first move the bounding box with us
    float LeftSide = light->Position.x - light->Attenuation;
    float RightSide = light->Position.x + light->Attenuation;
    float TopSide = light->Position.y - light->Attenuation;
    float BottomSide = light->Position.y + light->Attenuation;

    Edges[0].Start = { LeftSide, TopSide }; Edges[0].End = { RightSide, TopSide };
    Edges[1].Start = { RightSide, TopSide }; Edges[1].End = { RightSide, BottomSide };
    Edges[2].Start = { RightSide, BottomSide }; Edges[2].End = { LeftSide, BottomSide };
    Edges[3].Start = { LeftSide, BottomSide }; Edges[3].End = { LeftSide, TopSide };

    static int frame_count = 0;
    static float x_dir = -1, y_dir = 0;
    static int LastHitEdge = -1;
    static sf::Vector2f LAST_SEGMENT_ENDED;
    static sf::Vector2f SEGMENT_STARTED;
    static sf::Vector2f SWEEP_VERY_BEGINNING;

    LAST_SEGMENT_ENDED = sf::Vector2f(WindowSize.x / 2.f, WindowSize.y);
    SEGMENT_STARTED = sf::Vector2f(WindowSize.x / 2.f, WindowSize.y);
    SWEEP_VERY_BEGINNING = sf::Vector2f(WindowSize.x / 2.f, WindowSize.y);

    THETA = 0;
    LastHitEdge = -1;
    int PIBY2OFFSET = (int)(breaks_around_circle / 4.f);

    dTheta = 2 * PI / breaks_around_circle;

    std::chrono::system_clock::time_point Start = std::chrono::system_clock::now();
    sf::Vector2f Intersection;

    //So we don't have to redraw the light texture, figure out what the offset is from the center of the texture
    //and offset the texture coordinates by that much
    auto texSize = LightTextures[light->ID]->getSize();
    sf::Vector2f CenterOfTexture = sf::Vector2f(texSize.x / 2.f, texSize.y / 2.f);
    sf::Vector2f OffsetFromCenterOfTexture = light->Position - CenterOfTexture;
    sf::Vector2f PreviousPoint = {};

    std::size_t index = 0;
    LightTriangles.clear();
    LightTriangles = sf::VertexArray(sf::Triangles);
    THETA = 0.f;

    while (THETA <= 2 * PI) {

#ifdef USE_LOOKUP_TABLE

      y_dir = fastsin(THETA);
      x_dir = fastcos(THETA);
#else
      y_dir = std::sin(THETA);
      x_dir = std::cos(THETA);
#endif

      THETA += dTheta;

      sf::Vector2f dir{ x_dir, y_dir }; //should not need to normalize

      sf::Vector2f furthest_point = light->Position;
      furthest_point.x += x_dir * light->Attenuation;
      furthest_point.y += y_dir * light->Attenuation;
      int edge_index = -1;

      if (FindClosestEdge(light->Position, furthest_point, light->Attenuation, Intersection, edge_index)) {

        //we just stepped off an edge
        if (LastHitEdge != edge_index) {
          if (LastHitEdge != -1) {

            //and the ending point for the last segment will be determined by one final ray cast, exactly in the direction of the point, but at the segment we just left
            sf::Vector2f StoppingPoint = CastRay(light->Position, Intersection, Edges[LastHitEdge].Start, Edges[LastHitEdge].End);
            //now that we have that, we can cap off 

            sf::Vertex V1, V2, V3;
            V1.position = light->Position;
            V1.texCoords = light->Position - OffsetFromCenterOfTexture;

            V2.position = SEGMENT_STARTED;
            V2.texCoords = SEGMENT_STARTED - OffsetFromCenterOfTexture;

            V3.position = StoppingPoint;
            V3.texCoords = StoppingPoint - OffsetFromCenterOfTexture;
            LightTriangles.append(V1);
            LightTriangles.append(V2);
            LightTriangles.append(V3);

            //we need the starting point for this segment to be the point on the edge closest to this intersection
            //for now, we will just use the intersecion point. This will be improved later
            //  IF we sweep around with a high enough precision, this will probably never be noticable
            SEGMENT_STARTED = Intersection;
          }
          else {
            //make sure we start off at the right point
            SEGMENT_STARTED = Intersection;

            //also mark the very beginning so we can get to it when we loop back around
            SWEEP_VERY_BEGINNING = Intersection;
          }

          LastHitEdge = edge_index;
        }
      }
      else {
      }

      LastHitEdge = edge_index;
    }

    //on our very last iteration, we shouldn't have been able to cap off the last triangle. We need to do so
    sf::Vertex V1, V2, V3;
    V1.position = light->Position;
    V1.texCoords = light->Position - OffsetFromCenterOfTexture;

    V2.position = SEGMENT_STARTED;
    V2.texCoords = SEGMENT_STARTED - OffsetFromCenterOfTexture;

    V3.position = SWEEP_VERY_BEGINNING;
    V3.texCoords = SWEEP_VERY_BEGINNING - OffsetFromCenterOfTexture;
    LightTriangles.append(V1);
    LightTriangles.append(V2);
    LightTriangles.append(V3);
    LastHitEdge = -1;
  }

  void LightSystem::DrawLightMap(std::shared_ptr<Light> light)
  {
    static sf::RenderStates state;

    LightMaps[light->ID]->clear(sf::Color::Transparent);
    LightMaps[light->ID]->draw(LightTriangles, &LightTextures[light->ID]->getTexture());
    LightMaps[light->ID]->display();
  }


  bool LightSystem::CanIntersectSegment(sf::Vector2f start, sf::Vector2f end, sf::Vector2f light_source, sf::Vector2f vector, float rad)
  {
    sf::Vector2f VecToStart = start - light_source;
    sf::Vector2f VecToEnd = end - light_source;
    Normalize(VecToStart);
    Normalize(VecToEnd);

    float _acrossb = Cross2D(VecToStart, vector);
    float _acrossc = Cross2D(VecToStart, VecToEnd);
    float _ccrossb = Cross2D(VecToEnd, vector);
    float _ccrossa = Cross2D(VecToEnd, VecToStart);

    return ((_acrossb * _acrossc >= 0) && (_ccrossa * _ccrossb >= 0));
  }

  bool LightSystem::FindClosestEdge(sf::Vector2f LightSource, sf::Vector2f Point, float Attenuation, sf::Vector2f & Intersection, int &edge_index)
  {
    sf::Vector2f VecToPoint;
    sf::Vector2f VecToStart;
    sf::Vector2f VecToEnd;
    
    float Distance = FLOAT_MAX;
    float MinDistance = FLOAT_MAX;
    bool DidIntersect = false;

    sf::Vector2f ClosestEdge{ FLOAT_MAX, FLOAT_MAX };
    sf::Vector2f MaybeClosestEdge{ FLOAT_MAX, FLOAT_MAX };
    edge_index = -1;
    std::size_t index = 0;
    for (auto & edge : Edges) {

      if (CanIntersectSegment(edge.Start, edge.End, LightSource, Point, Attenuation)) {
        MaybeClosestEdge = CastRay(LightSource, Point, edge.Start, edge.End);

        if ((Distance = DistanceBetween(LightSource, MaybeClosestEdge)) < MinDistance) {
          MinDistance = Distance;
          ClosestEdge = MaybeClosestEdge;
          edge_index = index;
          DidIntersect = true;
        }
      }

      index++;
    }

    if (DidIntersect) {
      Intersection = ClosestEdge;
    }

    return DidIntersect;
  }


  void LightSystem::DrawLightTexture(std::size_t which)
  {
    sf::Color color = Lights[which]->Color;
    sf::Vector2f Center = { WindowSize.x / 2.f, WindowSize.y / 2.f };
    float rad = Lights[which]->Radius;
    float exp = Lights[which]->Expand;

    sf::CircleShape circle;
    circle.setRadius(rad);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(Center);
    circle.setFillColor(sf::Color::Transparent);

    LightShader->setUniform("color", sf::Glsl::Vec4(color.r, color.g, color.b, color.a));
    LightShader->setUniform("center", Center);
    LightShader->setUniform("radius", rad);
    LightShader->setUniform("expand", exp);
    LightShader->setUniform("windowHeight", (float)WindowSize.y);

    LightTextures[which]->clear();
    LightTextures[which]->draw(circle, LightShader.get());
    LightTextures[which]->display();
  }

  void Normalize(sf::Vector2f & v)
  {
    float mag = std::sqrt((v.x * v.x) + (v.y * v.y));
    v.x /= mag;
    v.y /= mag;
  }

  float Cross2D(const sf::Vector2f & v1, const sf::Vector2f & v2)
  {
    return ((v1.x * v2.y) - (v1.y * v2.x));
  }

  float DistanceBetween(const sf::Vector2f & v1, const sf::Vector2f & v2)
  {
    float x = v1.x - v2.x;
    float y = v1.y - v2.y;

    return (std::sqrt((x * x) + (y * y)));
  }

}
