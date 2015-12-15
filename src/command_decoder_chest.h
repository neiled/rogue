#ifndef COMMAND_DECODER_CHEST_H
#define COMMAND_DECODER_CHEST_H 

#include "command_decoder.h"
#include <SDL2/SDL.h>
class Game;
class Player;

class CommandDecoderChest : public CommandDecoder
{
public:
    CommandDecoderChest ();
    virtual ~CommandDecoderChest ();
    virtual bool Decode(SDL_Keycode key, Game& game) override;
    virtual bool Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game) override {return false;}

private:
    void use_item(Player& player, int index);
    void take_all(Player& player);

    void use_item(Player &player, int index, Game &game);

    void take_all(Player &player, Game &game);
};
#endif
