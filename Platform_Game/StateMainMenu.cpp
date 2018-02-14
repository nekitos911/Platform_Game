#include "StateMainMenu.h"


StateMainMenu::StateMainMenu(StateManager *stateManager) : BaseState(stateManager)
{
}


StateMainMenu::~StateMainMenu()
{
}

void StateMainMenu::OnCreate()
{
	menuNumber_ = 0;

	sf::Vector2u windowSize = stateManager_->GetContext()->window_->GetRenderWindow()->getSize();
	TextureManager *textureManager = stateManager_->GetContext()->textureManager_;
	textureManager->RequireResource("Intro");
	menuSprite_.setTexture(*textureManager->GetResource("Intro"));
	menuSprite_.setOrigin(textureManager->GetResource("Intro")->getSize().x / 2.0f,
		textureManager->GetResource("Intro")->getSize().y / 2.0f);
	menuSprite_.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	font_.loadFromFile("Test.ttf");

	std::string str[3] = {"PLAY","CREDITS","EXIT"};

	buttonPadding_ = 20; // 20px

	for(int i = 0;i < 3;++i)
	{
		lables_[i].setFont(font_);
		lables_[i].setString(sf::String(str[i]));
		lables_[i].setCharacterSize(32);

		sf::Vector2f _buttonPos(menuSprite_.getPosition().x, menuSprite_.getPosition().y +
			textureManager->GetResource("Intro")->getSize().y / 1.5f + (i * (buttonPadding_ + lables_[i].getLocalBounds().height / 2.0f)));

		sf::FloatRect rect = lables_[i].getLocalBounds();
		lables_[i].setOrigin(rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);
		lables_[i].setPosition(_buttonPos);
	}
	lables_[0].setFillColor(sf::Color::Blue);

	EventManager *eventManager = stateManager_->GetContext()->eventManager_;
	eventManager->AddCallback(StateType::MainMenu, "Key_Down", &StateMainMenu::OnClick, this);
	eventManager->AddCallback(StateType::MainMenu, "Key_Up", &StateMainMenu::OnClick, this);
	eventManager->AddCallback(StateType::MainMenu, "Enter_Pressed", &StateMainMenu::OnClick, this);
}

void StateMainMenu::OnDestroy()
{
	TextureManager *textureManager = stateManager_->GetContext()->textureManager_;
	textureManager->ReleaseResource("Intro");

	EventManager *evMgr = stateManager_->GetContext()->eventManager_;
	evMgr->RemoveCallback(StateType::MainMenu, "Key_Up");
	evMgr->RemoveCallback(StateType::MainMenu, "Key_Down");
	evMgr->RemoveCallback(StateType::MainMenu, "Enter_Pressed");
}

void StateMainMenu::Activate()
{
	if(stateManager_->HasState(StateType::Game) &&
		lables_[0].getString() != "RESUME")
	{
		lables_[0].setString(sf::String("RESUME"));
	} else
	{
		lables_[0].setString(sf::String("PLAY"));
	}

	sf::FloatRect rect = lables_[0].getLocalBounds();
	lables_[0].setOrigin(rect.left + rect.width / 2.0f,
		rect.top + rect.height / 2.0f);
}

void StateMainMenu::OnClick(EventDetails* details)
{
	SharedContext *context = stateManager_->GetContext();

	if (details->name_ == "Key_Down")
	{
		if(menuNumber_ < 2)
			++menuNumber_;
		else
		{
			menuNumber_ = 0;
		}
	}
	else if (details->name_ == "Key_Up")
	{
		if(menuNumber_ > 0)
			--menuNumber_;
		else
		{
			menuNumber_ = 2;
		}
	}
	for(int k = 0;k < 3; ++k)
	{
		lables_[k].setFillColor(sf::Color::White);
	}
	lables_[menuNumber_].setFillColor(sf::Color::Blue);

	if(details->name_ == "Enter_Pressed")
	{
		switch (menuNumber_)
		{
		case 0:
			stateManager_->SwitchTo(StateType::Game);
			break;
		case 1:
			//Credits
			break;
		case 2:
			stateManager_->GetContext()->window_->Close();
		}
	}
}

void StateMainMenu::Draw()
{
	sf::RenderWindow *window = stateManager_->GetContext()->window_->GetRenderWindow();
	//window->draw(text_);
	window->draw(menuSprite_);
	for(int i = 0;i < 3;++i)
	{
		//window->draw(rects_[i]);
		window->draw(lables_[i]);
	}
}


void StateMainMenu::Update(const sf::Time& time)
{}
void StateMainMenu::Deactivate()
{}



