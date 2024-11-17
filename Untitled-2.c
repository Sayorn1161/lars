#include <string>
#include <fstream>

class Weapon : public IFile {
private:
    std::string name;
    int damage;

public:
    Weapon(const std::string& name, int damage) : name(name), damage(damage) {}

    void Save(std::ofstream& stream) const override {
        size_t length = name.size();
        stream.write(reinterpret_cast<const char*>(&length), sizeof(length));
        stream.write(name.c_str(), length);
        stream.write(reinterpret_cast<const char*>(&damage), sizeof(damage));
    }

    void Save() const override {
        std::ofstream stream("weapon.dat", std::ios::binary);
        Save(stream);
    }

    void Load(std::ifstream& stream) override {
        size_t length;
        stream.read(reinterpret_cast<char*>(&length), sizeof(length));
        name.resize(length);
        stream.read(&name[0], length);
        stream.read(reinterpret_cast<char*>(&damage), sizeof(damage));
    }

    void Load() override {
        std::ifstream stream("weapon.dat", std::ios::binary);
        Load(stream);
    }
};
