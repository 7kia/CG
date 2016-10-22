uniform float TWIST;

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
	
}

void main()
{
	float x = gl_Vertex.x;
	float z = gl_Vertex.z;

	float height = -3.f;
	float maxHeight = 2.f;

	float radius = sqrt(x * x + z * z);

	// TOOD : rewrite
	float PI = 3.141592653f;
	float shift = PI;
	float y = maxHeight;

	float numberStep = GetNumberStep(TWIST);// TODO : see need the type

	shift = (TWIST + 1.f) * PI;
	/*
	if( (maxHeight * sin( (radius + shift)) / radius + height) > 0.10f )
	{
		y = maxHeight + height;
	}
	else
	{
		y = maxHeight * sin( (radius + shift)) / radius + height;
	}

	*/
	
	y = maxHeight * sin( (radius + shift)) / (radius + 1) + height;
	
	TWIST;
    vec4 twistedCoord = vec4(
		x,
		gl_Vertex.y + (y - gl_Vertex.y) * TWIST ,//* TWIST
        z ,
        gl_Vertex.w
    );

    vec4 position = gl_ModelViewProjectionMatrix * twistedCoord;

    // Transform twisted coordinate
    gl_Position = position;
    gl_FrontColor = (position + vec4(1.0)) * 0.5;
}
