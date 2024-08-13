#pragma once

#ifndef BOMBERMAN_UILABEL_H
#define BOMBERMAN_UILABEL_H

#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Game.h"
// #include "GameObject.h"
class UiLabel
{
public:
    UiLabel(int xpos, int ypos, std::string text, std::string font, SDL_Color &colour, std::string path) : labelFont(font), labelText(text), text_colour(colour)
    {
        position.x = xpos;
        position.y = ypos;
        addFont(labelFont, path, 64);
        setLabelText(labelText, labelFont);
    }
    // void update() override
    // {
    //     setLabelText();
    // }
    void setLabelText(std::string text, std::string font)
    {
        SDL_Surface *surf = TTF_RenderText_Blended(getFont(font), text.c_str(), text_colour);
        label_texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
        SDL_FreeSurface(surf);

        SDL_QueryTexture(label_texture, nullptr, nullptr, &position.w, &position.h);
    }
    void draw()
    {
        SDL_RenderCopy(Game::renderer, label_texture, nullptr, &position);
    }
    void addFont(std::string id, std::string path, int fontSize)
    {
        fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
    }
    TTF_Font *getFont(std::string id)
    {
        return fonts[id];
    }

private:
    std::map<std::string, TTF_Font *> fonts;
    SDL_Rect position;
    std::string labelText;
    std::string labelFont;
    SDL_Color text_colour;
    SDL_Texture *label_texture;
};

#endif // BOMBERMAN_UILABEL_H