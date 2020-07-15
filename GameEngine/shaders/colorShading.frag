#version 130
//4 component float vector that gets outputted to the screen for each pixel
//output of rgb color
in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D mySampler;

void main() {
	//color to red
	
	vec4 textureColor = texture(mySampler, fragmentUV);
	
	color = textureColor * fragmentColor;

}	