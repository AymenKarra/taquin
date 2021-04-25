#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<chrono>
#include"GameManager.h"

using namespace std;
using namespace sf;

/*Sprite* convertToTable(int n, string name) {
	Sprite* tab;
	tab = new Sprite[n * n];
	Texture t;
	t.loadFromFile("images/15.png");
	int w = 64;
	int c = 1;
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n; j++) {
			tab[c].setTexture(t);
			tab[c].setTextureRect(IntRect(i*w,j*w,w,w));
			c++;
		}
	}
	return tab;
}*/

int main() {
	Music music;
	Music woow;
	music.openFromFile("sounds/Spanish Flea (Herb Albert) - Comedy Background Music (HD).ogg");
	music.setLoop(true);
	SoundBuffer buffer;
	buffer.loadFromFile("sounds/Roblox Death Sound - Sound Effect (HD)-[AudioTrimmer.com].ogg");
	Sound sound;
	sound.setBuffer(buffer);
	cout << "enter the level you want to play, levels 3,4,5" << endl;
	int n;
	cin >> n;
	while (!(n == 3 || n == 4 || n == 5)) {
		cout << "invalid level, please enter again" << endl;
		cin >> n;
	}
	GameMaster game(n);
	RenderWindow app(VideoMode(91 * n, 91 * n), "TAQUIN");
	app.setFramerateLimit(60);
	Texture t;
	t.loadFromFile("images/numbers.png");
	int w = 91;
	Sprite sprite[25];
	for (int i = 0; i < n * n;i++) {
		sprite[i + 1].setTexture(t);
		sprite[i + 1].setTextureRect(IntRect(i * w, 0, w, w));
	}
	music.play();
	chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	while (app.isOpen()) {
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
				{
					Vector2i pos = Mouse::getPosition(app);
					int x = pos.x / w;
					int y = pos.y / w;

					game.move(y, x);
					sound.play();
				}

		}
		app.clear(Color::White);
		for (int i = 0;i < n;i++)
			for (int j = 0;j < n;j++)
			{
				int num = game.getItem(i, j);
				sprite[num].setPosition(j * w, i * w);
				app.draw(sprite[num]);
			}
		app.display();
		if (game.GameOver()) {
			std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
			int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
			woow.openFromFile("sounds/Anime wow sound effect.ogg");
			music.stop();
			woow.play();
			cout << "w";
			for (int i = 0;i < 50000;i++) cout << "o";
			cout << "w" << endl;
			cout << "time:" << elapsed_seconds << "seconds" << endl;
			app.close();
		}
	}
}
