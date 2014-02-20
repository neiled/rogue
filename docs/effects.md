Effects
=======

Effects can be:
* Perm or temp[no. turns]
* Positive/negative

states are things like blindness/underwater breathing/slow movement etc.


Properties of an effect

* Attribute modifiers
* State modifiers
* Length of time
```
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
```
