/// Name: Krystian Sendyk
/// Login: krred4
/// Date: 24/01/2022

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	firstPlane();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMouse(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::processMouse(sf::Event t_event)
{
	float Pi = 3.14159265359;
	m_up.x = t_event.mouseButton.x;
	m_up.y = t_event.mouseButton.y;

	m_down.x = t_event.mouseButton.x;
	m_down.y = t_event.mouseButton.y;

	sf::Vector2f velocity = m_up - m_down;

	float radians = std::atan2(velocity.x, velocity.y);
	float headingDegrees = 180.0f * radians / Pi;
	headingDegrees += 90.0f;

	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Mouse::Left == t_event.mouseButton.button)
	{
		m_firstPlaneVel = velocity / 100.0f;
		m_firstPlaneHeading = headingDegrees;
		m_firstPlane.setRotation(headingDegrees);
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	move();
	border();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_sky);
	m_window.draw(m_instruction);
	m_window.draw(m_firstPlane);
	m_window.display();
}

void Game::sky()
{
	if (!m_tSky.loadFromFile("ASSETS\\IMAGES\\sky.jpeg"))
	{
		std::cout << "Problem with the image" << std::endl;
	}
	m_sky.setTexture(m_tSky);
	m_sky.setOrigin(sf::Vector2f{ 34.0f, 23.9f });
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_instruction.setFont(m_ArialBlackfont);
	m_instruction.setString("Use your right and left mouse clicks to move the planes");
	m_instruction.setStyle(sf::Text::Underlined);
	m_instruction.setPosition(40.0f, 40.0f);
	m_instruction.setCharacterSize(20U);
	m_instruction.setFillColor(sf::Color::Black);
}

void Game::firstPlane()//loads texture for first plane
{
	if (!m_firstPlaneTexture.loadFromFile("ASSETS\\IMAGES\\1 plane.png"))
	{
		std::cout << "Problem with the image" << std::endl;
	}
	m_firstPlane.setTexture(m_firstPlaneTexture);
	m_firstPlane.setPosition(m_firstPlaneLocation);
	m_firstPlane.setOrigin(sf::Vector2f{ 34.0f, 23.9f });
}

void Game::border()
{
	if (m_firstPlaneLocation.x < 40.0f)
	{
		m_firstPlaneLocation.x = 40.0f;
	}
	if (m_firstPlaneLocation.x > 800.0f - 40.0f)
	{
		m_firstPlaneLocation.x = 740.0;
	}
	if (m_firstPlaneLocation.y < 100.0f)
	{
		m_firstPlaneLocation.y = 100.0f;
	}
	if (m_firstPlaneLocation.y > 530.0f - 10.0f)
	{
		m_firstPlaneLocation.y = 520.0f;
	}
}

void Game::move()
{
	m_firstPlaneLocation += m_firstPlaneVel;

	m_firstPlane.setPosition(m_firstPlaneLocation);
	

}