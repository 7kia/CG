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
                     , float outRadius
                     , float innerRadius
                     , int vertexIndex)
{
   const float M_PI = 3.14159265;
   const float STEP = M_PI * 4 / 5;

   float angle = -0.5;
   int residue = vertexIndex;


    float angleShift = 1.f + STEP * float(vertexIndex);
    float x;
    float y;
      
     
    x = center.x + innerRadius * cos(angle * angleShift);
    y = center.y + innerRadius * sin(angle * angleShift);
    return vec2(x, y);
    
      
   
 }



void main()
{
    vec2 pos = gl_TexCoord[0].xy;


	// Generate vertex
    vec2 starPoints[6];

	vec2 center = vec2(2.f, 2.f);
    for(int index = 0; index < 5; ++index)
    {
       starPoints[index] =  GenerateStarPoint(center
                                                , 1.5f
                                                , 0.5f
                                                , index);
                                                
    }
    

	// Sort vertex
	/*
	for(int index = 3; index < 5; ++index)
    {
       if(starPoints[index + 1].x < starPoints[index + 2].x)
	   {
			vec2 buffer = starPoints[index + 1];

			starPoints[index + 1] = starPoints[index + 2];
			starPoints[index + 2] = buffer;
	   }
                                                
    }
	*/
	/////
	int sizeInTriangle = 5;
    bool inTriangle[5];

	bool resultBool = false;
    for(int index = 0; index < (sizeInTriangle - 1); ++index)
    {
	//int index = 0;
			inTriangle[index] = PointIsInsideTriangle(starPoints[index]
															, starPoints[index + 1]
															, center, pos);

			//resultBool = resultBool || inTriangle[index];
    }

	resultBool = false;
	/////////////////////////////////////////////
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


    if (resultBool)
    {
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
    else
    {
        // determine whether fraction part of x and y
        // texture coordinate is greater than 0.5
        vec2 stepXY = step(vec2(0.5, 0.5), fract(pos));
        // determine whether the texture coordinate
        // is within a black or white check
        gl_FragColor = vec4((stepXY.x != stepXY.y) ? 1.0 : 0.0);
    }   
                                   
                                                
    
           

}
