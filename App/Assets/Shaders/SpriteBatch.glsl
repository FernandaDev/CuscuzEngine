#type vertex
#version 330

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec4 inColor;

uniform mat4 u_ViewProjection;

out vec2 fragTexCoord;
out vec4 fragColor;

void main()
{
    gl_Position = u_ViewProjection * vec4(inPosition, 1.0);

    fragTexCoord = inTexCoord;
    fragColor = inColor;
}

#type fragment
#version 330

layout(location = 0) out vec4 outColor;

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D u_Texture;

void main()
{
    //outColor = texture(u_Texture, fragTexCoord) * fragColor;
    outColor = fragColor;
}