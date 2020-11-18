#version 330

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec3 v_uw;
layout (location = 3) in vec3 v_color;


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;


out vec3 normal;
out vec2 uw;
out vec3 color;


vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
    normal = normalize(mat3(Model) * v_normal);
    uw = v_uw.xy;
    color = hsv2rgb(rgb2hsv(v_color) + vec3(time, 0, 0));

    gl_Position = Projection * View * (Model * vec4(v_position, 1) + vec4(sin(time), 0, cos(time), 0));
}
