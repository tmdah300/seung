#include <iostream>
#include <vector>
#include "MGameLoop.hpp"

using namespace MuSoeun;

namespace MuSoeun
{
    class Object
    {
    public:
        int x, y;  // position 33 40
        bool active = true;

        virtual void Render(char* screenBuf, int width)
        {
            if (active)
            {
                if (x >= 0 && y >= 0) {
                    screenBuf[x + y * (width + 2)] = '*';
                }
            }
        }
    };

    
    class SnakeBody : public Object
    {
    public:
        void Render(char* screenBuf, int width) override
        {
            if (active)
            {
                if (x >= 0 && y >= 0) {
                    screenBuf[x + y * (width + 2)] = '*';
                }
            }
        }
    };

    class Scene
    {
    public:
        int width;
        int height;
        std::vector<Object> objList;

        //screenBuf[width + (width * height)];

        char* screenBuf;

        void InitScreenBuf()
        {
            screenBuf = new char[(width + 2) * (height + 2) + 1];  // 끝부분 벽 +2 개행문자 +1

            for (int j = 0; j < width + 1; j++) {
                screenBuf[j] = '-';
            }
            screenBuf[width + 1] = '\n';

            // 중간 줄에 '|' 문자와 빈 공간을 채웁니다.
            for (int i = 1; i < height + 1; i++) {
                screenBuf[i * (width + 2)] = '|'; //12
                for (int j = 1; j < width; j++) {
                    screenBuf[j + i * (width + 2)] = ' ';  // 빈 공간으로 채웁니다. 13~21
                }
                screenBuf[width + i * (width + 2)] = '|'; //22
                screenBuf[width + 1 + i * (width + 2)] = '\n';  // 각 줄의 끝에 개행 문자를 삽입합니다.24 36
            }

            // 마지막 줄에 '-' 문자를 채웁니다.
            for (int j = 0; j < width + 1; j++) {
                screenBuf[j + (height + 1) * (width + 2)] = '-';
            }
            screenBuf[(width + 2) * (height + 2) - 1] = '\0';  // 문자열의 끝에 널 문자를 삽입합니다.
        
        }
        void ReleaseScreenBuf()
        {
            if (screenBuf != nullptr)
            {
                delete(screenBuf);
            }
        }

        void DrawScreenBuf()
        {
            system("cls");
            for (Object& obj : objList) {
                obj.Render(screenBuf, width);
            }
            std::cout << screenBuf;
        }
    };

    class Component //Unity MonoBehavior
    {
    public :
        void Start();
        void Update();
    };
}

int main()
{
    Scene myScene; //scene 생성
    myScene.width = 10;
    myScene.height = 10;
    myScene.InitScreenBuf(); //scene 10,10 초기화

    Object obj1;  // position 3,3 Object1생성
    obj1.x = 3;
    obj1.y = 3; 
    myScene.objList.push_back(obj1); //objList에 추가

    SnakeBody obj2;  // position 3,3 Object2생성
    obj2.x = 5;
    obj2.y = 5;
    obj2.active = false; //Object2생성 active는 false
    myScene.objList.push_back(obj2);//objList에 추가

    
    myScene.DrawScreenBuf(); //object1만 출력


    SnakeBody obj3;// position 6,6 object3 생성
    obj3.x = 6;
    obj3.y = 6;
    myScene.objList.push_back(obj3); //objList에 추가


    myScene.DrawScreenBuf(); //object1과 object3 출력


    myScene.ReleaseScreenBuf();

    return 0;



}

