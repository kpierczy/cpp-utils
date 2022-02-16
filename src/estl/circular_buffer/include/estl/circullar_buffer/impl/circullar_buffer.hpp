/** ==================================================================================================================================
 * @file     circullar_buffer.hpp
 * @author   jnk0le
 * @date     Wednesday, 5th January 2022 7:50:31 am
 * @modified Thursday, 3rd February 2022 12:01:58 pm
 * @project  Winder
 * @brief
 *    
 *    Implementation of the circular buffer class template
 *    
 * @source https://github.com/jnk0le/Ring-Buffer/blob/master/ringbuffer.hpp
 * @maintainer Krzysztof Pierczyk
 * ================================================================================================================================ */

#ifndef __ESTL_CIRCULAR_BUFFER_IMPL_CIRCULAR_BUFFER_H__
#define __ESTL_CIRCULAR_BUFFER_IMPL_CIRCULAR_BUFFER_H__

/* =========================================================== Includes =========================================================== */

#include "estl/circular_buffer.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace estl {

/* ====================================================== Public constructors ===================================================== */

template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::circular_buffer() :
    head(0),
    tail(0) 
{ }


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::circular_buffer(int dummy) {
    (void)(dummy); 
}

/* ======================================================== Public methods ======================================================== */

template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> void circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::producerClear(void) {
    
    // Head modification will lead to underflow if cleared during consumer read
    // doing this properly with CAS is not possible without modifying the consumer code
    consumer_clear();
    
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> void circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::consumer_clear(void) {
    tail.store(head.load(std::memory_order_relaxed), std::memory_order_relaxed);
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> bool circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::is_empty(void) const {
    return read_available() == 0;
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> bool circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::is_full(void) const {
    return write_available() == 0;
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> index_t circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::read_available(void) const {
    return head.load(index_acquire_barrier) - tail.load(std::memory_order_relaxed);
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> index_t circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::write_available(void) const {
    return buffer_size - (head.load(std::memory_order_relaxed) - tail.load(index_acquire_barrier));
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> bool circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::insert(T data) {
    
    index_t tmp_head = head.load(std::memory_order_relaxed);

    if((tmp_head - tail.load(index_acquire_barrier)) == buffer_size)
        return false;
    else {
        data_buff[tmp_head++ & buffer_mask] = data;
        std::atomic_signal_fence(std::memory_order_release);
        head.store(tmp_head, index_release_barrier);
    }
    return true;
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> bool circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::insert(const T* data) {
    
    index_t tmp_head = head.load(std::memory_order_relaxed);

    if((tmp_head - tail.load(index_acquire_barrier)) == buffer_size)
        return false;
    else
    {
        data_buff[tmp_head++ & buffer_mask] = *data;
        std::atomic_signal_fence(std::memory_order_release);
        head.store(tmp_head, index_release_barrier);
    }
    return true;
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> bool circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::insert_from_callback_when_available(T (*get_data_callback)(void)) {
    
    index_t tmp_head = head.load(std::memory_order_relaxed);

    if((tmp_head - tail.load(index_acquire_barrier)) == buffer_size)
        return false;
    else
    {
        //execute callback only when there is space in buffer
        data_buff[tmp_head++ & buffer_mask] = get_data_callback();
        std::atomic_signal_fence(std::memory_order_release);
        head.store(tmp_head, index_release_barrier);
    }
    return true;
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> bool circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::remove() {
    
    index_t tmp_tail = tail.load(std::memory_order_relaxed);

    if(tmp_tail == head.load(std::memory_order_relaxed))
        return false;
    else
        tail.store(++tmp_tail, index_release_barrier); // release in case data was loaded/used before

    return true;
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> size_t circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::remove(size_t cnt) {
    
    index_t tmp_tail = tail.load(std::memory_order_relaxed);
    index_t avail = head.load(std::memory_order_relaxed) - tmp_tail;

    cnt = (cnt > avail) ? avail : cnt;

    tail.store(tmp_tail + cnt, index_release_barrier);
    return cnt;
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> bool circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::remove(T& data) {
    return remove(&data); // references are anyway implemented as pointers
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> bool circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::remove(T* data) {

    index_t tmp_tail = tail.load(std::memory_order_relaxed);

    if(tmp_tail == head.load(index_acquire_barrier))
        return false;
    else
    {
        *data = data_buff[tmp_tail++ & buffer_mask];
        std::atomic_signal_fence(std::memory_order_release);
        tail.store(tmp_tail, index_release_barrier);
    }
    return true;
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> T* circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::peek() {

    index_t tmp_tail = tail.load(std::memory_order_relaxed);

    if(tmp_tail == head.load(index_acquire_barrier))
        return nullptr;
    else
        return &data_buff[tmp_tail & buffer_mask];
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> T* circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::at(size_t index) {

    index_t tmp_tail = tail.load(std::memory_order_relaxed);

    if((head.load(index_acquire_barrier) - tmp_tail) <= index)
        return nullptr;
    else
        return &data_buff[(tmp_tail + index) & buffer_mask];
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> size_t circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::write_buff(const T* buff, size_t count) {

    index_t available = 0;
    index_t tmp_head = head.load(std::memory_order_relaxed);
    size_t to_write = count;

    available = buffer_size - (tmp_head - tail.load(index_acquire_barrier));

    if(available < count) // do not write more than we can
        to_write = available;

    // maybe divide it into 2 separate writes
    for(size_t i = 0; i < to_write; i++)
        data_buff[tmp_head++ & buffer_mask] = buff[i];

    std::atomic_signal_fence(std::memory_order_release);
    head.store(tmp_head, index_release_barrier);

    return to_write;
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> size_t circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::write_buff(
    const T* buff,
    size_t count,
    size_t count_to_callback,
    void(*execute_data_callback)()
) {
    size_t written = 0;
    index_t available = 0;
    index_t tmp_head = head.load(std::memory_order_relaxed);
    size_t to_write = count;

    if(count_to_callback != 0 && count_to_callback < count)
        to_write = count_to_callback;

    while(written < count)
    {
        available = buffer_size - (tmp_head - tail.load(index_acquire_barrier));

        if(available == 0) // less than ??
            break;

        if(to_write > available) // do not write more than we can
            to_write = available;

        while(to_write--)
            data_buff[tmp_head++ & buffer_mask] = buff[written++];

        std::atomic_signal_fence(std::memory_order_release);
        head.store(tmp_head, index_release_barrier);

        if(execute_data_callback != nullptr)
            execute_data_callback();

        to_write = count - written;
    }

    return written;
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> size_t circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::read_buff(T* buff, size_t count) {

    index_t available = 0;
    index_t tmp_tail = tail.load(std::memory_order_relaxed);
    size_t to_read = count;

    available = head.load(index_acquire_barrier) - tmp_tail;

    if(available < count) // do not read more than we can
        to_read = available;

    // maybe divide it into 2 separate reads
    for(size_t i = 0; i < to_read; i++)
        buff[i] = data_buff[tmp_tail++ & buffer_mask];

    std::atomic_signal_fence(std::memory_order_release);
    tail.store(tmp_tail, index_release_barrier);

    return to_read;
}


template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> size_t circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::read_buff(
    T* buff,
    size_t count,
    size_t count_to_callback,
    void(*execute_data_callback)()
) {
    size_t read = 0;
    index_t available = 0;
    index_t tmp_tail = tail.load(std::memory_order_relaxed);
    size_t to_read = count;

    if(count_to_callback != 0 && count_to_callback < count)
        to_read = count_to_callback;

    while(read < count)
    {
        available = head.load(index_acquire_barrier) - tmp_tail;

        if(available == 0) // less than ??
            break;

        if(to_read > available) // do not write more than we can
            to_read = available;

        while(to_read--)
            buff[read++] = data_buff[tmp_tail++ & buffer_mask];

        std::atomic_signal_fence(std::memory_order_release);
        tail.store(tmp_tail, index_release_barrier);

        if(execute_data_callback != nullptr)
            execute_data_callback();

        to_read = count - read;
    }

    return read;
}

/* ======================================================= Public operators ======================================================= */

template<
    typename T,
    size_t buffer_size,
    bool fake_tso,
    size_t cacheline_size,
    typename index_t
> T& circular_buffer<T, buffer_size, fake_tso, cacheline_size, index_t>::operator[](size_t index) {
    return data_buff[(tail.load(std::memory_order_relaxed) + index) & buffer_mask];
}

/* ================================================================================================================================ */

} // End namespace Containers

#endif
