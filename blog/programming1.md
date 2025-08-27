# Welcome to Programming
Congratulations on deciding not to be poor. This series is to give the new homies some (very opinionated and ranty) background on the space. Im gonna boost you with like 10 years of knowledge in 4 posts but you will still need to put in the work and practice.

The good news is you can learn something new these days in a fraction of the time by asking an LLM the right questions. They can give very specific answers... 'explain this code' 'whats the syntax for ...' 'set me a task to test my understanding of X' etc. So there are no excuses any more. 

Its never been easier to learn anything. Those who can are able to put in the time and unstick themself via LLM dialogue will be quickly separated from those who can't

Anyway on with the first post so you can inform yourself of what language to learn...


# Programming Language Tier List
## S Tier
* C
* Rust
* HTML
* JavaScript
## A Tier
* Go
* TypeScript
* C++
## B Tier
* Bash
* Zig
## Brainrot Tier
* Python
* C#
* Java
## Not Mentioned
* (Probably not relevant enough to have a developed enough ecosystem, or I've no experience, or just simply 'y tho')


# A Look into each Language
## C - The King
C is the most important programming language of all time. Everything today is written in it. Your OS, your router, your applications, the runtime for your shitty managed languages, all C. C was conceived in Bell Labs in 1972 in an act of Genius by Dennis M. Ritchie and has scarcely been improved on since (though many have tried). 

Even though many refuse to learn C it is actually easier to fully understand than any other language and declining to understand it results in a failure to perceive the myriad ways it shapes all other computer systems implicitly.
t.

Its not to say its without its quirks being 53 years old but for both its pareto tradeoff and historical entrenchment there is no language that is more important to learn or effective for what it is.

It doesnt have to be your first language but I think it is ignorant not to spend 1 day learning C as an established developer. I can't imagine it. I don't think that person will have a general fluency in tools, operating system interaction, systems in general
Special shoutout to Raylib and SDL3.

### Strengths
* Performance
* Simplicity
* You are forced to use it anyway so in many ways its simpler to include libraries when you use it directly (everything else sits *atop* it)
* Fairly portable, easier to cross-compile etc.
* Fast compile times
### Weaknesses
* Standard library sucks (just write/vibe code your own utilities)
* No package manager - on Linux its fine, on Windows its hell to get libraries working. *Good luck and have fun.*
* Some quirks
* Header files, segfaults


## Rust - The Prodigy
Rust is my daily driver. It extends to a much higher level than C without compromising performance, though this comes at the cost of a more difficult learning curve than any other language on this list (Note that Haskell was not mentioned on this list). 

Note: You won't understand why Rust is the way it is until you try to learn C++ as in many ways its C++ remade from the ground up, slashing its backward compatibility with C.

### Strengths
* Excellent package manager (cargo)
* Safety (it sounds soy-pilled but really its good that more errors are ruled out at compile time. Very, very good)
* Just as good performance as C
* Good move semantics and multithreading

### Weaknesses
* Learning cliff
* Slow compile times
* Ecosystem is only just tolerable. Its improving and you can bridge the gap with C FFI.

## HTML
I'm kind of having a laugh with this one but its actually pretty underrated I feel. Its so widely adopted that we aren't conscious of it anymore. It was invented 1993 by Tim Berners-Lee at CERN. (Not Bell Labs!!) It was really a visionary technology to enable the World Wide Web, a decentralized mesh of hyperlinks between peoples' personal pages (which I would like to see it get back to). Anyway it is completely apt for this task, as simple markup language that allows you to define UI elements, buttons, images, links, even embedding scripts and canvas (WebGL) etc. It doesn't really have any shortcomings and when it comes down to it, its just bytes on a wire, i.e. plain text, so even though its usually used through layers of frameworks these days it is very easy to manipulate and substitute templates into from any sort of setup, even C running on bare metal, for example.

## JS - The Joker
It does have some absolutely ridiculous semantics but there is no getting past the fact that it is THE ultimate platform for deployment. Thats just what the web has become: a JavaScript application delivery system. And the ecosystem is completely comprehensive, if you just want to get something done and in the hands of users, JS eliminates the need to reach for 90% of other languages e.g. 'managed brainrot' because it is *just superior* (when performance and safety are not needed). And if you want to quickly one shot some vibe coding prototype just ask for a single html file, embedded JS using p5.js (2d) or three.js (3d) and be amazed as it downloads those libraries from the cdn directly into the code.

### Strengths
* Ultimate portability
* If you need a high level user application where performance and safety aren't critical its just superior to all other options (Note: it is *not* suitable for other applications)
* Really, really good debugger (built into Web Browser F12)
* Zero dependencies to set it up for development, you have a web browser already

### Weaknesses
* Its the first language on this list which is interpreted and managed (Garbage Collected). Its definitely the best one by far (except for Go), but in general these are weak languages, suffering performance from the fact that its running in a simulated computer on top of an actual computer, which is done to achieve scriptable hotreloading/sandboxing
* Even though someone with less than 15 minutes of programming experience would disagree, Dynamic typing is a weakness, the program can fail at runtime from obvious mistakes that should have been caught. You don't want to engineer a large system in JavaScript
* It has some ridiculous semantics (include holy trinity meme)


## Go
Go was made in 2009 inside Google, by Rob Pike, Ken Thompson et al. because of a shared hatred of C++. Go is for one task and that is Backend development. It is really quite good for this, having specific features (GoRoutines) and making reasonable design decisions. Its learning curve is soft. While it is managed, meaning its performance is a tier below C/Rust, it is not interpreted and in general it is a far, far better language than the other managed/interpreted langauges: Far better performance, static typing, decent ecosystem. A good early language to learn as well. It is a lot like C, one of the only attempts at improving C that actually went well.
### Strengths
* Easy learning curve
* Simple language
* Some good tools, Ok package system
* Ok performance for its weightclass
* If you want a cruizy job as a backend developer, just learn this, I guarantee you that your job will suck less because of it than other competing options. And I think its still quite in demand.

### Weaknesses
* Its more specialized for backends, its weird to make a game in this even if its a nice tradeoff point of difficulty for a beginner. Maybe just make the game in Javascript, thank me later
* Performance: you will probably get bit eventually still by GC pauses depending on your application. Its not that bad though, but please dont try to make Minecraft in a language like this. Oh wait...


## TypeScript
Now I am not an authority on TypeScript by any means. 


## C++
https://en.wikipedia.org/wiki/Criticism_of_C%2B%2B

Whats the deal
A lot of serious discussion of C++ reads like a joke. No, you really need 17 different constructors. 
Seriously I need to find that youtube video.
The errors. The intersectionality of different features. The compile time if you use the standard library. The compile time if you use boost. My word.

But it IS a superset of C. You can compile C in it. So you can use it for just the only needed features which is Operator overloading if you're making a game because vectores will save a lot of unneeded complexity, as well as maybe some generic containers even though you shouldnt use STL ones for the above reason (its not hard to write a std::vec equivalent though) 
It is even possible to get these in C using stb_ds although the errors on that arent very clear if you use it wrong.
Im pretty sure your errors would instantly get worse. No matching overloaded function found (did C have function overloading? dont remember). But C has implicit declaration of function which is also bad.

Wouldnt use classes either - forced public and private members into the header file .....
Definitely wouldn't use iostream, stdio was completely fine. Printf over cout, etc.

So yea its a tough one and as I say, look how they cooked on the initialization semantics and shit here and you will understand why rust is as complicated as it is (its not nearly as complicated as this and it also stepped clear of the brainrot)

In some sense it is strictly more capable than C, which amazes how it could be executed so poorly, that it is largely considered to be worse.

C++ also has brainrot, see next section

## Forgot Bash
Its unhinged. Learn linux. It has some garbage semantics like spaces mattering in the case of 'export A='mystring', thats an error if you put spaces around the = sign. BUT its the best at what it does.

# Brainrot Languages
These all added OOP paradigms and classes. So thats what I mean by brainrot. C++ added it too. The thing is it was a craze in the 90s. New languages don't have it anymore. It was a 20 year detour. Maybe its better for enterprise scaled development which I just wouldn't understand, idk. It all comes back to inheritance which is kind of a brainrot way of structuring programs. Beginners can kind of grok it which is why I think it took off. You kind of think that it will turn into good code if you directly map your human conceptual space into how the code is structured. Newsflash: that is actually not true. As well as that we had academics shilling it hard for 20 years and they developed all kinds of dumb-as-fuck rules or 'design patterns'that were supposedly the magical secrets to programming wisdom, that all break down under scrutiny.
* big 5 or whatever the fuck it is
* Include casey rants etc.

There are all actually good patterns to deal with these various scenarious which will be discussed in due course.

The only way to really learn something is from trying to do it. Academics never tried to do anything. The academic content is a long  game of chinese whispers through the ages. Back in the 70sthe programmers were just really good and they were writing assembly for decades, that was how they learned. There wasn't some false idea of design patterns being taught to all the newbies that they then had to unlearn.

We are only just coming to our senses now as none of the new languages include this shit.
Dont get me wrong, I still 'sometimes' do an OOP: its when Im refactoring how some internal structure works. For example in Gnomes, changing how History works so that its bounded and has a limit. You keep the interface the same and make the internals private so that it triggers breakage in all reference points, then you can fix all those (not something you can do in a dynamic language by the way). Thats the main idea in OOP thats actually good. Not inheritance. Inheritance can be done with function pointers or a switch statement. 

* oop is bad youtube video etc.


## Java
Java was invented in 1995. Its kind of a parallel Ecosystem to C because it is all virtualized, i.e. It is an interpreted language. So it is pretty portable. It was the first of its kind. JavaScript actually just apes the name of it. It actually doesn't feel that bad to use, its kind of OK but its not relevant anymore. You take the performance penalty of being interpreted, you should use JavaScript for the superior portability and integration, Go if you are doing a backend or just something better. Its all OOP brainrot anyway.

## C#
Literally Microsoft copied Java. Again it feels decent to use, LINQ is nice or whatever. But im warning you now, stay away from Microsoft ecosystem. Stay away from Unity its too bloated. I mean check it out if you want. But I could see doing something in Monogame with C# if you wanted something a bit more on the easier side. But you will hit the performance wall with it.

## Python
Its used for ML for some unexplainable reason. Python2/Python3 is aids. No types. Its like JavaScript without JavaScripts massive killer feature of being what the entire web runs on. Its performance is 100x slower than native speed and probably 10x slower than JavaScript, its the slowest language there is.
Like JavaScript its a sloppy language with no types, it will crash at runtime because you put too many spaces or used spaces instead of tabs for your indentation.
Please never use this. I think its taught as a first language because it has minimal syntax. Get over it, it takes 3 seconds to ask an LLM a syntax query
The package management is absolute dogshit and very brittle. You will know what I mean if you ever try.







I've already changed my recommendation for first language.
JS -> Go -> C -> C++ -> Rust
