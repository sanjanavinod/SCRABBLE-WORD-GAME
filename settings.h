#ifndef SETTINGS_H
#define SETTINGS_H

struct setting
{
    int size;
    int playerno;
};
void change_settings();
void load_settings();
extern int size;
extern int player_size;
#endif // SETTINGS_H

