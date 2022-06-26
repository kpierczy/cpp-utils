/** ==================================================================================================================================
 * @file       circular_buffer.hpp
 * @author     jnk0le
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Wednesday, 5th January 2022 7:50:31 am
 * @modified   Thursday, 3rd February 2022 12:00:01 pm
 * @project    cpp-utils
 * @brief      Header file declaring static circular buffer
 *    
 * @source https://github.com/jnk0le/Ring-Buffer/blob/master/ringbuffer.hpp
 * ================================================================================================================================ */

#ifndef __ESTL_CIRCULAR_BUFFER_H__
#define __ESTL_CIRCULAR_BUFFER_H__

/* =========================================================== Includes =========================================================== */

#include <stdint.h>
#include <stddef.h>
#include <limits>
#include <atomic>

/* ========================================================== Namespaces ========================================================== */

namespace estl {

/* ========================================================= Declarations ========================================================= */

/**
 * @brief Lock free, with no wasted slots ringbuffer implementation
 * 
 * @tparam T 
 *    Type of buffered elements
 * @tparam buffer_size 
 *    Size of the buffer. Must be a power of 2.
 * @tparam fake_tso 
 *    Omit generation of explicit barrier code to avoid unnecesary instructions in tso (total store order) 
 *    scenario (e.g. simple microcontrollers/single core)
 * @tparam cacheline_size 
 *    Size of the cache line, to insert appropriate padding in between indexes and buffer
 * @tparam index_t 
 *    Type of array indexing type. Serves also as placeholder for future implementations.
 */
template<
    typename T,
    size_t buffer_size,
    bool fake_tso = false,
    size_t cacheline_size = 0,
    typename index_t = size_t
> class circular_buffer {

public: /* ------------------------------------------------- Public constructors -------------------------------------------------- */

    /**
     * @brief Default constructor, will initialize head and tail indexes
     */
    circular_buffer();

    /**
     * @brief Special case constructor to premature out unnecessary initialization 
     *    code when object is instatiated in .bss section
     * @param dummy 
     *    ignored  
     * @warning If object is instantiated on stack, heap or inside noinit section 
     *    then the contents have to be explicitly cleared before use
     */
    circular_buffer(int dummy);

public: /* --------------------------------------------------- Public methods ----------------------------------------------------- */

    /**
     * @brief Clear buffer from producer side
     * @warning Function may return without performing any action if consumer tries
     *     to read data at the same time
     */
    void producer_clear(void);

    /**
     * @brief Clear buffer from consumer side
     */
    void consumer_clear(void);

    /**
     * @brief Check if buffer is empty
     * @returns
     *    True if buffer is empty
     */
    bool is_empty(void) const;

    /**
     * @brief Check if buffer is full
     * @returns
     *    True if buffer is full
     */
    bool is_full(void) const;

    /**
     * @brief Check how many elements can be read from the buffer
     * @returns
     *    Number of elements that can be read
     */
    index_t read_available(void) const;

    /**
     * @brief Check how many elements can be written into the buffer
     * @returns
     *    Number of free slots that can be be written
     */
    index_t write_available(void) const;

    /**
     * @brief Inserts data into internal buffer, without blocking
     * @param data 
     *    element to be inserted into internal buffer
     * @returns
     *    True if data was inserted
     */
    bool insert(T data);

    /**
     * @brief Inserts data into internal buffer, without blocking
     * @param[in] data 
     *    Pointer to memory location where element, to be inserted into internal buffer, is located
     * @returns
     *    True if data was inserted
     */
    bool insert(const T* data);

    /**
     * @brief Inserts data returned by callback function, into internal buffer, without blocking
     *
     * This is a special purpose function that can be used to avoid redundant availability checks in case when
     * acquiring data have a side effects (like clearing status flags by reading a peripheral data register)
     *
     * @param get_data_callback Pointer to callback function that returns element to be inserted into buffer
     * @returns
     *    True if data was inserted and callback called
     */
    bool insert_from_callback_when_available(T (*get_data_callback)(void));

    /**
     * @brief Removes single element without reading
     * @returns
     *    True if one element was removed
     */
    bool remove();

    /**
     * @brief Removes multiple elements without reading and storing it elsewhere
     * @param cnt Maximum number of elements to remove
     * @returns
     *    Number of removed elements
     */
    size_t remove(size_t cnt);

    /**
     * @brief Reads one element from internal buffer without blocking
     * @param[out] data 
     *    Reference to memory location where removed element will be stored
     * @returns
     *    True if data was fetched from the internal buffer
     */
    bool remove(T& data);

    /**
     * @brief Reads one element from internal buffer without blocking
     * @param[out] data 
     *    Pointer to memory location where removed element will be stored
     * @returns
     *    True if data was fetched from the internal buffer
     */
    bool remove(T* data);
    
    /**
     * @brief Gets the first element in the buffer on consumed side
     * @details It is safe to use and modify item contents only on consumer side
     * @returns
     *    Pointer to first element, nullptr if buffer was empty
     */
    T* peek();

    /**
     * @brief Gets the n'th element on consumed side
     * @details It is safe to use and modify item contents only on consumer side
     * @param index 
     *    Item offset starting on the consumed side
     * @returns
     *    Pointer to requested element, nullptr if index exceeds storage count
     */
    T* at(size_t index);

    /**
     * @brief Insert multiple elements into internal buffer without blocking
     * @details This function will insert as much data as possible from given buffer.
     * @param[in] buff 
     *    Pointer to buffer with data to be inserted from
     * @param count 
     *    Number of elements to write from the given buffer
     * @returns
     *    Number of elements written into internal buffer
     */
    size_t write_buff(const T* buff, size_t count);

    /**
     * @brief Insert multiple elements into internal buffer without blocking
     * @details This function will continue writing new entries until all data is written 
     *    or there is no more space. The callback function can be used to indicate to 
     *    consumer that it can start fetching data.
     * @warning This function is not deterministic
     *
     * @param[in] buff 
     *    Pointer to buffer with data to be inserted from
     * @param count 
     *    Number of elements to write from the given buffer
     * @param count_to_callback 
     *    Number of elements to write before calling a callback function in first loop
     * @param execute_data_callback 
     *    Pointer to callback function executed after every loop iteration
     * @returns
     *    Number of elements written into internal  buffer
     */
    size_t write_buff(const T* buff, size_t count, size_t count_to_callback, void (*execute_data_callback)(void));

    /**
     * @brief Load multiple elements from internal buffer without blocking
     * @details This function will read up to specified amount of data.
     * @param[out] buff 
     *    Pointer to buffer where data will be loaded into
     * @param count 
     *    Number of elements to load into the given buffer
     * @returns
     *    Number of elements that were read from internal buffer
     */
    size_t read_buff(T* buff, size_t count);

    /**
     * @brief Load multiple elements from internal buffer without blocking
     * @details This function will continue reading new entries until all requested data is 
     *    read or there is nothing more to read. The callback function can be used to indicate
     *    to producer that it can start writing new data.
     * @warning This function is not deterministic
     *
     * @param[out] buff 
     *    Pointer to buffer where data will be loaded into
     * @param count 
     *    Number of elements to load into the given buffer
     * @param count_to_callback 
     *    Number of elements to load before calling a callback function in first iteration
     * @param execute_data_callback 
     *    Pointer to callback function executed after every loop iteration
     * @returns
     *    Number of elements that were read from internal buffer
     */
    size_t read_buff(T* buff, size_t count, size_t count_to_callback, void (*execute_data_callback)(void));

    /**
     * @brief Gets the n'th element on consumed side
     * @details Unchecked operation, assumes that software already knows if the element can be used, if
     *    requested index is out of bounds then reference will point to somewhere inside the buffer
     *    The isEmpty() and readAvailable() will place appropriate memory barriers if used as loop limiter
     *    It is safe to use and modify T contents only on consumer side
     * @param index 
     *    Item offset starting on the consumed side
     * @returns
     *    Reference to requested element, undefined if index exceeds storage count
     */
    T& operator[](size_t index);

private: /* ------------------------------------------------- Private constants --------------------------------------------------- */

    /// bitwise mask for a given buffer size
    constexpr static index_t buffer_mask = buffer_size - 1; 
    // Acquire barier used (do not load from, or store to buffer before confirmed by the opposite side)
    constexpr static std::memory_order index_acquire_barrier = fake_tso ?
        std::memory_order_relaxed : std::memory_order_acquire;
    // Release barier used (do not update own side before all operations on data_buff committed)
    constexpr static std::memory_order index_release_barrier = fake_tso ?
        std::memory_order_relaxed : std::memory_order_release;

private: /* -------------------------------------------------- Private asserts ---------------------------------------------------- */

    // Check size of the buffer != 0
    static_assert((buffer_size != 0),
        "[circular_buffer] Buffer cannot be of zero size");
    // Check size of the buffer == 2^N
    static_assert((buffer_size & buffer_mask) == 0,
        "[circular_buffer] Buffer size is not a power of 2");
    // Check size of the index type
    static_assert(sizeof(index_t) <= sizeof(size_t),
        "[circular_buffer] Indexing type size is larger than size_t, operation is not lock free and doesn't make sense");

    // Check index type
    static_assert(std::numeric_limits<index_t>::is_integer,
        "[circular_buffer] Indexing type is not integral type");
    // Check index type signess
    static_assert(!(std::numeric_limits<index_t>::is_signed),
        "[circular_buffer] Indexing type shall not be signed");
    // Check buffer size
    static_assert(buffer_mask <= ((std::numeric_limits<index_t>::max)() >> 1),
        "[circular_buffer] Buffer size is too large for a given indexing type (maximum size for n-bit type is 2^(n-1))");

private: /* -------------------------------------------------- Private members ---------------------------------------------------- */

    /// Head index
    alignas(cacheline_size) std::atomic<index_t> head;
    /// Tail index
    alignas(cacheline_size) std::atomic<index_t> tail;

    // Put buffer after variables so everything can be reached with short offsets
    alignas(cacheline_size) T data_buff[buffer_size];
};

/* ================================================================================================================================ */

} // End namespace estl

/* ==================================================== Implementation includes =================================================== */

#include "estl/circullar_buffer/impl/circullar_buffer.hpp"

/* ================================================================================================================================ */

#endif
