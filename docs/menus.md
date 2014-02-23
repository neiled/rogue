in order to have menus we need to know the current game state
based on the state we'll determine how to translate the current keyboard key press to a command

abstract command_decoder

game_decoder
inventory_decoder

map[GAME_STATE,command_decoder]

command_decoders then add a command to the players command queue...
regular command processor can deal with the command


