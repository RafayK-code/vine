#version 330 core

in vec2 v_TexCoord;
in vec4 v_Color;

uniform sampler2D u_FontAtlas;

out vec4 FragColor;

float screenPxRange() 
{
	const float pxRange = 2.0; // set to distance field's pixel range
    vec2 unitRange = vec2(pxRange)/vec2(textureSize(u_FontAtlas, 0));
    vec2 screenTexSize = vec2(1.0)/fwidth(v_TexCoord);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

void main()
{
	vec4 texColor = v_Color * texture(u_FontAtlas, v_TexCoord);

	vec3 msd = texture(u_FontAtlas, v_TexCoord).rgb;
    float sd = median(msd.r, msd.g, msd.b);
    float screenPxDistance = screenPxRange()*(sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);
	if (opacity == 0.0)
		discard;

	vec4 bgColor = vec4(0.0);
    vec4 color = mix(bgColor, v_Color, opacity);
	if (color.a == 0.0)
		discard;

    FragColor = color;    
}