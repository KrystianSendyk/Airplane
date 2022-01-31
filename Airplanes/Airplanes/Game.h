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
	
	void sky(); //sprite for the background
	void setupFontAndText(); //instruction for the players
	void firstPlane(); //sprite of the first plane
	
	void border();
	void move(); //movement for the planes

	sf::Sprite m_firstPlane; //image for first plane
	sf::Texture m_firstPlaneTexture; //Texture for first plane
	sf::Vector2f m_firstPlaneLocation = sf::Vector2f{ 350.0f, 280.0f }; //location of the first plane
	sf::Vector2f m_firstPlaneVel = { 0.0f, 0.0f }; //velocity of a plane
	float m_firstPlaneHeading = 45.0f; //degress of turn

	sf::Texture m_tSky; //texture for sky
	sf::Sprite m_sky; //sprite for sky

	sf::Vector2f m_up{ 0.0f, 0.0f };
	sf::Vector2f m_down{ 0.0f,0.0f };

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_instruction; // text used for message on screen
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP