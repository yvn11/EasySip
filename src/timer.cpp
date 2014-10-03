/*
 * src/timer.cpp
 */
#include "timer.h"

namespace EasySip
{
    bool operator== (struct itimerval &a, struct itimerval &b)
    {
        return timercmp(&a.it_interval, &b.it_interval, ==)
                && timercmp(&a.it_value, &b.it_value, ==);
    }

    bool operator!= (struct itimerval &a, struct itimerval &b)
    {
        return !(timercmp(&a.it_interval, &b.it_interval, ==)
                && timercmp(&a.it_value, &b.it_value, ==));
    }

    std::ostream& operator<< (std::ostream &o, struct timeval &a)
    {
        return o << "[" << a.tv_sec << ", " << a.tv_usec << "]";
    }

    std::ostream& operator<< (std::ostream &o, struct itimerval &a)
    {
        return o << a.it_value << " : " << a.it_interval;
    }

    std::ostream& operator<< (std::ostream &o, struct timespec &a)
    {
        return o << "[" << a.tv_sec << ", " << a.tv_nsec << "]";
    }

    std::ostream& operator<< (std::ostream &o, struct itimerspec &a)
    {
        return o << a.it_value << " : " << a.it_interval;
    }
} // namespace EasySip
