#version 150

in  vec4 vPosition;
in  vec4 vColor;
in  vec4 vNormal;
out vec4 color;
out vec4 normal;

uniform float alpha;

uniform mat4 objectToCameraTransformation;

uniform mat4 rotationMat;
uniform mat4 scaleMat;
uniform mat4 translationMat;

void main() 
{
    color = vColor;//vec4(vColor.xyz, alpha);
    color.a = alpha;
    gl_Position = objectToCameraTransformation * translationMat * rotationMat * scaleMat * vPosition;
    normal = vNormal;
}