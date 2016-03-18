#version 450

in vec2 texPos_;
in vec3 normal_;

struct BaseLight
{
	vec3 color;
	float intensity;
};

struct DirectionalLight
{
	BaseLight base;
	vec3 direction;
};

uniform vec3 baseColor;
uniform vec3 ambientLight;
uniform sampler2D sampler;

uniform DirectionalLight directionalLight;

vec4 calcLight(BaseLight base, vec3 direction, vec3 normal) {
	float diffuseFactor = dot(-direction, normal);
	
	vec4 diffuseColor = vec4(0,0,0,0);
	
	if(diffuseFactor > 0) {
		diffuseColor = vec4(base.color, 1) * base.intensity * diffuseFactor;	
	}
	
	return diffuseColor;
}

vec4 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal) {
	return calcLight(directionalLight.base, directionalLight.direction, normal);
}

void main()
{
	vec4 textureColor = texture(sampler, texPos_.xy);
	
	vec4 totalLight = vec4(ambientLight, 1);
	vec4 color = vec4(baseColor, 1);
	
	if(textureColor != vec4(0,0,0,0)) {
		color *= textureColor;
	}
	
	vec3 normal = normalize(normal_);
	
	totalLight += calcDirectionalLight(directionalLight, normal);

	gl_FragColor = color * totalLight;
}
