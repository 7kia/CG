#version 130
// GLSL version 130 enabled with OpenGL Core Profile 3.0.
//  - `attribute` renamed to `in` for vertex shader
//  - `varying` renamed to `out` for vertex shader

bool IsBetween(float value, float start, float end)
{
	return (value >= start) && (value <= end);// TODO : see end
}

float GetNumberStep(float value)
{
	for(float start = 0.f; start < 3.f; ++start)
	{
		if( IsBetween(value, start, start + 1.f) )
		{
			return start;
		}
	}
	return 0.f;	
}

in vec3 vertex;
in vec3 normal;
in vec2 textureUV;


out vec2 fragTextureUV;
out vec3 fragNormal;
out vec3 fragViewDirection;

uniform mat4 modelView;
uniform mat4 normalModelView;
uniform mat4 projection;
uniform float TWIST;

void main(void)
{
	float x = vertex.x;
	float z = vertex.z;

	float height = -3.f;
	float maxHeight = 2.f;

	float radius = sqrt(x * x + z * z);

	// TOOD : rewrite
	float PI = 3.141592653f;
	float shift = PI;
	float y = maxHeight;

	float numberStep = GetNumberStep(TWIST);// TODO : see need the type

	shift = (TWIST + 1.f) * PI;
	y = maxHeight * sin( (radius + shift)) / (radius + 1) + height;
	
    vec3 resultVertex = vec3(
		vertex.x,
		vertex.y + (y - vertex.y) * TWIST ,//* TWIST
		vertex.z
    );

    vec4 posInViewSpace = modelView * vec4(resultVertex, 1.0);
    fragViewDirection = vec3(posInViewSpace);
    fragNormal = normalize(vec3(normalModelView * vec4(normal, 0.0)));
    fragTextureUV = textureUV;
    gl_Position = projection * posInViewSpace;
}