#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP

struct Prefix{
    short type;
    std::string name;
};

struct Suffix{
    short type;
    std::string name;
};

class Equipment{
public:
    //Constructors / Destructors
    Equipment(bool weapon_found, bool armor_found);
    ~Equipment();

    //Public variables
    short damageMod=0, hitMod=0;
    short hpMod=0, armorMod=0;
    bool attackLuck = false, dodgeLuck = false;

    //Functions
    std::string getName();
    short getType();

private:
    //Private variables
    short type;
    std::string name;

    Prefix item_prefix;
    Suffix item_suffix;

    //Private functions
    Prefix generatePrefix();
    Suffix generateSuffix();
};
#endif // EQUIPMENT_HPP

