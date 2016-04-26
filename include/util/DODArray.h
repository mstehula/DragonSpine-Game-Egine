#ifndef DOD_ARRAY_H
#define DOD_ARRAY_H

#include <stdlib.h>
#include <string.h>

namespace util
{
    template <typename T>
    class DODArray
    {
    private:
        size_t current_size;
        size_t min_size;
        size_t allocated_size;

        T* elements;
    public:
        DODArray()
        {
            current_size = 0;
            min_size = 128;
            allocated_size = 128;
            elements = new T[allocated_size];
        }
        DODArray(size_t size)
        {
            current_size = 0;
            min_size = size;
            allocated_size = min_size;
            elements = new T[allocated_size];
            memset(elements, 0, allocated_size * sizeof(T));
        }

        virtual ~DODArray()
        {
            delete elements;
        }

        T& operator[](int i)
        {
            return elements[i];
        }

        size_t Size()
        {
            return current_size;
        }

        size_t AllocatedSize()
        {
            return allocated_size;
        }

        int Add(T* object)
        {
            if(current_size + 1 == allocated_size)
            {
                T* temp = new T[allocated_size * 2];
                memset(temp, 0, allocated_size * 2 * sizeof(T));
                allocated_size *= 2;
                delete[] elements;
                elements = temp;
            }

            memcpy(&elements[current_size], object, sizeof(T));

            return current_size++;
        }

        /**
        *   Func: Delete
        *   Args: int i: The index of the element to remove.
        *   Comm: No bounds checking on what to remove.
        *     Puts last element in the array in the new slot.
        *     Any data structures that need to be synchronized must be done
        *      outside this method.
        *     Also, if the size is < 1/2 allocated size and allocated size > 128,
        *      will deallocate to 1/2 allocated size
        **/
        void Delete(int i)
        {

        }
    };

}

#endif // DODARRAY_H
