#include "Titan/ttn_pch.h"
#include "Titan/ColorCorrect.h"

namespace Titan {

	void TTN_ColorCorrect::Init(unsigned width, unsigned height)
	{

		if (!_shaders.size() > 0)
		{
			//set up framebuffers
			int index = int(_buffers.size());
			_buffers.push_back(new TTN_Framebuffer());
			_buffers[index]->AddColorTarget(GL_RGBA8);
			_buffers[index]->AddDepthTarget();
			_buffers[index]->Init(width, height);
		}

		_shaders.push_back(TTN_Shader::Create());
		_shaders[_shaders.size() - 1]->LoadShaderStageFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
		_shaders[_shaders.size() - 1]->LoadShaderStageFromFile("shaders/color_correction_frag.glsl", GL_FRAGMENT_SHADER);
		_shaders[_shaders.size() - 1]->Link();

		//Call base class Init
		TTN_PostEffect::Init(width, height);

	}

	void TTN_ColorCorrect::ApplyEffect(TTN_PostEffect* buffer)
	{
		BindShader(_shaders.size() - 1);

		buffer->BindColorAsTexture(0, 0, 0);

		_buffers[0]->RenderToFSQ();

		buffer->UnbindTexture(0);

		UnbindShader();
	}

	void TTN_ColorCorrect::DrawToScreen()
	{
		BindShader(_shaders.size() - 1);

		BindColorAsTexture(0, 0, 0);
		_buffers[0]->DrawFullScreenQuad();
		UnbindTexture(0);

		UnbindShader();
	}


	float TTN_ColorCorrect::GetIntensity() const
	{
		return _intensity;
	}

	void TTN_ColorCorrect::SetIntensity(float intensity)
	{
		_intensity = intensity;
	}

}

