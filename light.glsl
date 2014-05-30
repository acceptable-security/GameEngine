uniform vec2 lightpos;
uniform vec3 lightColor;
uniform float screenHeight;
uniform float radius;

void main() {
	vec3 lightColor = vec3(lightColor.x * radius, lightColor.y * radius, lightColor.z * radius);
	float distance = length(lightpos - gl_FragCoord.xy);
	float attenuation = 1.0 / distance;
	vec4 color = vec4(attenuation, attenuation, attenuation, 1.0) * vec4(lightColor, 1);

	gl_FragColor = color;
}