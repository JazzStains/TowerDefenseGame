#version 130
//4 component float vector that gets outputted to the screen for each pixel
//output of rgb color
in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;


uniform float time;
uniform sampler2D mySampler;

void main() {
	//color to red
	
	vec4 textureColor = texture(mySampler, fragmentUV);
	
	color = textureColor * fragmentColor;
	
	//color = vec4(fragmentColor.r *(cos(fragmentPosition.x*4.0 + time)+1.0)*0.05,
	//			fragmentColor.g *(cos(fragmentPosition.y*8.0 + time)+1.0)*0.05,
	//			fragmentColor.b *(cos(fragmentPosition.x*10.0 + time)+1.0)*0.05,
	//			fragmentColor.a)*textureColor; 
}	