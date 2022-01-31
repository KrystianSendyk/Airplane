/// Name: Krystian Sendyk
/// Login: krred4
/// Date: 24/01/2022
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouse(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void firstPlane();
	
	enum class direction
	{
		up, down, left, right
	};
	void move();

	sf::Sprite m_firstPlane; //image for first plane
	sf::Texture m_planeTex1; //Texture for first plane
	sf::Vector2f m_location1Plane = sf::Vector2f{ 350.0f, 280.0f };

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_instruction; // text used for message on screen
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

