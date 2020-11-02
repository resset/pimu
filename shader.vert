attribute vec4 vertex;
attribute vec3 normal;
attribute vec3 fragColor;
varying vec3 vert;
varying vec3 vertNormal;
varying vec3 color;
uniform mat4 projMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;
void main() {
   vert = vertex.xyz;
   vertNormal = normalMatrix * normal;
   color = fragColor;
   gl_Position = projMatrix * mvMatrix * vertex;
}
