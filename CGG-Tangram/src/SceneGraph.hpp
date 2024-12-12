
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "mgl/mgl.hpp"
#include "SceneNode.hpp"


class SceneGraph {
public:
    SceneGraph();


    // Creates the shaders starting from the root node
    void createshader();

    // Draws the scene starting from the root node
    void draw(float animationprogress);

    // Add a root node (mesh or camera) to the scene graph
    void addNode(SceneNode* node);

    std::vector<SceneNode*> nodes;  // All nodes (meshes, etc.) in the scene
};
