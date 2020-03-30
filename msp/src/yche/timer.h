#ifndef __TIMER_H__
#define __TIMER_H__

#include <iostream>
//#include <boost/format.hpp>
#include <chrono>

class Timer {
public:
    Timer() : beg_(clock_::now()) {}

    void reset() { beg_ = clock_::now(); }

    double elapsed() const {
        return std::chrono::duration_cast<second_>
                (clock_::now() - beg_).count();
    }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};
//inline void display_time(Timer & tmr){
//    cout << boost::format("elapsed time: %s") % tmr.elapsed() << endl;
//}
#endif
