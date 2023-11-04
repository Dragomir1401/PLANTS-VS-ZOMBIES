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
    glm::vec3 c1 = center;
    c1.z = 3;
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



