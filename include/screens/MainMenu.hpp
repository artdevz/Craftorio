#pragma once

#include "screens/Screen.hpp"
#include "utils/Button.hpp"

using utils::Button;

class MainMenu : public Screen {
    
public:
    MainMenu();
    void Init() override;
    void Update() override;
    void Draw() override;

    bool ShouldClose() const override;
    bool ShouldStartGame() const;

private:
    bool startGame = false;
    bool shouldClose = false;
    std::vector<Button> buttons;

};