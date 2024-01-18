#shader vertex
#version 330 core


in vec3 position;
in vec3 color;
in vec2 texCoord;

out vec3 Color;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	Color = color;
	TexCoord = texCoord;
	gl_Position = projection * view * model * vec4(position, 1.0);
};

#shader fragment
#version 330 core
in vec3 Color;
in vec2 TexCoord;

out vec4 outColor;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main()
{
	vec4 colTex1 = texture(ourTexture, TexCoord);
	if (colTex1 == vec4(1.0f, 0.f, 1.0f, 1.0f))
		discard;
	vec4 colTex2 = texture(ourTexture2, TexCoord);
	outColor = mix(colTex1, colTex2, 0.5);
};