

#include "Button.h"


Button::Button(int sWidth, int sHeight,int timeout)
{
    ScreenWidth = sWidth;
    ScreenHeight = sHeight;
    TimeOut = timeout;
    btnState = 0;
}

Button::~Button()
{
    if(resources_loaded)
    {
        CleanResources();
    }
}

long long Button::TimeInMilliseconds()
{
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void Button::UpdateTimer()
{
    if(visible == false) return;

    if(TimeInMilliseconds() > LastClickTime + TimeOut)
    {
        btnState = 0;
    }
}

bool Button::ClickStatus(Vector2 tap_point)
{
    if(visible == false) return false;

    if(CheckCollisionPointRec(tap_point, dstRec))
    {
        PlaySound(fxButton);
        btnState = 1;
        LastClickTime = TimeInMilliseconds();
        return true;
    }
return false;
}

void Button::Draw()
{
    if(visible == false) return;

    sourceRec.y = btnState*frameHeight;
    DrawTextureRec(ButtonTexture,
                   sourceRec,
                   (Vector2){ dstRec.x, dstRec.y },
                   WHITE);
}

bool Button::IsVisible() const
{
    return visible;
}

void Button::Show()
{
    ReLoadResources();
    visible = true;
}

void Button::Hide()
{
    CleanResources();
    visible = false;
}

void Button::Move(int x,int y)
{
    dstRec = { x - ButtonTexture.width/2.0f,
               y - ButtonTexture.height/BNUM_FRAMES/2.0f,
               (float)ButtonTexture.width,
               frameHeight };
}

void Button::MoveADD(int x,int y)
{
    dstRec.x += x;
    dstRec.y += y;
}

void Button::MoveSUB(int x,int y)
{
    dstRec.x -= x;
    dstRec.y -= y;
}

void Button::MoveCenter()
{
    dstRec = { ScreenWidth/2.0f - ButtonTexture.width/2.0f,
               ScreenHeight/2.0f - ButtonTexture.height/BNUM_FRAMES/2.0f,
               (float)ButtonTexture.width,
               frameHeight };
}

void Button::MoveBottomCenter()
{
    dstRec.x = ScreenWidth/2.0f - ButtonTexture.width/2.0f;
    dstRec.y = ScreenHeight - ButtonTexture.height/BNUM_FRAMES;
}

void Button::ReLoadResources()
{
    if(resources_loaded) return;

    fxButton = LoadSound(SoundFileName.c_str());
    ButtonTexture = LoadTexture(ImageFileName.c_str());

    frameHeight = (float)ButtonTexture.height/BNUM_FRAMES;
    sourceRec = { 0, 0, (float)ButtonTexture.width, frameHeight };

    resources_loaded = true;
}

void Button::LoadResources(const char *TextureName,const char *SoundName)
{
    ImageFileName = TextureName;
    SoundFileName = SoundName;

    ButtonTexture = LoadTexture(ImageFileName.c_str());
    fxButton = LoadSound(SoundFileName.c_str());

    frameHeight = (float)ButtonTexture.height/BNUM_FRAMES;
    sourceRec = { 0, 0, (float)ButtonTexture.width, frameHeight };

    if(initial_position == false)
    {
        // Define button bounds on screen, initial position:0,0
        dstRec = {0,
                  0,
                  (float) ButtonTexture.width,
                  frameHeight};
        initial_position = true;
     }

    resources_loaded = true;
}

void Button::CleanResources()
{
    if(!resources_loaded) return;
    UnloadSound(fxButton);
    UnloadTexture(ButtonTexture);
    resources_loaded = false;
}

