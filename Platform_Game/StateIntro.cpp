#include "StateIntro.h"



StateIntro::StateIntro(StateManager *stateManager) : BaseState(stateManager)
{}


StateIntro::~StateIntro()
{
}

void StateIntro::OnCreate()
{
	sf::Vector2u windowSize = stateManager_->GetContext()->window_->GetRenderWindow()->getSize();
	TextureManager *textureManager = stateManager_->GetContext()->textureManager_;
	textureManager->RequireResource("Intro");
	introSprite_.setTexture(*textureManager->GetResource("Intro"));
	introSprite_.setOrigin(textureManager->GetResource("Intro")->getSize().x / 2.0f,
		textureManager->GetResource("Intro")->getSize().y / 2.0f);
	elapsedTime_ = -1.0f;
	introSprite_.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
	text_.setString(sf::String("Press SPACE to continue"));
	font_.loadFromFile("Test.ttf");
	text_.setFont(font_);
	text_.setCharacterSize(20);
	sf::FloatRect textRect = text_.getLocalBounds();
	text_.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text_.setPosition(introSprite_.getPosition().x,
		introSprite_.getPosition().y + textureManager->GetResource("Intro")->getSize().y / 1.5f);

	EventManager *eventManager = stateManager_->GetContext()->eventManager_;
	eventManager->AddCallback(StateType::Intro, "Intro_Continue", &StateIntro::Continue,this);
}

void StateIntro::OnDestroy()
{
	TextureManager *textureManager = stateManager_->GetContext()->textureManager_;
	textureManager->ReleaseResource("Intro");

	EventManager *eventManager = stateManager_->GetContext()->eventManager_;
	eventManager->RemoveCallback(StateType::Intro, "Intro_Continue");
}

void StateIntro::Draw()
{
	sf::RenderWindow *window = stateManager_->GetContext()->window_->GetRenderWindow();
	window->draw(introSprite_);
	window->draw(text_);
}

void StateIntro::Continue(EventDetails* details)
{
	stateManager_->SwitchTo(StateType::MainMenu);
	stateManager_->Remove(StateType::Intro);
}

void StateIntro::Update(const sf::Time& time)
{
	elapsedTime_ += time.asSeconds();
	if (elapsedTime_ <= -0.5f)
	{
		text_.setFillColor(sf::Color::White);
	}
	else if(elapsedTime_ > -0.5f && elapsedTime_ < 0.0f)
	{
		text_.setFillColor(sf::Color::Black);
	}
	else if (elapsedTime_ >= 0.0f)
	{
		elapsedTime_ = -1;
	}
}

void StateIntro::Activate()
{}

void StateIntro::Deactivate()
{}


