//
// Created by Neil Edwards on 12/20/15.
//

#ifndef ROGUE_RENDERMAINMENU_H
#define ROGUE_RENDERMAINMENU_H


#include "graphics.h"

class Renderer;

class RenderMainMenu
{
public:
    RenderMainMenu(Graphics* graphics);
    void render(Renderer& renderer, SDL_Rect vp);
    void render_menu(Renderer& renderer);
    void init();
private:
    Graphics* _graphics;
    SDL_Texture* _panel;

};


#endif //ROGUE_RENDERMAINMENU_H
