/*
 * include/parameter.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include "utils.h"
#include "except.h"

namespace EasySip
{
    class Buffer
    {
    protected:

        char *data_;
        size_t len_;

    public:
        Buffer(size_t len) : len_(len)
        {
            data_ = new char[len_];
            memset(data_, 0, len_);
        }

        ~Buffer()
        {
            len_ = 0;
            if (data_) delete data_;
            data_ = 0;
        }

        char* data()
        {
            return data_;
        }

        size_t len()
        {
            return len_;
        }
    };
} // namespace EasiSip
