#include<bits/stdc++.h>

using namespace std;

class main_menu {
public:
    bool main_menu_state;
    bool play_state;
    bool options_state;
    bool exit_state;
public:
    main_menu() {
        main_menu_state = true;
        play_state = false;
        options_state = false;
        exit_state = false;
    }
    void switch_main_menu_state() {
        main_menu_state = !main_menu_state;
    }
    void switch_play_state() {
        play_state = !play_state;
        main_menu_state = !main_menu_state;
    }
    void switch_options_state() {
        options_state = !options_state;
        main_menu_state = !main_menu_state;
    }
    void switch_exit_state() {
        exit_state = !exit_state;
        main_menu_state = !main_menu_state;
    }
    bool get_play_state() {
        return play_state;
    }
    bool get_options_state() {
        return options_state;
    }
    bool get_exit_state() {
        return exit_state;
    }
    bool get_main_state() {
        return main_menu_state;
    }
};
class play_menu {
private:
    bool modes[3];
public:
    play_menu() {
        for (int i = 0;i < 3;i++) {
            modes[i] = false;
        }
    }
    void select_level(int i) {
        modes[i - 3] = true;

    }
    int get_level() {
        for (int i = 0;i < 3;i++) {
            if(modes[i]) return i+3;
        }
        return 0;
    }
    void reset() {
        for (int i = 0;i < 3;i++) {
            modes[i] = false;
        }
    }
};
class options_menu {
private:
    bool pictures_mode;
    bool number_mode;
public:
    options_menu() {
        pictures_mode = false;
        number_mode = true;
    }
    void set_picture_mode() {
        pictures_mode = true;
        number_mode = false;
    }
    void set_numbers_mode() {
        number_mode = true;
        pictures_mode = false;
    }
    bool get_picture_mode() {
        return pictures_mode;
    }
    bool get_number_mode() {
        return number_mode;
    }
};
class game_over_menu {
private:
    bool game_over_state ;
public:
    game_over_menu() {
        game_over_state = false;
    }
    void switch_over_state() {
        game_over_state = !game_over_state;
    }
    bool get_over_state() {
        return game_over_state;
    }

};