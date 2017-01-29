#include "UIBeastary.h"
#include "../EECS581Project/SFEngine/Source/Headers/UI/Theme.h"
#include "../EECS581Project/SFEngine/Source/Headers/UI/UICreationMacros.h"

namespace Engine {

	UIBeastary::UIBeastary()
	{

		try {
			UIHelper = UI::WidgetHelper::Create();
			UILayer = UI::UILayer::Create(UIHelper);
			UIHelper->AddUILayer(UILayer);

			//MakeMenu(ObjectSelectMenu, UILayer, UIHelper);
			//MakeMenuDefaultScreen(ObjectSelectTypeScreen, UI::DefaultDarkTheme, ObjectSelectMenu);
			//MakeMenuScreen(ObjectSelectPhysicsObjectScreen, UI::DefaultDarkTheme, ObjectSelectMenu);
			//MakeMenuScreen(ObjectSelectLightObjectScreen, UI::DefaultDarkTheme, ObjectSelectMenu);
			//MakeMenuScreen(ObjectSelectEffectObjectScreen, UI::DefaultDarkTheme, ObjectSelectMenu);

			//AddMenuScreen(ObjectSelectMenu, ObjectSelectPhysicsObjectScreen);
			//AddMenuScreen(ObjectSelectMenu, ObjectSelectLightObjectScreen);
			//AddMenuScreen(ObjectSelectMenu, ObjectSelectEffectObjectScreen);
		} catch (std::exception &err) {
			std::cerr << "Fuck: " << err.what() << std::endl;
		}
	}


	UIBeastary::~UIBeastary()
	{
		//TestMenu->Close();
	}


	void UIBeastary::TickUpdate(const double &delta)
	{

		//UIHelper->TickUpdate(delta);
	}

	void UIBeastary::Render(std::shared_ptr<sf::RenderTexture> Texture)
	{
		//UIHelper->Render(Texture);
	}
}