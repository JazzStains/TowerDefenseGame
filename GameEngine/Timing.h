#pragma once


namespace GameEngine {

	class FPSLimiter {
	public: 
		FPSLimiter();
		void init(float maxFPS);
		void setMaxFPS(float maxFPS);
		void beginFrame();
		//returns the fps
		float end(); 
	private:
		void calculateFPS();
		float _maxFPS;
		unsigned int _startTicks;
		float _fps;
		float _frameTime;
	};
}