#version 330 core

in vec4 vertexColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main() {
	vec2 texcoord = vec2(1.0f-texCoord.x,texCoord.y);
   	vec4 texcol1 = texture(tex1, texcoord);
   	vec4 texcol2 = texture(tex2, texcoord);
   	if (texcol2.a != 0) {
   		FragColor = mix(texcol1, texcol2, 0.2);
   	} else {
   		FragColor = texcol1;
   	}
   	FragColor = texcol2;
  	// FragColor = mix(texcol2, texcol1, 0.8);
}