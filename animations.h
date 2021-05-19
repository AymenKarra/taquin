#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;

Texture intro_texture[47];
Sprite intro[47];
bool intro_finished = false;

Texture banana_texture[8];
Sprite banana[8];
int banana_frame = 0;
int frame_counter = 0;

void initialize_intro(){
	for (int i = 0;i <= 46;i++) {
		intro_texture[i].loadFromFile("images/intro/intro 720_Trim_0" + to_string(i) + ".jpg");
		intro[i].setTexture(intro_texture[i]);
	}
}
void intro_animation(RenderWindow& app){
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

}

void intialize_banana() {
	for (int i = 0;i < 8;i++) {
		banana_texture[i].loadFromFile("images/victory/frame_" + to_string(i) + "_delay-0.1s.gif");
		banana[i].setTexture(banana_texture[i]);
		banana[i].setScale(0.5, 0.5);
		banana[i].setPosition(240 - banana[i].getGlobalBounds().width / 2, 370);
	}
}
void banana_animation(RenderWindow& app) {
	app.draw(banana[banana_frame]);
	frame_counter++;
	if (frame_counter > 6) {
		banana_frame = (banana_frame + 1) % 8;
		frame_counter = 0;
	}
}



class Button {
protected:
	Sprite idle, hover;
	Sound sound;
	pair<int, int> position,dimension;
	bool playing = false;
public:
	Button() {};
	Button( Sprite idle, Sprite hover, int x, int y, int width=0, int height=0) {
		this->idle = idle;
		this->hover = hover;

		this->position.first = x; this->position.second = y;
		if (width == 0 && height == 0) {
			this->dimension.first = this->hover.getGlobalBounds().width;
			this->dimension.second = this->hover.getGlobalBounds().height;
		}
		else {
			this->dimension.first = width;
			this->dimension.second = height;
			float scale1 = width / this->idle.getGlobalBounds().width;
			float scale2 = height / this->idle.getGlobalBounds().height;
			this->idle.setScale(scale1, scale2);
			this->hover.setScale(scale1, scale2);
		}

	}
	void setScale(float scale) {
		dimension.first = (int)(dimension.first*scale);
		dimension.second = (int)(dimension.second * scale);
		idle.setScale(scale, scale);
		hover.setScale(scale, scale);

	}
	void setPosition(int x, int y) {
		position.first = x;position.second = y;
	}
	bool inboundaries(Vector2i pos) {
		return((position.first <= pos.x && pos.x <= position.first + dimension.first) && (position.second <= pos.y && pos.y <= position.second + dimension.second));
	}
	void SoundState(bool state) {
		if (state == false)sound.setVolume(0);
		else sound.setVolume(100);
	}
	void setSound(SoundBuffer& buffer) {
		sound.setBuffer(buffer);
	}
	void display(RenderWindow& app) {
		idle.setPosition(position.first, position.second);
		hover.setPosition(position.first, position.second);
		Vector2i pos = Mouse::getPosition(app);
		if (inboundaries(pos)) {
			app.draw(hover);
			if (!playing) {
				sound.play();
				playing = true;
			}
		}
		else {
			app.draw(idle);
			playing = false;
		}
	}


	


};
class ToggleButton :public Button {
private:
	bool state;
public:
	ToggleButton(Sprite on, Sprite off, int x, int y, int width = 0, int height = 0) :Button(on, off, x, y, width, height) {
		state = true;
	};
	ToggleButton() {};
	void setOn() {
		state = true;
	}
	void setOff() {
		state = false;
	}
	bool getState() {
		return state;
	}
	void switchState() {
		state = !state;
	}
	void display(RenderWindow& app) {
		idle.setPosition(position.first, position.second);
		hover.setPosition(position.first, position.second);
		Vector2i pos = Mouse::getPosition(app);
		if (state) {
			app.draw(idle);
		}
		else {
			app.draw(hover);
		}

		if (inboundaries(pos)) {
			if (!playing) {
				sound.play();
				playing = true;
			}
		}
		else {
			playing = false;
		}
	}

	
};
