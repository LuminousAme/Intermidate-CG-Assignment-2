#pragma once

//include the precompile header with a bunch of system
#include "ttn_pch.h"
#include "PostEffect.h"

namespace Titan {

	class TTN_ColorCorrect : public TTN_PostEffect
	{
	public:
		//init framebuffer, overrirdes post effect Init
		void Init(unsigned width, unsigned height) override;

		//applies effect to buffer, passes previous framebuffer with the texture to apply as parameter
		void ApplyEffect(TTN_PostEffect* buffer) override;
		
		void DrawToScreen() override;
	
		//getters
		float GetIntensity() const;

		//setters
		void SetIntensity(float intensity);


	private:
		float _intensity = 1.0f;








	};


}
