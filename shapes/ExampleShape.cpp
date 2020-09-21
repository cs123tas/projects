#include "ExampleShape.h"

ExampleShape::ExampleShape()
{
}

ExampleShape::ExampleShape(int param1, int param2) :
    m_param1(param1),
    m_param2(param2)
{
    m_vertexData = CUBE_DATA_POSITIONS;
    buildVAO();
}

ExampleShape::~ExampleShape()
{
}
