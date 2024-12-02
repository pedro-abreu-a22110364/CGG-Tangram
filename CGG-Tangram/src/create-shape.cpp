#include "create-shape.hpp"
#include <GL/glew.h>
#include <iostream>


void Createshape::createbuffershape(GLuint VaoId) {
    glBindVertexArray(VaoId);
    glGenBuffers(2, VboId); // Generate two buffers: one for vertices and one for indices

    // VBO for vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
    glBufferData(GL_ARRAY_BUFFER, ShapeVertices.size() * sizeof(Vertex), ShapeVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);  // Vertex position attribute

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, RGBA));
    glEnableVertexAttribArray(1);  // Vertex color attribute

    // VBO for element (index) data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ShapeIndices.size() * sizeof(GLubyte), ShapeIndices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

// Function to set the color of all vertices in a shape
void Createshape::setColor(float red, float green, float blue, float transparency) {
    for (auto& vertex : ShapeVertices) {
        vertex.RGBA[0] = red;
        vertex.RGBA[1] = green;
        vertex.RGBA[2] = blue;
        vertex.RGBA[3] = transparency;
    }
}