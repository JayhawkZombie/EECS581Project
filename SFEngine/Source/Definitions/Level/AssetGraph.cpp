#include "../../Headers/Level/Level.h"

#ifdef WITH_EDITOR

namespace Engine
{

  namespace
  {

    std::map<std::string, sf::Sound> Sounds;

    std::shared_ptr<Animation> AnimPlaying;
  }

  void ShowTexture(const std::string &name, std::shared_ptr<sf::Texture> Texture)
  {
    if (ImGui::CollapsingHeader(name.c_str())) {

      auto dim = Texture->getSize();

      std::string size = "Size: < " + std::to_string(dim.x) + ", " + std::to_string(dim.y) + ">";
      ImGui::Text("Size: <%u, %u>", dim.x, dim.y);
      ImGui::Image(*Texture, ImVec2(100, 100));
    }
  }

  void ShowAudio(const std::string &name, std::shared_ptr<sf::SoundBuffer> Buffer)
  {
    if (ImGui::CollapsingHeader(name.c_str())) {

      auto time = Buffer->getDuration();
      auto sRate = Buffer->getSampleRate();
      auto channels = Buffer->getChannelCount();

      ImGui::Text("Duration: %i seconds", time.asSeconds());
      ImGui::Text("Sample Rate: %i", sRate);
      ImGui::Text("Channels: %i", channels);

      if (Sounds.find(name) != Sounds.end()) {
        if (ImGui::Button("Stop")) {
          Sounds[name].stop();
          Sounds.erase(name);
        }
      }
      else {
        if (ImGui::Button("Play")) {
          Sounds[name].setBuffer(*Buffer);
          Sounds[name].play();
        }
      }

    }
  }

  void ShowAnimationGraphNode(const std::string &name, std::shared_ptr<Animation> Anim)
  {
    static ImVec2 siz;

    static float minX = std::min(100.f, Anim->GetRect().getSize().x);
    static float scale = 100.f / (minX == 0 ? 1 : minX);

    if (ImGui::CollapsingHeader(name.c_str())) {

      ImGui::Text("Name: %s", name.c_str());
      static int dragint = 1;
      ImGui::Columns(2);

      ImGui::Image(*(Anim->GetSpriteSheet()), ImVec2(100, 100), static_cast<sf::FloatRect>(Anim->GetCurrentFrame()));
      ImGui::NextColumn();

      if (ImGui::DragInt("FrameTime: ", &dragint, 1.f, 10, 100)) {
        Anim->SetFrameTime(dragint);
      }

      if (Anim->IsPlaying()) {
        if (ImGui::Button("Stop"))
          Anim->Stop();
      }
      else {
        if (ImGui::Button("Play"))
          Anim->Play();
      }

      ImGui::Columns(1);
    }
  }

  void Level::ShowAnimationEditor(const std::string &name)
  {
    if (ImGui::BeginPopup("Animation Editor")) {

      AnimPlaying = Animations[name];

      ImGui::Text("Name: "); ImGui::SameLine();
      ImGui::Text(name.c_str());


      ImGui::EndPopup();
    }
  }

  void Level::ShowAssetGraph()
  {

    if (!ImGui::Begin("Asset Viewer")) {
      ImGui::End();

      return;
    }

    if (ImGui::CollapsingHeader("Assets : Count<NoTotalCount>")) {
      ImGui::Indent();

      static std::string texcnt = "Textures";
      texcnt = "Textures | Count: " + std::to_string(Textures.size());
      if (ImGui::CollapsingHeader(texcnt.c_str())) {
        ImGui::Indent();

        int i = 0;

        for (auto it = Textures.begin(); it != Textures.end(); ++it) {
          ImGui::PushID(i);
          ShowTexture(it->first, it->second);
          ImGui::PopID();
        }

        ImGui::Unindent();
      }

      static std::string animcnt = "Animations";
      animcnt = "Animations | Count: " + std::to_string(EditorGraphAnimations.size());
      if (ImGui::CollapsingHeader(animcnt.c_str())) {
        ImGui::Indent();

        int i = 300;

        for (auto it = EditorGraphAnimations.begin(); it != EditorGraphAnimations.end(); ++it) {
          ImGui::PushID(i);
          ShowAnimationGraphNode(it->first, it->second);
          ImGui::PopID();
        }

        ImGui::Unindent();
      }

      static std::string sndbuffsize = "Sounds";
      sndbuffsize = "Sounds | Count: " + std::to_string(SoundBuffers.size());
      if (ImGui::CollapsingHeader(sndbuffsize.c_str())) {
        ImGui::Indent();

        int i = 100;
        for (auto it = SoundBuffers.begin(); it != SoundBuffers.end(); ++it) {
          ImGui::PushID(i);
          ShowAudio(it->first, it->second);
          ImGui::PopID();
        }

        ImGui::Unindent();
      }

      static std::string fntsize = "Fonts";
      fntsize = "Fonts | Count: <None>";

      if (ImGui::CollapsingHeader(fntsize.c_str())) {
        ImGui::Indent();



        ImGui::Unindent();
      }


      static std::string shadersize = "Shaders";
      shadersize = "Shaders | Count: <None>";
      if (ImGui::CollapsingHeader(shadersize.c_str())) {
        ImGui::Indent();


        ImGui::Unindent();
      }

      static std::string scriptcount = "Scripts";
      scriptcount = "Scripts | Count: <None>";
      if (ImGui::CollapsingHeader(scriptcount.c_str())) {
        ImGui::Indent();



        ImGui::Unindent();
      }

      ImGui::Unindent();
    }

    ImGui::End();
  } //ShowAssetGraph

}

#endif
