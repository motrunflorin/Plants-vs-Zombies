#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

#include "lab_m1/Tema1/Utility.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill,
    bool occupied)
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
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 center2,
    float length,
    glm::vec3 color)
{
    glm::vec3 center = center2;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(0, 4 * length, 6), color),  
        VertexFormat(center + glm::vec3(0.89f * length, 1.23f * length, 6), color),  
        VertexFormat(center + glm::vec3(3.8f * length,  1.23f * length, 6), color),
        VertexFormat(center + glm::vec3(1.45f * length, -0.47f * length, 6), color),
        VertexFormat(center + glm::vec3(2.35f * length, -3.23f * length, 6), color),
        
        VertexFormat(center + glm::vec3(0, -1.52f * length, 6), color),
        VertexFormat(center + glm::vec3(-2.35f * length, -3.23f * length, 6), color),
        VertexFormat(center + glm::vec3(-1.45f * length, -0.47f *length, 6), color),
        VertexFormat(center + glm::vec3(-3.8f * length, 1.23f *length, 6), color),
        VertexFormat(center + glm::vec3(-0.89f * length, 1.23f * length, 6), color)
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = {
       0,4,5,
       0,5,6,
       2,5,8
    };

    
    star->InitFromData(vertices, indices);
    return star;
}

Mesh* object2D::CreateTurret(
    const std::string& name,
    glm::vec3 center2,
    float length,
    glm::vec3 color)
{
    glm::vec3 center = center2;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(0, 4 * length, 1), color),
        VertexFormat(center + glm::vec3(2 * length, 0, 1), color),
        VertexFormat(center + glm::vec3(0,  -4 * length, 1), color),
        VertexFormat(center + glm::vec3(-2 * length, 0, 1), color),

        VertexFormat(center + glm::vec3(1.5 * length, length, 1), color),
        VertexFormat(center + glm::vec3(4 * length, length, 1), color),
        VertexFormat(center + glm::vec3(-1.5 * length, -length, 1), color),
        VertexFormat(center + glm::vec3(4 * length, -length, 1), color),
        
    };

    Mesh* turret = new Mesh(name);
    std::vector<unsigned int> indices = {
        0, 1, 3,
        3, 1, 2,
        4, 5, 7,
        4, 6, 7
    };


    turret->InitFromData(vertices, indices);
    return turret;
}

Mesh* object2D::CreateEnemy(
    const std::string& name,
    glm::vec3 center2,
    float length,
    glm::vec3 color)
{
    glm::vec3 center = center2;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(0, 4 * length, 1), color),
        VertexFormat(center + glm::vec3(3.46f * length, 2 * length, 1), color),
        VertexFormat(center + glm::vec3(3.46f * length, -2 * length, 1), color),
        VertexFormat(center + glm::vec3(0, -4 * length, 1), color),
        VertexFormat(center + glm::vec3(-3.46f * length, -2 * length, 1), color),
        VertexFormat(center + glm::vec3(-3.46f * length, 2 * length, 1), color),
        

        VertexFormat(center + glm::vec3(0, 2.98f * length, 2),  glm::vec3(0, 1, 0)),
        VertexFormat(center + glm::vec3(2.58f * length, 1.49f * length, 2),     glm::vec3(0, 1, 0)),
        VertexFormat(center + glm::vec3(2.58f * length,  -1.49f * length, 2),  glm::vec3(0, 1, 0)),
        VertexFormat(center + glm::vec3(0, -2.98f * length, 2),  glm::vec3(0, 1, 0)),
        VertexFormat(center + glm::vec3(-2.58f * length, -1.49f * length, 2),  glm::vec3(0, 1, 0)),
        VertexFormat(center + glm::vec3(-2.58f * length, 1.49f * length, 2), glm::vec3(0, 1, 0)),
    };

    Mesh* enemy = new Mesh(name);
    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3,
        3, 4, 5,
        5, 3, 0,

        6, 9, 7,
        7, 8, 9,
        9, 10, 11,
        6, 9, 11
       
    };


    enemy->InitFromData(vertices, indices);
    return enemy;
}


Mesh* object2D::CreateLife(
    const std::string& name,
    glm::vec3 center2,
    float length,
    glm::vec3 color)
{
    glm::vec3 center = center2;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(0, 3 * length, 1), color),
        VertexFormat(center + glm::vec3(2 * length, 5 * length, 1), color),
        VertexFormat(center + glm::vec3(5 * length, 3 * length, 1), color),
        VertexFormat(center + glm::vec3(0, -3 * length, 1), color),
        VertexFormat(center + glm::vec3(-5 * length, 3 * length, 1), color),
        VertexFormat(center + glm::vec3(-2 * length, 5 * length, 1), color),
    };

    Mesh* life = new Mesh(name);
    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3,
        3, 4, 0,
        5, 4, 0

   

    };


    life->InitFromData(vertices, indices);
    return life;
}

Mesh* object2D::CreateTank(
    const std::string& name,
    glm::vec3 center2,
    float length,
    glm::vec3 color)
{
    glm::vec3 center = center2;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-4 * length, -2 * length, 3), color),
        VertexFormat(center + glm::vec3(4 * length, -2 * length, 3), color),
        VertexFormat(center + glm::vec3(6 * length,  0 * length, 3), color),
        VertexFormat(center + glm::vec3(4 * length, 2 * length, 3), color),
        VertexFormat(center + glm::vec3(2 * length, 2 * length, 3), color),
        VertexFormat(center + glm::vec3(1 * length, 4 * length, 3), color),
        VertexFormat(center + glm::vec3(-1 * length, 4 * length, 3), color),
        VertexFormat(center + glm::vec3(-2 * length, 2 * length, 3), color),
        VertexFormat(center + glm::vec3(-4 * length, 2 * length, 3), color),
        VertexFormat(center + glm::vec3(-6 * length,  0, 3), color),

        VertexFormat(center + glm::vec3(1.59f * length, 2.81f * length, 3), color),
        VertexFormat(center + glm::vec3(3 * length, 2.8f * length, 3), color),
        VertexFormat(center + glm::vec3(3 * length, 3.4f * length, 3), color),
        VertexFormat(center + glm::vec3(1.29f * length,  3.4f * length , 3), color),
    };

    Mesh* tank = new Mesh(name);
    std::vector<unsigned int> indices = {
       0, 1, 3,
       0, 8 ,3,
       1, 2, 3,
       0, 8, 9,
       4, 5, 7,
       5, 6, 7,
       10, 11, 12,
       10, 12, 13

    };


    tank->InitFromData(vertices, indices);
    return tank;
}

Mesh* object2D::CreateBonus(
    const std::string& name,
    glm::vec3 center2,
    float length)
{
    glm::vec3 center = center2;

    std::vector<VertexFormat> vertices =
    {
        

         VertexFormat(center + glm::vec3(0, 24 * length, 6), glm::vec3(0.33f, 0.33f, 0.34f)),//e
         VertexFormat(center + glm::vec3(4 * length, 18 * length, 6), glm::vec3(0.33f, 0.33f, 0.34f)),//d
         VertexFormat(center + glm::vec3(4 * length, 0, 6), glm::vec3(0.33f, 0.33f, 0.34f)),//b
         VertexFormat(center + glm::vec3(-4 * length, 0, 6), glm::vec3(0.33f, 0.33f, 0.34f)),//a
         VertexFormat(center + glm::vec3(-4 * length, 18 * length, 6), glm::vec3(0.33f, 0.33f, 0.34f)),//c

         VertexFormat(center + glm::vec3(-2 * length, 0, 6), glm::vec3(0.588f, 0.294f, 0)),//5 f
         VertexFormat(center + glm::vec3(2 * length, 0, 6), glm::vec3(0.588f, 0.294f, 0)),//6 g
         VertexFormat(center + glm::vec3(2 * length, -8 * length, 6), glm::vec3(0.588f, 0.294f, 0)),//7i
         VertexFormat(center + glm::vec3(-2 * length, -8 * length, 6), glm::vec3(0.588f, 0.294f, 0)),//8h

         VertexFormat(center + glm::vec3(-8 * length, 2 * length, 7), glm::vec3(1.0f, 0.843f, 0)),//9 m
         VertexFormat(center + glm::vec3(-6 * length, 2 * length, 7), glm::vec3(1.0f, 0.843f, 0)), //10 n
         VertexFormat(center + glm::vec3(-6 * length, 0, 7), glm::vec3(1.0f, 0.843f, 0)),// 11 a1 ---
         VertexFormat(center + glm::vec3(-8 * length, 0, 7), glm::vec3(1.0f, 0.843f, 0)),//12 l

         VertexFormat(center + glm::vec3(6 * length, 2 * length, 7), glm::vec3(1.0f, 0.843f, 0)),//13r
         VertexFormat(center + glm::vec3(8 * length, 2 * length, 7), glm::vec3(1.0f, 0.843f, 0)),//14q
         VertexFormat(center + glm::vec3(8 * length, 0, 7), glm::vec3(1.0f, 0.843f, 0)),//15p
         VertexFormat(center + glm::vec3(6 * length, 0, 7), glm::vec3(1.0f, 0.843f, 0)), //16 b1

         VertexFormat(center + glm::vec3(4 * length, 0, 7), glm::vec3(1.0f, 0.843f, 0)), //17 b
         VertexFormat(center + glm::vec3(4 * length, length, 7), glm::vec3(1.0f, 0.843f, 0)), //18 v
         VertexFormat(center + glm::vec3(6 * length, length, 7), glm::vec3(1.0f, 0.843f, 0)), //19 s
         
         VertexFormat(center + glm::vec3(-6 * length, length, 7), glm::vec3(1.0f, 0.843f, 0)),//20 o
         VertexFormat(center + glm::vec3(-4 * length, length, 7), glm::vec3(1.0f, 0.843f, 0)),//21 u
         VertexFormat(center + glm::vec3(-4 * length, 0, 7), glm::vec3(1.0f, 0.843f, 0)),//22 a

         VertexFormat(center + glm::vec3(0, 2 * length, 7), glm::vec3(1.0f, 0.843f, 0)),// 23 w
         VertexFormat(center + glm::vec3(0, 0, 7), glm::vec3(1.0f, 0.843f, 0)),// 24c1

         VertexFormat(center + glm::vec3(3 * length, -10 *length, 6), glm::vec3(1.0f, 0.843f, 0)),//25z
         VertexFormat(center + glm::vec3(0, -12 * length, 6), glm::vec3(1.0f, 0.843f, 0)),//26k
         VertexFormat(center + glm::vec3(-3 * length, -10 * length, 6), glm::vec3(1.0f, 0.843f, 0)),//27j

         VertexFormat(center + glm::vec3(-1.5f * length, -8.5f * length, 7), glm::vec3(0.878f, 0.067f, 0.373f)),//28 d1
         VertexFormat(center + glm::vec3(1.5f * length, -8.5f * length, 7), glm::vec3(0.878f, 0.067f, 0.373f)),//29 g1
         VertexFormat(center + glm::vec3(2 * length, -10 * length, 7), glm::vec3(0.878f, 0.067f, 0.373f)),//30h1
         VertexFormat(center + glm::vec3(0, -11.2f * length, 7), glm::vec3(0.878f, 0.067f, 0.373f)),//31 t
         VertexFormat(center + glm::vec3(-2 * length, -10 * length, 7), glm::vec3(0.878f, 0.067f, 0.373f)),//32f1



    };

    Mesh* bonus = new Mesh(name);
    std::vector<unsigned int> indices = {
        1,3,4,
        1,2,3,
        3,4,0,
        0,1,4,

        5,6,7,
        5,7,8,

        9,10,11,
        11,12,9,

        13,14,15,
        15,16,13,

        19,16,17,
        17,18,19,

        20,21,22,
        20,11,22,

        23,21,22,
        23,18,17,
        23,22,24,
        23,17,24,

        8,7,25,
        8,25,27,
        27,25,26,

        28,29,30,
        28,30,32,
        32,31,30,
    };


    bonus->InitFromData(vertices, indices);
    return bonus;
}


std::vector<Point> createRoundHeart(float centerX, float centerY, float radius, int numPoints) {
    std::vector<Point> heartPoints;

    for (int i = 0; i <= numPoints; ++i) {
        float t = static_cast<float>(i) / numPoints * 2 * M_PI;
        float x = radius * (16 * sin(t) * sin(t) * sin(t));
        float y = radius * (13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t));

        Point point;
        point.x = centerX + x;
        point.y = centerY - y; // invert y-axis

        heartPoints.push_back(point);
    }

    return heartPoints;
}

Mesh* object2D::CreateRoundHeart(
    const std::string& name,
    glm::vec3 center,
    float radius,
    glm::vec3 color,
    int numPoints)
{
    std::vector<Point> heartPoints = createRoundHeart(center.x, center.y, radius, numPoints);

    std::vector<VertexFormat> vertices;
    for (const auto& point : heartPoints) {
        vertices.push_back(VertexFormat(glm::vec3(point.x, point.y, center.z), color));
    }

    Mesh* heart = new Mesh(name);

    // Connect the vertices to form triangles
    std::vector<unsigned int> indices;
    for (int i = 0; i < numPoints; ++i) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back((i + 1) % numPoints);
    }

    heart->InitFromData(vertices, indices);
    return heart;
}

Mesh* object2D::CreateBonusLife(
    const std::string& name,
    glm::vec3 center2,
    float length)
{
    glm::vec3 center = center2;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-6 * length, 6 * length, 6), glm::vec3(1, 1, 1)),
        VertexFormat(center + glm::vec3(6 * length, 6 * length, 6), glm::vec3(1, 1, 1)),
        VertexFormat(center + glm::vec3(6 * length, -6 * length, 6), glm::vec3(1, 1, 1)),
        VertexFormat(center + glm::vec3(-6 * length, -6 * length, 6), glm::vec3(1, 1, 1)),

        VertexFormat(center + glm::vec3(-1 * length, 4 * length, 7), glm::vec3(1, 0, 0)),//4e
        VertexFormat(center + glm::vec3(1 * length, 4 * length, 7), glm::vec3(1, 0, 0)),//5f
        VertexFormat(center + glm::vec3(4 * length, 1 * length, 7), glm::vec3(1, 0, 0)),//6o
        VertexFormat(center + glm::vec3(4 * length, -1 * length, 7), glm::vec3(1, 0, 0)),//7a
        VertexFormat(center + glm::vec3(1 * length, -4 * length, 7), glm::vec3(1, 0, 0)),//8l
        VertexFormat(center + glm::vec3(-1 * length, -4 * length, 7), glm::vec3(1, 0, 0)),//9k
        VertexFormat(center + glm::vec3(-4 * length, -1 * length, 7), glm::vec3(1, 0, 0)),//10i
        VertexFormat(center + glm::vec3(-4 * length, 1 * length, 7), glm::vec3(1, 0, 0)),//11h
        
    };

    Mesh* life = new Mesh(name);
    std::vector<unsigned int> indices = {
      0,1,2,
      0,2,3,

      4,5,8,
      4,9,8,
      11,6,7,
      11,10,7,

    };


    life->InitFromData(vertices, indices);
    return life;
}

Mesh* object2D::CreateLetter(
    const std::string& name,
    glm::vec3 center2,
    float length,
    glm::vec3 color)
{
    glm::vec3 center = center2;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-6 * length, 6 * length, 8), color),
        VertexFormat(center + glm::vec3(6 * length, 6 * length, 8), color),
        VertexFormat(center + glm::vec3(6 * length, -6 * length, 8), color),
        VertexFormat(center + glm::vec3(-6 * length, -6 * length, 8), color),


    };

    Mesh* letter = new Mesh(name);
    std::vector<unsigned int> indices = {
      0,1,2,
      0,2,3,
    };


    letter->InitFromData(vertices, indices);
    return letter;
}

