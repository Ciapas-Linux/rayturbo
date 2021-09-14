
#include "BitmapFont.h"

BitmapFont::BitmapFont(int fontHeight)
{
    ScreenWidth = GetScreenWidth();
    ScreenHeight = GetScreenHeight();;
    FontHeight = fontHeight;
    subtitles = new vector<subtitles_data>;
}

BitmapFont::~BitmapFont()
{
    if(resources_loaded)
    {
        CleanResources();
    }
    delete subtitles;
}

void BitmapFont::Draw()
{
   for(size_t i = 0; i < subtitles->size(); i++)
   {
       subtitles_data* st = &subtitles->operator[](i);
        if(st->Visible)
        {
            for (int lop = 0; lop < subtitles->operator[](i).TextData.length(); lop++)
            {
                if (st->TextData[lop] != ' ')
                {
                    sourceRec = {static_cast<float>(st->src_x_let_position[lop]),
                                 0,
                                 static_cast<float>(letter_width),
                                 static_cast<float>(FontHeight)};

                    destRec = {(float)st->letter_x[lop],
                               (float)st->letter_y[lop],
                               (float) letter_width * st->Scale,
                               static_cast<float>(FontHeight) * st->Scale};

                    DrawTexturePro(FontTexture,
                                   sourceRec,
                                   destRec,
                                   st->Origin,
                                   st->Rotation,
                                   WHITE);
                }
            }
        }
   }
}

void BitmapFont::AddSubtitle(const char *Subtitle,
                             int x,
                             int y,
                             float scale,
                             int spacing,
                             int sID)
{

    subtitles_data st;
    st.TextData = Subtitle;
    st.TextHeight = FontHeight;
    st.TextWidth = (st.TextData.length() * letter_width)*scale;
    st.Scale = scale;
    st.txt_position.x = x;
    st.txt_position.y = y;
    st.spacing = spacing;
    st.Visible = true;

    for(int nchar = 0; nchar < st.TextData.length(); nchar++)
    {
        for(int lop_alph = 0; lop_alph < alphabet.length();lop_alph++)
        {
            if(st.TextData[nchar] == alphabet[lop_alph])
            {
                st.src_x_let_position.push_back(lop_alph * letter_width);
                break;
            }
        }
    }

    unsigned int x_pos = 0;
    for (int lop = 0; lop < st.TextData.length(); lop++)
    {
       st.letter_x.push_back(x_pos + (st.txt_position.x - letter_width / 2.0f));
       st.letter_y.push_back(st.txt_position.y - FontHeight / 2.0f);
       x_pos += (letter_width + st.spacing) * (int) scale;
    }

    st.subID = sID;
    subtitles->push_back(st);
}

void BitmapFont::Move(int id, int x, int y)
{
    subtitles_data* st = &subtitles->operator[](id);
    st->txt_position.x = x;
    st->txt_position.y = y;
    st->letter_x.clear();
    st->letter_y.clear();

    unsigned int x_pos = 0;
    for (int lop = 0; lop < st->TextData.length(); lop++)
    {
        st->letter_x.push_back(x_pos + (st->txt_position.x - letter_width / 2.0f));
        st->letter_y.push_back(st->txt_position.y - FontHeight / 2.0f);
        x_pos += (letter_width + st->spacing) * (int) st->Scale;
    }
}

void BitmapFont::MoveCenter(int id)
{
    subtitles_data* st = &subtitles->operator[](id);

    st->txt_position.x = (ScreenWidth / 2) - (st->TextWidth)/2;
    st->txt_position.y = (ScreenHeight / 2) - (st->TextHeight)/2;

    st->letter_x.clear();
    st->letter_y.clear();

    unsigned int x_pos = 0;
    for (int lop = 0; lop < st->TextData.length(); lop++)
    {
        st->letter_x.push_back(x_pos + (st->txt_position.x - letter_width / 2.0f));
        st->letter_y.push_back(st->txt_position.y - FontHeight / 2.0f);
        x_pos += (letter_width + st->spacing) * (int) st->Scale;
    }

}

void BitmapFont::LoadResources(const char *TextureName)
{
    FontTextureName = TextureName;
    FontTexture = LoadTexture(FontTextureName.c_str());
    letter_width = FontTexture.width/alphabet.length();
    FontHeight = FontTexture.height;
    resources_loaded = true;
}

unsigned int BitmapFont::GetTextWidth(int id)
{
    subtitles_data* st = &subtitles->operator[](id);
    return st->TextWidth;
}

unsigned int BitmapFont::GetTextHeight(int id)
{
    subtitles_data* st = &subtitles->operator[](id);
    return st->TextHeight;
}

void BitmapFont::ReLoadResources()
{
    if(resources_loaded) return;
    FontTexture = LoadTexture(FontTextureName.c_str());
    resources_loaded = true;
}

void BitmapFont::CleanResources()
{
    if(!resources_loaded) return;
    UnloadTexture(FontTexture);
    resources_loaded = false;
}

void BitmapFont::Show()
{
    ReLoadResources();
    visible = true;
}

void BitmapFont::Hide()
{
    CleanResources();
    visible = false;
}

bool BitmapFont::IsVisible() const
{
    return visible;
}