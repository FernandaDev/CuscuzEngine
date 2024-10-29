#type vertex
#version 330

in vec3 inPosition;

void main()
{
    gl_Position = vec4(inPosition, 1.0);
}

#type fragment
#version 330

out vec4 outColor;

void main()
{
    outColor = vec4(0.8, 1.0, 0.45, 1.0);   
}