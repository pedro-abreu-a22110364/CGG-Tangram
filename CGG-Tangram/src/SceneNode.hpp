#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <glm/gtx/matrix_decompose.hpp>
#include <vector>
#include "mgl/mgl.hpp"

const GLuint UBO_BP = 0;

class SceneNode {
public:
    SceneNode(mgl::Mesh* = nullptr);
    void addChild(SceneNode* child);
    void createshader(const glm::mat4& parentTransform = glm::mat4(1.0f));
    void translateend(glm::vec3 vector);
    void rotateend(float angle, glm::vec3 axis);
    void translatestart(glm::vec3 vector);
    void rotatestart(float angle, glm::vec3 axis);
    void scale(glm::vec3 vector);
    void draw(float animationprogress);
    void setColor(glm::vec3 vector);
    glm::mat4 interpolateMatrix(const glm::mat4& startMat, const glm::mat4& endMat, float animationProgress);

    mgl::Mesh* mesh;
    SceneNode* parent = nullptr;
    std::vector<SceneNode*> children;
    mgl::ShaderProgram* Shaders = nullptr;
    glm::mat4 RotateMatrixEnd = glm::mat4(1.0f);
    glm::mat4 TranslateMatrixEnd = glm::mat4(1.0f);
    glm::mat4 ScaleMatrix = glm::mat4(1.0f);
    glm::mat4 RotateMatrixStart = glm::mat4(1.0f);
    glm::mat4 TranslateMatrixStart = glm::mat4(1.0f);
    GLint ModelMatrixId;
    glm::vec3 color;
    GLint colorID;
};


