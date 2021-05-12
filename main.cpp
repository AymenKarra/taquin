#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<chrono>
#include"GameManager.h"
#include"display.h"

using namespace std;
using namespace sf;

Sprite sprite[25];


int main() {
	Music music;
	Music woow;
	music.openFromFile("sounds/Spanish Flea (Herb Albert) - Comedy Background Music (HD).ogg");
	music.setLoop(true);
	SoundBuffer buffer;
	buffer.loadFromFile("sounds/Roblox Death Sound - Sound Effect (HD)-[AudioTrimmer.com].ogg");
	Sound sound;
	sound.setBuffer(buffer);
	int n;
	cout << "enter the level you want to play, levels 3,4,5" << endl;
	cin >> n;
	int choice;
	cout << "type 1 for numbers \ntype 2 for photo\n";
	cin >> choice;
	while (!(n == 3 || n == 4 || n == 5)) {
		cout << "invalid level, please enter again" << endl;
		cin >> n;
	}
	GameMaster game(n);
	RenderWindow app(VideoMode(480, 720), "TAQUIN");//RenderWindow app(VideoMode(91 * n, 91 * n), "TAQUIN");
	app.setFramerateLimit(60);
	int w;
	Texture t;
	if (choice == 1) {
		t.loadFromFile("images/numbers.png");
		w = 480/n;
		int w2 = 91;
		float scale = 480.0 / (91 * n);
		for (int i = 0; i < n * n;i++) {
			sprite[i + 1].setTexture(t);
			sprite[i + 1].setTextureRect(IntRect(i * w2, 0, w2, w2));
			sprite[i + 1].setScale(scale,scale);
		}
	}
	//
	if (choice == 2) {
		w = 480 / n;
		string name = "image.jpg";
		t.loadFromFile("images/" + name);
		Sprite photo;
		photo.setTexture(t);
		int l = min(photo.getGlobalBounds().width, photo.getGlobalBounds().height);
	    float scale = 480.0 / l;
		cout << l << "et" << scale;
		//float scale =0.5;
		photo.setTextureRect(IntRect(0, 0, l, l));
		//photo.setScale(scale, scale);
		cout << photo.getGlobalBounds().width << "et" << photo.getGlobalBounds().height;
		float w2 = l / n;
		int c = 1;
		for (int i = 0;i < n;i++) {
			for (int j = 0;j < n; j++) {
				sprite[c] = photo;
				sprite[c].setTextureRect(IntRect(j * w2, i * w2, w2, w2));
				sprite[c].setScale(scale, scale);
				c++;
			}
		}
		cout << sprite[1].getLocalBounds().height;
	}
	
	//
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
					int y =(pos.y-240) / w;
					game.move(y, x);
					sound.play();
				}
		}
		app.clear(Color::White);
		for (int i = 0;i < n;i++)
			for (int j = 0;j < n;j++)
			{
				int num = game.getItem(i, j);
				sprite[num].setPosition(j * w,240+ i * w);
				app.draw(sprite[num]);
			}
		app.display();


		if (game.GameOver()) {
			std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
			int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
			woow.openFromFile("sounds/Anime wow sound effect.ogg");
			music.stop();
			woow.play();
			/*cout << "w";
			for (int i = 0;i < 50000;i++) cout << "o";
			cout << "w" << endl;*/
			cout << "time:" << elapsed_seconds << "seconds" << endl;
			//app.close();
		}
	}
}
