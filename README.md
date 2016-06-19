# GoodBird
![alt tag](/screenshots/1.png)

A clone of angry bird game written in C++. I develope it for practicing class design. It is intented to be cross-platform game but I haven't tested it on linux because my computer is broken. Maybe need some modify to cmake script.(I hate to write cmake script...) The game logic is seperated from rendering. Therefore, it is able to port to any rendering APIs without modifying.
### Build
The first two steps is needed if you are not able to run Goodbird.exe

1. Download SFML library, compile it and move include and lib into thirdparty/SFML. And move DLLs into bin

    If you aren't doing wrong here. you have thirdyparty/SFML/include/SFML/Config.hpp and thirdyparty/SFML/lib/libsfml-xxxxxx.a and bin/sfml-xxxxx-2.dll
2. Download Box2D library, compile it and move include and lib into thirdparty/Box2D (NOTE: You might need to add -DCMAKE_CXX_FLAGS=c++0x). 

    If you aren't doing wrong here. you have thirdyparty/Box2D/include/Box2D/Box2D.h and thirdyparty/Box2D/lib/libBox2D.a
3. goto bin directory and make(Windows)

        cmake .. -G "MinGW Makefiles"
        mingw32-make

    goto bin directory and make (Linux)
    
        cmake ..
        make
4. run GoodBird

### A Note for Porting to Different Rendering APIs
I provide SFML render interface here. But you can use your own.

### A Note for Adding New Entity
You can inherit from Entity, or PhysicsEntity if you need Box2D's help. There are something you need to take care

1. It's necessary to implement draw() function. please take Bird.cpp as reference
2. If you need to update your entity(inherited from PhysicsEntity) every frame. please implement update() function. And don't forget to call base class's update

        void update(double globalTime)
        {
        	PhysicsEntity::update(globalTime);
        	// do your things
        }

3. startContact and endContact is called when collision happens. It's useful if you need to do something when the event take place. you can implement it