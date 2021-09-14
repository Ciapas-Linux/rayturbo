

#ifndef RAYTURBO_BUTTON_H
#define RAYTURBO_BUTTON_H

#include <sys/time.h>
#include <cstring>
#include <string>
#include <stdio.h>
#include <iosfwd>
#include "raylib.h"

using namespace std;

#define BNUM_FRAMES  3

class Button
{
private:
    int ScreenWidth;
    int ScreenHeight;

    string ImageFileName;
    string SoundFileName;

    Texture2D ButtonTexture;
    Sound fxButton;
    double LastClickTime;
    long TimeOut = 200;
    struct timeval tv;

    bool visible = true;
    float frameHeight;
    Rectangle sourceRec;
    Rectangle dstRec;
    bool initial_position;
    int btnState = 0;

    bool resources_loaded = false;

    void ReLoadResources();
    void CleanResources();
    long long TimeInMilliseconds();

public:
    Button(int sWidth, int sHeight,int timeout);
    ~Button();
    void LoadResources(const char *TextureName,const char *SoundName);
    bool ClickStatus(Vector2 tap_point);
    void Draw();
    void UpdateTimer();
    bool IsVisible() const;
    void Move(int x,int y);
    void MoveADD(int x,int y);
    void MoveSUB(int x,int y);
    void MoveCenter();
    void MoveBottomCenter();
    void Show();
    void Hide();
};


#endif //RAYTURBO_BUTTON_H
