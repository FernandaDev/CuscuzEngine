#type vertex
#version 330

in vec3 inPosition;

uniform mat4 uWorldTransform;
uniform mat4 uViewProjection;

void main()
{
    vec4 pos = vec4(inPosition, 1.0);
    gl_Position = pos * uWorldTransform * uViewProjection;
}

#type fragment
#version 330

out vec4 outColor;

void main()
{
    outColor = vec4(0.8, 1.0, 0.45, 1.0);   
}