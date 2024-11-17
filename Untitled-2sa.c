#include <vector>

class Team {
private:
    std::vector<Unit*> units;

public:
    void AddUnit(Unit* unit) {
        units.push_back(unit);
    }

};
