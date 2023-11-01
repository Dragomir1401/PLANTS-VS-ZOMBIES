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
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3((double)4.5 / 12 * length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length / 2, (double)5 / 12 * length, 0), color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3((double)10 / 12 * length, (double)-8 / 12 * length, 0), color),
        VertexFormat(corner + glm::vec3((double)2 / 12 * length, (double)-8 / 12 * length, 0), color),
    };


    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = { 1, 2, 4,
                                          1, 3, 5,
                                          1, 4, 0,
                                        };

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }

    star->InitFromData(vertices, indices);
    return star;
}

Mesh* shapes::CreateHexagon(
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
        VertexFormat(corner + glm::vec3(0, (double)length / 2, 0), color),
        VertexFormat(corner + glm::vec3((double)length / 2, (double)13 / 16 * length, 0), color),
        VertexFormat(corner + glm::vec3(length, (double)length / 2, 0), color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3((double)length / 2, -(double)5 / 16 * length, 0), color),
    };


    Mesh* hex = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          0, 2, 3,
                                          0, 3, 4,
                                          0, 4, 5,
                                        };

    if (!fill) {
        hex->SetDrawMode(GL_LINE_LOOP);
    }

    hex->InitFromData(vertices, indices);
    return hex;
}



