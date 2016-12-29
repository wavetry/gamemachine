#version 400
#define W_IS_NOT_ONE_BREAK(VEC4) if (VEC4.w - 1 > 0.001) return;
#define ZERO_BREAK(n) if (n <= 0.001) return;
#define MORE_THAN_N_BREAK(value, n) if (value > n) return;

uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 projection_matrix;
uniform mat4 shadow_matrix;
uniform mat4 local_scaling_matrix = mat4(1);

uniform vec4 light_position;
uniform vec4 view_position;
uniform float light_shininess;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;
layout (location = 2) in vec2 uv;

out float diffuse;
out float specular;
out vec4 shadow_coord;
out vec2 ambient_texture_uv;

void main(void)
{
	vec4 world_coord = model_matrix * local_scaling_matrix * position;

    vec4 pos = projection_matrix * view_matrix * world_coord;

    vec3 light_direction = normalize(light_position.xyz - world_coord.xyz);

    vec3 view_direction = normalize(view_position.xyz - world_coord.xyz);

    vec3 half_vector = 0.5 * (light_direction + view_direction);

    vec3 normalized = normal.xyz;

    diffuse = dot(light_direction, normalized);

    specular = pow(dot(half_vector, normalized), light_shininess);

	shadow_coord = shadow_matrix * world_coord;

    ambient_texture_uv = uv;

    gl_Position = pos;
}