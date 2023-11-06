#include "Shapes.hpp"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* shapes::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* shapes::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    glm::vec3 color,
    bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
    {
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
    else {
		// Draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}

Mesh* shapes::CreateShooter(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;
    std::vector<VertexFormat> vertices =
    {
        // Diamond vertices
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length / 4, length / 2, 0), color),
		VertexFormat(corner + glm::vec3(length / 2, 0, 0), color),
		VertexFormat(corner + glm::vec3(length / 4, -length / 2, 0), color),

        // Rectangle vertices
        VertexFormat(corner + glm::vec3(length / 4, length / 6, 0), color),
        VertexFormat(corner + glm::vec3(length, length / 6, 0), color),
        VertexFormat(corner + glm::vec3(length / 4, -length / 6, 0), color),
        VertexFormat(corner + glm::vec3(length, -length / 6, 0), color),
	};


    Mesh* shooter = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          0, 2, 3,
                                          0, 4, 5,
                                          0, 5, 7,
                                          0, 6, 7};

    if (!fill) {
		shooter->SetDrawMode(GL_LINE_LOOP);
	}

    shooter->InitFromData(vertices, indices);
    return shooter;
}

Mesh* shapes::CreateHeart(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, -length / 4, 0), color),
        VertexFormat(corner + glm::vec3(0, 0, 0), color),
        VertexFormat(corner + glm::vec3(length / 4, length / 4, 0), color),
        VertexFormat(corner + glm::vec3(length / 2, 0, 0), color),
        VertexFormat(corner + glm::vec3(3 * length / 4, length / 4, 0), color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, -length / 4, 0), color),
        VertexFormat(corner + glm::vec3(length / 2, -3 * length / 4, 0), color),
    };


    Mesh* heart = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          0, 2, 3,
                                          0, 3, 4,
                                          0, 4, 5,
                                          0, 5, 6,
                                          0, 6, 7,  
                                          0, 2, 6        
                                        };

    if (!fill) {
        heart->SetDrawMode(GL_LINE_LOOP);
    }

    heart->InitFromData(vertices, indices);
    return heart;
}

Mesh* shapes::CreateStar(
    const std::string& name,
    glm::vec3 center,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 c = center;
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(c, color),
        VertexFormat(c + glm::vec3(-length / 2, length / 6, 0), color),
        VertexFormat(c + glm::vec3((double)-1.4 / 12 * length, length / 6, 0), color),
        VertexFormat(c + glm::vec3(0, length / 2, 0), color),
        VertexFormat(c + glm::vec3((double)1.4 / 12 * length, length / 6, 0), color),
        VertexFormat(c + glm::vec3(length / 2, length / 6, 0), color),

        VertexFormat(c + glm::vec3((double)2.35 / 12 * length, -length / 12, 0), color),
        VertexFormat(c + glm::vec3((double)4 / 12 * length, -length / 2, 0), color),
        VertexFormat(c + glm::vec3(0, -2.8 / 12 * length, 0), color),
        VertexFormat(c + glm::vec3(-(double)4 / 12 * length, -length / 2, 0), color),
        VertexFormat(c + glm::vec3(-(double)2.35 / 12 * length, -length / 12, 0), color),
    };


    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          0, 2, 3,
                                          0, 3, 4,
                                          0, 4, 5,
                                          0, 5, 6,
                                          0, 6, 7,
                                          0, 7, 8,
                                          0, 8, 9,
                                          0, 9, 10,
                                          0, 10, 1
    };

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }

    star->InitFromData(vertices, indices);
    return star;
}

Mesh* shapes::CreateHexagon(
    const std::string& name,
    glm::vec3 center,
    float length,
    glm::vec3 colorOutside,
    glm::vec3 colorInside,
    bool fill)
{
    glm::vec3 c = center;
    float r = length / 2;
    c.z = 3;
    glm::vec3 c1 = center;
    c1.z = 4;
    float scale = 1.5;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(c, colorOutside),
        VertexFormat(c + glm::vec3(-r, (double)-3 / 5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-r, (double)3 / 5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(0, r, 0), colorOutside),
        VertexFormat(c + glm::vec3(r, (double)3 / 5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(r, (double)-3 / 5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(0, -r, 0), colorOutside),

        VertexFormat(c1, colorInside),
        VertexFormat(c1 + glm::vec3(-r / 2 * scale, (double)-1 / 5 * r * scale, 0), colorInside),
        VertexFormat(c1 + glm::vec3(-r / 2 * scale, (double)1 / 5 * r * scale, 0), colorInside),
        VertexFormat(c1 + glm::vec3(0, r / 2 * scale, 0), colorInside),
        VertexFormat(c1 + glm::vec3(r / 2 * scale, (double)1 / 5 * r * scale, 0), colorInside),
        VertexFormat(c1 + glm::vec3(r / 2 * scale, (double)-1 / 5 * r * scale, 0), colorInside),
        VertexFormat(c1 + glm::vec3(0, -r / 2 * scale, 0), colorInside),

    };


    Mesh* hex = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          0, 2, 3,
                                          0, 3, 4,
                                          0, 4, 5,
                                          0, 5, 6,
                                          0, 6, 1,

                                          7, 8, 9,
                                          7, 9, 10,
                                          7, 10, 11,
                                          7, 11, 12,
                                          7, 12, 13,
                                          7, 13, 8
    };

    if (!fill) {
        hex->SetDrawMode(GL_LINE_LOOP);
    }

    hex->InitFromData(vertices, indices);
    return hex;
}


Mesh* shapes::CreateSpawner(
    const std::string& name,
    glm::vec3 center,
    float length,
    glm::vec3 colorOutside,
    glm::vec3 colorInside,
    bool fill)
{

    glm::vec3 c = center;
    float r = length / 10;
    float r1 = length / 15;
    glm::vec3 c1 = center;
    c1.z = 3;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(c, colorOutside),
        VertexFormat(c + glm::vec3(-3 * r, r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-5 * r, 3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-3 * r, 3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-2 * r, 6 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(0, 3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(2 * r, 6 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(3 * r, 3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(5 * r, 3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(3 * r, r, 0), colorOutside),

        VertexFormat(c + glm::vec3(5 * r, -r, 0), colorOutside),
        VertexFormat(c + glm::vec3(5 * r, -3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(3 * r, -5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(r, -5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(0, -3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-r, -5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-3 * r, -5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-5 * r, -3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-5 * r, -r, 0), colorOutside),


        VertexFormat(c1, colorInside),
        VertexFormat(c1 + glm::vec3(-3.5 * r1, -5 * r1, 0), colorInside),
        VertexFormat(c1 + glm::vec3(-2 * r1, -1.75 * r1, 0), colorInside),
        VertexFormat(c1 + glm::vec3(-4.5 * r1, 0.5 * r1, 0), colorInside),
        VertexFormat(c1 + glm::vec3(-1.5 * r1, 0.5 * r1, 0), colorInside),
        VertexFormat(c1 + glm::vec3(0, 3.5 * r1, 0), colorInside),
        VertexFormat(c1 + glm::vec3(1.5 * r1, 0.5 * r1, 0), colorInside),
        VertexFormat(c1 + glm::vec3(4.5 * r1, 0.5 * r1, 0), colorInside),
        VertexFormat(c1 + glm::vec3(2 * r1, -1.75 * r1, 0), colorInside),
        VertexFormat(c1 + glm::vec3(3.5 * r1, -5 * r1, 0), colorInside),
        VertexFormat(c1 + glm::vec3(0, -2.5 * r1, 0), colorInside),
    };

    Mesh* spawner = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
    								      0, 2, 3,
    								      0, 3, 4,
    								      0, 4, 5,
    								      0, 5, 6,
    								      0, 6, 7,
    								      0, 7, 8,
    								      0, 8, 9,
    								      0, 9, 10,
    								      0, 10, 11,
    								      0, 11, 12,
    								      0, 12, 13,
    								      0, 13, 14,
    								      0, 14, 15,
    								      0, 15, 16,
    								      0, 16, 17,
    								      0, 17, 18,
    								      0, 18, 1,
                                          19, 20, 21,
                                          19, 21, 22,
                                          19, 22, 23,
                                          19, 23, 24,
                                          19, 24, 25,
                                          19, 25, 26,
                                          19, 26, 27,
                                          19, 27, 28,
                                          19, 28, 29,
                                          19, 29, 20,
                                          };

    if (!fill) {
		spawner->SetDrawMode(GL_LINE_LOOP);
    }

    spawner->InitFromData(vertices, indices);
    return spawner;
}

Mesh* shapes::CreateCannon(const std::string& name, glm::vec3 center, float length, glm::vec3 colorOutside, glm::vec3 colorInside, bool fill)
{
    glm::vec3 c = center;
    float r = length / 10;
    glm::vec3 c1 = center;
    c1.z = 3;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(c, colorOutside),
        VertexFormat(c + glm::vec3(-8 * r, 5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-2 * r, 5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(1 * r, 2 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(6 * r, 5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(6 * r, -5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(1 * r, -2 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-2 * r, -5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-8 * r, -5 * r, 0), colorOutside),

        VertexFormat(c1, colorInside),
        VertexFormat(c1 + glm::vec3(-4 * r, r, 0), colorInside),
        VertexFormat(c1 + glm::vec3(3 * r, r, 0), colorInside),
        VertexFormat(c1 + glm::vec3(4 * r, 0, 0), colorInside),
        VertexFormat(c1 + glm::vec3(3 * r, -r, 0), colorInside),
        VertexFormat(c1 + glm::vec3(-4 * r, -r, 0), colorInside),

        VertexFormat(c1 + glm::vec3(-r, 2 * r, 0), colorInside),
        VertexFormat(c1 + glm::vec3(0, 2 * r, 0), colorInside),
        VertexFormat(c1 + glm::vec3(0, -2 * r, 0), colorInside),
        VertexFormat(c1 + glm::vec3(-r, -2 * r, 0), colorInside),
    };

    Mesh* spawner = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          0, 2, 3,
                                          0, 3, 4,
                                          0, 4, 5,
                                          0, 5, 6,
                                          0, 6, 7,
                                          0, 7, 8,
                                          0, 8, 1,
                                          9, 10, 11,
                                          9, 11, 12,
                                          9, 12, 13,
                                          9, 13, 14,
                                          9, 14, 10,  

                                          9, 15, 16,
                                          9, 17, 18,
                                        };

    if (!fill) {
        spawner->SetDrawMode(GL_LINE_LOOP);
    }

    spawner->InitFromData(vertices, indices);
    return spawner;
}

Mesh* shapes::CreateRocket(const std::string& name, glm::vec3 center, float length, glm::vec3 color, bool fill)
{
    glm::vec3 c = center;
    float r = length / 10;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(c, color),
        VertexFormat(c + glm::vec3(-4 * r, r, 0), color),
        VertexFormat(c + glm::vec3(3 * r, r, 0), color),
        VertexFormat(c + glm::vec3(4 * r, 0, 0), color),
        VertexFormat(c + glm::vec3(3 * r, -r, 0), color),
        VertexFormat(c + glm::vec3(-4 * r, -r, 0), color),

        VertexFormat(c + glm::vec3(-r, 2 * r, 0), color),
        VertexFormat(c + glm::vec3(0, 2 * r, 0), color),
        VertexFormat(c + glm::vec3(0, -2 * r, 0), color),
        VertexFormat(c + glm::vec3(-r, -2 * r, 0), color),
    };

    Mesh* spawner = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          0, 2, 3,
                                          0, 3, 4,
                                          0, 4, 5,
                                          0, 5, 1,
                                          0, 6, 7,
                                          0, 8, 9,
                                        };

    if (!fill) {
        spawner->SetDrawMode(GL_LINE_LOOP);
    }

    spawner->InitFromData(vertices, indices);
    return spawner;
}

Mesh* shapes::CreateEater(const std::string& name, glm::vec3 center, float length, glm::vec3 colorOutside, glm::vec3 colorInside, bool fill)
{
    glm::vec3 c = center;
    float r = length / 12;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(c, colorOutside),
        VertexFormat(c + glm::vec3(3 * r, 6.5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(1 * r, 8 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-1 * r, 7.5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-6 * r, 7 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-3 * r, 5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-8 * r, 6 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-4 * r, 5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-5 * r, 3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-6 * r, 2 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-6.5 * r, 0.5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-6 * r, -1 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-5.5 * r, -1.5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-5 * r, -4 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-4 * r, -5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-2.5 * r, -5.5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-1 * r, -6 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(1 * r, -6 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(3 * r, -5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(5 * r, -4 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(4 * r, -2 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(5 * r, -1 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(4 * r, 0 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(5 * r, 2 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(4 * r, 2.5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(5 * r, 4 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(3.5 * r, 5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(4 * r, 7 * r, 0), colorOutside),

        VertexFormat(c + glm::vec3(3 * r, 9 * r, 1), colorInside),
        VertexFormat(c + glm::vec3(5 * r, 8 * r, 1), colorInside),
        VertexFormat(c + glm::vec3(5 * r, 5 * r, 1), colorInside),
        VertexFormat(c + glm::vec3(7 * r, 3 * r, 1), colorInside),
        VertexFormat(c + glm::vec3(6 * r, 1 * r, 1), colorInside),
        VertexFormat(c + glm::vec3(7 * r, -1 * r, 1), colorInside),
        VertexFormat(c + glm::vec3(6 * r, -3 * r, 1), colorInside),
        VertexFormat(c + glm::vec3(5 * r, -7 * r, 1), colorInside),
    };

    Mesh* eater = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          0, 2, 3,
                                          0, 3, 4,
                                          0, 4, 5,
                                          0, 5, 1,
                                          0, 6, 7,
                                          0, 8, 9,
                                          0, 9, 10,
                                          0, 10, 11,
                                          0, 11, 12,
                                          0, 12, 13,
                                          0, 13, 14,
                                          0, 14, 15,
                                          0, 15, 16,
                                          0, 16, 17,
                                          0, 17, 18,
                                          0, 18, 19,
                                          0, 19, 20,
                                          0, 20, 21,
                                          0, 21, 22,
                                          0, 22, 23,
                                          0, 23, 24,
                                          0, 24, 25,
                                          0, 25, 26,
                                          0, 26, 27,
                                          0, 27, 28,
                                          0, 28, 29,
                                          0, 29, 30,
                                          0, 30, 31,
                                          0, 31, 32,
                                          0, 32, 33,
                                          0, 33, 34,
                                          0, 34, 35,
                                          0, 35, 1
                                       };

    if (!fill) {
        eater->SetDrawMode(GL_LINE_LOOP);
    }

    eater->InitFromData(vertices, indices);
    return eater;
}

Mesh* shapes::CreateSnowBullet(const std::string& name, glm::vec3 center, float length, glm::vec3 colorOutside, glm::vec3 colorInside, bool fill)
{
    glm::vec3 c = center;
    float r = length / 12;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(c, colorInside),

        VertexFormat(c + glm::vec3(-0.5 * r, -5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-2 * r, -5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-1.7 * r, -3.5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-2 * r, -3 * r, 0), colorOutside), // S

        VertexFormat(c + glm::vec3(-3 * r, -3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-4 * r, -4 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-5 * r, -3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-6 * r, -3 * r, 0), colorOutside), // A

        VertexFormat(c + glm::vec3(-5.3 * r, -2 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-6 * r, -0.5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-4.2 * r, -0.4 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-4 * r, 0 * r, 0), colorOutside), // N

        VertexFormat(c + glm::vec3(-4.4 * r, 0.6 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-6 * r, 1 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-5.4 * r, 2.1 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-6 * r, 3 * r, 0), colorOutside), // D

        VertexFormat(c + glm::vec3(-5 * r, 3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-4 * r, 4 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-3 * r, 3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-2 * r, 3 * r, 0), colorOutside), // O

        // Middle

        VertexFormat(c + glm::vec3(-1.6 * r, 3.6 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-2 * r, 5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-0.6 * r, 5.2 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(0 * r, 6 * r, 0), colorOutside), // B

        VertexFormat(c + glm::vec3(0.6 * r, 5.2 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(2 * r, 5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(1.6 * r, 3.6 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(2 * r, 3 * r, 0), colorOutside), // P

        VertexFormat(c + glm::vec3(3 * r, 3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(4 * r, 4 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(5 * r, 3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(6 * r, 3 * r, 0), colorOutside), // F

        VertexFormat(c + glm::vec3(5.4 * r, 2.1 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(6 * r, 1 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(4.4 * r, 0.6 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(4 * r, 0 * r, 0), colorOutside), // Q

        VertexFormat(c + glm::vec3(4.2 * r, -0.4 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(6 * r, -0.5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(5.3 * r, -2 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(6 * r, -3 * r, 0), colorOutside), // C

        VertexFormat(c + glm::vec3(5 * r, -3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(4 * r, -4 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(3 * r, -3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(2 * r, -3 * r, 0), colorOutside), // R

        VertexFormat(c + glm::vec3(1.7 * r, -3.5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(2 * r, -5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(0.5 * r, -5 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(0 * r, -6 * r, 0), colorOutside), // E
    };

    Mesh* snowBullet = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          0, 2, 3,
                                          0, 3, 4,
                                          0, 4, 5,
                                          0, 5, 1,
                                          0, 6, 7,
                                          0, 7, 8,
                                          0, 8, 9,
                                          0, 9, 10,
                                          0, 10, 11,
                                          0, 11, 12,
                                          0, 12, 13,
                                          0, 13, 14,
                                          0, 14, 15,
                                          0, 15, 16,
                                          0, 16, 17,
                                          0, 17, 18,
                                          0, 18, 19,
                                          0, 19, 20,
                                          0, 20, 21,
                                          0, 21, 22,
                                          0, 22, 23,
                                          0, 23, 24,
                                          0, 24, 25,
                                          0, 25, 26,
                                          0, 26, 27,
                                          0, 27, 28,
                                          0, 28, 29,
                                          0, 29, 30,
                                          0, 30, 31,
                                          0, 31, 32,
                                          0, 32, 33,
                                          0, 33, 34,
                                          0, 34, 35,
                                          0, 35, 36,
                                          0, 36, 37,
                                          0, 37, 38,
                                          0, 38, 39,
                                          0, 39, 40,
                                          0, 40, 41,
                                          0, 41, 42,
                                          0, 42, 43,
                                          0, 43, 44,
                                          0, 44, 45,
                                          0, 45, 46,
                                          0, 46, 47,
                                          0, 47, 48,
                                          0, 48, 1
                                        };

    if (!fill) {
        snowBullet->SetDrawMode(GL_LINE_LOOP);
    }

    snowBullet->InitFromData(vertices, indices);
    return snowBullet;
}

Mesh* shapes::CreateSnowCannon(const std::string& name, glm::vec3 center, float length, glm::vec3 colorOutside, glm::vec3 colorInside, bool fill)
{
    glm::vec3 c = center;
    float r = length / 8;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(c, colorOutside),
        VertexFormat(c + glm::vec3(-4 * r, 1 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-2 * r, 2 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(0 * r, 4 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(2 * r, 4 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(4 * r, 2 * r, 0), colorOutside), // C

        VertexFormat(c + glm::vec3(6 * r, 2 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(6 * r, 1 * r, 0), colorOutside),

        VertexFormat(c + glm::vec3(6 * r, 0 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(6 * r, -1 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(6 * r, -2 * r, 0), colorOutside),

        VertexFormat(c + glm::vec3(4 * r, -3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-2 * r, -3 * r, 0), colorOutside),
        VertexFormat(c + glm::vec3(-4 * r, -1 * r, 0), colorOutside),

        VertexFormat(c, colorInside)
    };

    Mesh* snowCannon = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          0, 2, 3,
                                          0, 3, 4,
                                          14, 4, 5,
                                          14, 5, 7,
                                          14, 6, 7,
                                          14, 8, 9,
                                          14, 9, 10,
                                          14, 8, 11,
                                          0, 9, 10,
                                          0, 10, 11,
                                          0, 11, 12,
                                          0, 12, 13,
                                          0, 13, 1
										};


    if (!fill) {
        snowCannon->SetDrawMode(GL_LINE_LOOP);
    }

    snowCannon->InitFromData(vertices, indices);
    return snowCannon;
}


Mesh* shapes::CreateGameOverSymbol(const std::string& name, glm::vec3 center, float size, glm::vec3 color, bool fill) 
{
    float halfSize = size / 4.0f;

    std::vector<VertexFormat> vertices = {
        VertexFormat(center, color),

        VertexFormat(center + glm::vec3(-halfSize, 0, 0), color),
        VertexFormat(center + glm::vec3(-6 * halfSize, 3 * halfSize, 0), color),
        VertexFormat(center + glm::vec3(-4 * halfSize, 5 * halfSize, 0), color),
        VertexFormat(center + glm::vec3(0 * halfSize, 1 * halfSize, 0), color),
        VertexFormat(center + glm::vec3(4 * halfSize, 5 * halfSize, 0), color),
        VertexFormat(center + glm::vec3(6 * halfSize, 3 * halfSize, 0), color),
        VertexFormat(center + glm::vec3(1 * halfSize, 0 * halfSize, 0), color),
        VertexFormat(center + glm::vec3(6 * halfSize, -3 * halfSize, 0), color),
        VertexFormat(center + glm::vec3(4 * halfSize, -5 * halfSize, 0), color),
        VertexFormat(center + glm::vec3(0 * halfSize, -1 * halfSize, 0), color),
        VertexFormat(center + glm::vec3(-4 * halfSize, -5 * halfSize, 0), color),
        VertexFormat(center + glm::vec3(-6 * halfSize, -3 * halfSize, 0), color)
    };

    std::vector<unsigned int> indices = {
                                            0, 1, 2,
                                            0, 2, 3,
                                            0, 3, 4,
                                            0, 4, 5,
                                            0, 5, 6,
                                            0, 6, 7,
                                            0, 7, 8,
                                            0, 8, 9,
                                            0, 9, 10,
                                            0, 10, 11,
                                            0, 11, 12,
                                            0, 12, 1
                                        };

    Mesh* gameOverSymbol = new Mesh(name);

    if (!fill) {
        gameOverSymbol->SetDrawMode(GL_LINES);
    }
    else {
        gameOverSymbol->SetDrawMode(GL_TRIANGLES); 
    }

    gameOverSymbol->InitFromData(vertices, indices);

    return gameOverSymbol;
}
