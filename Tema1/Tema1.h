#pragma once

#include <vector>
#include <iostream>

#include "components/simple_scene.h"

#include "lab_m1/Tema1/Utility.h"

#include "lab_m1/lab3/lab3_vis2D.h"




namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;



        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void RenderText(const std::string& text, Shader* shader, const glm::vec2& position, float scale, float letterSpacing, bool sw);
        float random(float min, float max);
       

    protected:

        glm::mat3 modelMatrix;

        // initial values
        bool sure = false;
        bool isPaused = false;
        bool gameOver = false;
        bool quit = false;
        bool restart = false;
        bool yes = false;
        bool no = false;
        int star_count = 5;
        int lifes = 3;
        int score = 0;
        

        GridSquare board[3][3]; // positions for turrets
        GridSquare turret_board[1][4]; // select turrets positions
        GridSquare options[1][3];
        GridSquare options_paused[3][1];
        GridSquare options_gameOver[2][1];
        Turret turrets[4];  // turrrets for chosing

        glm::vec3 center = glm::vec3(0, 0, 0);
        glm::vec3 corner = glm::vec3(0, 0, 0);

        float squareSide = 100;
        float starSide = 4;
        float turretSide = 10;
        float enemySide = 10;
        float tankSide = 8.0f;
        float initial_enemy_rad = 10;
        float enemyScale = 1.0f;
        float bonusSide = 1.2f;
        float letterSide = 0.5f;
        float letterSide2 = 0.1f;

        std::vector<Star> stars;
        std::vector<Enemy> enemies;
        std::vector<Star> randomStars;
        std::vector<Turret> turretsOnBoard;
        std::vector<Tank> tanks;
        std::vector<Bonus> bonuses;
        std::vector<BonusLife> bonlifes;

        // random stars
        float starSpawnTimer = 0.0f;
        float starSpawnInterval;

        // random enemies
        float enemySpawnTimer = 0.0f;
        float enemySpawnInterval;

        // random bonus
        float bonusSpawnInterval = 25.0f;
        float bonusSpawnTimer = 0.0f;

        // bonus life
        float bonuslifeSpawnInterval = 60.0f;
        float bonuslifeSpawnTimer = 0.0f;

        
        // put turrets
        Turret* selectedTurret = nullptr;
        glm::vec2 selectedTurretInitialPosition = glm::vec2(0, 0);
        bool leftMousePressed = false;
        bool validPlacement = false;
        bool isDragging = false;

       
        // stars count positions
        float starX_init = 800.0f;
        float starY_init = 600.0f; 
        float starSpacingX = 30.0f; 
        float starSpacingY = 60.0f; 

        
        
    };
}   // namespace m1
