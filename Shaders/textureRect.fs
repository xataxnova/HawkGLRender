#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixParam;

void main()
{
	vec2 inverseCoord = new vec2( 1-TexCoord.x, TexCoord.y );	
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, inverseCoord), mixParam);
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixParam);
}