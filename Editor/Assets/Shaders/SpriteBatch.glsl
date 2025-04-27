#type vertex
#version 330

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec4 inTexCoordAndIndex;
layout(location = 3) in vec2 inTilingOffset;

uniform mat4 u_ViewProjection;

out vec4 fragColor;
out vec2 fragTexCoord;
flat out int fragTexIndex;

void main()
{
    gl_Position = u_ViewProjection * vec4(inPosition, 1.0);

    fragColor = inColor;
    fragTexCoord = inTexCoordAndIndex.xy * inTilingOffset;
    fragTexIndex = int(inTexCoordAndIndex.z);
}

#type fragment
#version 330

layout(location = 0) out vec4 outColor;

in vec4 fragColor;
in vec2 fragTexCoord;
flat in int fragTexIndex;

uniform sampler2D u_Textures[32];

void main()
{
    outColor = texture(u_Textures[fragTexIndex], fragTexCoord) * fragColor;
}