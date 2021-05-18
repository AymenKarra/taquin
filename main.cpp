#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<chrono>
#include"GameManager.h"
#include"display.h"


using namespace std;
using namespace sf;





int main() {
	initialize_buttons();
	initialize_background();
	hover.loadFromFile("sounds/hover.ogg");
	click_buffer.loadFromFile("sounds/click.ogg");
	click.setBuffer(click_buffer);
	menu_music.openFromFile("sounds/main music.ogg");
	menu_music.setVolume(20);
	play_music.openFromFile("sounds/play music.ogg");
	victory_music.openFromFile("sounds/victory.ogg");
	victory_music.setVolume(50);
	game_texture.loadFromFile("images/game background.png");
	game_background.setTexture(game_texture);
	game_background.setScale(0.5,0.5);
	slide_buffer.loadFromFile("sounds/slide click.ogg");
	slide_sound.setBuffer(slide_buffer);
	Texture intro_texture[47];
	Sprite intro[47];
	for (int i = 0;i <= 46;i++) {
		intro_texture[i].loadFromFile("images/intro/intro 720_Trim_0" + to_string(i) + ".jpg");
		intro[i].setTexture(intro_texture[i]);
	}
	bool intro_finished = false;
	Music intro_music;
	intro_music.openFromFile("sounds/intro.ogg");
	intro_music.play();


	//Music music;
	//Music woow;
	//music.openFromFile("sounds/Spanish Flea (Herb Albert) - Comedy Background Music (HD).ogg");
	//music.setLoop(true);
	//SoundBuffer buffer;
	//buffer.loadFromFile("sounds/Roblox Death Sound - Sound Effect (HD)-[AudioTrimmer.com].ogg");
	//Sound sound;
	//sound.setBuffer(buffer);
	//int n;
	//int choice;
	//cout << "type 1 for numbers \ntype 2 for photo\n";
	//cin >> choice;
	//GameMaster game(n);
	RenderWindow app(VideoMode(480, 720), "TAQUIN",Style::Close);//RenderWindow app(VideoMode(91 * n, 91 * n), "TAQUIN");
	app.setFramerateLimit(60);
	//int w;
	//Texture t;
	/*if (choice == 1) {
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
	
	*/
	//music.play();
	//chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	while (app.isOpen()) {
		/*Event e;
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
		app.display();*/
		Event e;
		if (!intro_finished) {
			for (int i = 0;i <= 46;i++) {
				for (int j = 0;j < 4;j++) {
					app.draw(intro[i]);
					app.display();
				}
			}
			intro_finished = true;
			sleep(seconds(3));
		}
		
		display_currentState(app, e);
		app.display();
		
			
		


		/*if (game.GameOver()) {
			std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
			int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
			woow.openFromFile("sounds/Anime wow sound effect.ogg");
			music.stop();
			woow.play();
			cout << "w";
			for (int i = 0;i < 50000;i++) cout << "o";
			cout << "w" << endl;
			cout << "time:" << elapsed_seconds << "seconds" << endl;
			//app.close();
		}*/
	}
}