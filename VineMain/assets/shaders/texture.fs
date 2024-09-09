#version 330 core

in vec2 v_TexCoord;
in vec4 v_Color;
in float v_TexIndex;

uniform sampler2D u_Textures[32];

out vec4 FragColor;

void main()
{
    vec4 texColor = texture(u_Textures[int(v_TexIndex)], v_TexCoord);
    FragColor = texColor * v_Color;
}