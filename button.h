#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;

class Button {
protected:
	Sprite idle, hover;
	Sound sound;
	pair<int, int> position,dimension;
	bool playing = false;
public:
	Button() {};
	Button( Sprite idle, Sprite hover, SoundBuffer& buffer, int x, int y, int width=0, int height=0) {
		this->idle = idle;
		this->hover = hover;
		sound.setBuffer(buffer);
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
	ToggleButton(Sprite on, Sprite off, SoundBuffer& buffer, int x, int y, int width = 0, int height = 0) :Button(on, off, buffer, x, y, width, height) {
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
