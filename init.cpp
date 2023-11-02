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

    staticScene = new StaticScene();
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
                staticScene->getPlacing(i, j)->setPositionX((float)(MATRIX_CORNER_X + j * MATRIX_DISPLACEMENT));
                staticScene->getPlacing(i, j)->setPositionY((float)(MATRIX_CORNER_Y + i * MATRIX_DISPLACEMENT));
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
        staticScene->getHitBar()->setPositionX(INITIAL_X);
        staticScene->getHitBar()->setPositionY(INITIAL_Y);
    }
}

void InitClass::RendShooters()
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transformUtils::Translate(PLACEHOLDERS_X + DEFAULT_SQUARE_SIDE / 8, PLACEHOLDERS_Y + DEFAULT_SQUARE_SIDE / 2);
    for (int i = 0; i < PLACEHOLDERS_COUNT; i++)
    {
        if (i)
        {
            modelMatrix *= transformUtils::Translate(SHOOTER_DISPLACEMENT, 0);
        }
        if (staticScene->getShooters()[i]->getVisibility())
        {
            RenderMesh2D(staticScene->getShooters()[i]->getMesh(), shaders["VertexColor"], modelMatrix);

            // Set position of the shooter
            staticScene->getShooters()[i]->setPositionX((float)(PLACEHOLDERS_X + DEFAULT_SQUARE_SIDE / 8 + SHOOTER_DISPLACEMENT * i));
            staticScene->getShooters()[i]->setPositionY((float)(PLACEHOLDERS_Y + DEFAULT_SQUARE_SIDE / 2));
        }
    }
}

void InitClass::RendHealthPoints()
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transformUtils::Translate(HEALTH_POINTS_X, HEALTH_POINTS_Y);
    for (int i = 0; i < HEALTH_POINTS_COUNT; i++)
    {
        if (i)
        {
            modelMatrix *= transformUtils::Translate(MATRIX_DISPLACEMENT, 0);
        }

        if (staticScene->getHealthPoints()[i]->getVisibility())
        {
			RenderMesh2D(staticScene->getHealthPoints()[i]->getMesh(), shaders["VertexColor"], modelMatrix);

            // Set position of the health point
            staticScene->getHealthPoints()[i]->setPositionX((float)(HEALTH_POINTS_X + i * MATRIX_DISPLACEMENT));
            staticScene->getHealthPoints()[i]->setPositionY((float)(HEALTH_POINTS_Y));
		}
    }
}

void InitClass::RendPlaceHolders()
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transformUtils::Translate(PLACEHOLDERS_X, PLACEHOLDERS_Y);
    for (int i = 0; i < PLACEHOLDERS_COUNT; i++)
    {
        if (i)
        {
            modelMatrix *= transformUtils::Translate(SHOOTER_DISPLACEMENT, 0);
        }
        if (staticScene->getPlaceHolders()[i]->getVisibility())
        {
            RenderMesh2D(staticScene->getPlaceHolders()[i]->getMesh(), shaders["VertexColor"], modelMatrix);

            // Set position of the place holder
            staticScene->getPlaceHolders()[i]->setPositionX((float)(PLACEHOLDERS_X + i * SHOOTER_DISPLACEMENT));
            staticScene->getPlaceHolders()[i]->setPositionY((float)(PLACEHOLDERS_Y));
        }
    }
}

void InitClass::Shoot()
{
    for (int i = 0; i < PLACINGS_SIZE; i++)
    {
		for (int j = 0; j < PLACINGS_SIZE; j++)
		{
			if (staticScene->getPlacing(i, j)->getTaken() && staticScene->getPlacing(i, j)->getVisibility())
			{   
                glm::vec3 color = shootersMatrix[i][j]->getColor();

                // Create bullets with a timer of 2 seconds
                if (timedShooting[i][j] > GetBulletIntervalByColor(color))
                {
                    MeshWrapper* star = new MeshWrapper(shapes::CreateStar("starShooting", glm::vec3(0, 0, 2), DEFAULT_BULLET_SIZE, color, true));
                    star->setPositionX(shootersMatrix[i][j]->getPositionX() + DEFAULT_BULLET_SIZE);
                    star->setPositionY(shootersMatrix[i][j]->getPositionY() + DEFAULT_SQUARE_SIDE / 8);
                    star->setColor(shootersMatrix[i][j]->getColor());
                    star->setBulletWasShot(true);
                    star->setShooterPower(shootersMatrix[i][j]->getShooterPower());
                    line1Bullets.push_back(star);

                    timedShooting[i][j] = 0;
                }
            }
		}
    }
}

void InitClass::DisapearAnimation(float deltaTimeSeconds, MeshWrapper* mesh, int displacementScale)
{
    // Make a disapear animation for the shooter in the corresponding placing in the matrix of shooters
    mesh->setScaleX(mesh->getScaleX() - 0.7f * deltaTimeSeconds);
    mesh->setScaleY(mesh->getScaleY() - 0.7f * deltaTimeSeconds);

    if (mesh != nullptr)
    {
		// Rend the shooter at the position of the corresponding placing in matrix
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformUtils::Translate(mesh->getPositionX(), mesh->getPositionY());
        modelMatrix *= transformUtils::Translate(DEFAULT_SQUARE_SIDE / 2, 0);
        modelMatrix *= transformUtils::Scale(mesh->getScaleX(), mesh->getScaleY());
        modelMatrix *= transformUtils::Translate(-DEFAULT_SQUARE_SIDE / 2, 0);
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

        for (int i = 0; i < PLACEHOLDERS_COUNT; i++)
        {
            if (pressedCorrectly && !releasedCorrectly)
            {
                // Rend the shooter at the mouse coordinates
                Mesh* shooter = shapes::CreateShooter("shooterMouse", glm::vec3(0, 0, 2), DEFAULT_SQUARE_SIDE * SHOOTER_SCALE, holdingShooterColor, true);
                modelMatrix = glm::mat3(1);
                modelMatrix *= transformUtils::Translate((float)mouseX, (float)mouseY);
                RenderMesh2D(shooter, shaders["VertexColor"], modelMatrix);
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

void InitClass::RendActiveShooters()
{
    // Rend the active shooters
    for (int i = 0; i < PLACINGS_SIZE; i++)
    {
        for (int j = 0; j < PLACINGS_SIZE; j++)
        {
            if (staticScene->getPlacing(i, j)->getTaken() && staticScene->getPlacing(i, j)->getVisibility())
            {
                MeshWrapper* shooter = new MeshWrapper(
                    shapes::CreateShooter("shooterActive",
                    glm::vec3(0, 0, 2),
                    DEFAULT_SQUARE_SIDE * SHOOTER_SCALE, 
                    staticScene->getPlacing(i, j)->getColor(),
                    true));
                shooter->setColor(staticScene->getPlacing(i, j)->getColor());
                shooter->setShooterPower(SelectShootingPowerByColor(staticScene->getPlacing(i, j)->getColor()));

                modelMatrix = glm::mat3(1);
                modelMatrix *= transformUtils::Translate(
                    (float)(MATRIX_CORNER_X + j * MATRIX_DISPLACEMENT + DEFAULT_SQUARE_SIDE / 8),
                    (float)(MATRIX_CORNER_Y + MATRIX_DISPLACEMENT * i + DEFAULT_SQUARE_SIDE / 2));
                RenderMesh2D(shooter->getMesh(), shaders["VertexColor"], modelMatrix);

                // Set position of the shooter
                shooter->setPositionX((float)(MATRIX_CORNER_X + j * MATRIX_DISPLACEMENT + DEFAULT_SQUARE_SIDE / 8));
                shooter->setPositionY((float)(MATRIX_CORNER_Y + MATRIX_DISPLACEMENT * i + DEFAULT_SQUARE_SIDE / 2));

                // Add the shooter in the matrix of shooters
                shootersMatrix[i][j] = shooter;
            }
        }
    }
}

int InitClass::SelectShootingPowerByColor(glm::vec3 color)
{
    if (color == glm::vec3(1.0f, 0.5f, 0.0f))
	{
		return 1;
	}
	else if (color == glm::vec3(0.0f, 0.0f, 1.0f))
	{
		return 2;
	}
	else if (color == glm::vec3(1.0f, 1.0f, 0.0f))
	{
		return 3;
	}
	else if (color == glm::vec3(0.6f, 0.0f, 1.0f))
	{
		return 4;
	}
	else
	{
		return 0;
	}
 
}

void InitClass::RendShootingLine()
{
    for (int i = 0; i < line1Bullets.size(); i++)
    {
        if (line1Bullets[i]->getBulletWasShot())
        {
            // Increment translation of the shooting bullet
            float newXPosition = line1Bullets[i]->getTranslateX() + currentTimer * 100;
            line1Bullets[i]->setTranslateX(newXPosition);

            float angularStep = line1Bullets[i]->getAngularStep() + currentTimer * 6;
            line1Bullets[i]->setAngularStep(angularStep);

            // Start with an identity matrix
            modelMatrix = glm::mat3(1);

            // Translate to the bullet's position
            modelMatrix *= transformUtils::Translate(line1Bullets[i]->getPositionX(), line1Bullets[i]->getPositionY());

            // Translate by the increment (newXPosition)
            modelMatrix *= transformUtils::Translate(newXPosition, 0);

            // Translate to the center of the bullet (assuming width and height can be accessed)
            modelMatrix *= transformUtils::Translate(DEFAULT_BULLET_SIZE / 2, -DEFAULT_BULLET_SIZE / 8);

            //  Rotate the bullet around its center
            modelMatrix *= transformUtils::Rotate(angularStep);

            // Translate back from the center
            modelMatrix *= transformUtils::Translate(-DEFAULT_BULLET_SIZE / 2, DEFAULT_BULLET_SIZE / 8);

            // Render the bullet with the transformations
            RenderMesh2D(line1Bullets[i]->getMesh(), shaders["VertexColor"], modelMatrix);
        }
    }
}

int InitClass::GetTypeByColor(glm::vec3 color)
{
    if (color == glm::vec3(1.0f, 0.5f, 0.0f))
    {
        return 0;
    }
    else if (color == glm::vec3(0.0f, 0.0f, 1.0f))
    {
        return 1;
    }
    else if (color == glm::vec3(1.0f, 1.0f, 0.0f))
    {
        return 2;
    }
    else if (color == glm::vec3(0.6f, 0.0f, 1.0f))
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

int InitClass::GetBulletIntervalByColor(glm::vec3 color)
{
    if (color == glm::vec3(1.0f, 0.5f, 0.0f))
    {
        return 4;
    }
    else if (color == glm::vec3(0.0f, 0.0f, 1.0f))
    {
        return 3;
    }
    else if (color == glm::vec3(1.0f, 1.0f, 0.0f))
    {
        return 3;
    }
    else if (color == glm::vec3(0.6f, 0.0f, 1.0f))
    {
        return 2;
    }
    else
    {
        return 0;
    }
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
                if (disapearSteps > 0)
                {
                    DisapearAnimation(currentTimer, shootersMatrix[i][j], 1);
                    disapearSteps--;
                }
                else
                {
                    staticScene->getPlacing(i, j)->setDisapearing(false);
                    disapearSteps = DISAPEAR_STEPS;
                    shootersMatrix[i][j] = nullptr;
                }
            }
        }
    }

}

void InitClass::Update(float deltaTimeSeconds)
{
    currentTimer = deltaTimeSeconds;
    for (int i = 0; i < PLACINGS_SIZE; i++)
	{
		for (int j = 0; j < PLACINGS_SIZE; j++)
		{
			timedShooting[i][j] += deltaTimeSeconds;
		}
	}

    RendPlacings();
	RendHitBar();
	RendShooters();
	RendHealthPoints();
	RendPlaceHolders();
    RendMovingShooter();
    RendActiveShooters();
    Shoot();
    RendDisapearingShooters();
    RendShootingLine();
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
            holdingShooterColor = SelectColor(i);
            pressedCorrectly = true;
        }
    }

    // If one of placings are pressed, set the corresponding placing as not taken
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
				}
			}
		}
	}
}

glm::vec3 InitClass::SelectColor(int index)
{
    switch (index)
    {
	case 0:
		return  glm::vec3(1.0f, 0.5f, 0.0f);
	case 1:
		return glm::vec3(0.0f, 0.0f, 1.0f);
	case 2:
		return glm::vec3(1.0f, 1.0f, 0.0f);
	case 3:
		return glm::vec3(0.6f, 0.0f, 1.0f);
	default:
		return glm::vec3(0, 0, 0);
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


