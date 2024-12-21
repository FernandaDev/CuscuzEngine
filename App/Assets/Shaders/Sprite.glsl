#type vertex
#version 330

uniform mat4 u_WorldTransform;
uniform mat4 u_ViewProjection;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

out vec2 fragTexCoord;

void main()
{
    gl_Position = u_ViewProjection * u_WorldTransform * vec4(inPosition, 1.0);
    
    fragTexCoord = inTexCoord;
}

#type fragment
#version 330

uniform sampler2D u_Texture;
uniform vec4 u_Color;

in vec2 fragTexCoord;

out vec4 outColor;

void main()
{
    outColor = texture(u_Texture, fragTexCoord) * u_Color;   
}