#include <GL/glew.h>
#include <vector>

typedef struct {
    GLfloat XYZW[4];
    GLfloat RGBA[4];
} Vertex;

class Createshape {
public:
    std::vector<Vertex> ShapeVertices;
    std::vector<GLubyte> ShapeIndices;
    GLuint VaoId, VboId[2];
public:
    Createshape(std::vector<Vertex> vertices, std::vector<GLubyte> indices) : ShapeVertices(vertices), ShapeIndices(indices) {}
    void createbuffershape(GLuint VaoId);
    void setColor(float red, float green, float blue, float transparency);


};
class Square : public Createshape {
public:
    Square() : Createshape({ {{0.25f, 0.25f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
                            {{0.5f, 0.25f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
                            {{0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
                            {{0.25f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}} },
        { 0, 1, 3, 1, 2, 3 }) {
    }
};
class Parallelogram : public Createshape {
public:
    Parallelogram() : Createshape({ {{0.50f, 0.25f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
                                    {{0.75f, 0.25f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
                                    {{0.50f, 0.50f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
                                    {{0.25f, 0.50f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}} },
        { 0, 1, 3, 1, 2, 3 }) {
    }
};
class Triangle : public Createshape {
public:
    Triangle() : Createshape({
            {{0.25f, 0.25f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
            {{0.5f, 0.25f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
            {{0.25f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}} },
        { 0, 1, 2 }) {
    }
};