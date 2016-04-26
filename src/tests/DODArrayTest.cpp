
#define BOOST_TEST_MODULE DODArray
#include <boost/test/unit_test.hpp>
#include <boost/log/trivial.hpp>

#include <stdio.h>

#include "util/DODArray.h"

typedef struct
{
    int id;
} TestStruct;

typedef util::DODArray<TestStruct> TestArray;

BOOST_AUTO_TEST_CASE(setup_default_constructor)
{
    //Test Arrays - Automatic and Dynamically allocated
    TestArray test_array;

    //Testing methods - checks empty size and allocated size
    //These are the only values to be changed by the constructor
    BOOST_CHECK(test_array.Size() == 0);
    BOOST_CHECK(test_array.AllocatedSize() == 128);
}

BOOST_AUTO_TEST_CASE(setup_allocated_constructor)
{
    //Test Arrays - Automatic and Dynamically allocated
    TestArray test_array(256);

    //Testing methods - checks empty size and allocated size
    //These are the only values to be changed by the constructor
    BOOST_CHECK(test_array.Size() == 0);
    BOOST_CHECK(test_array.AllocatedSize() == 256);
}

BOOST_AUTO_TEST_CASE(one_item_default)
{
    TestArray test_array;
    TestStruct test_struct;
    int test_struct_index;

    test_struct.id = 1;

    test_struct_index = test_array.Add(test_struct);
    BOOST_CHECK(test_array.Size() == 1);
    BOOST_CHECK(test_array.AllocatedSize() == 128);
    BOOST_CHECK(test_struct_index == 0);
    BOOST_CHECK(test_array[test_struct_index].id == test_struct.id);
    test_array.Delete(test_struct_index);
    BOOST_CHECK(test_array.Size() == 0);
    BOOST_CHECK(test_array.AllocatedSize() == 128);
}

BOOST_AUTO_TEST_CASE(multiple_item_default)
{
    TestArray test_array;
    TestStruct test_struct;
    int test_struct_index;

    for(int i = 0; i < 5; i++)
    {
        test_struct.id = i;
        test_array.Add(test_struct);
    }

    BOOST_CHECK(test_array.Size() == 5);
    BOOST_CHECK(test_array.AllocatedSize() == 128);

    for(int i = 0; i < 5; i++)
    {
        BOOST_CHECK(test_array[i].id == i);
    }

    test_array.Delete(0);
    BOOST_CHECK(test_array[0].id == 4);
    BOOST_CHECK(test_array.Size() == 4);

    test_array.Delete(0);
    BOOST_CHECK(test_array[0].id == 3);
    BOOST_CHECK(test_array.Size() == 3);

    test_array.Delete(0);
    BOOST_CHECK(test_array[0].id == 2);
    BOOST_CHECK(test_array.Size() == 2);

    test_array.Delete(0);
    BOOST_CHECK(test_array[0].id == 1);
    BOOST_CHECK(test_array.Size() == 1);

    test_array.Delete(0);
    BOOST_CHECK(test_array.Size() == 0);
    BOOST_CHECK(test_array.AllocatedSize() == 128);
}

BOOST_AUTO_TEST_CASE(large_item_default)
{
    TestArray test_array;
    TestStruct test_struct;
    int test_struct_index;

    for(int i = 0; i < 129; i++)
    {
        test_struct.id = i;
        test_array.Add(test_struct);
    }

    BOOST_CHECK(test_array.Size() == 129);
    BOOST_CHECK(test_array.AllocatedSize() == 256);

    size_t size = test_array.Size();
    for (size_t i = 0; i < size; i++) {
        test_array.Delete(0);
    }

    BOOST_CHECK(test_array.Size() == 0);
    BOOST_CHECK(test_array.AllocatedSize() == 128);
}
