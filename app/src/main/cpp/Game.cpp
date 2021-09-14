
#include <string.h>
#include "Game.h"



Game::Game()
{
    // Possible raylib window flags
    /*
    FLAG_VSYNC_HINT
    FLAG_FULLSCREEN_MODE    -> not working properly -> wrong scaling!
    FLAG_WINDOW_RESIZABLE
    FLAG_WINDOW_UNDECORATED
    FLAG_WINDOW_TRANSPARENT
    FLAG_WINDOW_HIDDEN
    FLAG_WINDOW_MINIMIZED   -> Not supported on window creation
    FLAG_WINDOW_MAXIMIZED   -> Not supported on window creation
    FLAG_WINDOW_UNFOCUSED
    FLAG_WINDOW_TOPMOST
    FLAG_WINDOW_HIGHDPI     -> errors after minimize-resize, fb size is recalculated
    FLAG_WINDOW_ALWAYS_RUN
    FLAG_MSAA_4X_HINT
    */

    // SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    // SetConfigFlags(FLAG_FULLSCREEN_MODE);  //not work for mobile

    //start mobile full screen app
    InitWindow(0, 0, "Virus",true);
    InitAudioDevice();
    EnableCursor();
    SetTargetFPS(60);

    ScreenWidth  = GetScreenWidth();
    ScreenHeight = GetScreenHeight();

    ButtonNext = new Button(ScreenWidth,ScreenHeight,200);
    ButtonNext->LoadResources("button.png",
                              "scifi1.ogg");

    ButtonNext->MoveBottomCenter();
    ButtonNext->MoveSUB(0,100);

    bmpFont1 = new BitmapFont(42);
    bmpFont1->LoadResources("greenfont2.png");
    bmpFont1->AddSubtitle("ala ma kota",
                            300,
                            1500,
                            3.0f,
                            0,
                            0);

    bmpFont1->MoveCenter(0);



}

bool Game::IsVisible() const
{
    return visible;
}

void Game::Show()
{
    LoadResources();
    PlayMusicStream(intro_music);
    visible = true;
}

void Game::Hide()
{
    cls();
    CleanResources();
    StopMusicStream(intro_music);
    visible = false;
}

void Game::UpdateKeyboard()
{
    if (IsKeyPressed(KEY_SPACE))
    {

    }
}

void Game::DrawHUD()
{
    DrawText("Example App v0.001", ScreenWidth/100, 30, 60, GREEN);
    DrawText(TextFormat("FPS: %4i", GetFPS()), ScreenWidth/100, 100, 60, RED);
}

void Game::Draw()
{
    if(!visible) return;

   BeginDrawing();
        ClearBackground(BLACK);
        DrawBackground();

        ButtonNext->Draw();
        bmpFont1->Draw();

        DrawHUD();
    EndDrawing();
}

void Game::cls()
{
    BeginDrawing();
      ClearBackground(BLACK);
    EndDrawing();
}

void Game::DrawBackground()
{
    DrawTexture(texture, 0, 0, WHITE);
}


void Game::Run()
{
    while(!WindowShouldClose())
    {
        UpdateMusicStream(intro_music);

        currentGesture = GetGestureDetected();
        touchPosition = GetTouchPosition(0);

        ButtonNext->UpdateTimer();

        if (currentGesture == GESTURE_TAP)
        {
            if (ButtonNext->ClickStatus(touchPosition))
            {

            }
        }


        UpdateKeyboard();
        Draw();
    }
}

void Game::LoadResources()
{
    background = LoadImage("bkgnd1.png");
    ImageResize(&background, ScreenWidth, ScreenHeight);

    texture = LoadTextureFromImage(background);
    UnloadImage(background);

    intro_music = LoadMusicStream("ambience03.mp3");
    intro_music.looping = true;

    resources_loaded = true;
}

void Game::CleanResources()
{
    UnloadMusicStream(intro_music);
    UnloadTexture(texture);
    resources_loaded = false;
}

Game::~Game()
{
    if(resources_loaded)
    {
      CleanResources();
    }

    CloseAudioDevice();
}