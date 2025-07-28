# Shadertoy Reference

## Hash
### Crappy Float Hash
```c
float hash11(float p) {
    return fract(sin(p * 12.9898) * 43758.5453);
}
vec2 hash12(float p) {
    vec2 p2 = vec2(p, p + 1.0);
    return fract(sin(p2 * vec2(12.9898, 10.1414)) * 43758.5453);
}
float hash21(vec2 p) {
    return fract(sin(dot(p, vec2(12.9898, 78.233))) * 43758.5453);
}
vec2 hash22(vec2 p) {
    p = vec2(dot(p, vec2(127.1, 311.7)),
             dot(p, vec2(269.5, 183.3)));
    return fract(sin(p) * 43758.5453);
}
float hash31(vec3 uv) {
 	vec3 suv = fract(sin(uv));
    mat3 rdz = mat3(0.324354, 0.303147, 0.21024,
                    0.405434, 0.723953, 0.69343,
                    0.904379, 0.594319, 0.10439);
    suv = rdz*suv;
    return fract(dot(suv, uv)*1204.9324234934);
}
vec3 hash33(vec3 p) {
    p = vec3(dot(p, vec3(127.1, 311.7, 74.7)),
             dot(p, vec3(269.5, 183.3, 246.1)),
             dot(p, vec3(419.2, 371.9, 21.8)));
    return fract(sin(p) * 43758.5453);
}
```

### Unsigned Hash
```c
uint uhash(uint h) {
    h = (h ^ 2747636419u) * 2654435769u;
    h = (h ^ (h >> 16)) * 2654435769u;
    h = (h ^ (h >> 16)) * 2654435769u;
    return h;
}
```



## Noise
### Value Noise
```c
float smooth_hash31(vec3 uv)
{
 	vec3 lower	= floor(uv);
    vec3 frac 	= fract(uv);
    vec3 f = frac*frac*(3.0-2.0*frac);
    
    return mix( // Z
        mix( // Y
            mix( // X
                hash31(lower+vec3(0.0, 0.0, 0.0)), hash31(lower+vec3(1.0, 0.0, 0.0)), f.x),
            mix( // X
                hash31(lower+vec3(0.0, 1.0, 0.0)), hash31(lower+vec3(1.0, 1.0, 0.0)), f.x),
            f.y),
        mix( // Y
            mix( // X
                hash31(lower+vec3(0.0, 0.0, 1.0)), hash31(lower+vec3(1.0, 0.0, 1.0)), f.x),
            mix( // X
                hash31(lower+vec3(0.0, 1.0, 1.0)), hash31(lower+vec3(1.0, 1.0, 1.0)), f.x),
            f.y),
        f.z);
}
```
## Distance
### Line Segment
```c
float dseg(vec2 p, vec2 a, vec2 b) {
    vec2 pa = p - a;
    vec2 ba = b - a;
    float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
    return length(pa - ba * h);
}
```





