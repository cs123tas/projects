#include "ExampleShape.h"

ExampleShape::ExampleShape()
{
}

ExampleShape::ExampleShape(int param1, int param2) :
    m_param1(param1),
    m_param2(param2)
{
    /**
     * We build in vertex data for a cube, in this case they are handwritten.
     * You'll want to expand upon or refactor this code heavily to take advantage
     * of polymorphism, vector math/glm library, and utilize good software design
     *
     */
    m_vertexData = CUBE_DATA_POSITIONS;
    /** build the VAO so that the shape is ready to be drawn */
    buildVAO();
}

ExampleShape::~ExampleShape()
{
}
