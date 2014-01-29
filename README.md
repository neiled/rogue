rogue
=====

RogueLike game

* Procedural generated map.
* Further player goes into the dungeon (lower levels) the harder the game becomes.
* ? Monsters can keep coming up from the lower levels
* Turn based movement. Each time the user moves a 'tick' is calculated.
* ? Interaction with other players of the game somehow... [Notes?]

Map Generation
==============

* Generate X rooms in 2d space with no relation to each other except their plane.
* Generate relative neighbour graph of all points.
* Carve out all paths on the grid (use A* to generate path from point to point).
* Convert Y points at random into a room where the point is the centre of the room.
* Carve out the rooms.
