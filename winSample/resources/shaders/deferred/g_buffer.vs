#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV0;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in vec4 skinIndex;
layout (location = 6) in vec4 skinWeight;
uniform bool isSkinning;
out vec2 UV0;
out vec3 FragPos;
out mat3 TBN;
out vec4 ClipSpacePos;
out vec4 PrevClipSpacePos;

#include ../common/uniforms.glsl

uniform mat4 model;
uniform mat4 prevModel;
;
float time;
uniform vec4 skinningMatrix[240];

	
void main()
{
	UV0 = aUV0;
	vec3 transformed_pos;
	vec3 transformed_nor;
	vec3 transformed_tangent;
	vec3 transformed_bitangent;
	if(isSkinning)
	{
		vec4 row1 = skinningMatrix[int(skinIndex.x)*3] * skinWeight.x;
			 row1 += skinningMatrix[int(skinIndex.y)*3] * skinWeight.y;
	         row1 += skinningMatrix[int(skinIndex.z)*3] * skinWeight.z;
	         row1 += skinningMatrix[int(skinIndex.w)*3] * skinWeight.w;

	vec4 row2 = skinningMatrix[int(skinIndex.x)*3+1] * skinWeight.x;
	row2 += skinningMatrix[int(skinIndex.y)*3+1] * skinWeight.y;
	row2 += skinningMatrix[int(skinIndex.z)*3+1] * skinWeight.z; 
	row2 += skinningMatrix[int(skinIndex.w)*3+1] * skinWeight.w;

	vec4 row3 = skinningMatrix[int(skinIndex.x)*3+2] * skinWeight.x;
	row3 += skinningMatrix[int(skinIndex.y)*3+2] * skinWeight.y;
	row3 += skinningMatrix[int(skinIndex.z)*3+2] * skinWeight.z;
	row3 += skinningMatrix[int(skinIndex.w)*3+2] * skinWeight.w;

	mat4 tempmat = mat4(vec4(row1[0], row2[0], row3[0], 0.0),
						vec4(row1[1], row2[1], row3[1], 0.0),
						vec4(row1[2], row2[2], row3[2], 0.0),
						vec4(row1[3], row2[3], row3[3], 1.0));
	vec4 newPosition = tempmat * vec4( aPos,1.0 );
	transformed_pos=newPosition.xyz;
	transformed_nor = normalize(mat3(tempmat) * aNormal);
	transformed_tangent = normalize(mat3(tempmat) * aTangent);
	transformed_bitangent = normalize(mat3(tempmat) * aBitangent);
	}
	else
	{
		transformed_pos=aPos;
		transformed_nor=aNormal;
		transformed_tangent=aTangent;
		transformed_bitangent=aBitangent;
	}
	FragPos = vec3(model * vec4(transformed_pos, 1.0));
        
    vec3 N = normalize(mat3(model) * transformed_nor);
    vec3 T = normalize(mat3(model) * transformed_tangent);
    T = normalize(T - dot(N, T) * N);
    // vec3 B = cross(N, T);
    vec3 B = normalize(mat3(model) * transformed_bitangent);

    // TBN must form a right handed coord system.
    // Some models have symetric UVs. Check and fix.
    if (dot(cross(N, T), B) < 0.0)
        T = T * -1.0;
    
    TBN = mat3(T, B, N);
    
    ClipSpacePos     = viewProjection * model * vec4(aPos, 1.0);
    PrevClipSpacePos = prevViewProjection * prevModel * vec4(aPos, 1.0);
	
	gl_Position =  projection * view * vec4(FragPos, 1.0);
}