uniform float TWIST;

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

	////////////////////////
	// first step
	///*
	y = maxHeight * sin(radius + shift) / radius + height;
	//*/
	////////////////////////

	////////////////////////
	// second step
	///*
	shift = PI;
	y = maxHeight * sin( 1.5 * (radius + shift) ) / radius + height;
	//*/
	////////////////////////


	////////////////////////
	// third step
	///*
	shift = 2.f * PI;
	float flatShift = 1.5f * PI;// TODO : rename
	if( (radius) > flatShift )
	{
		y = maxHeight * sin(radius + shift) / radius + height;
	}
	else
	{
		y = maxHeight * sin(flatShift) / flatShift + height;
	}
	//*/
	////////////////////////

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
