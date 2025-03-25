# matcha-game
Personal project. I like matcha. So I want to make a game on making matcha.

Currently working on the visuals. Quick mock up below.
![example_background3](https://github.com/user-attachments/assets/40b0cd50-95d2-4821-94d8-823ad6aae65a)
![background_test](https://github.com/user-attachments/assets/1a657d71-5f3f-4c3e-957a-4660e4879f06)



![char1_walk_anim](https://github.com/user-attachments/assets/115beea4-cb12-416c-b61f-9bcfb56af5d0) ![pearl_walk_anim](https://github.com/user-attachments/assets/32eb5619-2147-4a1a-9f76-c60880a3a3b8) ![soma_walk](https://github.com/user-attachments/assets/65ccaec8-7b8c-4e75-a20d-a4714fe4f0f7)

Priorities:
- The assets or visuals. Assets for drinks, then for other customer chars, then for styling the game up more, like chairs, tables, plants, etc. Oh, and of course the cafe itself. Outside and inside which might take a while. I want the player to be able to walk throughout the street, so further down the line, I would also like to design other houses. It's a lot, so I'll make sort of a schedule:
- Feb 7th: Have one customer done.
- Feb 11th: Have one drink (downscaled) done.
- Feb 12th: Having tables and chairs done.
- Feb 13th: Have exterior of cafe done.
- Feb 17th: Have interior of cafe done. (Only the register, windows, floor, tables and chairs.)
- Feb 20th: Have more of the interior done. (Menu?, plant decor)
- Feb 23rd: Street light?
- Feb 24th: Figure out how to have char move in environment.
- Feb 25th: Work on game plot. Game objectives.


# Update: March 3rd

Ok, I did not follow this timeline at all and just made a bunch of characters instead. I did brainstorm a bit of gameplay, but more of an overarching view, not of the specifics.


![all chars](https://github.com/user-attachments/assets/4af68262-7933-44dc-9fca-febaed2bedf7)


IT IS TIME TO BE STRICTER.
- Mar 13th: C++ chosen. Want to learn about C++, so screw it. I'll use Java or JavaScript for the next project. 
- Mar 15th: (1) One drink. Small. (2) Exterior of Cafe. (3) Pearl walking.
- Mar 17th: (1) Same drink, but large for closer gameplay. Deisgn matcha materials to be used. Figure out how you want the close-up section of the game to be (when you are making the drink). Will it be show on a table? What are the specifics there?
- Mar 19th: (1) Sky clouds. (2) Outside table. (3) Outside chair.
- Mar 21st: Have animations for Feyisola walking, Winnie sitting, and everybody else walking done. 
- Mar 23rd: Design bamboo whisk, chasen, and powder container. Need animations for these too for the gameplay.
- Mar 25th: Figure out how to trigger key events. So once you do something, it triggers a cutscene or dialogue.
- Mar 27th: Code gameplay -> Mixing the matcha, adding milk, y yeah.
- Mar 29th: Figure out game incentives. Is there a level up system? How can you make drinks better?
- Mar 31st: Yeah, just misc. The first two customers will be Timothy and Feyisola. Uhhh yeah. maybe after certain progress, the game just cuts to a demo screen LOL

A game like this has a lot of expand on. Story-wise, setting-wise, the leveling system, new ingredients/drinks, venue/decor. I think having all of the above working before adding more would be a really good base.


# Update: March 13th

I am using XCode for writing and running c++. I am using the SDL3 library for graphics. Have only gotten a background to load, but it's something. I have to figure out how I will organize my code.

-> Look into game states for switching between the startup menu and gameplay.
-> Move Winnie around with a basic controller.
-> UML design?
-> Look into what fundamental concepts of c++ I SHOULD be aware of, like pointers and memory management.
![background_test](https://github.com/user-attachments/assets/57379b41-1428-4f22-bce3-4559b9361f61)

# Update: March 20th

I have a very simple program that is able to just load a background, but I think implementing a controller to move a single char should be painless. I am just considering now that I should also have some class that pre-loads textures and such since I don't want things like pathnames to be present in major classes. I think major classes should refer to enums when they want a specific background, char., etc. texture. 

# Update: March 25th
Walking can now be done. Learned about pointers, not to instantiate objects in constructors, that was my bad. Declaring objects also automatically uses the default constructor!! But I now have a program where the user can walk Winnie in the left or right directions. Implemented using the MVC design pattern, I just have a SimpleMatchaGame project folder with a SimpleGameModel, SimpleGameView, and SimpleController classes. Programming wise, my main goal rn is to clean up the code implement a cleaner way to pre-load the textures without having to do so during gameplay. I am also thinking of abstracting the current classes to make the program more modular overall. For ex., separate controllers - one for walking, another for other types of input. Having a data structure that contains the animation sheets for every sprite, rather than burdening the sheet class with a bunch of sheets. I should also work on:
- clean code
- abstract data pre-loading and other classes
- create textures for environment and finish animations for other sprites
- Determine gameplay

From all of this, I see that I have underestimated the time it takes to just get Winnie to walk properly, lol. But it's a good basis!


https://github.com/user-attachments/assets/d573b9a3-2fee-4721-bc0d-69e511860703







