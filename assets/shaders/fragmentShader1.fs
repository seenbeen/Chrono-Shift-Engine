#version 330 core

in vec3 fragNormal;
in vec2 texCoord;
in vec4 fragPos;

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

  //FragColor = vec4(0.0f,1.0f,1.0f,1.0f);

 	vec3 lightPos = vec3(0.0f,0.0f,4.0f);
  vec4 lightCol = vec4(1.0f,1.0f,1.0f,1.0f);
  vec3 norm = normalize(fragNormal);
  vec3 lightDir = normalize(lightPos - fragPos.xyz);
  
  float ambientStrength = 0.1;
  vec4 ambient = ambientStrength * lightCol;

  float diff = max(dot(norm, lightDir), 0.0);
  vec4 diffuse = diff * lightCol;

  FragColor = (ambient + diffuse) * FragColor;
  FragColor.a = 1.0f;
}