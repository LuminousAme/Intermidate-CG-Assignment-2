//Titan Engine, by Atlas X Games 
// Material.cpp - source file for the class that represents materials on 3D objects

//precompile header
#include "Titan/ttn_pch.h"
//include the header
#include "Titan/Material.h"

namespace Titan {
	//default constructor
	TTN_Material::TTN_Material() 
		: m_Shininess(0), m_HeightInfluence(1.0f)
	{
		//set the albedo to an all white texture by default
		m_Albedo = TTN_Texture2D::Create();
		m_Albedo->Clear(glm::vec4(1.0f));

		//set the specular to an all white texture by default
		m_SpecularMap = TTN_Texture2D::Create();
		m_SpecularMap->Clear(glm::vec4(1.0f));
		//set the cube map to an all white texture by default
		m_SkyboxTexture = TTN_TextureCubeMap::Create();
		m_SkyboxTexture->Clear(glm::vec4(1.0f));

		//set the height map to an all black texture by default 
		m_HeightMap = TTN_Texture2D::Create();
		m_HeightMap->Clear(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}

	//default desctructor
	TTN_Material::~TTN_Material()
	{ }

	//sets the albedo texture
	void TTN_Material::SetAlbedo(TTN_Texture2D::st2dptr albedo)
	{
		m_Albedo = albedo;
	}

	//sets the shininess
	void TTN_Material::SetShininess(float shininess)
	{
		m_Shininess = shininess;
	}

	//sets the specular map texture
	void TTN_Material::SetSpecularMap(TTN_Texture2D::st2dptr specular)
	{
		m_SpecularMap = specular;
	}

	//sets a cube map texture for a skybox
	void TTN_Material::SetSkybox(TTN_TextureCubeMap::stcmptr Skybox)
	{
		m_SkyboxTexture = Skybox;
	}

	//sets the height map texture
	void TTN_Material::SetHeightMap(TTN_Texture2D::st2dptr height)
	{
		m_HeightMap = height;
	}

	//sets a multipliers for how how influence the height map should have
	void TTN_Material::SetHeightInfluence(float influence)
	{
		m_HeightInfluence = influence;
	}

	//// Setters for shader bools ////
	void TTN_Material::SetNoLight(bool noLight)
	{
		m_NoLight = noLight;
		if (m_NoLight == true) {
			m_Ambient = false;
			m_AmbientSpecular = false;
			m_AmbientSpecularCustom = false;
			m_Specular = false;
		}
	}
	void TTN_Material::SetAmbient(bool ambient)
	{
		m_Ambient = ambient;
		if (m_Ambient == true) {
			m_NoLight = false;
			m_AmbientSpecular = false;
			m_AmbientSpecularCustom = false;
			m_Specular = false;
		}
	}
	void TTN_Material::SetSpecular(bool specular)
	{
		m_Specular = specular;
		if (m_Specular == true) {
			m_Ambient = false;
			m_AmbientSpecular = false;
			m_AmbientSpecularCustom = false;
			m_NoLight = false;
		}
	}
	void TTN_Material::SetAmbientSpecular(bool ambientSpecular)
	{
		m_AmbientSpecular = ambientSpecular;
		if (m_NoLight == true) {
			m_Ambient = false;
			m_AmbientSpecular = false;
			m_AmbientSpecularCustom = false;
			m_Specular = false;
		}
	}
	void TTN_Material::SetCustom(bool custom)
	{
		m_AmbientSpecularCustom = custom;
		if (m_NoLight == true) {
			m_Ambient = false;
			m_AmbientSpecular = false;
			m_AmbientSpecularCustom = false;
			m_Specular = false;
		}
	}
}