#include <string>
#include <fstream>
#include <vector>

class Unit : public IFile {
private:
    std::string name;
    int health;
    std::vector<Weapon> weapons;

public:
    Unit(const std::string& name, int health) : name(name), health(health) {}

    void Save(std::ofstream& stream) const override {
        size_t length = name.size();
        stream.write(reinterpret_cast<const char*>(&length), sizeof(length));
        stream.write(name.c_str(), length);
        stream.write(reinterpret_cast<const char*>(&health), sizeof(health));
        size_t weaponsCount = weapons.size();
        stream.write(reinterpret_cast<const char*>(&weaponsCount), sizeof(weaponsCount));
        for (const auto& weapon : weapons) {
            weapon.Save(stream);
        }
    }

    void Save() const override {
        std::ofstream stream("unit.dat", std::ios::binary);
        Save(stream);
    }

    void Load(std::ifstream& stream) override {
        size_t length;
        stream.read(reinterpret_cast<char*>(&length), sizeof(length));
        name.resize(length);
        stream.read(&name[0], length);
        stream.read(reinterpret_cast<char*>(&health), sizeof(health));
        size_t weaponsCount;
        stream.read(reinterpret_cast<char*>(&weaponsCount), sizeof(weaponsCount));
        weapons.resize(weaponsCount);
        for (auto& weapon : weapons) {
            weapon.Load(stream);
        }
    }

    void Load() override {
        std::ifstream stream("unit.dat", std::ios::binary);
        Load(stream);
    }
};
