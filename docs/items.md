###Types###
* Weapons
* Potions
	
###Weapons###
* weapon_type //[Knife/Sword/Club/Axe]
* max_damage
* attr_modifiers
* skill_used

Damage Done = Skill/100 * max_damage; //min 1

###Potions###
* attr_modifiers

###Future Types###
* Scrolls
* Wands
* Traps
* Armor
* Bags
* Rings
* Amulets

###What defines an Item:###

* Name
* Description
* Type
* Subtype
* Weight
* Volume
* Base Value
* Rarity_in_10000
* attr_modifiers
* state_modifiers

####Example####

* Small Health Potion
* A small bottle filled with a red liquid. It glows slightly.
* POTION
* POTION_HEALTH
* 1
* 1
* 100
* 4000
* {{HEALTH, 25, 0}}
* {}

* Large Broadsword of Defense
* Huge broadsword with special grip designed for blocking.
* SWORD
* SWORD_BROADSWORD
* 1000
* 10000
* 20
* {{DEF, 5, 0}}
* {}
