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

   float angle = -0.5 * M_PI;

      float angleShift = 1.f + STEP * float(vertexIndex);
      float x;
      float y;
      
      int residue = vertexIndex - (vertexIndex / 3);
      if (residue == 0)
      {
         return center;
      }
      else if(residue == 1)
      {
         x = center.x + outRadius * cos(angle * angleShift);
         y = center.y + outRadius * sin(angle * angleShift);
         return vec2(x, y);
      }
      else if(residue == 2)
      {
         x = center.x + innerRadius * cos(angle * angleShift);
         y = center.y + innerRadius * sin(angle * angleShift);
         return vec2(x, y);
      }

      ///
      ///
      ///
     // result.push_back(SVertexP2T2(result, vec2()));

   //}
   
 }

void main()
{
    vec2 pos = gl_TexCoord[0].xy;


    vec2 starPoints[30];
    for(int index = 0; index < 30; ++index)
    {
       starPoints[index] =  GenerateStarPoint(vec2(2.5f, 2.5f)
                                                , 2.f
                                                , 1.f
                                                , index);
                                                
    }
    
    
    //for(int index = 0; index < 30; index += 3)
    //{
               int index = 0;
    if (PointIsInsideTriangle(starPoints[index], starPoints[index + 1], starPoints[index + 2], pos))
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
    
    //}                                     
                                                
    
           

}
