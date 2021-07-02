#include <equipment.hpp>
/*Type of equipment
 * 0 - sword
 * 1 - dagger
 * 2 - greatsword
 * 3 - armor
 * 4 - ring
 * 5 - amulet
 * 6 - potion
 */
Equipment::Equipment(bool weapon_found, bool armor_found){
    short id=rand()%100+1;

    //Generator bazowego przedmiotu
    if(weapon_found==false && armor_found==false){
        if(id<=10){
            this->type=0;
        }
        else if(id<=20){
            this->type=1;
        }
        else if(id<=30){
            this->type=2;
        }
        else if(id<=50){
            this->type=3;
        }
        else if(id<=60){
            this->type=4;
        }
        else if(id<=70){
            this->type=5;
        }
        else{
            this->type=6;
        }
    }
    else if(weapon_found==false && armor_found==true){
        if(id<=20){
            this->type=0;
        }
        else if(id<=30){
            this->type=1;
        }
        else if(id<=40){
            this->type=2;
        }
        else if(id<=55){
            this->type=4;
        }
        else if(id<=70){
            this->type=5;
        }
        else{
            this->type=6;
        }
    }
    else if(weapon_found==true && armor_found==false){
        if(id<=40){
            this->type=3;
        }
        else if(id<=55){
            this->type=4;
        }
        else if(id<=70){
            this->type=5;
        }
        else{
            this->type=6;
        }
    }

    else{
        if(id<=30){
            this->type=4;
        }
        else if(id<=60){
            this->type=5;
        }
        else{
            this->type=6;
        }
    }

    switch(this->type){
    case 0:
        this->name = "sword";
        break;
    case 1:
        this->name = "dagger";
        break;
    case 2:
        this->name = "greatsword";
        break;
    case 3:
        this->name = "armor";
        break;
    case 4:
        this->name = "ring";
        break;
    case 5:
        this->name = "amulet";
        break;
    case 6:
        this->name = "potion";
    }
    //Generacja modyfikatorów
    if(this->type!=6){
        this->item_prefix = generatePrefix();
        this->item_suffix = generateSuffix();
    }
}

Equipment::~Equipment(){

}

std::string Equipment::getName(){
    return std::string(this->item_prefix.name + " " + this->name + " " + this->item_suffix.name);
}

short Equipment::getType(){
    return this->type;
}

Prefix Equipment::generatePrefix(){
    Prefix generate;
    short id=rand()%100+1;
    switch(this->type){
    /* Offensive prefixes
     * 0 - brak
     *  1 - damage+
     *  2 - damage++
     *  3 - hit+
     *  4 - hit++
     * Defensive prefixes
     * 0 - brak
     * 1 - armor+
     * 2 - armor++
     * 3 - hp+
     * 4 - hp++
     */
    case 0:
        if(id<=50){
            generate.type=0;
            generate.name="";
        }
        else if(id<=70){
            generate.type=1;
            generate.name="sharp";
            this->damageMod+=1;
        }
        else if(id<=75){
            generate.type=2;
            generate.name="vorpal";
            this->damageMod+=2;
        }
        else if(id<=95){
            generate.type=3;
            generate.name="accurate";
            this->hitMod+=5;
        }
        else{
            generate.type=4;
            generate.name="precise";
            this->hitMod+=10;
        }
        break;
    case 1:
        if(id<=50){
            generate.type=0;
            generate.name="";
        }
        else if(id<=70){
            generate.type=1;
            generate.name="sharp";
            this->damageMod+=1;
        }
        else if(id<=75){
            generate.type=2;
            generate.name="vorpal";
            this->damageMod+=2;
        }
        else if(id<=95){
            generate.type=3;
            generate.name="accurate";
            this->hitMod+=5;
        }
        else{
            generate.type=4;
            generate.name="precise";
            this->hitMod+=10;
        }
        break;
    case 2:
        if(id<=50){
            generate.type=0;
            generate.name="";
        }
        else if(id<=70){
            generate.type=1;
            generate.name="sharp";
            this->damageMod+=1;
        }
        else if(id<=75){
            generate.type=2;
            generate.name="vorpal";
            this->damageMod+=2;
        }
        else if(id<=95){
            generate.type=3;
            generate.name="accurate";
            this->hitMod+=5;
        }
        else{
            generate.type=4;
            generate.name="precise";
            this->hitMod+=10;
        }
        break;
    case 3:
        if(id<=50){
            generate.type=0;
            generate.name="";
        }
        else if(id<=70){
            generate.type=1;
            generate.name="leather";
            this->armorMod+=1;
        }
        else if(id<=75){
            generate.type=2;
            generate.name="adamantium";
            this->armorMod+=2;
        }
        else if(id<=95){
            generate.type=3;
            generate.name="healthy";
            this->hpMod+=2;
        }
        else{
            generate.type=4;
            generate.name="behemoth's";
            this->hpMod+=5;
        }
        break;
    case 4:
        if(id<=40){
            generate.type=0;
            generate.name="";
        }
        else if(id<=55){
            generate.type=1;
            generate.name="iron";
            this->damageMod+=1;
        }
        else if(id<=70){
            generate.type=2;
            generate.name="pearl";
            this->hitMod+=2;
        }
        else if(id<=85){
            generate.type=3;
            generate.name="onyx";
            this->armorMod+=1;
        }
        else{
            generate.type=4;
            generate.name="ruby";
            this->hpMod+=2;
        }
        break;
    case 5:
        if(id<=40){
            generate.type=0;
            generate.name="";
        }
        else if(id<=55){
            generate.type=1;
            generate.name="diamond";
            this->damageMod+=1;
        }
        else if(id<=70){
            generate.type=2;
            generate.name="sapphire";
            this->hitMod+=2;
        }
        else if(id<=85){
            generate.type=3;
            generate.name="stone";
            this->armorMod+=1;
        }
        else{
            generate.type=4;
            generate.name="emerald";
            this->hpMod+=2;
        }
        break;
    }
    return generate;

}

Suffix Equipment::generateSuffix(){
    Suffix generate;
    short id=rand()%100+1;
    switch(this->type){
    /* Offensive prefixes
     * 0 - brak
     *  1 - damage+
     *  2 - damage++
     *  3 - hit+
     *  4 - hit++
     *  5 - lucky strikes
     * Defensive prefixes
     * 0 - brak
     * 1 - armor+
     * 2 - armor++
     * 3 - hp+
     * 4 - hp++
     * 5 - lucky dodge
     */
    case 0:
        if(id<=50){
            generate.type=0;
            generate.name="";
        }
        else if(id<=65){
            generate.type=1;
            generate.name="of cutting";
            this->damageMod+=1;
        }
        else if(id<=70){
            generate.type=2;
            generate.name="of slashing";
            this->damageMod+=2;
        }
        else if(id<=90){
            generate.type=3;
            generate.name="of perfection";
            this->hitMod+=5;
        }
        else if(id<=95){
            generate.type=4;
            generate.name="of eagle eye";
            this->hitMod+=10;
        }
        else{
            generate.type=5;
            generate.name="of luck";
            this->attackLuck=true;
        }
        break;

    case 1:
        if(id<=50){
            generate.type=0;
            generate.name="";
        }
        else if(id<=65){
            generate.type=1;
            generate.name="of cutting";
            this->damageMod+=1;
        }
        else if(id<=70){
            generate.type=2;
            generate.name="of slashing";
            this->damageMod+=2;
        }
        else if(id<=90){
            generate.type=3;
            generate.name="of perfection";
            this->hitMod+=5;
        }
        else if(id<=95){
            generate.type=4;
            generate.name="of eagle eye";
            this->hitMod+=10;
        }
        else{
            generate.type=5;
            generate.name="of luck";
            this->attackLuck=true;
        }
        break;

    case 2:
        if(id<=50){
            generate.type=0;
            generate.name="";
        }
        else if(id<=65){
            generate.type=1;
            generate.name="of cutting";
            this->damageMod+=1;
        }
        else if(id<=70){
            generate.type=2;
            generate.name="of slashing";
            this->damageMod+=2;
        }
        else if(id<=90){
            generate.type=3;
            generate.name="of perfection";
            this->hitMod+=5;
        }
        else if(id<=95){
            generate.type=4;
            generate.name="of eagle eye";
            this->hitMod+=10;
        }
        else{
            generate.type=5;
            generate.name="of luck";
            this->attackLuck=true;
        }
        break;
    case 3:
        if(id<=50){
            generate.type=0;
            generate.name="";
        }
        else if(id<=65){
            generate.type=1;
            generate.name="of stone";
            this->armorMod+=1;
        }
        else if(id<=70){
            generate.type=2;
            generate.name="of iron skin";
            this->armorMod+=2;
        }
        else if(id<=90){
            generate.type=3;
            generate.name="of vitality";
            this->hpMod+=2;
        }
        else if(id<=95){
            generate.type=4;
            generate.name="of vigour";
            this->hpMod+=5;
        }
        else{
            generate.type=5;
            generate.name="of luck";
            this->dodgeLuck = true;
        }
        break;
    case 4:
        if(id<=40){
            generate.type=0;
            generate.name="";
        }
        else if(id<=55){
            generate.type=1;
            generate.name="of power";
            this->damageMod+=1;
        }
        else if(id<=70){
            generate.type=2;
            generate.name="of precision";
            this->hitMod+=2;
        }
        else if(id<=85){
            generate.type=3;
            generate.name="of bastion";
            this->armorMod+=1;
        }
        else{
            generate.type=4;
            generate.name="of virility";
            this->hpMod+=2;
        }
        break;
    case 5:
        if(id<=40){
            generate.type=0;
            generate.name="";
        }
        else if(id<=55){
            generate.type=1;
            generate.name="of destruction";
            this->damageMod+=1;
        }
        else if(id<=70){
            generate.type=2;
            generate.name="of a hunter";
            this->hitMod+=2;
        }
        else if(id<=85){
            generate.type=3;
            generate.name="of resistance";
            this->armorMod+=1;
        }
        else{
            generate.type=4;
            generate.name="of an athlete";
            this->hpMod+=2;
        }
        break;
    }
    return generate;

}
