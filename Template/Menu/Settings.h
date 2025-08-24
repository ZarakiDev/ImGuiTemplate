#pragma once

#include <string>
#include "imgui.h"
#include <mach-o/dyld.h>
#include <mach/mach.h>
#include <iostream>
#include <filesystem>
#include <fstream>

class Settings
{
public:
    ImVec2 MenuSize;
    ImVec2 MenuPos;

    // hide all
    bool StreamerMode = false;
    // add more options here
    
public:
    
    static Settings& GetInstance()
    {
        static Settings Instance{};
        return Instance;
    }
    
    static inline std::filesystem::path FilePath = std::filesystem::path(std::string(getenv("HOME")) + "/Documents/Settings.txt");

    void Save() 
    {
        std::ofstream OutFile(FilePath, std::ios::binary | std::ios::trunc);
        OutFile.write(reinterpret_cast<const char*>(this), sizeof(Settings));
        OutFile.close();
    }

    void Load() 
    {
        if (std::filesystem::exists(FilePath)) 
        {
            std::ifstream InFile(FilePath, std::ios::binary);
            InFile.read(reinterpret_cast<char*>(this), sizeof(Settings));
            InFile.close();
        }
    }
    
    void Reset()
    {
        *this = Settings{};
        return Save();
    }
    
private:
    
    // constructed once, will be overriden by the Load function
    Settings() : MenuSize(ImVec2(390, 370)), MenuPos(ImVec2(1200, 500)) {};
    ~Settings() { };
};
