#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "SceneNode.hpp"
#include "mgl/mgl.hpp"

// Constructor with an optional transformation (identity matrix by default)
SceneNode::SceneNode(mgl::Mesh* mesh ) : mesh(mesh) {
}

// Add a child node to this node
void SceneNode::addChild(SceneNode* child) {
    children.push_back(child);
    child->parent = this;
}

void SceneNode::createshader(const glm::mat4& parentTransform) {

    if (mesh != nullptr) {
        Shaders = new mgl::ShaderProgram();

        Shaders->addShader(GL_VERTEX_SHADER, "cube-vs.glsl");
        Shaders->addShader(GL_FRAGMENT_SHADER, "cube-fs.glsl");

        Shaders->addAttribute(mgl::POSITION_ATTRIBUTE, mgl::Mesh::POSITION);

        if (mesh->hasNormals()) {
            Shaders->addAttribute(mgl::NORMAL_ATTRIBUTE, mgl::Mesh::NORMAL);
        }

        if (mesh->hasTexcoords()) {
            Shaders->addAttribute(mgl::TEXCOORD_ATTRIBUTE, mgl::Mesh::TEXCOORD);
        }

        if (mesh->hasTangentsAndBitangents()) {
            Shaders->addAttribute(mgl::TANGENT_ATTRIBUTE, mgl::Mesh::TANGENT);
        }

        Shaders->addUniform(mgl::MODEL_MATRIX);
        Shaders->addUniform("givenColor");
        Shaders->addUniformBlock(mgl::CAMERA_BLOCK, UBO_BP);

        Shaders->create();

        ModelMatrixId = Shaders->Uniforms[mgl::MODEL_MATRIX].index;
        colorID = Shaders->Uniforms["givenColor"].index;
    }
    if (size(children) != 0) {
        for (int i = 0; i < size(children); i++) {
            children[i]->createshader();
        }
    }
}

// A simple draw method (for demonstration purposes)
void SceneNode::draw(float animationprogress) {
    glm::mat4 Matrix;
    glm::mat4 MatrixEnd = TranslateMatrixEnd * RotateMatrixEnd * ScaleMatrix;
    glm::mat4 MatrixStart = TranslateMatrixStart * RotateMatrixStart * ScaleMatrix;
    glm::mat4 AnimatedMatrix = interpolateMatrix(MatrixStart, MatrixEnd, animationprogress);
    if (parent != nullptr) {
        glm::mat4 MatrixEndparent = this->parent->TranslateMatrixEnd * this->parent->RotateMatrixEnd * this->parent->ScaleMatrix;
        glm::mat4 MatrixStartparent = this->parent->TranslateMatrixStart * this->parent->RotateMatrixStart * this->parent->ScaleMatrix;
        glm::mat4 AnimatedMatrixParent = interpolateMatrix(MatrixStartparent, MatrixEndparent, animationprogress);
        Matrix = AnimatedMatrixParent * AnimatedMatrix;
    }
    else {
        Matrix = AnimatedMatrix;
    }

    if (mesh != nullptr) {
        Shaders->bind();
        glUniformMatrix4fv(ModelMatrixId, 1, GL_FALSE, glm::value_ptr(Matrix));
        glUniform3fv(colorID, 1, glm::value_ptr(color));
        mesh->draw();
        Shaders->unbind();
    }

    if (size(children) != 0) {
        for (int i = 0; i < size(children); i++) {
            children[i]->draw(animationprogress);
        }
    }
}

glm::mat4 SceneNode::interpolateMatrix(const glm::mat4& startMat, const glm::mat4& endMat, float animationProgress) {
    // Decompose the start and end matrices into translation, rotation, and scale
    glm::vec3 startTranslation, endTranslation, startScale, endScale, startSkew, endSkew;
    glm::vec4 startPerspective, endPerspective;
    glm::quat startRotation, endRotation;

    // Decompose both matrices
    glm::decompose(startMat, startScale, startRotation, startTranslation, startSkew, endPerspective);
    glm::decompose(endMat, endScale, endRotation, endTranslation, endSkew, startPerspective);

    // Interpolate translation, rotation, and scale
    glm::vec3 interpolatedTranslation = glm::mix(startTranslation, endTranslation, animationProgress);
    glm::quat interpolatedRotation = glm::slerp(startRotation, endRotation, animationProgress);
    glm::vec3 interpolatedScale = glm::mix(startScale, endScale, animationProgress);

    // Reconstruct the final matrix with the interpolated components
    glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), interpolatedTranslation);
    glm::mat4 rotationMat = glm::mat4_cast(interpolatedRotation);
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), interpolatedScale);

    // Combine the matrices: Scale -> Rotate -> Translate
    return translationMat * rotationMat * scaleMat;
}

void SceneNode::translatestart(glm::vec3 vector) {
    TranslateMatrixStart = glm::translate(TranslateMatrixStart, vector);
};

void SceneNode::rotatestart(float angle, glm::vec3 axis) {
    RotateMatrixStart = glm::rotate(RotateMatrixStart, glm::radians(angle), axis);
};

void SceneNode::scale(glm::vec3 vector) {
    ScaleMatrix = glm::scale(ScaleMatrix, vector);
};

void SceneNode::translateend(glm::vec3 vector) {
    TranslateMatrixEnd = glm::translate(TranslateMatrixEnd, vector);
};

void SceneNode::rotateend(float angle, glm::vec3 axis) {
    RotateMatrixEnd = glm::rotate(RotateMatrixEnd, glm::radians(angle), axis);
};

void SceneNode::setColor(glm::vec3 vector) {
    color = vector;
}