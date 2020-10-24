#ifndef WARRIOR_H
#define WARRIOR_H

#include <string>

using namespace std;

class Warrior
{
public:
    Warrior();
    Warrior(string namePC, int strengthPC, int loyaltyPC, int moralePC, bool is_freePC, bool has_shipPC, bool has_wildfirePC, bool has_dragonglassPC);
    void Warrior_setName(string nameInput);
    string Warrior_getName();
    void Warrior_setStrength(int strengthInput);
    int Warrior_getStrength();
    void Warrior_setLoyalty(int loyaltyInput);
    int Warrior_getLoyalty();
    void Warrior_setMorale(int moraleInput);
    int Warrior_getMorale();
    void Warrior_set_is_free(bool is_freeInput);
    bool Warrior_get_is_free();
    void Warrior_set_has_ship(bool has_shipInput);
    bool Warrior_get_has_ship();
    void Warrior_set_has_wildfire(bool has_wildfireInput);
    bool Warrior_get_has_wildfire();
    void Warrior_set_has_dragonglass(bool has_dragonglassInput);
    bool Warrior_get_has_dragonglass();
    void Warrior_setLocationRow(int rowInput);
    void Warrior_setLocationColumn(int columnInput);
    int Warrior_getLocationRow();
    int Warrior_getLocationColumn();
private:
    string Warrior_name;
    int Warrior_strength;
    int Warrior_loyalty;
    int Warrior_morale;
    bool Warrior_is_free;
    bool Warrior_has_ship;
    bool Warrior_has_wildfire;
    bool Warrior_has_dragonglass;
    int Warrior_locationRow;
    int Warrior_locationColumn;
};

#endif
