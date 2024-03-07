#include "Tema1.h"

#include <vector>
#include <iostream>
#include <string>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

#include "core/engine.h"
#include "utils/gl_utils.h"
#include "lab_m1/Tema1/Utility.h"
#include <GLFW/glfw3.h>




using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


void Tema1::RenderText(const std::string& text, Shader* shader, const glm::vec2& position, float scale, float letterSpacing, bool sw)
{
	glm::mat3 modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(position.x, position.y);
	modelMatrix *= transform2D::Scale(scale, scale);

	float charWidth = 2.0f * scale;
	float charHeight = 3.0f * scale;

	float x = 0.0f;
	float y = 0.0f;

	for (char c : text) {
		if (characterMap.find(c) != characterMap.end()) {
			const std::vector<std::string>& charLines = characterMap.at(c);
			for (int i = 0; i < charLines.size(); ++i) {
				for (int j = 0; j < charLines[i].size(); ++j) {
					if (charLines[i][j] == '#') {
						glm::mat3 charModelMatrix = modelMatrix * transform2D::Translate(x + j * charWidth, y - i * charHeight);
						if (sw)
							RenderMesh2D(meshes["letter"], shaders["VertexColor"], charModelMatrix);
						else
							RenderMesh2D(meshes["letter2"], shaders["VertexColor"], charModelMatrix);
					}
				}
			}
			x += charWidth + letterSpacing; 
		}
		else if (c == ' ') {
			// skip for space character
			x += letterSpacing;
		}
	}
}

float Tema1::random(float min, float max) {
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));

}

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, 1280, 0, 720, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);


	//green square
	Mesh* square_green = object2D::CreateSquare("square_green", corner, squareSide, glm::vec3(0, 1, 0), true, false);
	AddMeshToList(square_green);

	// red square
	Mesh* square_red = object2D::CreateSquare("square_red", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square_red);

	// empty square
	Mesh* square_empty = object2D::CreateSquare("square_empty", corner, squareSide, glm::vec3(0, 0, 1));
	AddMeshToList(square_empty);

	// star blue
	Mesh* star_blue = object2D::CreateStar("star_blue", center, starSide, glm::vec3(0, 0, 1));
	AddMeshToList(star_blue);

	// star orange
	Mesh* star_orange = object2D::CreateStar("star_orange", center, starSide, glm::vec3(1, 0.647f, 0));
	AddMeshToList(star_orange);

	// star yellow
	Mesh* star_yellow = object2D::CreateStar("star_yellow", center, starSide, glm::vec3(1, 1, 0));
	AddMeshToList(star_yellow);

	// star fuchsia 
	Mesh* star_pink = object2D::CreateStar("star_pink", center, starSide, glm::vec3(0.937f, 0.231f, 0.486f));
	AddMeshToList(star_pink);

	// star purple
	Mesh* star_purple = object2D::CreateStar("star_purple", center, starSide, glm::vec3(0.627f, 0.125f, 0.941f));
	AddMeshToList(star_purple);

	// star grey
	Mesh* star_grey = object2D::CreateStar("star_grey", center, starSide, glm::vec3(0.502f, 0.502f, 0.502f));
	AddMeshToList(star_grey);

	// turret orange
	Mesh* turret_orange = object2D::CreateTurret("turret_orange", center, turretSide, glm::vec3(1, 0.647f, 0));
	AddMeshToList(turret_orange);

	// turret blue
	Mesh* turret_blue = object2D::CreateTurret("turret_blue", center, turretSide, glm::vec3(0, 0, 1));
	AddMeshToList(turret_blue);

	// turret yellow
	Mesh* turret_yellow = object2D::CreateTurret("turret_yellow", center, turretSide, glm::vec3(1, 1, 0));
	AddMeshToList(turret_yellow);

	// turret purple
	Mesh* turret_purple = object2D::CreateTurret("turret_purple", center, turretSide, glm::vec3(0.627f, 0.125f, 0.941f));
	AddMeshToList(turret_purple);

	// enemy purple
	Mesh* enemy_purple = object2D::CreateEnemy("enemy_purple", center, turretSide, glm::vec3(0.627f, 0.125f, 0.941f));
	AddMeshToList(enemy_purple);

	// enemy yellow
	Mesh* enemy_yellow = object2D::CreateEnemy("enemy_yellow", center, turretSide, glm::vec3(1, 1, 0));
	AddMeshToList(enemy_yellow);

	// enemy blue
	Mesh* enemy_blue = object2D::CreateEnemy("enemy_blue", center, turretSide, glm::vec3(0, 0, 1));
	AddMeshToList(enemy_blue);

	// enemy orange
	Mesh* enemy_orange = object2D::CreateEnemy("enemy_orange", center, turretSide, glm::vec3(1, 0.647f, 0));
	AddMeshToList(enemy_orange);

	// life
	Mesh* life = object2D::CreateRoundHeart("life", glm::vec3(0, 0, 1), 3.0f, glm::vec3(1.0f, 0.0f, 0.0f), 100);
	AddMeshToList(life);

	// tank
	Mesh* tank = object2D::CreateTank("tank", center, tankSide, glm::vec3(0, 0.2f, 0.13f));
	AddMeshToList(tank);

	// bonus
	Mesh* bonus = object2D::CreateBonus("bonus", center, bonusSide);
	AddMeshToList(bonus);

	//bonus life
	Mesh* bonuslife = object2D::CreateBonusLife("bonuslife", center, bonusSide);
	AddMeshToList(bonuslife);

	//letter
	Mesh* letter = object2D::CreateLetter("letter", center, letterSide, glm::vec3(1, 1, 1));
	AddMeshToList(letter);

	Mesh* letter2 = object2D::CreateLetter("letter2", center, letterSide2, glm::vec3(1, 1, 1));
	AddMeshToList(letter2);

	// tanks
	for (int i = 0; i < 3; i++) {

		Tank tank;
		tank.position.x = 100;
		tank.position.y = 370 - i * 150;

		tanks.push_back(tank);

	}

}



void Tema1::FrameStart()
{

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.243f, 0.706f, 0.537f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
	// render turrets available positions
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j].position.x = 500 - i * 150;
			board[i][j].position.y = 350 - j * 150;

			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(board[i][j].position.x, board[i][j].position.y);
			RenderMesh2D(meshes["square_green"], shaders["VertexColor"], modelMatrix);
		}
	}

	// render rectangle
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(50, 450);
	modelMatrix *= transform2D::Scale(1, -4);
	RenderMesh2D(meshes["square_red"], shaders["VertexColor"], modelMatrix);

	// render score
	RenderText("SCORE", shaders["VertexColor"], glm::vec2(50.0f, 525.0f), 1.40f, 30.0f, true);
	RenderText(std::to_string(score), shaders["VertexColor"], glm::vec2(300.0f, 525.0f), 1.40f, 30.0f, true);

	// render choose turrets area
	for (int i = 0; i < 4; i++) {
		turret_board[0][i].position.x = 650 - i * 200;
		turret_board[0][i].position.y = 600;

		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(turret_board[0][i].position.x, turret_board[0][i].position.y);
		RenderMesh2D(meshes["square_empty"], shaders["VertexColor"], modelMatrix);
	}

	// reender options area & checked
	for (int i = 0; i < 3; i++) {
		options[0][i].position.x = 200 - i * 70;
		options[0][i].position.y = 15;

		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(options[0][i].position.x, options[0][i].position.y);
		modelMatrix *= transform2D::Scale(0.2f, 0.2f);
		//checked

		if (isPaused == true && i == 2 && restart == false && quit == false)
			RenderMesh2D(meshes["square_red"], shaders["VertexColor"], modelMatrix);
		if (restart == true && i == 1)
			RenderMesh2D(meshes["square_red"], shaders["VertexColor"], modelMatrix);
		if (quit == true && i == 0)
			RenderMesh2D(meshes["square_red"], shaders["VertexColor"], modelMatrix);
			
		RenderMesh2D(meshes["square_empty"], shaders["VertexColor"], modelMatrix);
	}

	RenderText("Q", shaders["VertexColor"], glm::vec2(230.0f, 30.0f), 1, 30.0f, false);
	RenderText("R", shaders["VertexColor"], glm::vec2(160.0f, 30.0f), 1, 30.0, false);
	RenderText("P", shaders["VertexColor"], glm::vec2(90.0f, 30.0f), 1, 30.0f, false);

	// render lifes
	for (int i = 0; i < lifes; i++) {
		float x = 1200 - i * 150;
		float y = 665;


		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(x, y);
		modelMatrix *= transform2D::Rotate(3.14f);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
	}

	// render stars for turrets
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(70, 570);
	RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(270, 570);
	RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(305, 570);
	RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(470, 570);
	RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(505, 570);
	RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(670, 570);
	RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(705, 570);
	RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(740, 570);
	RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

	// render tanks
	for (auto& tank : tanks) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(tank.position.x, tank.position.y);
		RenderMesh2D(meshes["tank"], shaders["VertexColor"], modelMatrix);
	}

	// render turrets for choosing
	for (int i = 0; i < 4; i++) {
		modelMatrix = glm::mat3(1);
		turrets[i].position.x = turret_board[0][i].position.x + squareSide / 2;
		turrets[i].position.y = turret_board[0][i].position.y + squareSide / 2;

		modelMatrix *= transform2D::Translate(turrets[i].position.x, turrets[i].position.y);

		switch (i) {
		case 0:
			RenderMesh2D(meshes["turret_purple"], shaders["VertexColor"], modelMatrix);
			turrets[i].cost = 3;
			turrets[i].color = "purple";
			break;
		case 1:
			RenderMesh2D(meshes["turret_yellow"], shaders["VertexColor"], modelMatrix);
			turrets[i].cost = 2;
			turrets[i].color = "yellow";
			break;
		case 2:
			RenderMesh2D(meshes["turret_blue"], shaders["VertexColor"], modelMatrix);
			turrets[i].cost = 2;
			turrets[i].color = "blue";
			break;
		case 3:
			RenderMesh2D(meshes["turret_orange"], shaders["VertexColor"], modelMatrix);
			turrets[i].cost = 1;
			turrets[i].color = "orange";
			break;
		}
	}


	// render turrets on the board || deleting
	for (auto& turret : turretsOnBoard) {

		glm::mat3 modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(turret.position.x, turret.position.y);

		// deleting
		if (turret.scale) {
			if (turret.scaleFactor > 0.0f) {
				turret.scaleFactor -= 0.05f;
				modelMatrix *= transform2D::Scale(turret.scaleFactor, turret.scaleFactor);
			}
		}

		if (turret.color == "purple") {
			RenderMesh2D(meshes["turret_purple"], shaders["VertexColor"], modelMatrix);
		}
		else if (turret.color == "yellow") {
			RenderMesh2D(meshes["turret_yellow"], shaders["VertexColor"], modelMatrix);
		}
		else if (turret.color == "blue") {
			RenderMesh2D(meshes["turret_blue"], shaders["VertexColor"], modelMatrix);
		}
		else if (turret.color == "orange") {
			RenderMesh2D(meshes["turret_orange"], shaders["VertexColor"], modelMatrix);
		}

	}

	// Render random stars
	for (auto& star : randomStars) {
		glm::mat3 modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(star.position.x, star.position.y);
		modelMatrix *= transform2D::Scale(2.0f, 2.0f);
		RenderMesh2D(meshes["star_pink"], shaders["VertexColor"], modelMatrix);
	}

	// render "money"
	float starX = starX_init;
	float starY = starY_init;

	for (int i = 0; i < star_count; i++) {
		glm::mat3 modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(starX, starY);
		RenderMesh2D(meshes["star_yellow"], shaders["VertexColor"], modelMatrix);
		starX += starSpacingX;


		//  end of the window
		if (starX > 1250.0f) {
			// move yo the next row
			// reset  X-coordinate
			starX = starX_init;
			// next row
			starY -= starSpacingY;
		}
	}

	// render enemies
	for (auto& enemy : enemies) {
		glm::mat3 modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(enemy.position.x, enemy.position.y);

		if (enemy.die) {

			// if die, scale to 0
			if (enemy.scaleFactor > 0.0f) {
				enemy.scaleFactor -= 0.7f;
			}
		}
		else if (enemy.lifes < 3) {

			float scaleFactor = enemyScale / 3 * enemy.hits;

			if (enemy.scaleFactor > scaleFactor) {
				enemy.scaleFactor -= 0.01f;

			}
		}

		modelMatrix *= transform2D::Scale(enemy.scaleFactor, enemy.scaleFactor);

		if (enemy.color == "purple") {
			RenderMesh2D(meshes["enemy_purple"], shaders["VertexColor"], modelMatrix);
		}
		else if (enemy.color == "yellow") {
			RenderMesh2D(meshes["enemy_yellow"], shaders["VertexColor"], modelMatrix);
		}
		else if (enemy.color == "blue") {
			RenderMesh2D(meshes["enemy_blue"], shaders["VertexColor"], modelMatrix);
		}
		else if (enemy.color == "orange") {
			RenderMesh2D(meshes["enemy_orange"], shaders["VertexColor"], modelMatrix);
		}
	}

	// render bonuses
	for (auto& bonus : bonuses) {
		if (bonus.active) {

			glm::mat3 modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(bonus.position.x, bonus.position.y);
			modelMatrix *= transform2D::Scale(2.0f, 2.0f);
			modelMatrix *= transform2D::Rotate(0.65f);
			RenderMesh2D(meshes["bonus"], shaders["VertexColor"], modelMatrix);
		}
	}

	// render bonus lifes
	for (auto& bonus : bonlifes) {
		if (bonus.active) {

			glm::mat3 modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(bonus.position.x, bonus.position.y);
			modelMatrix *= transform2D::Scale(2.5f, 2.5f);
			RenderMesh2D(meshes["bonuslife"], shaders["VertexColor"], modelMatrix);
		}
	}

	// render shooting stars
	for (auto& star : stars) {
		glm::mat3 modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(star.position.x, star.position.y);
		modelMatrix *= transform2D::Scale(1.5f, 1.5f);
		modelMatrix *= transform2D::Rotate(-star.angle_rotation);


	
		if (star.color == "purple") {
			RenderMesh2D(meshes["star_purple"], shaders["VertexColor"], modelMatrix);
		}
		else if (star.color == "yellow") {
			RenderMesh2D(meshes["star_yellow"], shaders["VertexColor"], modelMatrix);
		}
		else if (star.color == "orange") {
			RenderMesh2D(meshes["star_orange"], shaders["VertexColor"], modelMatrix);
		}
		else if (star.color == "blue") {
			RenderMesh2D(meshes["star_blue"], shaders["VertexColor"], modelMatrix);
		}
	}
	
	if (restart) {
		sure = true;
		RenderText("ARE YOU SURE?", shaders["VertexColor"], glm::vec2(200.0f, 360.0f), 2.0f, 30.0f, true);
		isPaused = true;

		// render yes and no
		for (int i = 0; i < 2; i++) {

			options_gameOver[i][0].position.x = 700;
			options_gameOver[i][0].position.y = 200 - i * 50;

			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(options_gameOver[i][0].position.x, options_gameOver[i][0].position.y);
			modelMatrix *= transform2D::Scale(0.2f, 0.2f);
			RenderMesh2D(meshes["square_empty"], shaders["VertexColor"], modelMatrix);
		}

		RenderText("YES", shaders["VertexColor"], glm::vec2(750.0f, 215.0f), 1, 30.0f, false);
		RenderText("NO", shaders["VertexColor"], glm::vec2(750.0f, 165.0f), 1, 30.0f, false);
	}

	if (quit) {
		sure = true;
		RenderText("ARE YOU SURE?", shaders["VertexColor"], glm::vec2(200.0f, 360.0f), 2.0f, 30.0f, true);
		isPaused = true;

		// render yes and no
		for (int i = 0; i < 2; i++) {

			options_gameOver[i][0].position.x = 700;
			options_gameOver[i][0].position.y = 200 - i * 50;

			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(options_gameOver[i][0].position.x, options_gameOver[i][0].position.y);
			modelMatrix *= transform2D::Scale(0.2f, 0.2f);
			RenderMesh2D(meshes["square_empty"], shaders["VertexColor"], modelMatrix);
		}

		RenderText("YES", shaders["VertexColor"], glm::vec2(750.0f, 215.0f), 1, 30.0f, false);
		RenderText("NO", shaders["VertexColor"], glm::vec2(750.0f, 165.0f), 1, 30.0f, false);

	}

	if (gameOver == false) {

		if (isPaused == false) {

			// Update  bonus lifes
			for (auto& bonus : bonlifes) {
				if (bonus.active) {
					// direction timer
					bonus.directionChangeTimer += deltaTimeSeconds;

					// update rotation
					bonus.rotationAngle += bonus.rotationSpeed * deltaTimeSeconds;

					// update  position 
					float frequency = 0.01f; 
					bonus.position.x += bonus.velocity.x * deltaTimeSeconds * 2;
					bonus.position.y = bonus.initialPosition.y + 70.0f * glm::sin(frequency * bonus.position.x);

					// edge
					if (bonus.position.y < -20.0f || bonus.position.x < -20.0f || bonus.position.x > 1300.0f) {
						bonus.active = false;
					}

					// change direction 
					if (bonus.directionChangeTimer >= 0.7f) {
						bonus.directionChangeTimer = 0.0f; // reset  direction timer
						bonus.velocity = glm::vec2(-100.0f, 0.0f);
					}
				}
			}

			// Update bonuses
			for (auto& bonus : bonuses) {
				if (bonus.active) {
					// direction  timer
					bonus.directionChangeTimer += deltaTimeSeconds;

					// update  position
					bonus.position.x += bonus.velocity.x * deltaTimeSeconds;
					bonus.position.y += bonus.velocity.y * deltaTimeSeconds;

					// edge
					if (bonus.position.y < -20.0f || bonus.position.x < -20.0f || bonus.position.x > 1300.0f) {
						bonus.active = false;
					}

					// change direction 
					if (bonus.directionChangeTimer >= 0.7f) {
						bonus.direction *= -1; // change direction 
						bonus.velocity.x = bonus.direction * bonus.speed; // update velocity
						bonus.directionChangeTimer = 0.0f; // reset direction timer
					}
				}
			}

			// start tanks
			for (auto& enemy : enemies)
				for (auto& tank : tanks)
					if ((enemy.position.y + 20) == (tank.position.y + (squareSide / 2)) && enemy.position.x < 250)
						tank.start = true;

			// update tanks position
			for (auto& tank : tanks)
				if (tank.start == true)
					tank.position.x += tank.speed * deltaTimeSeconds;

			// tanks turrets
			tanks.erase(
				std::remove_if(tanks.begin(), tanks.end(),
					[](Tank& tank) { return tank.position.x > 1320; }),
				tanks.end());

			// erase turrets
			turretsOnBoard.erase(
				std::remove_if(turretsOnBoard.begin(), turretsOnBoard.end(),
					[](Turret& turret) { return turret.scale && turret.scaleFactor <= 0.0f; }),
				turretsOnBoard.end());

			// add turret on board
			if (selectedTurret != nullptr) {
				glm::mat3 modelMatrix = glm::mat3(1);
				modelMatrix *= transform2D::Translate(selectedTurret->position.x, selectedTurret->position.y);

				if (selectedTurret->color == "purple") {
					RenderMesh2D(meshes["turret_purple"], shaders["VertexColor"], modelMatrix);

				}
				else if (selectedTurret->color == "yellow") {
					RenderMesh2D(meshes["turret_yellow"], shaders["VertexColor"], modelMatrix);

				}
				else if (selectedTurret->color == "blue") {
					RenderMesh2D(meshes["turret_blue"], shaders["VertexColor"], modelMatrix);

				}
				else if (selectedTurret->color == "orange") {
					RenderMesh2D(meshes["turret_orange"], shaders["VertexColor"], modelMatrix);

				}
			}

			// generate random stars
			starSpawnTimer += deltaTimeSeconds;
			if (starSpawnTimer >= starSpawnInterval && star_count < 15) {
				for (int i = 0; i < 3; i++) {
					Star star;
					star.position.x = static_cast<float>(rand() % 1250);
					star.position.y = static_cast<float>(rand() % 700);
					randomStars.push_back(star);
				}

				starSpawnInterval = random(7.0f, 14.0f);
				// reset timer
				starSpawnTimer = 0;
			}

			//  eliminate enemies when take life
			for (auto it = enemies.begin(); it != enemies.end();) {
				it->position.x -= it->speed * deltaTimeSeconds;

				if (it->position.x < -50) {
					it = enemies.erase(it);
				}
				else {
					++it;
				}
			}

			// random enemy spawn
			enemySpawnTimer = enemySpawnTimer + 2 * deltaTimeSeconds;
			if (enemySpawnTimer >= enemySpawnInterval) {
				// rows and color
				std::vector<string> lineColors = { "purple", "yellow", "blue", "orange" };
				std::vector<float> rows = { 350 + squareSide / 2, 200 + squareSide / 2, 50 + squareSide / 2 };

				// random row and color
				int line = rand() % rows.size();
				int color = rand() % lineColors.size();

				Enemy enemy;
				enemy.position.x = 1280;
				enemy.position.y = rows[line];
				enemy.color = lineColors[color];
				enemy.radius = initial_enemy_rad;
				enemies.push_back(enemy);

				enemySpawnInterval = random(4.0f, 10.0f);

				enemySpawnTimer = 0.0f; // reset the timer
			}


			// generate random bonus
			bonusSpawnTimer += deltaTimeSeconds;
			if (bonuses.empty() && bonusSpawnTimer >= bonusSpawnInterval) {
				Bonus bonus;
				bonus.position.x = static_cast<float>(rand() % 1000);
				bonus.position.y = 720.0f; 

				bonus.directionChangeTimer = 0.0f;

				bonus.velocity.x = bonus.direction * bonus.speed; 
				bonus.velocity.y = -bonus.speed; 

				bonus.active = true;
				bonuses.push_back(bonus);
				// reset the timer
				bonusSpawnTimer = 0.0f;
			}

			// random bonus life
			bonuslifeSpawnTimer += deltaTimeSeconds;
			if (bonlifes.empty() && bonuslifeSpawnTimer >= bonuslifeSpawnInterval) {
				BonusLife bonus;
				bonus.initialPosition.x = 1300.0f; 
				bonus.initialPosition.y = static_cast<float>(rand() % 500 + 100);
				bonus.position = bonus.initialPosition;
				bonus.directionChangeTimer = 0.0f; 
				bonus.rotationAngle = 0.0f; 
				bonus.rotationSpeed = static_cast<float>(rand() % 180 + 90); 
				bonus.velocity = glm::vec2(-100.0f, 0.0f); 
				bonus.active = true;

				bonlifes.push_back(bonus);
				// reset the timer
				bonuslifeSpawnTimer = 0.0f;
			}

			// remove inactive bonuses
			bonuses.erase(std::remove_if(bonuses.begin(), bonuses.end(), [](const Bonus& bonus) {
				return !bonus.active;
				}), bonuses.end());

			// update stars for turrets
			for (auto& turret : turretsOnBoard) {
				turret.starSpawnTimer += deltaTimeSeconds;
				// check if must shot
				if (turret.starSpawnTimer >= turret.starSpawnInterval) {

					// same color same line
					bool shouldshoot = false;
					for (auto& enemy : enemies) {
						if (enemy.position.x >= turret.position.x && enemy.color == turret.color
							&& enemy.position.y == turret.position.y) {
							shouldshoot = true;
							break;
						}

					}
					if (shouldshoot) {
						Star star;
						star.position.x = turret.position.x + 40;
						star.position.y = turret.position.y;
						star.color = turret.color;

						stars.push_back(star);
					}

					// reset the timer
					turret.starSpawnTimer = 0.0f;
				}
			}

			// update pos and rotation stars
			for (auto& star : stars) {
				star.position.x += star.speed * deltaTimeSeconds;
				star.angle_rotation += 5.0f * deltaTimeSeconds;
			}

			// colisions star-enemy
			for (auto& star : stars) {
				for (auto& enemy : enemies) {
					float distance = glm::distance(star.position, enemy.position);

					// same color collision
					if (distance < (star.radius + enemy.radius) && star.color == enemy.color) {
						star.collision = true;
						enemy.hits--;
						enemy.radius -= initial_enemy_rad / 3;
						enemy.lifes--;

						if (enemy.lifes == 0) {
							if (enemy.color == "purple") {
								score += 40;
							}
							else if (enemy.color == "yellow") {
								score += 30;
							}
							else if (enemy.color == "blue") {
								score += 20;
							}
							else if (enemy.color == "orange") {
								score += 10;
							}
						}

					}

				}

			}

			// collisions tank-enemy
			for (auto& tank : tanks)
				for (auto& enemy : enemies) {
					float distance = glm::distance(tank.position, enemy.position);

					if (distance < (tank.radius + enemy.radius)) {
						enemy.die = true;
						enemy.dead += 1;

						if (enemy.color == "purple" && enemy.dead == 1) {
							score += 40;

						}
						else if (enemy.color == "yellow" && enemy.dead == 1) {
							score += 30;

						}
						else if (enemy.color == "blue" && enemy.dead == 1) {
							score += 20;

						}
						else if (enemy.color == "orange" && enemy.dead == 1) {
							score += 10;

						}
					}
				}

			// colisions turret-enemy
			for (auto& turret : turretsOnBoard) {
				for (Enemy& enemy : enemies) {
					float distance = glm::distance(turret.position, enemy.position);
					float starRadius = 60;

					// check for collision 
					if (distance < (starRadius + enemy.radius) && enemy.lifes != 0) {
						turret.scale = true;
						// update board
						for (int k = 0; k < 3; k++)
							for (int j = 0; j < 3; j++)
								if ((board[k][j].position.x + squareSide / 2) == turret.position.x && (board[k][j].position.y + squareSide / 2) == turret.position.y)
									board[k][j].occupied = false;
					}

				}

			}

			// Remove inactive bonus lifes
			bonlifes.erase(std::remove_if(bonlifes.begin(), bonlifes.end(), [](const BonusLife& bonus) {
				return !bonus.active;
				}), bonlifes.end());

			// erase star from array
			stars.erase(
				std::remove_if(stars.begin(), stars.end(),
					[](const Star& star) {
						return star.collision;
					}),
				stars.end());


			// errase enemy from array
			enemies.erase(
				std::remove_if(enemies.begin(), enemies.end(),
					[](const Enemy& enemy) {
						return  (enemy.die && enemy.scaleFactor <= 0.0f) || enemy.scaleFactor <= 0.0f;
					}),
				enemies.end());

			// update the lifes
			for (auto it = enemies.begin(); it != enemies.end();) {

				if (it->position.x + it->radius < 150) {
					it = enemies.erase(it);
					lifes--;

				}
				else {
					++it;
				}
			}

			// lose game
			if (lifes == 0) {
				gameOver = true;

			}

			if (quit)
				exit(0);

			

		} 

		else {
			if (quit == false && restart == false) {

				RenderText("PAUSED", shaders["VertexColor"], glm::vec2(400.0f, 360.0f), 2.0f, 50.0f, true);
				// render options area
				for (int i = 0; i < 3; i++) {

					options_paused[i][0].position.x = 650;
					options_paused[i][0].position.y = 260 - i * 50;

					modelMatrix = glm::mat3(1);
					modelMatrix *= transform2D::Translate(options_paused[i][0].position.x, options_paused[i][0].position.y);
					modelMatrix *= transform2D::Scale(0.2f, 0.2f);
					RenderMesh2D(meshes["square_empty"], shaders["VertexColor"], modelMatrix);
				}
				RenderText("QUIT", shaders["VertexColor"], glm::vec2(700.0f, 275.0f), 1, 30.0f, false);
				RenderText("RESTART", shaders["VertexColor"], glm::vec2(700.0f, 225.0f), 1, 30.0, false);
				RenderText("CONTINUE", shaders["VertexColor"], glm::vec2(700.0f, 175.0f), 1, 30.0f, false);
			
			
			}
			else if (restart) {

				if (yes) {
					lifes = 3;
					score = 0;
					star_count = 5;
					bonusSpawnTimer = 0.0f;
					bonuslifeSpawnTimer = 0.0f;
					starSpawnTimer = 0.0f;
					

					// eliminate enemies 
					for (auto it = enemies.begin(); it != enemies.end();) {
						it = enemies.erase(it);
					}

					// eliminate random stars
					for (auto it = randomStars.begin(); it != randomStars.end();) {
						it = randomStars.erase(it);
					}

					// eliminate shooting stars
					for (auto it = stars.begin(); it != stars.end();) {
						it = stars.erase(it);
					}

					// clear the board for nwe turrets
					for (size_t i = 0; i < turretsOnBoard.size(); i++)
						for (int k = 0; k < 3; k++)
							for (int j = 0; j < 3; j++)
								if ((board[k][j].position.x + squareSide / 2) == turretsOnBoard[i].position.x && (board[k][j].position.y + squareSide / 2) == turretsOnBoard[i].position.y)
									board[k][j].occupied = false;

					// eliminate turrets
					for (auto it = turretsOnBoard.begin(); it != turretsOnBoard.end();) {
						it = turretsOnBoard.erase(it);
					}

					// eliminate bonuses
					for (auto it = bonuses.begin(); it != bonuses.end();) {
						it = bonuses.erase(it);
					}

					// eliminate bonus lifes
					for (auto it = bonlifes.begin(); it != bonlifes.end();) {
						it = bonlifes.erase(it);
					}

					// eliminate tanks
					for (auto it = tanks.begin(); it != tanks.end();) {
						it = tanks.erase(it);
					}

					restart = false;
					yes = false;
					isPaused = false;

					
					Update(deltaTimeSeconds);
					Init();
				}

				if (no) {
					no = false;
					isPaused = false;
					restart = false;
				}
			}
			else if (quit) {

				if (yes)
					exit(0);

				if (no) {
					no = false;
					quit = false;
					isPaused = false;

				}
			}
		}
	}
	else {

		if (restart == false && quit == false) {

			isPaused = true;
			RenderText("GAME OVER", shaders["VertexColor"], glm::vec2(200.0f, 360.0f), 2.0f, 50.0f, true);

			// render options area
			for (int i = 0; i < 2; i++) {

				options_gameOver[i][0].position.x = 700;
				options_gameOver[i][0].position.y = 200 - i * 50;

				modelMatrix = glm::mat3(1);
				modelMatrix *= transform2D::Translate(options_gameOver[i][0].position.x, options_gameOver[i][0].position.y);
				modelMatrix *= transform2D::Scale(0.2f, 0.2f);
				RenderMesh2D(meshes["square_empty"], shaders["VertexColor"], modelMatrix);
			}

			RenderText("PLAY AGAIN", shaders["VertexColor"], glm::vec2(750.0f, 215.0f), 1, 30.0f, false);
			RenderText("QUIT", shaders["VertexColor"], glm::vec2(750.0f, 165.0f), 1, 30.0f, false);
		}
		
	}



}



void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_P) {
		isPaused = !isPaused;
	}

	if (key == GLFW_KEY_Y) {
		yes = true;
	}

	if (key == GLFW_KEY_N) {
		no = true;
	}

	if (key == GLFW_KEY_Q) {
		quit = !quit;

	}

	if (key == GLFW_KEY_R) {
		restart = !restart;

	}
	if (key == GLFW_KEY_C && (restart == false && quit == false) && isPaused == true) {
		isPaused = false;

	}

}


void Tema1::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// new window
	auto camera = GetSceneCamera();
	glm::ivec2 res = window->GetResolution();
	glm::vec4 mouse_coord = glm::vec4((mouseX * 2.f) / (res.x * 1.f) - 1.f, (mouseY * 2.f) / (res.y * 1.f) - 1.f, 1.0f, 1.0f);
	mouse_coord = glm::inverse(camera->GetProjectionMatrix()) * mouse_coord;
	mouse_coord = glm::inverse(camera->GetViewMatrix()) * mouse_coord;
	mouseX = mouse_coord.x;
	mouseY = 720 - mouse_coord.y;


	// dragging turret
	if (isDragging && selectedTurret != nullptr) {

		float animationStep = 1;
		glm::vec2 targetPosition(mouseX, mouseY);
		selectedTurret->position = selectedTurretInitialPosition + (targetPosition - selectedTurretInitialPosition) * animationStep;

		Update(0);
	}
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// new window
	auto camera = GetSceneCamera();
	glm::ivec2 res = window->GetResolution();
	glm::vec4 mouse_coord = glm::vec4((mouseX * 2.f) / (res.x * 1.f) - 1.f, (mouseY * 2.f) / (res.y * 1.f) - 1.f, 1.0f, 1.0f);
	mouse_coord = glm::inverse(camera->GetProjectionMatrix()) * mouse_coord;
	mouse_coord = glm::inverse(camera->GetViewMatrix()) * mouse_coord;
	mouseX = mouse_coord.x;
	mouseY = 720 - mouse_coord.y;

	if (isPaused == false) {
		// click turret for chosing
		if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
			leftMousePressed = true;
			for (auto& turret : turrets) {
				float distance = glm::distance(glm::vec2(mouseX, mouseY), turret.position);
				int cost = 0;

				if (turret.color == "orange")
					cost = 1;
				if (turret.color == "blue")
					cost = 2;
				if (turret.color == "yellow")
					cost = 2;
				if (turret.color == "purple")
					cost = 3;

				if (turret.draggable && distance < turret.radius && cost <= star_count) {

					if (selectedTurret == nullptr) {
						selectedTurret = new Turret(turret);
						selectedTurretInitialPosition = selectedTurret->position;

					}
					else {
						*selectedTurret = turret;
						selectedTurretInitialPosition = selectedTurret->position;

					}

					isDragging = true;
					break;
				}

			}
		}

		// click star
		if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
			// check if clicked on a star
			for (auto it = randomStars.begin(); it != randomStars.end(); it++) {
				float distance = glm::distance(glm::vec2(mouseX, mouseY), it->position);
				if (distance < it->radius) {
					if (star_count < 15)
					star_count++;
					randomStars.erase(it);
					break;
				}
			}
		}

		// click bonus
		if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
			for (auto it = bonuses.begin(); it != bonuses.end(); ) {
				float distance = glm::distance(glm::vec2(mouseX, mouseY), it->position);

				// check if in area
				if (distance < it->radius) {
					for (auto& enemy : enemies) {
						enemy.hits--;
						enemy.lifes--;
						enemy.radius -= initial_enemy_rad / 3;
					}

					it = bonuses.erase(it);
				}
				else {
					++it;
				}
			}
		}

		// delete turret
		if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
			// rwmove
			for (size_t i = 0; i < turretsOnBoard.size(); i++) {
				float distance = glm::distance(glm::vec2(mouseX, mouseY), turretsOnBoard[i].position);
				if (distance < turretsOnBoard[i].radius) {
					// scale to 0
					turretsOnBoard[i].scale = true;

					// update board
					for (int k = 0; k < 3; k++)
						for (int j = 0; j < 3; j++)
							if ((board[k][j].position.x + squareSide / 2) == turretsOnBoard[i].position.x && (board[k][j].position.y + squareSide / 2) == turretsOnBoard[i].position.y)
								board[k][j].occupied = false;

					break;
				}
			}
		}

		// click bonus life
		if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
			for (auto it = bonlifes.begin(); it != bonlifes.end(); ) {
				float distance = glm::distance(glm::vec2(mouseX, mouseY), it->position);

				// check if in area
				if (distance < it->radius) {
					if (lifes < 3)
						lifes++;

					it = bonlifes.erase(it); 
				}
				else {
					++it;
				}
			}
		}

		// click options
		if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
			for (int i = 0; i < 3; i++) {

				float distance = glm::distance(glm::vec2(mouseX, mouseY), glm::vec2(options[0][i].position.x + 10.0f, options[0][i].position.y + 10.0f));
				if (distance < 15.0f) {
					if (i == 2)
						isPaused = !isPaused;

					if (i == 0)
						quit = !quit;

					if (i == 1)
						restart = !restart;
				}
			}

		}
	}
	
	// click options paused
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && gameOver == false && sure == false) {
			for (int i = 0; i < 3; i++) {

				float distance = glm::distance(glm::vec2(mouseX, mouseY), glm::vec2(options_paused[i][0].position.x + 10.0f, options_paused[i][0].position.y + 10.0f));
				if (distance < 15.0f) {
					if (i == 2)
						isPaused = false;

					if (i == 0)
						quit = !quit;

					if (i == 1)
						restart = true;


				}
			}

		}

	// click options gameover
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && gameOver == true && sure == false) {
			for (int i = 0; i < 2; i++) {

				float distance = glm::distance(glm::vec2(mouseX, mouseY), glm::vec2(options_gameOver[i][0].position.x + 10.0f, options_gameOver[i][0].position.y + 10.0f));
				if (distance < 15.0f) {
					if (i == 1)
						quit = !quit;

					if (i == 0) {
						restart = true;
						gameOver = false;
					}
				}
			}

	}

	// click yes and no
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && sure == true) {
		for (int i = 0; i < 2; i++) {

			float distance = glm::distance(glm::vec2(mouseX, mouseY), glm::vec2(options_gameOver[i][0].position.x + 10.0f, options_gameOver[i][0].position.y + 10.0f));
			if (distance < 15.0f) {
				if (i == 1) {
					no = true;
					sure = false;
				}

				if (i == 0) 
					yes = true;
			}
		}
		sure = false;
	}
	
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// new window
	auto camera = GetSceneCamera();
	glm::ivec2 res = window->GetResolution();
	glm::vec4 mouse_coord = glm::vec4((mouseX * 2.f) / (res.x * 1.f) - 1.f, (mouseY * 2.f) / (res.y * 1.f) - 1.f, 1.0f, 1.0f);
	mouse_coord = glm::inverse(camera->GetProjectionMatrix()) * mouse_coord;
	mouse_coord = glm::inverse(camera->GetViewMatrix()) * mouse_coord;
	mouseX = mouse_coord.x;
	mouseY = 720 - mouse_coord.y;

	// put turret
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && leftMousePressed) {
		leftMousePressed = false;
		if (isDragging && selectedTurret != nullptr) {
			validPlacement = false;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					float distance = glm::distance(glm::vec2(mouseX, mouseY), glm::vec2(board[i][j].position.x + squareSide / 2, board[i][j].position.y + squareSide / 2));
					if (distance < board[i][j].radius && !board[i][j].occupied) {


						selectedTurret->position.x = board[i][j].position.x + squareSide / 2;
						selectedTurret->position.y = board[i][j].position.y + squareSide / 2;
						board[i][j].occupied = true;
						turretsOnBoard.push_back(*selectedTurret);


						if (selectedTurret->color == "purple") {

							star_count -= 3;
						}
						else if (selectedTurret->color == "yellow") {

							star_count -= 2;
						}
						else if (selectedTurret->color == "blue") {

							star_count -= 2;
						}
						else if (selectedTurret->color == "orange") {

							star_count -= 1;
						}


						delete selectedTurret;
						selectedTurret = nullptr;
						validPlacement = true;
						isDragging = false;

						break;
					}
				}
			}
			if (!validPlacement) {
				delete selectedTurret;
				selectedTurret = nullptr;
				isDragging = false;
			}
		}
	}
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
