//
// Created by kot on 10.09.2021.
//

#ifndef RAYTURBO_BITMAPFONT_H
#define RAYTURBO_BITMAPFONT_H

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <iosfwd>
#include "raylib.h"

using namespace std;

struct subtitles_data
{
    Vector2 txt_position;
    Vector2 Speed = Vector2 {0, 0};
    Vector2 Origin = Vector2 {0, 0};
    float Rotation = 0.0f;
    int spacing;
    float Scale;
    bool Visible;
    string TextData;
    unsigned int TextWidth;
    unsigned int TextHeight;
    vector<int> letter_x;
    vector<int> letter_y;
    vector<int> src_x_let_position;
    unsigned int subID;
};

class BitmapFont
{
public:
    BitmapFont(int fontHeight);
    ~BitmapFont();

    void LoadResources(const char *FontTextureName);
    void AddSubtitle(const char *Subtitle,
                     int x,
                     int y,
                     float scale,
                     int spacing,
                     int sID);
    void Show();
    void Hide();
    bool IsVisible() const;
    unsigned int GetTextWidth(int id);
    unsigned int GetTextHeight(int id);
    void Draw();
    void Move(int id, int x,int y);
    void MoveCenter(int id);

private:

    void ReLoadResources();
    void CleanResources();


    vector<subtitles_data>* subtitles;
    string FontTextureName;
    string alphabet = "abcdefghijklmnopqrstuvwxyz ";
    Texture2D FontTexture;
    Rectangle sourceRec;
    Rectangle destRec;
    bool visible = false;
    bool resources_loaded = false;

    unsigned int ScreenWidth;
    unsigned int ScreenHeight;
    unsigned int FontHeight = 0;
    unsigned int letter_width;

};


#endif //RAYTURBO_BITMAPFONT_H
