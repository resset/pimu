varying highp vec3 vert;
varying highp vec3 vertNormal;
uniform highp vec3 lightPos;
void main() {
   highp vec3 L = normalize(lightPos - vert);
   highp float NL = max(dot(normalize(vertNormal), L), 0.0);
   highp vec3 color = vec3(0.85, 0.85, 0.85);
   highp vec3 col = clamp(color * 0.4 + color * 0.6 * NL, 0.0, 1.0);
   gl_FragColor = vec4(col, 1.0);
}
