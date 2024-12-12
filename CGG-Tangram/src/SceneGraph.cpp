#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "mgl/mgl.hpp"
#include "SceneGraph.hpp"

SceneGraph::SceneGraph() = default;

// Render the scene starting from the root node
void SceneGraph::draw(float animationprogress) {
    for (int i = 0; i < size(nodes); i++) {
        nodes[i]->draw(animationprogress);
   }
}

void SceneGraph::createshader() {
    for (int i = 0; i < size(nodes); i++) {
        nodes[i]->createshader();
    }
}

// Add a root node (mesh or camera) to the scene graph
void SceneGraph::addNode(SceneNode* node) {
    nodes.push_back(node);
}