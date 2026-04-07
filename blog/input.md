# Reaching the bottom of the input handling rabbithole
For 'Components' (in the web sense, not the ECS sense) which respond to input and are configurable.
* incidentally, being configurable is a requirement because of key bindings.

Shown for one example (A 2D camera with pan and zoom). Pls forgive cringe AI generated comments

Starting with the common code:

```rust
use sdl3::event::Event as SDLEvent;
use sdl3::keyboard::Keycode;
use sdl3::mouse::MouseButton;

// The dynamic value type for your settings menu
#[derive(Clone, Debug)]
pub enum ConfigValue {
    Float(f32),
    KeyBind(Keycode),
    MouseBind(MouseButton),
}

// What the UI reads to build the menus
pub struct ConfigSchema {
    pub key: &'static str,
    pub name: &'static str,
    pub default: ConfigValue,
}

pub trait Configurable {
    fn get_schema() -> Vec<ConfigSchema> where Self: Sized;
    fn apply_setting(&mut self, key: &str, value: ConfigValue) -> bool;
}

// Your centralized event pipe
pub enum GameEvent {
    SDL(SDLEvent),
    // Route window resolution changes cleanly here if you aren't catching SDL window events directly
    WindowResized(crate::Vec2), 
    SettingChanged {
        namespace: String,
        key: String,
        value: ConfigValue,
    },
}
```

And the specific code for the Camera Controller (its a real camera controller):

```rust
use crate::*; // Assuming Vec2, vec2, Dir, etc. are here

pub struct Cam2D {
    // Live State
    held: [bool; 4],
    mouse_pos: Vec2,
    mouse_grab_screen: Option<Vec2>,
    origin_at_grab: Option<Vec2>,
    origin: Vec2,
    zoom: f32,
    res: Vec2,

    // Owned Tunables (Configured via Settings)
    pub speed: f32,
    pub min_zoom: f32,
    pub max_zoom: f32,
    pub zoom_sensitivity: f32,

    // Owned Bindings
    pub bind_up: Keycode,
    pub bind_down: Keycode,
    pub bind_left: Keycode,
    pub bind_right: Keycode,
    pub bind_grab: MouseButton,
}

impl Default for Cam2D {
    fn default() -> Self {
        Cam2D {
            held: [false; 4],
            origin: vec2(0., 0.),
            mouse_pos: vec2(0., 0.),
            mouse_grab_screen: None,
            origin_at_grab: None,
            zoom: 1.,
            res: vec2(1., 1.),
            
            // Defaults that can be overridden by config
            speed: 1.,
            min_zoom: 0.01,
            max_zoom: 100.0,
            zoom_sensitivity: 0.12,

            // Default Bindings
            bind_up: Keycode::W,
            bind_down: Keycode::S,
            bind_left: Keycode::A,
            bind_right: Keycode::D,
            bind_grab: MouseButton::Right,
        }
    }
}

// --- THE SETTINGS MENU BRIDGE ---
impl Configurable for Cam2D {
    fn get_schema() -> Vec<ConfigSchema> {
        vec![
            ConfigSchema { key: "speed", name: "Camera Speed", default: ConfigValue::Float(1.0) },
            ConfigSchema { key: "zoom_sens", name: "Zoom Sensitivity", default: ConfigValue::Float(0.12) },
            ConfigSchema { key: "bind_up", name: "Pan Up", default: ConfigValue::KeyBind(Keycode::W) },
            ConfigSchema { key: "bind_down", name: "Pan Down", default: ConfigValue::KeyBind(Keycode::S) },
            ConfigSchema { key: "bind_left", name: "Pan Left", default: ConfigValue::KeyBind(Keycode::A) },
            ConfigSchema { key: "bind_right", name: "Pan Right", default: ConfigValue::KeyBind(Keycode::D) },
            ConfigSchema { key: "bind_grab", name: "Grab Canvas", default: ConfigValue::MouseBind(MouseButton::Right) },
        ]
    }

    fn apply_setting(&mut self, key: &str, value: ConfigValue) -> bool {
        match (key, value) {
            ("speed", ConfigValue::Float(v)) => { self.speed = v; true }
            ("zoom_sens", ConfigValue::Float(v)) => { self.zoom_sensitivity = v; true }
            ("bind_up", ConfigValue::KeyBind(k)) => { self.bind_up = k; true }
            ("bind_down", ConfigValue::KeyBind(k)) => { self.bind_down = k; true }
            ("bind_left", ConfigValue::KeyBind(k)) => { self.bind_left = k; true }
            ("bind_right", ConfigValue::KeyBind(k)) => { self.bind_right = k; true }
            ("bind_grab", ConfigValue::MouseBind(m)) => { self.bind_grab = m; true }
            _ => false, // Not for us, or type mismatch
        }
    }
}

// --- THE EVENT ROUTER ---
impl Cam2D {
    // the bool is if it was used or not, for stealing
    pub fn handle_event(&mut self, e: &GameEvent) -> bool {
        match e {
            // 1. Handle Dynamic Configuration Updates
            GameEvent::SettingChanged { namespace, key, value } => {
                if namespace == "camera" {
                    return self.apply_setting(key, value.clone());
                }
                false
            }
            
            // 2. Handle Resolution Overrides
            GameEvent::WindowResized(r) => {
                self.res = *r;
                false // Don't consume, other systems might need resize events
            }

            // 3. Localized Input Mapping (Rawdogging SDL)
            GameEvent::SDL(sdl_event) => {
                match sdl_event {
                    // Keyboard Processing
                    SDLEvent::KeyDown { keycode: Some(k), .. } => {
                        if *k == self.bind_up { self.held[Dir::Up.to_index()] = true; return true; }
                        if *k == self.bind_down { self.held[Dir::Down.to_index()] = true; return true; }
                        if *k == self.bind_left { self.held[Dir::Left.to_index()] = true; return true; }
                        if *k == self.bind_right { self.held[Dir::Right.to_index()] = true; return true; }
                        false
                    }
                    SDLEvent::KeyUp { keycode: Some(k), .. } => {
                        if *k == self.bind_up { self.held[Dir::Up.to_index()] = false; return true; }
                        if *k == self.bind_down { self.held[Dir::Down.to_index()] = false; return true; }
                        if *k == self.bind_left { self.held[Dir::Left.to_index()] = false; return true; }
                        if *k == self.bind_right { self.held[Dir::Right.to_index()] = false; return true; }
                        false
                    }

                    // Mouse Processing
                    SDLEvent::MouseButtonDown { mouse_btn, .. } if *mouse_btn == self.bind_grab => {
                        self.mouse_grab_screen = Some(self.mouse_pos);
                        self.origin_at_grab = Some(self.origin);
                        true
                    }
                    SDLEvent::MouseButtonUp { mouse_btn, .. } if *mouse_btn == self.bind_grab => {
                        self.mouse_grab_screen = None;
                        self.origin_at_grab = None;
                        true
                    }
                    
                    // The Math (Copied directly from your working implementation)
                    SDLEvent::MouseMotion { x, y, .. } => {
                        self.mouse_pos = vec2(*x as f32, *y as f32);
                        if let (Some(grab_screen), Some(origin_at_grab)) = (self.mouse_grab_screen, self.origin_at_grab) {
                            let res = vec2(self.res.x.max(1.0), self.res.y.max(1.0));
                            let aspect = res.x / res.y;
                            let d = self.mouse_pos - grab_screen;
                            let dndc_x = 2.0 * d.x / res.x;
                            let dndc_y = -2.0 * d.y / res.y;
                            let world_dx = dndc_x * aspect / self.zoom.max(0.0001);
                            let world_dy = dndc_y / self.zoom.max(0.0001);
                            self.origin = origin_at_grab - vec2(world_dx, world_dy);
                        }
                        false // Allow UI to still know where the mouse is
                    }
                    
                    SDLEvent::MouseWheel { y, .. } => {
                        let factor = (2.0_f32).powf(*y as f32 * self.zoom_sensitivity);
                        let old_zoom = self.zoom.max(self.min_zoom);
                        let new_zoom = (old_zoom * factor).clamp(self.min_zoom, self.max_zoom);

                        let res = vec2(self.res.x.max(1.0), self.res.y.max(1.0));
                        let aspect = res.x / res.y;
                        let ndc = vec2(
                            2.0 * self.mouse_pos.x / res.x - 1.0,
                            1.0 - 2.0 * self.mouse_pos.y / res.y,
                        );
                        let world_point_at_cursor = vec2(ndc.x * aspect, ndc.y);
                        let origin_shift = world_point_at_cursor * (1.0 / old_zoom - 1.0 / new_zoom);
                        self.origin += origin_shift;
                        self.zoom = new_zoom;

                        if let (Some(grab_screen), Some(_)) = (self.mouse_grab_screen, self.origin_at_grab) {
                            let d = self.mouse_pos - grab_screen;
                            let dndc_x = 2.0 * d.x / res.x;
                            let dndc_y = -2.0 * d.y / res.y;
                            let world_dx = dndc_x * aspect / self.zoom.max(0.0001);
                            let world_dy = dndc_y / self.zoom.max(0.0001);
                            self.origin_at_grab = Some(self.origin + vec2(world_dx, world_dy));
                        }
                        true
                    }
                    _ => false,
                }
            }
        }
    }

    pub fn update(&mut self, dt: f32) {
        for (i, dir) in DIRS.iter().cloned().enumerate() {
            if self.held[i] {
                self.origin += dir.to_ivec2().as_vec2() * dt * self.speed / self.zoom.max(0.0001)
            }
        }
    }

    // More impls for this camera incude proj(&self) -> [f32; 16] (projection matrix)
    // also stuff like inverse proj for picking and screen bounds for culling etc etc
}

# What are the benefits of this
In a structured way it handles
* Horizontally scalable (componentwise) input handling
* Correct event stealing (the bool return value)
* Rebindable inputs (and other setting can be handled too)
* Settings loading, saving, updating from UI and UI menu population are ✨all taken care of✨

While having all concerns isolated to a singular file.

# Explanation of how its used (horizontal scalability)
Procedural approach is recommended. Something like this as a sketch:
```rust
pub struct LevelContext {
    pub camera: Cam2D, // real
    pub building_controller: BuildingController, // believable
    pub floating_butons: FloatingButtons, // plausible
    // could even have a quit controller for all i care, might be over engineering at this point but you could for perfect uniformity of the handle_event function
}

impl LevelContext {
    pub fn handle_event(&mut self, e: &GameEvent) {
        if self.camera.handle_event(event) { return false; }
        if self.building_controller.handle_event(event) { return false; }
        if self.floating_buttons.handle_event(event) { return false; }
        // etc more stuff, horizontally scalable
        // if you wanted a Vec<Box<dyn InputHandler>> just pretend this is it
        // I think this is better, they need to be referenced positionally for their specific functions in say update or in the game loop anyway
        // P R O C E D U R A L
    }
}
```

# Remarks
Basically we are thinking like a JS developer for the settings ('but what if it was just a hashmap with string keys'). This is just the finished solution but you can think for yourself through the other alternatives and their shortcomings. I'm told that this is what engines do for their 'property system'. At least I'm catching up.

Later im probably striking out the english name from the schemas because thats got to be loaded from the text registry in whatever language but we can save that rabbithole for another time. Minor detail.

Why not use an interface for EventHandler? well we dont strictly need it, it would just be to attempt to railroad our LLMs more but they probably can get the idea anyway from this.