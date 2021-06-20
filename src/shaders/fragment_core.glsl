#version 330

precision mediump float;

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform sampler2D _texture;
uniform vec3 camPosition;

uniform vec3 lightPos0;
uniform vec3 lightPos1;
uniform vec3 lightPos2;

uniform float shininess;

const vec3 ambientColor = vec3(.6f, .6f, .6f);
const vec3 diffuseColor = vec3(.35f, .35f, .35f);
const vec3 specularColor = vec3(.6f, .6f, .6f);

// diffuse light
vec3 diffuseLight(vec3 lightPos){
	vec3 posToLightDirVec = normalize(lightPos - vs_position);
	float diffuse = max(dot(posToLightDirVec, vs_normal), 0.0);
	vec3 diffuseFinal = diffuseColor * diffuse;
	return diffuseFinal;
}

// specular light
vec3 specularLight(vec3 lightPos, vec3 diffuseFinal){
	vec3 specularFinal = vec3(0.f);
	if (length(diffuseFinal) > 0) {
		vec3 lightToPosDirVec = normalize(vs_position - lightPos);
		vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
		vec3 posToViewDirVec = normalize(camPosition - vs_position);
		float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0.f), shininess);
		specularFinal = specularColor * specularConstant;
	}
	return specularFinal;
}

void main()
{
	//fs_color = vec4(vs_color, 1.f);
	//fs_color = mix(texture(_texture, vs_texcoord), texture(_texture, vs_texcoord), 1);

	vec3 diffuse0 = diffuseLight(lightPos0);
	vec3 diffuse1 = diffuseLight(lightPos1);
	vec3 diffuse2 = diffuseLight(lightPos2);

	vec3 specular0 = specularLight(lightPos0, diffuse0);
	vec3 specular1 = specularLight(lightPos1, diffuse1);
	vec3 specular2 = specularLight(lightPos2, diffuse2);

	vec3 diffuseFinal = diffuse0   + diffuse1 + diffuse2;
	vec3 specularFinal = specular0 + specular1 + specular2;

	//Final light
	fs_color = texture(_texture, vs_texcoord) * (vec4(ambientColor, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));

}