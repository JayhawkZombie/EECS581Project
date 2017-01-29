#pragma once
#ifndef UIBeastary_H
#define UIBeastary_H
#include <SFML/Graphics.hpp>

#include "../EECS581Project/SFEngine/Source/Headers/BasicIncludes.h"

#include "../EECS581Project/SFEngine/Source/Headers/Actor/Player.h"
#include "../EECS581Project/SFEngine/Source/Headers/Animation/Animation.h"
#include "../EECS581Project/SFEngine/Source/Headers/Render/Render.h"

#include "../EECS581Project/SFEngine/Source/Headers/UI/List/List.h"
#include "../EECS581Project/SFEngine/Source/Headers/UI/Text/TextLabel.h"
#include "../EECS581Project/SFEngine/Source/Headers/UI/WIdgetHelper.h"
#include "../EECS581Project/SFEngine/Source/Headers/UI/Buttons/ClickButtonBase.h"
#include "../EECS581Project/SFEngine/Source/Headers/UI/Draggables/DraggableTile.h"
#include "../EECS581Project/SFEngine/Source/Headers/UI/Alerts/PopupObject.h"

#include "../EECS581Project/SFEngine/Source/Headers/UI/Alerts/Alert.h"

#include "../EECS581Project/SFEngine/Source/Headers/UI/Menu/MenuWidget.h"
#include "../EECS581Project/SFEngine/Source/Headers/UI/Menu/MenuScreen.h"

namespace Engine {

	class UIBeastary
	{
	public:
		UIBeastary();
		~UIBeastary();

		void TickUpdate(const double &delta);
		void Render(std::shared_ptr<sf::RenderTexture> Texture);

	protected:
		std::shared_ptr<UI::WidgetHelper> UIHelper;
		std::shared_ptr<UI::UILayer> UILayer;


	};

}

#endif