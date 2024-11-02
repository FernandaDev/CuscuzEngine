#type vertex
#version 330

uniform mat4 uWorldTransform;
uniform mat4 uViewProjection;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

out vec2 fragTexCoord;

void main()
{
    vec4 pos = vec4(inPosition, 1.0);
    gl_Position = pos * uWorldTransform * uViewProjection;
    
    fragTexCoord = inTexCoord;
}

#type fragment
#version 330

uniform sampler2D uTexture;

in vec2 fragTexCoord;

out vec4 outColor;

void main()
{
    outColor = texture(uTexture, fragTexCoord);   
}