#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include "SDL.h"
#include <cmath>
#include <chrono>
#include "battlefield.h"
#include <mutex>
#include <deque>
#include <condition_variable>
//#include "message.h"



constexpr float kPHI{3.14};
struct Point
{
    float x;
    float y;
};



template <class T>
class MessageQueue
{
public:
    T receive();
    void send(T &&msg);
private:
    std::mutex _mutex;
    std::condition_variable _condition;
    std::deque<T> _queue;
};


class Bullet : public BattleField 
{
public:
    enum class Direction
    {
        kUp,
        kDown,
        kLeft,
        kRight
    };

    Bullet(int pos_x, int pos_y)
    {
        start_position_.x = pos_x;
        start_position_.y = pos_y;
        Reset();
        
    }

    void SetTarget(int const &target_x, int const &target_y);

    std::vector<SDL_Point> GetBulletBody();
    void Update();



    float life_time{2}; // 2s life time of the bullet
    float speed{0.05f};
    float theta{kPHI / 4};
    float const trail_length{20};
    float const pos_error{0.1};

    Point current_position;
    float a{0};
    float b{0};
    int counter{0};

private:
    float BangBangControl(float deltatheta);
    void Reset();
    void UpadatePosition();
    float EvaluateY(float x);

    Point start_position_;
    Point target_position_;
    std::vector<SDL_Point> body;
    MessageQueue<Point> bullet_msg_queue_;
};

#endif
