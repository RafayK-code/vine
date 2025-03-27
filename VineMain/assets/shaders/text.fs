#version 410 core

in vec2 v_TexCoord;
in vec4 v_Color;

uniform sampler2D u_FontAtlas;

out vec4 FragColor;

float screenPxRange() 
{
	const float pxRange = 8.0; // set to distance field's pixel range
    vec2 unitRange = vec2(pxRange)/vec2(textureSize(u_FontAtlas, 0));
    vec2 screenTexSize = vec2(1.0)/fwidth(v_TexCoord);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

void main()
{
    float out_bias = 0.25;
    float outline_width_absolute = 1.0 / 16.0;
    float outline_width_relative = 1.0 / 7.0;

    vec4 distances = texture(u_FontAtlas, v_TexCoord);
	float d_msdf = median(distances.r, distances.g, distances.b);
    float d_sdf = distances.a;

    float roundedFonts = 0.0;   //uniform
    float roundedOutlines = 0.0;    //uniform
    float d_inner = mix(d_msdf, d_sdf, roundedFonts);
    float d_outer = mix(d_msdf, d_sdf, roundedOutlines);

    float threshold = 0.60;  //uniform
    float inverted_threshold = 1.0 - threshold;
    float width = screenPxRange();
    float inner = width * (d_inner - inverted_threshold) + 0.5; + out_bias;
    float outer = width * (d_outer - inverted_threshold + outline_width_relative) + 0.5 + out_bias + outline_width_absolute;

    float inner_opacity = clamp(inner, 0.0, 1.0);
    vec4 inner_color = vec4(1.0, 1.0, 1.0, 1.0);
    float outer_opacity = clamp(outer, 0.0, 1.0);
    vec4 outer_color = vec4(0.0, 0.0, 0.0, 1.0);

    vec4 color = (inner_color * inner_opacity) + (outer_color * (outer_opacity - inner_opacity));
    if (color.a == 0.0)
        discard;

    FragColor = color;

    //FragColor = vec4(texture(u_FontAtlas, v_TexCoord).rgb, 1.0);
}