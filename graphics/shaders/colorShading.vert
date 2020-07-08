#version 130
//input of x and y positions
in vec2 vertexPosition;

in vec4 vertexColor;
in vec2 vertexUV;

out vec4 fragmentColor;
out vec2 fragmentUV;
out vec2 fragmentPosition;

uniform mat4 P;

void main(){
	//set x y position
	gl_Position.xy = (P*vec4 (vertexPosition,0.0,1.0)).xy;

	//set z position to 0 since 2D 
	gl_Position.z = 0.0;

	//indicate the coordinates are normalized
	gl_Position.w = 1.0;
	
	fragmentPosition = vertexPosition; 
	fragmentColor = vertexColor;
	
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y); 
	
}