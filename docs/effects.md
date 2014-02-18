Notes

certain monsters can be used to generate certain things
	for example orc eyes can be used to make XXXX

Food deteriorates over time?
Food ripens and gets better for it rotts and becomes useless?

Eating takes multiple turns
Changing armour takes multiple turns

stats for everything

graveyard shows previous characters and their diary.


effects
=======

Effects can be:
* Perm or temp[no. turns]
* Positive/negative

states are things like blindness/underwater breathing/slow movement etc.


Properties of an effect

* Attribute modifiers
* State modifiers
* Length of time

    class Effect
    {
	    Effect(std::string name, Item* item, vector<AttributeModifier> attr, vector<StateModifier> states);
    }

    class AttributeModifier
    {
	    int turns;
	    Actor::Atribute attr;
	    int modifier;
    }

    class StateModifier
    {
	    int turns;
	    Actor::State state;
    }
