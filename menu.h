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
    bool picture_mode;
    bool number_mode;
public:
    options_menu() {
        picture_mode = false;
        number_mode = true;
    }
    void switch_picture_mode() {
        picture_mode = !picture_mode;
    }
    void switch_number_mode() {
        number_mode = !number_mode;
    }
    bool get_picture_mode() {
        return picture_mode;
    }
    bool get_number_mode() {
        return number_mode;
    }
};