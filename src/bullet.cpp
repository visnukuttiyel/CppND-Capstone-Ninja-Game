#include "bullet.h"
#include <iostream>
#include <math.h>


template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 

    // perform queue modification under the lock
    std::unique_lock<std::mutex> uLock(_mutex);  // lock_guard cant be used here since lock needs to be temporarily released during wait

    // !_queue.empty()  gaurds againist spurious wakeups or random wakeups
    _condition.wait(uLock, [this] { return !_queue.empty(); }); // pass unique lock to condition variable

    // remove last vector element from queue
    T msg = std::move(_queue.back());
    _queue.pop_back();
    return msg; // will not be copied due to return value optimization (RVO) in C++
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.

        // perform vector modification under the lock
        std::lock_guard<std::mutex> uLock(_mutex);  // lock is released once ulock gets out of scope

        // add vector to queue
        // std::cout << "   Message " << msg << " has been sent to the queue" << std::endl;
        _queue.clear();
        _queue.emplace_back(std::move(msg));
        _condition.notify_one(); // notify client after pushing new Vehicle into vector

}

void Bullet::Update() {

threads.emplace_back(std::thread(&Bullet::UpadatePosition, this));

}

float Bullet::BangBangControl(float const error)
{
    float corrective_action {0.0F};

    if (error > 0)
    {
        corrective_action = 1.0f;
    } else
    {
        corrective_action = -1.0f;    
    }

    return corrective_action;

}

void Bullet::UpadatePosition()
{
     std::chrono::time_point<std::chrono::system_clock> lastUpdate;
    while(true)
    {
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        
        long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        if (timeSinceLastUpdate >= 3500)
        {
            theta = atan((target_position_.y-current_position.y)/(target_position_.x-current_position.x));
            b = (theta);
            a = current_position.y - b*current_position.x;
            current_position.x = current_position.x + speed*cos(theta)*BangBangControl(target_position_.x-current_position.x);
            current_position.y = EvaluateY(current_position.x);
            lastUpdate = std::chrono::system_clock::now();

        }
        
        bullet_msg_queue_.send(std::move(current_position));
    }
    
}
   
float Bullet::EvaluateY(float x)
{
    return (a + b*x);
 }

void Bullet::Reset()
{
    body.clear();
    counter = 0;
    current_position = start_position_;
    theta = atan((50-current_position.y)/(50-current_position.x));
    body.emplace_back(SDL_Point{static_cast<int>(current_position.x), static_cast<int>(current_position.y)});

}

void Bullet::SetTarget(int const &target_x, int const &target_y)
{
        target_position_.x = target_x;
        target_position_.y = target_y;
}

 std::vector<SDL_Point> Bullet::GetBulletBody()
 {
    Point point = bullet_msg_queue_.receive();
    
    body.emplace_back(SDL_Point{static_cast<int>(point.x), static_cast<int>(point.y)});
        counter++;
        if (counter > trail_length)
        {
            counter--;
            body.erase(body.begin());
        } 
    return body;
 }
