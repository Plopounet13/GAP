cl -o Polynome.obj -c Polynome.cpp /EHsc 

cl -o Library/Point.obj -c Library/Point.cpp  /EHsc 

cl -o Library/Platform.obj -c Library/Platform.cpp  /EHsc 

cl -o Library/Library.obj -c Library/Library.cpp  /EHsc 

cl -o Instance/Instance.obj -c Instance/Instance.cpp  /EHsc 

cl -o Instance/PlatInstance.obj -c Instance/PlatInstance.cpp  /EHsc 

cl -o Instance/Position.obj -c Instance/Position.cpp  /EHsc 

cl -o Instance/Vec3.obj -c Instance/Vec3.cpp  /EHsc 

cl -o main.obj -c main.cpp  /EHsc 

cl -o patate main.obj Library.obj Platform.obj Point.obj Polynome.obj Instance.obj PlatInstance.obj Position.obj Vec3.obj   /EHsc
