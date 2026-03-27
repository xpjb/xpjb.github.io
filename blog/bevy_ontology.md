# ECS Theme
I'm going to argue that if we should not use bevy itself, we should maybe use its Language when making games.

Went to Rust Melbourne meetup yesterday. Talk on the subject of Bevy development (he was making a CAD with Bevy)
I mention bevy in discord, love how any ECS related thing arcs up massive discussion. Its probably a sort of bike shedding thing. But well, it usually boils down to, yeah the performance benefit is negligible over fat structs. But the remaining argument is if there are additional benefits.

Bevy lays out this idea of mathematical perfection of a game engine that sounds really promising. Everything snaps into a specific place.

Even if one doesn't fully subscribe to Bevy or ECS there are still principles to take away here. Or at least Names for certain features of game engines.

## Systems

Take *Systems* for example - the procedures that constitute the games simulation step. I've got an example here somewhere. 

```rs
use crate::*;
impl InGame {
    pub fn run_systems(&mut self, dt: Q1616) {
        self.update_farms(dt);
        self.level.entities.update_shooting(dt, &self.level.units, &self.level.unit_hash, &mut self.level.projectiles); // idk why this is like this lmao but the other ones are all quite alright. could be because spawning
        self.barracks_respawn(dt);
        self.repairer_respawn(dt);
        self.update_units_death_timer(dt);
        self.update_melee_cooldown(dt);

        self.note_enemy_positions();
        self.apply_enemy_velocity(dt);
        self.apply_repairman_pathing(dt);
        self.apply_unit_pathing(dt);
        self.apply_repairman_repair(dt);
        self.unit_attack(dt);

        self.move_projectiles(dt);
        self.check_projectile_collisions();
        self.cleanup_projectiles();

        self.move_unit_projectiles(dt);
        self.check_unit_projectile_collisions();
        self.cleanup_unit_projectiles();

        self.snap_to_map(dt);

        // these can be iterated if helpful
        self.separate_units_entities(dt);
        self.separate_units(dt);
        
        self.set_velocities(dt);
        self.mark_entities();
        self.mark_units(dt);
    }
}
```

Its honestly nothing fancy but just having the concept that there is a big ordered list of procedures that constitute the games logic, and laying them out cleanly, is nice.

## Components

Take the the famous *Components* for example. These are either the members of your struct OR your arrays if doing SoA / ECS for example. eg. I had this in an SoA example:

```rs
#[derive(Clone)]
pub struct Entities {
    // === Runtime identification ===
    pub prototype_id: Vec<usize>,
    pub generations: Vec<u32>,
    pub first_empty: usize,
    pub alloc_generation: u32,

    // === Prototype-driven core stats ===
    pub sizes: Vec<IVec2>,
    pub max_hp: Vec<Q1616>,
    pub upgrade_level: Vec<u32>,
    pub repair_rate: Vec<Q1616>,
    pub range: Vec<Q1616>,
    pub cooldown: Vec<Q1616>,
    pub damage: Vec<Q1616>,
    pub healing: Vec<Q1616>,
    pub atk_cooldown: Vec<Q1616>,
    pub flags: Vec<EntityFlags>,
    pub per_second_income: Vec<Q1616>,
    pub hue: Vec<f32>, // degrees
    pub colour: Vec<Vec4>, // alpha == 0 => "not set"

    // === Prototype-only / overlay/static ===
    pub name: Overlay<String>,
    pub initial: Overlay<String>,
    pub cost: Overlay<Q1616>,

    // === Runtime state (not specified in defs JSON) ===
    pub grid_positions: Vec<IVec2>,
    pub hp: Vec<Q1616>,
    pub cooldown_timers: Vec<Q1616>,
    pub marked_for_removal: Vec<bool>,
    pub barracks_respawn_timer: Vec<Q1616>, // countdown for barracks; only used when prototype is barracks
    pub rally_tile: Vec<Option<IVec2>>,    // rally point for unit-producing buildings (e.g. barracks); None for others
    pub repairer_respawn_timer: Vec<Q1616>, // countdown for repairer; only used when prototype is repairer

    // Spatial occupancy grid (rebuilt after removals)
    pub entity_grid: EntityHash,
}
```

The EntityHash is really more of a resource but I guess it made sense at the time and maybe still does.

I'm just going to mention that for me one of the key ideas is about Object Oriented Programming. I'm not going to tell you its bad or good. I'm here to speak about what should constitute 'one object'. I think we are starting to see it as bad when it is pretty good (or even perfect) for certain problem shapes. If you're trying to wrap a horrible, stateful dependency like OpenGL, I think that an OOP way is the best way to do that. You do like, exactly oop. Just to contain the horribleness. Its like putting a giant dome over something like in the Simpsons Movie. Anyway.

Game development is one of the places where it really breaks down and people have noticed. And I'm going to argue its because the game simulation is 'One Object'. Cooking up a complex system of interrelations between various tiny fragments is not the way to program your game logic. The best way to program your game logic is to program your game logic, ie. write procedures (Systems) that update the state (Components) each frame. 

### Justifying One Objectness
The game simulation is one object because everything inside it cares about everything else inside it. Putting everything in mini domes like if you were doing it in OOP way only gets in the way, you still ultimately need to write the procedures that cause the games state to update from one frame to the next, only its just been obfuscated by data hiding rules where you have to go and thread it all through un hiding anyway, because again, it all talks to each other by definition (especially if its a good game (good games tend to fill out the joint space of all orthogonal mechanics vectors)).

## Resources
*Resources* will be essentially the members of your Game or Level or World struct or whatever. They are all the one-off things that are also involved in your game simulation. (I'm not sharing mine because its always such a spaghetti - goes to show that I should think about them in a more organised way)

## Edge cases that bevy handles
* Spawning entities during your game loop
* Entity deletion
* Hierarchical relationship between entities
* Valid references across generations and entities spawning / dying

You can also just handle them yourself. Once again I'm more arguing that Bevy's ontology is nice here than necessarily using Bevy.

The key point here is that, while Systems and Components seem Horizontally Scalable, like you can just keep adding them until the game is done, (and you more or less can) but there are just a few more issues that crop up where reality comes knocking and you will get a crash or some weird bugs.

Again, because Bevy aims to be a panacea it handles all of thse by definition (as would any other working game engine). I will get into them now.

### Spawning Entities
If you add an entity halfway through some of your systems it might break an invariant. It also might not. It also depends on your underlying storage. Actually its hard to imagine it being a big deal honestly because theres no circumstance you would insert in the middle of the array and shift things.. I think

### Despawning Entities
This one is more common. If you delete an entity and shift everything this can be bad for many reasons:
* Invalidating held references for other entities
* Maybe causing updates to be skipped if it moved them during system update (maybe idk)
* Bad performance if its shifting everything each time theres a delete
So two of these are 'fixed' by going from naive removal to swap remove, but the invalidating held references, is still a deal breaker. You can't move things around. Its much better to use some kind of flag whether its health < 0.0 authoritative or literally a bool flag is_alive. Just set the flag to zero, no worries. You can allocate to the first dead slot with a scan. You can store the first free entity index to scan less. Its what I do.

I think Dreams does something different where they actually do some double buffering thing where they copy each entity each frame. There are reasons, maybe to do with playback and determinism. Idk. I'm sure they know what they are doing.

### Valid References
Now that we have stopped our adding and deleting from moving all the entities about willy-nilly we may actually be able to hold on to a reference. However, the entities can still die and be replaced with another one in the same spot. So references must have not only the index but the generation so we can know if our guy has since died when we go to check that slot. 

### Hierarchical Relationship
You just add a component called parent and an index (and a generation - all valid references must contain a generation). But you must need some logic to delete children when deleting parents, or something, if you want. I don't really have this yet.

## More stuff to mention
I'm literally just mentioning this stuff here because I don't have time to go into it. Out of scope! But interesting.
* 'Fix your timestep' type stuff
* State machine states.. main menu.. options menu.. etc
* Plugins. How we all dream of modular plugins


## Why is it so fun to talk about ECS
I guess mixing up any one part of the ontology with what the ECS does etc.
Like that OG Jon Blow video commenting on kyrens talk about making an ECS in Rust.


## Conclusion
Again because bevy is trying to be mathematically and logically some kind of perfect simulacrum of game architecture, it at least succeeds in defining a clear and useful ontology of terms (names, nouns) for various things we see all the time in our games code.

We should all appreciate Rust for bridging the world of abstract and balls deep mathematical proofs and a programming environment that normal (ish) people can use to write and run real code. You know, obviously Bevy does some crazy shit about taking a declarative (at this particular abstraction layer) definition of a Game's procedures (Systems) and state (Components) and cutting it up into archetypal tables, an optimized execution graph that runs in multiple threads, and the only price is 12 minute compile times. While I may not be using it in the near future (until there is enough LLM training data and Cranelift is replacing LLVM or whatever), I think it is pretty cool.