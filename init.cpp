#include <vector>
#include <iostream>
#include "lab_m1/tema1/init.hpp"
#include "lab_m1/tema1/TransformUtils.hpp"
#include "lab_m1/tema1/Shapes.hpp"
#include <math.h>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

InitClass::InitClass()
{
}


InitClass::~InitClass()
{
}


void InitClass::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // Initialize time accumulators matrix
    for (int i = 0; i < PLACINGS_SIZE; i++)
	{
		for (int j = 0; j < PLACINGS_SIZE; j++)
        {
            timedShooting[i][j] = 0.0f;
	    }
    }

    // Initialise line enemy timer
    for (int i = 0; i < PLACINGS_SIZE; i++)
    {
        for (int j = 0; j < TYPES_OF_SHOOTERS; j++)
        {
            lineEnemyTimer[i][j] = 0.0f;
        }
    }

    slowDownTimer = 0.0f;
    healthPointSpawnRate = 0.0f;
    coinSpawnTimer = 0.0f;
    bigCoinTimer = 0.0f;
    difficultyTimer = 0.0f;
    enemyPositionTimer = 0.0f;

    staticScene = new StaticScene();
    colorUtils = new ColorUtils();
}


void InitClass::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}
 

void InitClass::RendPlacings()
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transformUtils::Translate(-INITIAL_X / 8, INITIAL_Y);

    for (int i = 0; i < PLACINGS_SIZE; i++)
    {
        if (i)
        {
            modelMatrix *= transformUtils::Translate(0, MATRIX_DISPLACEMENT);
            modelMatrix *= transformUtils::Translate(-MATRIX_DISPLACEMENT * PLACINGS_SIZE, 0);
        }
        for (int j = 0; j < PLACINGS_SIZE; j++) {
            modelMatrix *= transformUtils::Translate(MATRIX_DISPLACEMENT, 0);

            if (staticScene->getPlacing(i, j)->getVisibility())
            {
				RenderMesh2D(staticScene->getPlacing(i, j)->getMesh(), shaders["VertexColor"], modelMatrix);

                // Set position of the placing
                glm::vec2 position;
                position.x = (float)(MATRIX_CORNER_X + j * MATRIX_DISPLACEMENT);
                position.y = (float)(MATRIX_CORNER_Y + i * MATRIX_DISPLACEMENT);
                staticScene->getPlacing(i, j)->setPosition(position);
			}
        }
    }
}


void InitClass::RendHitBar()
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transformUtils::Translate(INITIAL_X, INITIAL_Y);

    if (staticScene->getHitBar()->getVisibility())
	{ 
        RenderMesh2D(staticScene->getHitBar()->getMesh(), shaders["VertexColor"], modelMatrix);

        // Set position of the hit bar
        glm::vec2 position;
        position.x = (float)(INITIAL_X);
        position.y = (float)(INITIAL_Y);
        staticScene->getHitBar()->setPosition(position);
    }
}


void InitClass::RendShooters()
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transformUtils::Translate(PLACEHOLDERS_X + DEFAULT_SQUARE_SIDE / 8, PLACEHOLDERS_Y + DEFAULT_SQUARE_SIDE / 2);
    bool loweredLine = false;
    int lastRow = 0;

    for (int i = 0; i < PLACEHOLDERS_COUNT_TOTAL; i++)
    {
        int row = i / PLACEHOLDERS_COUNT;
        if (row != lastRow)
        {
            loweredLine = false;
            lastRow = row;
        }

        if (i)
        {
            modelMatrix *= transformUtils::Translate(SHOOTER_DISPLACEMENT, 0);
        }

        if (i >= PLACEHOLDERS_COUNT)
        {
            if (i == 4)
            {
                modelMatrix *= transformUtils::Translate(DEFAULT_SQUARE_SIDE * SPAWNER_SCALE, 0);
            }
            else if (i == 5)
            {
				modelMatrix *= transformUtils::Translate(DEFAULT_SQUARE_SIDE * CANNON_SCALE, 0);
            }
            else if (i == 7)
            {
                modelMatrix *= transformUtils::Translate(-DEFAULT_SQUARE_SIDE * SNOW_CANNON_SCALE, 0);
            }
        }

        if (!loweredLine && row)
        {
            modelMatrix *= transformUtils::Translate(0, -MATRIX_DISPLACEMENT);
            modelMatrix *= transformUtils::Translate(-SHOOTER_DISPLACEMENT * PLACEHOLDERS_COUNT, 0);
            loweredLine = true;
        }

        if (staticScene->getShooters()[i]->getVisibility())
        {
            RenderMesh2D(staticScene->getShooters()[i]->getMesh(), shaders["VertexColor"], modelMatrix);

            // Set position of the shooter
            glm::vec2 position;
            position.x = (float)(PLACEHOLDERS_X + DEFAULT_SQUARE_SIDE / 8 + SHOOTER_DISPLACEMENT * i);
            position.y = (float)(PLACEHOLDERS_Y + DEFAULT_SQUARE_SIDE / 2);

            staticScene->getShooters()[i]->setMovingPosition(position);
        }
    }
}


void InitClass::RendHealthPoints()
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transformUtils::Translate(HEALTH_POINTS_X, HEALTH_POINTS_Y);
    for (int i = 0; i < nrOfHealthPoints; i++)
    {
        if (i)
        {
            modelMatrix *= transformUtils::Translate(MATRIX_DISPLACEMENT, 0);
        }

        if (staticScene->getHealthPoints()[i]->getVisibility())
        {
			RenderMesh2D(staticScene->getHealthPoints()[i]->getMesh(), shaders["VertexColor"], modelMatrix);

            // Set position of the health point
            glm::vec2 position;
            position.x = (float)(HEALTH_POINTS_X + i * MATRIX_DISPLACEMENT);
            position.y = (float)(HEALTH_POINTS_Y);

            staticScene->getHealthPoints()[i]->setPosition(position);
		}
    }
}


void InitClass::RendPlaceHolders()
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transformUtils::Translate(PLACEHOLDERS_X, PLACEHOLDERS_Y);
    bool loweredLine = false;
    int lastRow = 0;

    for (int i = 0; i < PLACEHOLDERS_COUNT_TOTAL; i++)
    {
        int row = i / PLACEHOLDERS_COUNT;
        if (row != lastRow)
        {
            loweredLine = false;
            lastRow = row;
        }

        if (i)
        {
            modelMatrix *= transformUtils::Translate(SHOOTER_DISPLACEMENT, 0);
        }

        if (!loweredLine && row)
        {
            modelMatrix *= transformUtils::Translate(0, -MATRIX_DISPLACEMENT);
            modelMatrix *= transformUtils::Translate(-SHOOTER_DISPLACEMENT * PLACEHOLDERS_COUNT, 0);
            loweredLine = true;
        }

        if (staticScene->getPlaceHolders()[i]->getVisibility())
        {
            RenderMesh2D(staticScene->getPlaceHolders()[i]->getMesh(), shaders["VertexColor"], modelMatrix);

            // Set position of the place holder
            glm::vec2 position;
            position.x = (float)(PLACEHOLDERS_X + i * SHOOTER_DISPLACEMENT);
            position.y = (float)(PLACEHOLDERS_Y);
            staticScene->getPlaceHolders()[i]->setPosition(position);
        }
    }
}


void InitClass::Shoot()
{
    for (int i = 0; i < PLACINGS_SIZE; i++)
    {
		for (int j = 0; j < PLACINGS_SIZE; j++)
		{
			if (staticScene->getPlacing(i, j)->getTaken() && 
                staticScene->getPlacing(i, j)->getVisibility() &&
                shootersMatrix[i][j] != nullptr &&
                createdShooter[i][j] &&
                !shootersMatrix[i][j]->getIsSpawner() &&
                !shootersMatrix[i][j]->getIsEater())
			{   
                glm::vec3 color = shootersMatrix[i][j]->getColor();

                // Create bullets with a timer of 2 seconds
                if (timedShooting[i][j] > colorUtils->GetBulletIntervalByColor(color) &&
                    (LineContainsEnemyOfColor(i, color) ||
                        (shootersMatrix[i][j]->getIsCannon() || shootersMatrix[i][j]->getIsSnowCannon()) &&
                         LineContainsEnemy(i)))
                {
                    MeshWrapperBullet* bullet = new MeshWrapperBullet(shapes::CreateStar(
                                                                            "starShooting",
                                                                            glm::vec3(0, 0, 2), 
                                                                            DEFAULT_BULLET_SIZE,
                                                                            color,
                                                                            true));
                    if (shootersMatrix[i][j]->getIsCannon())
                    {
                        bullet = new MeshWrapperBullet(shapes::CreateRocket(
                                                                "starShooting",
                                                                glm::vec3(0, 0, 2),
                                                                DEFAULT_BULLET_SIZE,
                                                                glm::vec3(1.0f, 1.0f, 1.0f), true));
                        bullet->setIsRocket(true);
                    }

                    if (shootersMatrix[i][j]->getIsSnowCannon())
                    {
                        bullet = new MeshWrapperBullet(shapes::CreateSnowBullet(
																"starShooting",
																glm::vec3(0, 0, 2),
																DEFAULT_BULLET_SIZE,
                                                                glm::vec3(0.7f, 0.7f, 0.9f),
																glm::vec3(1.0f, 1.0f, 1.0f), true));
						bullet->setIsSnowball(true);
					}


                    bullet->setPosition(shootersMatrix[i][j]->getPosition().x + DEFAULT_BULLET_SIZE, shootersMatrix[i][j]->getPosition().y);
                    bullet->setMovingPosition(shootersMatrix[i][j]->getPosition().x + DEFAULT_BULLET_SIZE, shootersMatrix[i][j]->getPosition().y);
                    bullet->setColor(shootersMatrix[i][j]->getColor());
                    bullet->setBulletWasShot(true);
                    bullet->setShooterPower(shootersMatrix[i][j]->getShooterPower());

                    shootersMatrix[i][j]->setBulletCount(shootersMatrix[i][j]->getBulletCount() + 1);
                    lineBullets[i].push_back(bullet);

                    timedShooting[i][j] = 0;
                }
            }
		}
    }
}


void InitClass::DisapearAnimation(float deltaTimeSeconds, MeshWrapper* mesh, float radius)
{
    // Make a disapear animation for the shooter in the corresponding placing in the matrix of shooters
    glm::vec2 scale = mesh->getScale();
    scale.x -= 0.7f * deltaTimeSeconds;
    scale.y -= 0.7f * deltaTimeSeconds;
    mesh->setScale(scale);

    if (mesh != nullptr)
    {
		// Rend the shooter at the position of the corresponding placing in matrix
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformUtils::Translate(mesh->getMovingPosition());
        modelMatrix *= transformUtils::Translate(radius, 0);
        modelMatrix *= transformUtils::Scale(mesh->getScale());
        modelMatrix *= transformUtils::Translate(-radius, 0);
        RenderMesh2D(mesh->getMesh(), shaders["VertexColor"], modelMatrix);
	}
}


void InitClass::PulsingAnimation(float deltaTimeSeconds, MeshWrapper* mesh, float radius, float treshold, float speed)
{
    // Creates a pulsing animation like a heart beat
    glm::vec2 scale = mesh->getScale();

    if (mesh->getTimeAccumulator() < treshold / 2)
    {
		scale.x -= speed * deltaTimeSeconds;
		scale.y -= speed * deltaTimeSeconds;
	}
    else
    {
		scale.x += speed * deltaTimeSeconds;
		scale.y += speed * deltaTimeSeconds;
	}

    if (mesh->getTimeAccumulator() > treshold)
    {
        mesh->setTimeAccumulator(0.0f);
    }

    mesh->setScale(scale);

    if (mesh != nullptr)
    {
		// Rend the shooter at the position of the corresponding placing in matrix
		modelMatrix = glm::mat3(1);
		modelMatrix *= transformUtils::Translate(mesh->getMovingPosition());
		modelMatrix *= transformUtils::Translate(radius, 0);
		modelMatrix *= transformUtils::Scale(mesh->getScale());
		modelMatrix *= transformUtils::Translate(-radius, 0);
		RenderMesh2D(mesh->getMesh(), shaders["VertexColor"], modelMatrix);
	}
}


void InitClass::RendMovingShooter()
{
    // If the mouse is pressed, render the shooter at the mouse coordinates
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
    {
        if (pressedCorrectly)
        {
            holdingShooter = true;
        }

        int mouseX = window->GetCursorPosition().x;
        int mouseY = window->GetCursorPosition().y;

        // Set mouse coordinates to world coordinates
        mouseY = window->GetResolution().y - mouseY;

        {
            if (pressedCorrectly && !releasedCorrectly)
            {
                // Rend the shooter at the mouse coordinates
                if (isSimpleShooter)
                {
                    Mesh* mesh = shapes::CreateShooter("shooterMouse", glm::vec3(0, 0, 2), DEFAULT_SQUARE_SIDE * SHOOTER_SCALE, holdingShooterColor, true);
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transformUtils::Translate((float)mouseX, (float)mouseY);
                    RenderMesh2D(mesh, shaders["VertexColor"], modelMatrix);
                }
                else if (isSpawner)
                {
                    Mesh* mesh = shapes::CreateSpawner("shooterMouse", glm::vec3(0, 0, 2), DEFAULT_SQUARE_SIDE * SHOOTER_SCALE, holdingShooterColor, glm::vec3(1.0f, 1.0f, 1.0f), true);
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transformUtils::Translate((float)mouseX, (float)mouseY);
                    RenderMesh2D(mesh, shaders["VertexColor"], modelMatrix);
                } 
                else if (isCannon)
                {
                    Mesh* mesh = shapes::CreateCannon("shooterMouse", glm::vec3(0, 0, 2), DEFAULT_SQUARE_SIDE * SHOOTER_SCALE, holdingShooterColor, glm::vec3(1.0f, 1.0f, 1.0f), true);
					modelMatrix = glm::mat3(1);
					modelMatrix *= transformUtils::Translate((float)mouseX, (float)mouseY);
					RenderMesh2D(mesh, shaders["VertexColor"], modelMatrix);
                }
                else if (isEater)
                {
                    Mesh* mesh = shapes::CreateEater("shooterMouse", glm::vec3(0, 0, 2), DEFAULT_SQUARE_SIDE * SHOOTER_SCALE, holdingShooterColor, glm::vec3(1.0f, 0.0f, 0.0f), true);
					modelMatrix = glm::mat3(1);
					modelMatrix *= transformUtils::Translate((float)mouseX, (float)mouseY);
					RenderMesh2D(mesh, shaders["VertexColor"], modelMatrix);
                } 
                else if (isSnowCannon)
                {
                    Mesh* mesh = shapes::CreateSnowCannon("shooterMouse", glm::vec3(0, 0, 2), DEFAULT_SQUARE_SIDE * SHOOTER_SCALE, holdingShooterColor, glm::vec3(1.0f, 1.0f, 1.0f), true);
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transformUtils::Translate((float)mouseX, (float)mouseY);
                    RenderMesh2D(mesh, shaders["VertexColor"], modelMatrix);
                }
            }
        }
    }
    else
    {
		holdingShooter = false;
	}


    // If released correctly, render the shooter in the corresponding placing
    if (releasedCorrectly && staticScene->getPlacing(releaseRow, releaseCol)->getTaken() == false)
    {
        // Set the corresponding placing as taken
        staticScene->getPlacing(releaseRow, releaseCol)->setTaken(true);
        staticScene->getPlacing(releaseRow, releaseCol)->setColor(releasedShooterColor);
        releasedCorrectly = false;
        releaseRow = -1;
        releaseCol = -1;
    }
}


void InitClass::CreateActiveShooters()
{
    // Create the active shooters
    for (int i = 0; i < PLACINGS_SIZE; i++)
    {
        for (int j = 0; j < PLACINGS_SIZE; j++)
        {
            if (staticScene->getPlacing(i, j)->getTaken() && staticScene->getPlacing(i, j)->getVisibility() && !createdShooter[i][j])
            {
                MeshWrapperShooter* shooter = nullptr;
                if (isSimpleShooter)
                {
                    shooter = new MeshWrapperShooter(
                        shapes::CreateShooter("shooterActive",
                            glm::vec3(0, 0, 2),
                            DEFAULT_SQUARE_SIDE * SHOOTER_SCALE,
                            staticScene->getPlacing(i, j)->getColor(),
                            true));
                    shooter->setColor(staticScene->getPlacing(i, j)->getColor());
                    shooter->setShooterPower(colorUtils->SelectShootingPowerByColor(staticScene->getPlacing(i, j)->getColor()));
                } 
                else if (isSpawner)
                {
                    shooter = new MeshWrapperShooter(
                        shapes::CreateSpawner("shooterActive",
                        glm::vec3(0, 0, 2),
                        DEFAULT_SQUARE_SIDE * SHOOTER_SCALE,
                        staticScene->getPlacing(i, j)->getColor(),
                        glm::vec3(1.0f, 1.0f, 1.0f),
                        true));
                    shooter->setColor(staticScene->getPlacing(i, j)->getColor());
                    shooter->setShooterPower(colorUtils->SelectShootingPowerByColor(staticScene->getPlacing(i, j)->getColor()));
                    shooter->setIsSpawner(true);
                } 
                else if (isEater)
                {
                    shooter = new MeshWrapperShooter(
                        shapes::CreateEater("shooterActive",
                            glm::vec3(0, 0, 2),
                            DEFAULT_SQUARE_SIDE * SHOOTER_SCALE,
                            staticScene->getPlacing(i, j)->getColor(),
                            glm::vec3(1.0f, 0.0f, 0.0f),
                            true));
                    shooter->setColor(staticScene->getPlacing(i, j)->getColor());
                    shooter->setShooterPower(colorUtils->SelectShootingPowerByColor(staticScene->getPlacing(i, j)->getColor()));
                    shooter->setIsEater(true);
                }
                else if (isCannon)
                {
                    shooter = new MeshWrapperShooter(
						shapes::CreateCannon("shooterActive",
                        glm::vec3(0, 0, 2),
                        DEFAULT_SQUARE_SIDE * SHOOTER_SCALE,
                        staticScene->getPlacing(i, j)->getColor(),
                        glm::vec3(1.0f, 1.0f, 1.0f),
                        true));
					shooter->setColor(staticScene->getPlacing(i, j)->getColor());
					shooter->setShooterPower(colorUtils->SelectShootingPowerByColor(staticScene->getPlacing(i, j)->getColor()));
                    shooter->setIsCannon(true);
                }
                else if (isSnowCannon)
                {
                    shooter = new MeshWrapperShooter(
						shapes::CreateSnowCannon("shooterActive",
                            							glm::vec3(0, 0, 2),
                            							DEFAULT_SQUARE_SIDE * SHOOTER_SCALE,
                            							staticScene->getPlacing(i, j)->getColor(),
                            							glm::vec3(1.0f, 1.0f, 1.0f),
                            							true));
					shooter->setColor(staticScene->getPlacing(i, j)->getColor());
					shooter->setShooterPower(colorUtils->SelectShootingPowerByColor(staticScene->getPlacing(i, j)->getColor()));
					shooter->setIsSnowCannon(true);
                }

                // Set position of the shooter
                glm::vec2 position;
                position.x = (float)(MATRIX_CORNER_X + j * MATRIX_DISPLACEMENT + DEFAULT_SQUARE_SIDE / 8);
                if (isSpawner)
                {
                    position.x += DEFAULT_SQUARE_SIDE / 2.5;
                } 
                if (isCannon)
                {
					position.x += DEFAULT_SQUARE_SIDE / 2;
				}
                if (isEater)
                {
                    position.x += DEFAULT_SQUARE_SIDE / 2.5;
                }
                if (isSnowCannon)
                {
                    position.x += DEFAULT_SQUARE_SIDE / 3;
                }

                position.y = (float)(MATRIX_CORNER_Y + MATRIX_DISPLACEMENT * i + DEFAULT_SQUARE_SIDE / 2);
                shooter->setPosition(position);
                shooter->setMovingPosition(position);

                // Add the shooter in the matrix of shooters
                shootersMatrix[i][j] = shooter;

                // Set the corresponding placing as taken
                staticScene->getPlacing(i, j)->setTaken(true);

                // Set the shooter as created
                createdShooter[i][j] = true;
            }
        }
    }
}


void InitClass::RendShootingLine()
{
    for (int line = 0; line < PLACINGS_SIZE; line++)
    {
        for (int i = 0; i < lineBullets[line].size(); i++)
        {
            if (lineBullets[line][i]->getBulletWasShot())
            {
                // Increment translation of the shooting bullet
                glm::vec2 t = lineBullets[line][i]->getTranslate();
                t.x += currentTimer * 300;
                lineBullets[line][i]->setTranslate(t);

                float angularStep = lineBullets[line][i]->getAngularStep() + currentTimer * 6;
                lineBullets[line][i]->setAngularStep(angularStep);

                // Start with an identity matrix
                modelMatrix = glm::mat3(1);

                // Translate to the bullet's position
                modelMatrix *= transformUtils::Translate(lineBullets[line][i]->getPosition());

                // Translate by the increment (newXPosition)
                modelMatrix *= transformUtils::Translate(t);

                // Set moving position
                glm::vec2 position = lineBullets[line][i]->getMovingPosition();
                position.x += currentTimer * 300;
                lineBullets[line][i]->setMovingPosition(position);

                if (!lineBullets[line][i]->getIsRocket())
                {
                    //  Rotate the bullet around its center
                    modelMatrix *= transformUtils::Rotate(angularStep);
                }

                // Render the bullet with the transformations
                RenderMesh2D(lineBullets[line][i]->getMesh(), shaders["VertexColor"], modelMatrix);
            }
        }
    }
}


void InitClass::DetectHitBarCollision()
{
    for (int line = 0; line < PLACINGS_SIZE; line++)
    {
        for (int i = 0; i < lineEnemies[line].size(); i++)
        {
            if (lineEnemies[line][i]->getEnemyStarted() && !lineEnemies[line][i]->getEnemyIsDead())
            {
				// Check if the enemy is in the hit bar
                if (lineEnemies[line][i]->getMovingPosition().x >= INITIAL_X &&
                    lineEnemies[line][i]->getMovingPosition().x <= INITIAL_X + DEFAULT_ENEMY_SIZE)
                {
                    lineEnemies[line][i]->setEnemyStarted(false);
                    lineEnemies[line][i]->setEnemyIsDead(true);
                    
                    // Decrease the number of health points
                    if (!lineEnemies[line][i]->getIsHealthPoint())
                    {
                        if (nrOfHealthPoints > 0)
                        {
                            nrOfHealthPoints--;
                        }
                    }

                    // Remove the enemy from the line
                    lineEnemies[line].erase(lineEnemies[line].begin() + i);
				}
			}
		}
	}
}


void InitClass::DetectBulletEnemyCollision()
{
    float radiusSum = DEFAULT_BULLET_SIZE / 2 + DEFAULT_ENEMY_SIZE / 2;

    for (int line = 0; line < PLACINGS_SIZE; line++)
    {
        for (int i = 0; i < lineBullets[line].size(); i++)
        {
            if (lineBullets[line][i]->getBulletWasShot() && !lineBullets[line][i]->getBulletHitSomething())
            {
                for (int j = 0; j < lineEnemies[line].size(); j++)
                {
                    glm::vec3 colorBullet = lineBullets[line][i]->getColor();
                    glm::vec3 colorEnemy = lineEnemies[line][j]->getColor();

                    if (lineEnemies[line][j]->getEnemyStarted() &&
                        !lineEnemies[line][j]->getEnemyIsDead() && 
                        (colorBullet == colorEnemy || lineBullets[line][i]->getIsRocket() || lineBullets[line][i]->getIsSnowball()))
                    {
						// Check if the bullet radius + enemy radius is greater than the distance between their centers
                        float distance = glm::distance(lineBullets[line][i]->getMovingPosition(), lineEnemies[line][j]->getMovingPosition());

                        if (radiusSum > distance)
                        {
                            if (!lineBullets[line][i]->getIsSnowball())
                            { 
							    lineEnemies[line][j]->setEnemyHealth(lineEnemies[line][j]->getEnemyHealth() - lineBullets[line][i]->getShooterPower());
                            }
                            else
                            {
                                // Set enemy as frozen
                                lineEnemies[line][j]->setIsFrozen(true);
                                // Set position
                                lineEnemies[line][j]->setFrozenPosition(lineEnemies[line][j]->getMovingPosition());
                            }

							// Check if the enemy is dead
                            if (lineEnemies[line][j]->getEnemyHealth() <= 0)
                            {
								lineEnemies[line][j]->setEnemyStarted(false);
							    lineEnemies[line][j]->setEnemyIsDead(true);

								// Increase the number of health points if we hit a health point
                                if (lineEnemies[line][j]->getIsHealthPoint())
                                {
                                    if (nrOfHealthPoints < HEALTH_POINTS_COUNT)
                                    {
										nrOfHealthPoints++;
									}
								}
                                
                                // Set enemy as disapearing and add it to disappearing list
                                lineEnemies[line][j]->setDisapearing(true);
                                disapearingEnemies[line].push_back(lineEnemies[line][j]);

                                // Remove the enemy from the line
								lineEnemies[line].erase(lineEnemies[line].begin() + j);
							}
                            // Set bullet properties
                            lineBullets[line][i]->setBulletWasShot(false);

                            // Set bullet hit something
                            lineBullets[line][i]->setBulletHitSomething(true);
						}
					}
				}
			}

            // Remove the bullet from the line if it hit something
            if (lineBullets[line][i]->getBulletHitSomething())
            {
                lineBullets[line].erase(lineBullets[line].begin() + i);
            }
		}
	}
}


bool InitClass::LineContainsEnemyOfColor(int line, glm::vec3 color)
{
    // Checks if there are enemies of color given on the line
    for (int i = 0; i < lineEnemies[line].size(); i++)
    {
        if (lineEnemies[line][i]->getEnemyStarted() && !lineEnemies[line][i]->getEnemyIsDead())
        {
            if (lineEnemies[line][i]->getColor() == color)
            {
                return true;
			}
		}
	}

    return false;
}


bool InitClass::LineContainsEnemy(int line)
{
    // Checks if there is an enemy on the line
    for (int i = 0; i < lineEnemies[line].size(); i++)
    {
        if (lineEnemies[line][i]->getEnemyStarted() && !lineEnemies[line][i]->getEnemyIsDead())
        {
			return true;
		}
	}

    return false;
}


void InitClass::RendDisapearingEnemies()
{
    // Rend the enemies from the disapearing lists
    for (int line = 0; line < PLACINGS_SIZE; line++)
    {
        for (int i = 0; i < disapearingEnemies[line].size(); i++)
        {
            if (disapearingEnemies[line][i]->getDisapearing())
            {
				// Make a disapear animation for the enemy in the corresponding placing in the matrix of enemies
                if (disapearingEnemies[line][i]->getDisappearSteps() > 0)
                {
					DisapearAnimation(currentTimer, disapearingEnemies[line][i], DEFAULT_ENEMY_SIZE / 2);
					disapearingEnemies[line][i]->setDisappearSteps(disapearingEnemies[line][i]->getDisappearSteps() - 1);
				}
                else
                {
					// Remove the enemy from the disapearing list
					disapearingEnemies[line].erase(disapearingEnemies[line].begin() + i);
				}
			}
		}
	}
}


void InitClass::RendStartingCoins()
{
    // Rends 5 coins at the beginning of the game under the health points
    modelMatrix = glm::mat3(1);
    modelMatrix *= transformUtils::Translate(HEALTH_POINTS_X, HEALTH_POINTS_Y - COINS_Y_DISPLACEMENT);
    bool loweredLine = false;
    int lastRow = 0;
    for (int i = 0; i < nrOfCoins; i++)
    {
        int row = i / COINS_COUNT_PER_ROW;
        if (row != lastRow)
        {
            loweredLine = false;
			lastRow = row;
        }

        if (i)
        {
            modelMatrix *= transformUtils::Translate(DEFAULT_STAR_COST_SIZE, 0);
        }

        if (!loweredLine && row)
        {
            modelMatrix *= transformUtils::Translate(0, -DEFAULT_STAR_COST_SIZE);
            modelMatrix *= transformUtils::Translate(-DEFAULT_STAR_COST_SIZE * COINS_COUNT_PER_ROW, 0);
            loweredLine = true;
		}

        RenderMesh2D(shapes::CreateStar("starCost", glm::vec3(0, 0, 2), DEFAULT_STAR_COST_SIZE, glm::vec3(1.0f, 0.84f, 0.0f), true),
                     shaders["VertexColor"],
                     modelMatrix);
    }
}


void InitClass::RendActiveShooters()
{
    // Rend the active shooters
    for (int i = 0; i < PLACINGS_SIZE; i++)
    {
        for (int j = 0; j < PLACINGS_SIZE; j++)
        {
            if (staticScene->getPlacing(i, j)->getTaken() && staticScene->getPlacing(i, j)->getVisibility() && createdShooter[i][j] && shootersMatrix[i][j] != nullptr)
            {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transformUtils::Translate(shootersMatrix[i][j]->getPosition());
                RenderMesh2D(shootersMatrix[i][j]->getMesh(), shaders["VertexColor"], modelMatrix);

                // Increase timer of shooters[i][j]
                shootersMatrix[i][j]->setTimeAccumulator(shootersMatrix[i][j]->getTimeAccumulator() + currentTimer);

                // Dont rend spawners that surpased time limit of 6 seconds
                if (shootersMatrix[i][j]->getIsSpawner() && shootersMatrix[i][j]->getTimeAccumulator() > SPAWNER_LIFE_TIME)
                {
					staticScene->getPlacing(i, j)->setTaken(false);
					createdShooter[i][j] = false;
					shootersMatrix[i][j] = nullptr;

                    continue;
				}

                // Decrease coins by cost of shooter
                if (!shootersMatrix[i][j]->getCostWasPaid())
                {
                    if (nrOfCoins >= colorUtils->GetShooterCostByColor(staticScene->getPlacing(i, j)->getColor()))
                    {
                        nrOfCoins -= colorUtils->GetShooterCostByColor(staticScene->getPlacing(i, j)->getColor());
                        shootersMatrix[i][j]->setCostWasPaid(true);
                    }
                    else
                    {
                        // If we don't have enough coins, remove the shooter from the matrix of shooters
                        staticScene->getPlacing(i, j)->setTaken(false);
                        createdShooter[i][j] = false;
                        shootersMatrix[i][j] = nullptr;
                    }
                }
            }
        }
    }
}


void InitClass::GenerateRandomCoins()
{
    int screenWidth = window->GetResolution().x;
    int screenHeight = window->GetResolution().y;

    // Generates stars at random positions on the screen that can be collected with click
    if (coinSpawnTimer > COIN_SPAWN_RATE)
    {
        int randomX = rand() % screenWidth;
        int randomY = rand() % screenHeight;

        if (randomX > MATRIX_DISPLACEMENT * 4 || randomY > MATRIX_DISPLACEMENT * 4)
        {
            glm::vec2 position;
            position.x = (float)(randomX);
            position.y = (float)(randomY);

            MeshWrapperCoin* star = new MeshWrapperCoin(shapes::CreateStar("star", glm::vec3(0, 0, 2), DEFAULT_BULLET_SIZE, glm::vec3(1.0f, 0.98f, 0.97f), true));
            star->setPosition(position);
            star->setMovingPosition(position);
            star->setCoinWasCollected(false);
            randomCoins.push_back(star);

            coinSpawnTimer = 0.0f;
        }
    }

    // Generate a big coin at random position on the screen that can be collected with click
    if (bigCoinTimer > BIG_COIN_SPAWN_RATE)
    {
		int randomX = rand() % screenWidth;
		int randomY = rand() % screenHeight;

        if (randomX > MATRIX_DISPLACEMENT * 4 || randomY > MATRIX_DISPLACEMENT * 4)
        {
            glm::vec2 position;
            position.x = (float)(randomX);
            position.y = (float)(randomY);

            MeshWrapperCoin* star = new MeshWrapperCoin(shapes::CreateStar("star", glm::vec3(0, 0, 2), (double)(DEFAULT_BULLET_SIZE * 1.5), glm::vec3(1.0f, 0.87f, 0.0f), true));
            star->setPosition(position);
            star->setMovingPosition(position);
            star->setCoinWasCollected(false);
            star->setIsBigCoin(true);
            randomCoins.push_back(star);

            bigCoinTimer = 0.0f;
        }
	}
}


void InitClass::RendRandomCoins()
{
    // Rend all coins from list
    for (int i = 0; i < randomCoins.size(); i++)
    {
        if (!randomCoins[i]->getCoinWasCollected())
        {
            glm::mat3 modelMatrix = glm::mat3(1);
            if (randomCoins[i]->getIsBigCoin())
            {
                // Make a pulsing animation for big coins
                randomCoins[i]->setTimeAccumulator(randomCoins[i]->getTimeAccumulator() + currentTimer);
				PulsingAnimation(currentTimer, randomCoins[i], (double)(DEFAULT_BULLET_SIZE * 1.5), 1.0f, 0.5f);
			}
            else
            {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transformUtils::Translate(randomCoins[i]->getPosition());
                RenderMesh2D(randomCoins[i]->getMesh(), shaders["VertexColor"], modelMatrix);
            }
		}
	}
}


void InitClass::DetectShooterEnemyCollision()
{
    // Detects if enemy colided with shooter and then makes a disappearing animation for the shooter
    for (int line = 0; line < PLACINGS_SIZE; line++)
    {
        for (int i = 0; i < lineEnemies[line].size(); i++)
        {
            if (lineEnemies[line][i]->getEnemyStarted() && !lineEnemies[line][i]->getEnemyIsDead() && !lineEnemies[line][i]->getIsHealthPoint())
            {
                for (int j = 0; j < PLACINGS_SIZE; j++)
                {
                    if (staticScene->getPlacing(line, j)->getTaken() && staticScene->getPlacing(line, j)->getVisibility() && shootersMatrix[line][j] != nullptr && createdShooter[line][j])
                    {
						float distance = glm::distance(lineEnemies[line][i]->getMovingPosition(), shootersMatrix[line][j]->getMovingPosition());
                        glm::vec3 colorEnemy = lineEnemies[line][i]->getColor();
                        glm::vec3 colorShooter = shootersMatrix[line][j]->getColor();

                        if (distance < DEFAULT_ENEMY_SIZE / 2 + DEFAULT_SQUARE_SIDE * SHOOTER_SCALE / 2)
                        {
                            if (!shootersMatrix[line][j]->getIsEater() &&
                                (colorEnemy == colorShooter || shootersMatrix[line][j]->getIsCannon() || shootersMatrix[line][j]->getIsSnowCannon() || shootersMatrix[line][j]->getIsSpawner()))
                            {
                                // Remove the shooter from the matrix of shooters
                                staticScene->getPlacing(line, j)->setDisapearing(true);
                                staticScene->getPlacing(line, j)->setTaken(false);
                                createdShooter[i][j] = false;
                            }
                            else if (shootersMatrix[line][j]->getIsEater())
                            {
                                // Let eater eat 2 enemies and make a pulsation animation when eating them
                                if (shootersMatrix[line][j]->getEatenCount() < 2)
                                {
                                    // Make a pulsation animation for the shooter
                                    shootersMatrix[line][j]->setTimeAccumulator(shootersMatrix[line][j]->getTimeAccumulator() + currentTimer);
                                    EatingAnimation(currentTimer, shootersMatrix[line][j], DEFAULT_SQUARE_SIDE * SPAWNER_SCALE / 10);

									shootersMatrix[line][j]->setEatenCount(shootersMatrix[line][j]->getEatenCount() + 1);
									lineEnemies[line][i]->setEnemyStarted(false);
									lineEnemies[line][i]->setEnemyIsDead(true);
									lineEnemies[line][i]->setDisapearing(true);
									disapearingEnemies[line].push_back(lineEnemies[line][i]);
									lineEnemies[line].erase(lineEnemies[line].begin() + i);

								}
                                else
                                {
									shootersMatrix[line][j]->setEatenCount(0);
                                    staticScene->getPlacing(line, j)->setDisapearing(true);
                                    staticScene->getPlacing(line, j)->setTaken(false);
                                    createdShooter[i][j] = false;
								}
                            }
						}
					}
				}
			}
		}
	}
}


bool InitClass::SpawnerIsOnTheTable()
{
    // Checks if there is a spawner on the table shootersMatrix
    for (int i = 0; i < PLACINGS_SIZE; i++)
    {
        for (int j = 0; j < PLACINGS_SIZE; j++)
        {
            if (staticScene->getPlacing(i, j)->getTaken() && staticScene->getPlacing(i, j)->getVisibility() && shootersMatrix[i][j]->getIsSpawner())
            {
				return true;
            }
        }
    }

    return false;
}


void InitClass::MakeShootersDisappear()
{
    // Make shooters dissapear from the table
    // After 10 bullets if normal shooter, after 5 if cannon
    for (int i = 0; i < PLACINGS_SIZE; i++)
    {
        for (int j = 0; j < PLACINGS_SIZE; j++)
        {
            if (staticScene->getPlacing(i, j)->getTaken() && staticScene->getPlacing(i, j)->getVisibility() && shootersMatrix[i][j] != nullptr && createdShooter[i][j])
            {
                if (shootersMatrix[i][j]->getBulletCount() > 10 && !shootersMatrix[i][j]->getIsCannon())
                {
					staticScene->getPlacing(i, j)->setDisapearing(true);
					staticScene->getPlacing(i, j)->setTaken(false);
					createdShooter[i][j] = false;
				}
                else if (shootersMatrix[i][j]->getBulletCount() > 5 && shootersMatrix[i][j]->getIsCannon())
                {
					staticScene->getPlacing(i, j)->setDisapearing(true);
					staticScene->getPlacing(i, j)->setTaken(false);
					createdShooter[i][j] = false;
				}
                else if (shootersMatrix[i][j]->getBulletCount() > 7 && shootersMatrix[i][j]->getIsSnowCannon())
                {
                    staticScene->getPlacing(i, j)->setDisapearing(true);
                    staticScene->getPlacing(i, j)->setTaken(false);
                    createdShooter[i][j] = false;
                }
			}
		}
	}
}

void InitClass::ClearRandomCoins()
{
    // Clear the random coins list
    for (int i = 0; i < randomCoins.size(); i++)
    {
        if (randomCoins[i]->getCoinWasCollected())
        {
			randomCoins.erase(randomCoins.begin() + i);
		}
	}
}

void InitClass::EatingAnimation(float deltaTimeSeconds, MeshWrapper* mesh, float radius)
{
    // Make a eating like animation using a sinusoidal function
    float angularStep = mesh->getAngularStep() + deltaTimeSeconds;
    mesh->setAngularStep(angularStep);

    glm::vec2 scale = mesh->getScale();
    scale.x = radius * (1 + sin(angularStep)) / 2;
    scale.y = radius * (1 + sin(angularStep)) / 2;
    mesh->setScale(scale);

    glm::vec3 color = mesh->getColor();
    color.r = (1 + sin(angularStep)) / 2;
    color.g = (1 + sin(angularStep)) / 2;
    color.b = (1 + sin(angularStep)) / 2;
    mesh->setColor(color);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformUtils::Translate(mesh->getPosition());
    modelMatrix *= transformUtils::Rotate(angularStep);
    modelMatrix *= transformUtils::Scale(scale);
    RenderMesh2D(mesh->getMesh(), shaders["VertexColor"], modelMatrix);
}

void InitClass::UpdateEnemiesTimers(float deltaTimeSeconds)
{
    // Increases all active enemies timers
    for (int line = 0; line < PLACINGS_SIZE; line++)
    {
        for (int i = 0; i < lineEnemies[line].size(); i++)
        {
            if (lineEnemies[line][i]->getEnemyStarted() && !lineEnemies[line][i]->getEnemyIsDead())
            {
                lineEnemies[line][i]->setTimeAccumulator(lineEnemies[line][i]->getTimeAccumulator() + deltaTimeSeconds);
            }
        }
    }
}

void InitClass::UnfreezeEnemies()
{
    // Unfreeze enemies after 5 seconds usign their internal timers
    for (int line = 0; line < PLACINGS_SIZE; line++)
    {
        for (int i = 0; i < lineEnemies[line].size(); i++)
        {
            if (lineEnemies[line][i]->getEnemyStarted() &&
                !lineEnemies[line][i]->getEnemyIsDead() && 
                lineEnemies[line][i]->getIsFrozen())
            {
                if (lineEnemies[line][i]->getTimeAccumulator() > 10.0f)
                {
					lineEnemies[line][i]->setIsFrozen(false);
					lineEnemies[line][i]->setTimeAccumulator(0.0f);

                    // Set position and moving position to frozen position
                    lineEnemies[line][i]->setPosition(lineEnemies[line][i]->getFrozenPosition());
                    lineEnemies[line][i]->setMovingPosition(lineEnemies[line][i]->getFrozenPosition());
				}
			}
		}
	}
}

void InitClass::IncreaseDifficulty()
{
    // Every 10 seconds make enemies come in bigger numbers, faster and increase their health by a point
    if (difficultyTimer > 10.0f)
    {
		colorUtils->IncreaseDifficulty();
		difficultyTimer = 0.0f;
	}
}

void InitClass::CheckGameOver()
{
    // Rend a game over message with survived time if we lost all health points
    if (nrOfHealthPoints <= 0)
    {
        gameOver = true;
	}
}

void InitClass::MakeGameOver()
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transformUtils::Translate(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    RenderMesh2D(shapes::CreateGameOverSymbol("gameOver", glm::vec3(0, 0, 2), 200, glm::vec3(1.0f, 0.0f, 0.0f), true), shaders["VertexColor"], modelMatrix);
}


void InitClass::RendDisapearingShooters()
{
    // Rend the disapearing shooters
    for (int i = 0; i < PLACINGS_SIZE; i++)
    {
        for (int j = 0; j < PLACINGS_SIZE; j++)
        {
            if (staticScene->getPlacing(i, j)->getDisapearing() && staticScene->getPlacing(i, j)->getVisibility())
            {
                // Make a disapear animation for the shooter in the corresponding placing in the matrix of shooters
                if (shootersMatrix[i][j]->getDisappearSteps() > 0)
                {
                    if (shootersMatrix[i][j]->getIsCannon() ||
                        shootersMatrix[i][j]->getIsSnowCannon() ||
                        shootersMatrix[i][j]->getIsSpawner())
                    {
                        DisapearAnimation(currentTimer, shootersMatrix[i][j], DEFAULT_SQUARE_SIDE / 8);
                    } 
                    else if (shootersMatrix[i][j]->getIsEater())
                    {
						DisapearAnimation(currentTimer, shootersMatrix[i][j], DEFAULT_SQUARE_SIDE / 16);
					}
                    else 
                    {
                        DisapearAnimation(currentTimer, shootersMatrix[i][j], DEFAULT_SQUARE_SIDE / 2);
                    }

                    shootersMatrix[i][j]->setDisappearSteps(shootersMatrix[i][j]->getDisappearSteps() - 1);
                }
                else
                {
                    staticScene->getPlacing(i, j)->setDisapearing(false);
                    createdShooter[i][j] = false;
                    shootersMatrix[i][j] = nullptr;
                }
            }
        }
    }

}


void InitClass::GenerateEnemies()
{
    if (slowDownTimer < 3.0f)
    {
		return;
	}

    int i = colorUtils->SelectRandomLine();
    glm::vec3 color = colorUtils->getRandomColor();
    glm::vec3 insideColor = colorUtils->getRandomColor();

    // Create bullets with a timer
    if (lineEnemyTimer[i][colorUtils->GetTypeByColor(color)] > colorUtils->GetSpawnIntervalByColor(color) + colorUtils->getRandomFloat(5.0f, 15.0f))
    {
        MeshWrapperEnemy* hex = new MeshWrapperEnemy(shapes::CreateHexagon("enemy", glm::vec3(0, 0, 2), DEFAULT_BULLET_SIZE, color, insideColor, true));
        if (healthPointSpawnRate < 25.0f)
        {
            hex = new MeshWrapperEnemy(shapes::CreateHexagon("enemy", glm::vec3(0, 0, 2), DEFAULT_BULLET_SIZE, color, insideColor, true));
        }
        else
        {
			hex = new MeshWrapperEnemy(shapes::CreateHeart("healthPoint", glm::vec3(0, 0, 2), DEFAULT_BULLET_SIZE, color, true));
            hex->setIsHealthPoint(true);
            healthPointSpawnRate = 0.0f;
		}

        hex->setPosition((float)(SCREEN_WIDTH), (float)(MATRIX_CORNER_Y + MATRIX_DISPLACEMENT * i + DEFAULT_SQUARE_SIDE / 2));
        hex->setMovingPosition((float)(SCREEN_WIDTH), (float)(MATRIX_CORNER_Y + MATRIX_DISPLACEMENT * i + DEFAULT_SQUARE_SIDE / 2));
        hex->setEnemyStarted(true);
        hex->setColor(color);
        hex->setEnemyHealth(colorUtils->SelectHealthByColor(color));
        hex->setEnemySpeed(colorUtils->SelectSpeedByColor(color));

        lineEnemies[i].push_back(hex);

        lineEnemyTimer[i][colorUtils->GetTypeByColor(color)] = 0;
    }

    slowDownTimer = 0.0f;
}


void InitClass::RendEnemies()
{
    for (int line = 0; line < PLACINGS_SIZE; line++)
    {
        for (int i = 0; i < lineEnemies[line].size(); i++)
        {
            if (lineEnemies[line][i]->getEnemyStarted() &&
                !lineEnemies[line][i]->getEnemyIsDead() &&
                !lineEnemies[line][i]->getDisapearing())
            {
				// Increment translation of the moving enemy
				glm::vec2 t = lineEnemies[line][i]->getTranslate();
				t.x -= currentTimer * 100 * lineEnemies[line][i]->getEnemySpeed();
				lineEnemies[line][i]->setTranslate(t);
				modelMatrix = glm::mat3(1);
    
                if (!lineEnemies[line][i]->getIsFrozen())
                {
				    modelMatrix *= transformUtils::Translate(lineEnemies[line][i]->getPosition());
				    modelMatrix *= transformUtils::Translate(t);
				    // Set moving position
				    glm::vec2 position = lineEnemies[line][i]->getMovingPosition();
				    position.x -= currentTimer * 100 * lineEnemies[line][i]->getEnemySpeed();
				    lineEnemies[line][i]->setMovingPosition(position);
                }
                else
                {
					modelMatrix *= transformUtils::Translate(lineEnemies[line][i]->getFrozenPosition());
				}

				// Render the bullet with the transformations
				RenderMesh2D(lineEnemies[line][i]->getMesh(), shaders["VertexColor"], modelMatrix);
			}
		}
	}
}


void InitClass::RendShootersCosts()
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transformUtils::Translate(PLACEHOLDERS_X, PLACEHOLDERS_Y);
    int lastRow = 0;
    bool loweredLine = false;

    for (int i = 0; i < PLACEHOLDERS_COUNT_TOTAL; i++)
    {
        int row = i / PLACEHOLDERS_COUNT;
        if (row != lastRow)
        {
            loweredLine = false;
            lastRow = row;
        }

        if (i)
        {
            modelMatrix *= transformUtils::Translate(SHOOTER_DISPLACEMENT, 0);
        }

        if (!loweredLine && row)
        {
            modelMatrix *= transformUtils::Translate(0, -MATRIX_DISPLACEMENT);
            modelMatrix *= transformUtils::Translate(-SHOOTER_DISPLACEMENT * PLACEHOLDERS_COUNT, 0);
            loweredLine = true;
        }

        if (staticScene->getPlaceHolders()[i]->getVisibility())
        {
            glm::mat3 modelMatrixCopy = modelMatrix;
            int nr = i;
            if (i == 5)
            {
                nr = 4;
            }
            else if (i == 6)
            {
                nr = 0;
            }
            else if (i == 7)
            {
                nr = 2;
            }

            for (int j = 0; j <= nr; j++)
            {
                if (j)
                {
                    modelMatrixCopy *= transformUtils::Translate(DEFAULT_STAR_COST_SIZE, 0);
                }

                RenderMesh2D(shapes::CreateStar("starCost",
                                                glm::vec3(0, 0, 2),
                                                DEFAULT_STAR_COST_SIZE,
                                                glm::vec3(1.0f, 0.84f, 0.0f), 
                                                true),
                             shaders["VertexColor"],
                             modelMatrixCopy);
            }
        }
    }
}


void InitClass::Update(float deltaTimeSeconds)
{
    if (!gameOver)
    {
        currentTimer = deltaTimeSeconds;
        for (int i = 0; i < PLACINGS_SIZE; i++)
        {
            for (int j = 0; j < PLACINGS_SIZE; j++)
            {
                timedShooting[i][j] += deltaTimeSeconds;
            }
        }

        for (int i = 0; i < PLACINGS_SIZE; i++)
        {
            for (int j = 0; j < TYPES_OF_SHOOTERS; j++)
            {
                lineEnemyTimer[i][j] += deltaTimeSeconds;
            }
        }
        slowDownTimer += deltaTimeSeconds;
        healthPointSpawnRate += deltaTimeSeconds;
        coinSpawnTimer += deltaTimeSeconds;
        bigCoinTimer += deltaTimeSeconds;
        difficultyTimer += deltaTimeSeconds;

        RendPlacings();
        RendHitBar();
        RendShooters();
        RendHealthPoints();
        RendPlaceHolders();
        RendMovingShooter();
        CreateActiveShooters();
        RendActiveShooters();
        Shoot();
        RendShootingLine();
        GenerateEnemies();
        RendEnemies();
        RendShootersCosts();
        DetectHitBarCollision();
        DetectBulletEnemyCollision();
        RendDisapearingEnemies();
        RendStartingCoins();

        UpdateEnemiesTimers(deltaTimeSeconds);

        if (SpawnerIsOnTheTable() || nrOfCoins <= 3)
        {
            GenerateRandomCoins();
            RendRandomCoins();
        }
        else
        {
            ClearRandomCoins();
        }

        DetectShooterEnemyCollision();
        RendDisapearingShooters();
        MakeShootersDisappear();
        //UnfreezeEnemies();
        IncreaseDifficulty();

        CheckGameOver();
    }
    else
    {
        MakeGameOver();
    }
}


void InitClass::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Set mouse coordinates to world coordinates
    mouseY = window->GetResolution().y - mouseY;

    for (int i = 0; i < PLACEHOLDERS_COUNT; i++)
    {
        double shooterBeginX = PLACEHOLDERS_X + DEFAULT_SQUARE_SIDE / 8 + SHOOTER_DISPLACEMENT * i;
        double shooterEndX = shooterBeginX + DEFAULT_SQUARE_SIDE * SHOOTER_SCALE;

        double shooterBeginY = PLACEHOLDERS_Y + DEFAULT_SQUARE_SIDE / 4;
        double shooterEndY = PLACEHOLDERS_Y + (double)3 / 4 * DEFAULT_SQUARE_SIDE;

        if (mouseX >= shooterBeginX && mouseX <= shooterEndX &&
            mouseY >= shooterBeginY && mouseY <= shooterEndY)
        {
            holdingShooterColor = colorUtils->SelectColor(i);
            pressedCorrectly = true;
            isSimpleShooter = true;
            isSpawner = false;
            isCannon = false;
            isEater = false;
            isSnowCannon = false;
        }
    }

    for (int i = 0; i < PLACEHOLDERS_COUNT_TOTAL - PLACEHOLDERS_COUNT; i++)
    {
		double shooterBeginX = PLACEHOLDERS_X + DEFAULT_SQUARE_SIDE / 8 + SHOOTER_DISPLACEMENT * i;
		double shooterEndX = shooterBeginX + DEFAULT_SQUARE_SIDE * SHOOTER_SCALE;

		double shooterBeginY = PLACEHOLDERS_Y + DEFAULT_SQUARE_SIDE / 4 - MATRIX_DISPLACEMENT;
		double shooterEndY = PLACEHOLDERS_Y + (double)3 / 4 * DEFAULT_SQUARE_SIDE - MATRIX_DISPLACEMENT;

        if (mouseX >= shooterBeginX && mouseX <= shooterEndX &&
            mouseY >= shooterBeginY && mouseY <= shooterEndY)
        {
			holdingShooterColor = colorUtils->SelectColor(i + PLACEHOLDERS_COUNT);
			pressedCorrectly = true;
            isSimpleShooter = false;

            if (i == 0)
            {
                isSpawner = true;
                isCannon = false;
                isEater = false;
                isSnowCannon = false;
            } 
            else if (i == 1)
            {
            	isCannon = true;
                isSpawner = false;
                isEater = false;
                isSnowCannon = false;
            } 
            else if (i == 2)
            {
				isEater = true;
				isSpawner = false;
				isCannon = false;
                isSnowCannon = false;
			} 
            else if (i == 3)
            {
                isSpawner = false;
                isCannon = false;
                isEater = false;
                isSnowCannon = true;
            }
		}
    }


    // If one of placings are pressed with right click, set the corresponding placing as not taken
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        for (int i = 0; i < PLACINGS_SIZE; i++)
        {
            for (int j = 0; j < PLACINGS_SIZE; j++)
            {
                double shooterBeginX = MATRIX_CORNER_X + MATRIX_DISPLACEMENT * j;
                double shooterEndX = shooterBeginX + DEFAULT_SQUARE_SIDE;

                double shooterBeginY = MATRIX_CORNER_Y + MATRIX_DISPLACEMENT * i;
                double shooterEndY = shooterBeginY + DEFAULT_SQUARE_SIDE;

                if (mouseX >= shooterBeginX && mouseX <= shooterEndX &&
                    mouseY >= shooterBeginY && mouseY <= shooterEndY)
                {
                    // Eliminate the shooter from the matrix of shooters
                    if (staticScene->getPlacing(i, j)->getTaken())
                    {
                        staticScene->getPlacing(i, j)->setDisapearing(true);
                        staticScene->getPlacing(i, j)->setTaken(false);
                        createdShooter[i][j] = false;
                    }
                }
            }
        }
    }

    // Detect if click was done inside the radius of a coin and collect it
    for (int i = 0; i < randomCoins.size(); i++)
    {
        if (!randomCoins[i]->getCoinWasCollected())
        {
			double coinCenterX = randomCoins[i]->getPosition().x;
            double coinCenterY = randomCoins[i]->getPosition().y;

            double radius = DEFAULT_BULLET_SIZE / 2;
            if (randomCoins[i]->getIsBigCoin())
            {
				radius = DEFAULT_BULLET_SIZE * 3 / 4;
			}

            if (mouseX >= coinCenterX - radius && mouseX <= coinCenterX + radius &&
                mouseY >= coinCenterY - radius && mouseY <= coinCenterY + radius)
            {
				randomCoins[i]->setCoinWasCollected(true);
				nrOfCoins++;
                if (randomCoins[i]->getIsBigCoin())
                {
                    nrOfCoins += 4;
                }
			}
		}
	}
}


void InitClass::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    pressedCorrectly = false;

    // Set mouse coordinates to world coordinates
    mouseY = window->GetResolution().y - mouseY;

    for (int i = 0; i < PLACINGS_SIZE; i++)
    {
        for (int j = 0; j < PLACINGS_SIZE; j++)
        {
            double shooterBeginX = MATRIX_CORNER_X + MATRIX_DISPLACEMENT * j;
            double shooterEndX = shooterBeginX + DEFAULT_SQUARE_SIDE;

            double shooterBeginY = MATRIX_CORNER_Y + MATRIX_DISPLACEMENT * i;
            double shooterEndY = shooterBeginY + DEFAULT_SQUARE_SIDE;
            
            if (holdingShooter)
            {
                if (mouseX >= shooterBeginX && mouseX <= shooterEndX &&
                    mouseY >= shooterBeginY && mouseY <= shooterEndY)
                {
                    releasedCorrectly = true;
                    releaseRow = i;
                    releaseCol = j;
                    releasedShooterColor = holdingShooterColor;
                }
            }
        }
    }
}
