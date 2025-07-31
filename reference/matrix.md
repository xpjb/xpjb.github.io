# 3D Camera Math
So this is the necessary math for basic 3D camera. Conventions:
* Y up
* Column major matrices (I think) (does it look like how the math is written or is it reversed? who knows. but tranpose not needed in gl_uniform_matrix4)
* Right handed

## View Matrix
```rust
pub fn mat_view(eye: Vec3, target: Vec3, up: Vec3) -> [f32; 16] {
    let z_axis = (eye - target).unit();
    let x_axis = up.cross(&z_axis).unit();
    let y_axis = z_axis.cross(&x_axis);

    [
        x_axis.x, y_axis.x, z_axis.x, 0.0,
        x_axis.y, y_axis.y, z_axis.y, 0.0,
        x_axis.z, y_axis.z, z_axis.z, 0.0,
        -x_axis.dot(&eye), -y_axis.dot(&eye), -z_axis.dot(&eye), 1.0,
    ]
}
```

## Projection Matrix
```rust
pub fn mat_orthographic(left: f32, right: f32, bottom: f32, top: f32, near: f32, far: f32) -> [f32; 16] {
    let rl = 1.0 / (right - left);
    let tb = 1.0 / (top - bottom);
    let nf = 1.0 / (near - far);
    [
        2.0 * rl, 0.0, 0.0, 0.0,
        0.0, 2.0 * tb, 0.0, 0.0,
        0.0, 0.0, -2.0 * nf, 0.0,
        -(right + left) * rl, -(top + bottom) * tb, (far + near) * nf, 1.0,
    ]
}

pub fn mat_perspective(fov_y_radians: f32, aspect_ratio: f32, near: f32, far: f32) -> [f32; 16] {
    let f = 1.0 / (fov_y_radians * 0.5).tan();
    let nf = 1.0 / (near - far);
    [
        f / aspect_ratio, 0.0, 0.0, 0.0,
        0.0, f, 0.0, 0.0,
        0.0, 0.0, (far + near) * nf, -1.0,
        0.0, 0.0, 2.0 * far * near * nf, 0.0,
    ]
}
```

N.B. VP = Projection * View

N.B. Setting near too close will get you precision issues



