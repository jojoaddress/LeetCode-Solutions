/**
 ** This file is part of the hxkBootloder project.
 ** Copyright (C) Hua Xin Ke Medical Technology Co., LTD
 ** All Rights Reserved.
 ** Unauthorized copying of this file, via any medium is strictly prohibited
 ** Proprietary and confidential
 **
 ** Writtenby Dewu Lv <d.lv@cardiacsci.com>, 2022/06/15
 **/


#ifndef __RingBuffer_H
#define __RingBuffer_H

#include <memory.h>
#include <algorithm>

/**
 * @note  Lock-less ring buffer, is OK when when has only one producer and consumer
 */
template<typename T> class RingBuffer
{
public:
    /**
     * create a RingBuffer with space for up to size elements.
     */
    explicit RingBuffer(size_t size)
            : size(size), begin(0), end(0), wrap(false)
    {
        buffer = new T[size];
    }

    /**
     * copy constructor
     */
    RingBuffer(const RingBuffer<T> &rb)
    {
        this(rb.size);
        begin = rb.begin;
        end = rb.end;
//        size = rb.size;
        wrap = rb.wrap;
        memcpy(buffer, rb.buffer, sizeof(T) * size);
    }

    /**
     * Destruction
     */
    ~RingBuffer()
    {
    }

    /**
     * @brief push one data into the end of buffer
     * @param data
     * @return true if data have been pushed into the buffer, otherwise, false
     */
    bool push(const T &data)
    {
        bool ret = false;
        if (getFree())
        {
            ret = true;
            buffer[end] = data;
            end = (end + 1) % size;

            if (begin == end)
            {
                wrap = true;
            }
            else if (wrap)
            {
                /* drop old data */
                begin = end;
            }
        }
        return ret;
    }

    /**
     * @brief pop first data from buffer
     * @param n number of data to pop from buffer
     * @return number of has been pop from the buffer
     */
    T pop(size_t n = 1)
    {
        n = std::min(n, getDataSize());

        if (n == 0)
        {
            return n;
        }

        if (wrap)
        {
            wrap = false;
        }

        begin = (begin + n) % size;
        return n;
    }

    /**
     * @brief get data at the specific index
     * @param index the index
     * @return the data
     */
    T at(size_t index)
    {
        return buffer[(begin + index) % size];
    }

    /**
     * @brief write a buffer of data into the ring buffer
     * @note if the ring buffer is full, no more data will write to the buffer
     * @param data: pointer to the date need to push into the buffer
     * @param n: number of the data
     * @return data number write to the buffer
     */
    size_t write(const T *data, size_t n)
    {
        n = std::min(n, getFree());

        if (n == 0)
        {
            return n;
        }

        //ADD_
        if(data[1] == 0xEE)
        {
        	int i=100;
        }

        const size_t first_chunk = std::min(n, size - end);
        memcpy(buffer + end, data, first_chunk * sizeof(T));
        end = (end + first_chunk) % size;

        if (first_chunk < n)
        {
            const size_t second_chunk = n - first_chunk;
            memcpy(buffer + end, data + first_chunk, second_chunk * sizeof(T));
            end = (end + second_chunk) % size;
        }

        if (begin == end)
        {
            wrap = true;
        }

        return n;
    }

    /**
     * @brief read specified number of data from the ring buffer
     * @param dest: buffer to hold the read data
     * @param n: number of date need to  read
     * @return number of the read data
     */
    size_t read(T *dest, size_t n)
    {
        n = std::min(n, getDataSize());

        if (n == 0)
        {
            return n;
        }

        //ADD_
        if(dest[1] == 0xEE)
        {
        	int i=100;
        }

        if (wrap)
        {
            wrap = false;
        }

        const size_t first_chunk = std::min(n, size - begin);
        memcpy(dest, buffer + begin, first_chunk * sizeof(T));
        begin = (begin + first_chunk) % size;

        if (first_chunk < n)
        {
            const size_t second_chunk = n - first_chunk;
            memcpy(dest + first_chunk, buffer + begin, second_chunk * sizeof(T));
            begin = (begin + second_chunk) % size;
        }
        return n;
    }

    /**
     * @brief copy data from the ring buffer but didn't pop the data
     * @param dest buffer to store the data
     * @param n number of data to copy
     * @return number of data has been copied
     */
    size_t copy(T *dest, size_t n)
    {
        n = std::min(n, getDataSize());

        if (n == 0)
        {
            return n;
        }

        const size_t first_chunk = std::min(n, size - begin);
        memcpy(dest, buffer + begin, first_chunk * sizeof(T));

        if (first_chunk < n)
        {
            const size_t second_chunk = n - first_chunk;
            memcpy(dest + first_chunk, buffer, second_chunk * sizeof(T));
        }
        return n;
    }

    /**
     * @brief get the number of data in the buffer
     * @return number of data in the buffer
     */
    size_t getDataSize()
    {
        auto e = end;
        auto b = begin;
        if (e == b)
        {
            return wrap ? size : 0;
        }
        else if (e > b)
        {
            return e - b;
        }
        else
        {
            return size + e - b;
        }
    }

    /**
     * @brief get the free space of the buffer
     * @return number of free space
     */
    size_t getFree()
    {
        return size - getDataSize();
    }

    /**
     * @brief clear the buffer
     */
    void clear()
    {
        wrap = false;
        begin = end;
    }

private:
    T *buffer;
    size_t size;
    size_t begin;
    size_t end;
    bool wrap;
};

#endif  // __RingBuffer_H
