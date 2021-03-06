#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<chrono>
#include"display.h"


using namespace std;
using namespace sf;





int main() {
	initialize_intro();
	initialize_buttons();
	initialize_background();
	intialize_banana();
	initialize_font();
	initialize_sounds();

	Music intro_music;
	intro_music.openFromFile("sounds/intro.ogg");
	intro_music.play();

	RenderWindow app(VideoMode(480, 720), "TAQUIN",Style::Close);
	app.setFramerateLimit(60);

	sf::Image icon;
	icon.loadFromFile("images/TAQUIN.ico");
	app.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
	while (app.isOpen()) {
		intro_animation(app);
		Event e;
		display_currentState(app, e);
		display_version(app);
		app.display();
	}
}