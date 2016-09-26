uniform float TWIST;

void main()
{
	const float a = 1.f;
	const float b = 1.f;

	float x = gl_Vertex.x;
	float z = gl_Vertex.z;

	float y = (pow(x, 2) / pow(a, 2) - pow(z, 2) / pow(b, 2)) / 2;


	TWIST;
    vec4 twistedCoord = vec4(
		x,//* TWIST
		gl_Vertex.y + (y - gl_Vertex.y) * TWIST ,//* TWIST
        z ,//* TWIST
		//x ,//+ (x - gl_Vertex.x) * TWIST
       // gl_Vertex.y ,//+ (y - gl_Vertex.y) * TWIST
        //z,// + (z - gl_Vertex.z) * TWIST
        gl_Vertex.w
    );

    vec4 position = gl_ModelViewProjectionMatrix * twistedCoord;
    // Transform twisted coordinate
    gl_Position = position;
    gl_FrontColor = (position + vec4(1.0)) * 0.5;
}
