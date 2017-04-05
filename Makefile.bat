cl -c LevelGenerator/Polynome.cpp /EHsc 

cl -c LevelGenerator/Library/Point4.cpp  /EHsc 

cl -c LevelGenerator/Library/Platform.cpp  /EHsc 

cl -c LevelGenerator/Library/Library.cpp  /EHsc 

cl -c LevelGenerator/Instance/Instance.cpp  /EHsc 

cl -c LevelGenerator/Instance/PlatInstance.cpp  /EHsc

cl -c LevelGenerator/levelGenerator.cpp /EHsc

cl -c LevelGenerator/Polynome.cpp /EHsc

cl -c LevelGenerator/Instance/Position.cpp  /EHsc 

cl -c LevelGenerator/Instance/Vec3.cpp  /EHsc 

cl -c WorldGenerator/createWorld.cpp /EHsc

cl -c WorldGenerator/functions.cpp /EHsc

cl -c WorldGenerator/geometrie.cpp /EHsc

cl -c WorldGenerator/main.cpp /EHsc



cl -o level_generator.exe createWorld.obj Library.obj Platform.obj Point4.obj Polynome.obj Instance.obj PlatInstance.obj Position.obj Vec3.obj functions.obj geometrie.obj main.obj levelGenerator.obj /EHsc 
