
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "raylib.h"
#include "Button.h"
#include "BitmapFont.h"

using namespace std;

class Game
{
protected:
    Image background;
    Texture2D texture;

    int ScreenWidth;
    int ScreenHeight;

    Music intro_music;
    Button* ButtonNext;
    BitmapFont* bmpFont1;

    Vector2 touchPosition = { 0, 0 };
    int currentGesture = GESTURE_NONE;
    bool visible = false;
    bool resources_loaded = false;
    enum { SCREEN_LOADING, SCREEN_INTRO, SCREEN_MENU } actual_screen = SCREEN_LOADING;

    void LoadResources();
    void UpdateKeyboard();
    void Draw();
    void DrawHUD();
    void DrawBackground();
    void CleanResources();

public:
    Game();
    ~Game();
    bool IsVisible() const;
    void Show();
    void Hide();
    void Run();
    void cls();

};



