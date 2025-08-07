# Real Speak
## 1. Inheritance
Thanks to OOP we often hear there is an example that goes like this:
```
class Animal {
    virtual String speak()
}


class Dog: Animal {
    String Speak() {
        return "woof"
    }
}

class Cat: Animal {
    A field_a;

    String Speak() {
        return "meow"
    }
}
```
## 2. Tagged Fat Union
What I actually do is this:
```rust
enum AnimalType {
    Dog,
    Cat,
}
impl AnimalType {
    fn speak(self) -> String {
        match self {
            AnimalType::Dog => "woof",
            AnimalType::Cat => "meow",
        }
    }
}

struct Animal {
    ty: AnimalType,
    field_a: A,
}
```
Which is a great for just geting the job done but I'd be lying if I said there weren't some match statements with 100 cases.
Of course they can be broken up with the use of traits but I didn't want to.

## 3. SoA
This is probably how I'd probably prefer to do it (shown with static array):
```rust
const MAX_ANIMALS: usize = 64000;
pub struct Animals {
    types: [Option<AnimalType>; MAX_ANIMALS],
    field_a: [Option<A>; MAX_ANIMALS],
}
```

## 4. All Loaded at Runtime
Or truly, loading all logic from disk so the game has unlimited mod support:
```
// ???
// Lua shit
```
Truly I think this depends completely. Can it be completely data driven - serialize and deserialize. Does it need to run scripts? Then we would become API maintainers.

===
This relates to [my game Gnomes](https://store.steampowered.com/app/3133060/Gnomes/) as it approaches 50,000 sales. 2. is in production. I think 3. would assist me to design a proper save format AS WELL AS improve performance for [peoples crazy lategame builds]() (although that has more to do with it being stored in a HashMap though the solution would BECOME this). I think 4. would be the ultimate dream of a game but takes planning.
