// Check if the point p is on the left side of the line p0p1
bool PointIsOnTheLeft(vec2 p0, vec2 p1, vec2 p)
{
    vec2 p0p1 = p1 - p0;
    // find the orthogonal vector to p0p1
    vec2 n = vec2(-p0p1.y, p0p1.x);
    // Find the dot product between n and (p - p0)
    return dot(p - p0, n) > 0.0;
}

bool PointIsInsideTriangle(vec2 p0, vec2 p1, vec2 p2, vec2 p)
{
    return PointIsOnTheLeft(p0, p1, p) &&
           PointIsOnTheLeft(p1, p2, p) &&
           PointIsOnTheLeft(p2, p0, p);
}

vec2 GenerateStarPoint(const vec2 center
                     , float radius
                     , int vertexIndex)
{
	const float M_PI = 3.141592653;
	const float STEP = M_PI * 4 / 5;

	float angle = -0.5;

	float angleShift = 2.f + STEP * float(vertexIndex);
    float x;
    float y;    
     
    x = center.x + radius * cos(angle * angleShift);
    y = center.y + radius * sin(angle * angleShift);
    return vec2(x, y); 
 }

bool CheckFillRectangle(vec2 firstPoint
						, vec2 secondPoint
						, vec2 thirdPoint
						, vec2 fourthPoint
						, vec2 positionFill)
{
	bool resultBool = false;
	/////////////////////////////////////////////
	// TODO : see can rewrite another

	// TODO : crutch for draw border between triangles
	//thirdPoint.x = thirdPoint.x * 0.99f;
	thirdPoint.y = thirdPoint.y * 0.9999f;


	resultBool = resultBool || PointIsInsideTriangle(thirdPoint
															, secondPoint
															, firstPoint, positionFill);

	resultBool = resultBool || PointIsInsideTriangle(secondPoint
														, thirdPoint
														, fourthPoint, positionFill);

	return resultBool;
}

bool DrawHammerAndSickle(vec2 pos)
{
	bool resultBool = false;
	/////////////////////////////////////////////
	// Hammer peen
	resultBool = resultBool || CheckFillRectangle(vec2(0.433f, 2.632f)
													,vec2(0.902f, 3.045f)
													,vec2(0.724f, 2.365f)
													,vec2(1.328f, 2.92f)
													
													, pos);
	/////////////////////////////////////////////
	// Handle hammer
	resultBool = resultBool || CheckFillRectangle(vec2(0.843f, 2.583f)
													,vec2(1.015f, 2.77f)
													,vec2(1.863f, 1.618f)
													,vec2(2.035f, 1.805f)
													, pos);
	
	/////////////////////////////////////////////
	// Sickle peen
	resultBool = resultBool || CheckFillRectangle(vec2(0.551f, 1.794f)
													,vec2(0.777f, 1.976f)
													,vec2(0.696f, 1.603f)												
													,vec2(0.922f, 1.784f)
													, pos);
	/////////////////////////////////////////////
	// Sickle peen
	resultBool = resultBool || CheckFillRectangle(vec2(0.551f, 1.794f)
													,vec2(0.777f, 1.976f)
													,vec2(0.696f, 1.603f)												
													,vec2(0.922f, 1.784f)
													, pos);
	/////////////////////////////////////////////
	// Sickle blade
	resultBool = resultBool || CheckFillRectangle(vec2(0.794f, 1.929f)
													,vec2(0.997f, 2.071f)
													,vec2(0.903f, 1.808f)												
													,vec2(1.1f, 1.963f)
													, pos);

	resultBool = resultBool || CheckFillRectangle(vec2(1.09f, 1.967f)
													,vec2(1.268f, 1.865f)
													,vec2(0.958f, 1.851f)												
													,vec2(1.241f, 1.703f)
													, pos);

	resultBool = resultBool || CheckFillRectangle(vec2(1.256f, 1.87f)
													,vec2(1.495f, 1.85f)
													,vec2(1.223, 1.702f)												
													,vec2(1.507f, 1.686f)
													, pos);

	resultBool = resultBool || CheckFillRectangle(vec2(1.478f, 1.846f)
													,vec2(1.678f, 1.953f)
													,vec2(1.497f, 1.686f)												
													,vec2(1.769f, 1.833f)
													, pos);

	resultBool = resultBool || CheckFillRectangle(vec2(1.478f, 1.846f)
													,vec2(1.678f, 1.953f)
													,vec2(1.497f, 1.686f)												
													,vec2(1.769f, 1.833f)
													, pos);
	/////////////////////////////////////////////

	return resultBool;
}

void main()
{
	const vec4 RED_COLOR = vec4(0.8f, 0.f, 0.f, 1.f);
	const vec4 YELLOW_COLOR = vec4(1.f, 1.f, 0.1f, 1.f);

    vec2 pos = gl_TexCoord[0].xy;


	// Generate vertex
    vec2 starPoints[5];

	vec2 center = vec2(1.f, 3.5f);
    for(int index = 0; index < 5; ++index)
    {
       starPoints[index] =  GenerateStarPoint(center
                                                , 0.25f
                                                , index);
                                                
    }

	bool resultBool = false;
	/////////////////////////////////////////////
	// TODO : see can rewrite another
	resultBool = resultBool || PointIsInsideTriangle(starPoints[0]
															, starPoints[3]
															, center, pos);
	resultBool = resultBool || PointIsInsideTriangle(starPoints[1]
															, starPoints[4]
															, center, pos);
	resultBool = resultBool || PointIsInsideTriangle(starPoints[2]
															, starPoints[0]
															, center, pos);
	resultBool = resultBool || PointIsInsideTriangle(starPoints[3]
															, starPoints[1]// TODO
															, center, pos);
	resultBool = resultBool || PointIsInsideTriangle(starPoints[4]
															, starPoints[2]
															, center, pos);
	/////////////////////////////////////////////
	// HammerAndSickle
	resultBool = resultBool || DrawHammerAndSickle(pos);

    if (resultBool)
    {
        gl_FragColor = YELLOW_COLOR;
    }
    else
    {
        gl_FragColor = RED_COLOR;
    }   
                                   
                                                
    
           

}
