#pragma once
#include "MobileDevice.hpp"
#include <vector>

class Smartphone : public MobileDevice {
private:
    uint8_t ramGB;  // RAM in GB
    uint16_t storageGB;  // Storage in GB
    std::vector<std::string> installedApps;

    void validateRAM(uint8_t ram) const;
    void validateStorage(uint16_t storage) const;

public:
    Smartphone(
        const std::string& model = "Undefined",
        const std::string& color = "Undefined",
        uint16_t year = 2020,
        double price = 0, 
        uint8_t ram = 8, 
        uint16_t storage = 32
    );

    // Getters
    uint8_t getRAM() const { return ramGB; }
    uint16_t getStorage() const { return storageGB; }
    const std::vector<std::string>& getInstalledApps() const { return installedApps; }

    // Setters
    void setRAM(uint8_t ram);
    void setStorage(uint16_t storage);
    void addApp(const std::string& appName);
    bool removeApp(const std::string& appName);

    // Virtual functions
    std::string toString() const override;
};