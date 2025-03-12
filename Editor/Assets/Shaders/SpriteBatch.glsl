#type vertex
#version 330

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in float inTexIndex;
layout(location = 4) in vec2 inTilingOffset;

uniform mat4 u_ViewProjection;

out vec2 fragTexCoord;
out vec4 fragColor;
out float fragTexIndex;
out vec2 fragTilingOffset;

void main()
{
    gl_Position = u_ViewProjection * vec4(inPosition, 1.0);

    fragTexCoord = inTexCoord;
    fragColor = inColor;
    fragTexIndex = inTexIndex;
    fragTilingOffset = inTilingOffset;
}

#type fragment
#version 330

layout(location = 0) out vec4 outColor;

in vec2 fragTexCoord;
in vec4 fragColor;
in float fragTexIndex;
in vec2 fragTilingOffset;

uniform sampler2D u_Textures[32];

void main()
{
    outColor = texture(u_Textures[int(fragTexIndex)], vec2(fragTexCoord.x * fragTilingOffset.x, fragTexCoord.y * fragTilingOffset.y)) * fragColor;
}