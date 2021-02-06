#version 420

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inUV;

uniform bool u_Option1; //no lighting
uniform bool u_Option2; //ambient lighting only
uniform bool u_Option3; //specular lighting only
uniform bool u_Option4; //ambient + specular + diffuse
uniform bool u_Option5;	 // ambient + specular + special effect
uniform bool u_Option6; //diffuse warp/ramp
uniform bool u_Option7; //specular warp/ramp
uniform bool u_Option8; //color correction warm	
uniform bool u_Option9; //color correction cool
uniform bool u_Option0; //color correction custom effect	
	
uniform sampler2D s_Diffuse;
uniform sampler2D s_Diffuse2;
uniform sampler2D s_Specular;

uniform vec3  u_AmbientCol;
uniform float u_AmbientStrength;

uniform vec3  u_LightPos;
uniform vec3  u_LightCol;
uniform float u_AmbientLightStrength;
uniform float u_SpecularLightStrength;
uniform float u_Shininess;

uniform float u_LightAttenuationConstant;
uniform float u_LightAttenuationLinear;
uniform float u_LightAttenuationQuadratic;
uniform float time;
uniform float u_TextureMix;
uniform vec3  u_CamPos;

layout(binding = 0) uniform sampler2D u_FinishedFrame;
layout(binding = 30) uniform sampler3D u_TexColorGrade;

out vec4 frag_color;

void main() {
	// Lecture 5
	vec3 ambient = u_AmbientLightStrength * u_LightCol;

	// Diffuse
	vec3 N = normalize(inNormal);
	vec3 lightDir = normalize(u_LightPos - inPos);

	float dif = max(dot(N, lightDir), 0.0);
	vec3 diffuse = dif * u_LightCol;// add diffuse intensity

	//Attenuation
	float dist = length(u_LightPos - inPos);
	float attenuation = 1.0f / (
		u_LightAttenuationConstant + 
		u_LightAttenuationLinear * dist +
		u_LightAttenuationQuadratic * dist * dist);

	// Specular
	vec3 viewDir  = normalize(u_CamPos - inPos);
	vec3 h        = normalize(lightDir + viewDir);

	// Get the specular power from the specular map
	float texSpec = texture(s_Specular, inUV).x;
	float spec = pow(max(dot(N, h), 0.0), u_Shininess); // Shininess coefficient (can be a uniform)
	vec3 specular = u_SpecularLightStrength * texSpec * spec * u_LightCol; // Can also use a specular color

	// Get the albedo from the diffuse / albedo map
	vec4 textureColor1 = texture(s_Diffuse, inUV);
	vec4 textureColor2 = texture(s_Diffuse2, inUV);
	vec4 textureColor = mix(textureColor1, textureColor2, u_TextureMix);

	//color correction 
	vec4 textureColorCorrect = texture(u_FinishedFrame, inUV);
	vec3 scale = vec3((64.0-1.0)/64.0 );
	vec3 offset = vec3(1.0/(2.0*64.0));

	if (u_Option1 == true){
	vec3 result = inColor*textureColor.rgb;
	frag_color = vec4(result, textureColor.a);}

	else if (u_Option2 == true){
	vec3 result = (ambient) *inColor*textureColor.rgb;
	frag_color = vec4(result, textureColor.a);}
	
	else if (u_Option3 == true){
	vec3 result = (specular) *inColor*textureColor.rgb;
	frag_color = vec4(result, textureColor.a);}

	else if (u_Option4 == true){
	vec3 result = (ambient+specular+diffuse) * inColor * textureColor.rgb;
	frag_color = vec4(result, textureColor.a);}

	else if (u_Option5 == true){
	vec3 result = sin( (ambient+specular+diffuse) * inColor * textureColor.rgb + time );
	//result.x = result.x+time;
	frag_color = vec4(result, textureColor.a);
	}

	else if (u_Option6 == true){
	frag_color.rgb = texture(u_TexColorGrade, scale * textureColor.rgb + offset).rgb;
	frag_color.a = textureColor.a;
	}

	else {
	vec3 result = (
		(u_AmbientCol * u_AmbientStrength) + // global ambient light
		(ambient + diffuse + specular) * attenuation // light factors from our single light
		) * inColor * textureColor.rgb; // Object color

	frag_color = vec4(result, textureColor.a);}



}