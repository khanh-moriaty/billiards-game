#version 330

precision mediump float;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};


in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;
uniform sampler2D _texture;
uniform vec3 lightPos0;
uniform vec3 camPosition;

uniform float shininess;

void main()
{
	//fs_color = vec4(vs_color, 1.f);
	//fs_color = mix(texture(_texture, vs_texcoord), texture(_texture, vs_texcoord), 1);

	//ambient light
	vec3 ambientLight = vec3(.75f, .75f, .75f);

	//diffuse light
	vec3 posToLightDirVec = normalize(lightPos0 - vs_position);
	vec3 diffuseColor = vec3(.75f, .75f, .75f);
	float diffuse = max(dot(posToLightDirVec, vs_normal), 0.0);
	vec3 diffuseFinal = diffuseColor * diffuse;

	//Specular light
	vec3 specularFinal = vec3(0.f, 0.f, 0.f);
	if (diffuse != 0.0) {
		vec3 lightToPosDirVec = normalize(vs_position - lightPos0);
		vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
		vec3 posToViewDirVec = normalize(camPosition - vs_position);
		float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0.f), shininess);
		specularFinal = vec3(1.f, 1.f, 1.f) * specularConstant;
	}

	//Final light
	fs_color = texture(_texture, vs_texcoord) * (vec4(ambientLight, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));

}