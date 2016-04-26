
#define BOOST_TEST_MODULE DODArray
#include <boost/test/unit_test.hpp>
#include <boost/log/trivial.hpp>

#include "util/DODArray.h"

typedef struct
{
    int id;
} TestStruct;

typedef util::DODArray<TestStruct> TestArray;

BOOST_AUTO_TEST_CASE(setup_default_constructor)
{
    //Test Arrays - Automatic and Dynamically allocated
    TestArray test_array_1;

    //Testing methods - checks empty size and allocated size
    //These are the only values to be changed by the constructor
    BOOST_CHECK(test_array_1.Size() == 0);
    BOOST_CHECK(test_array_1.AllocatedSize() == 128);
}

BOOST_AUTO_TEST_CASE(setup_allocated_constructor)
{
    //Test Arrays - Automatic and Dynamically allocated
    TestArray test_array_2(256);

    //Testing methods - checks empty size and allocated size
    //These are the only values to be changed by the constructor
    BOOST_CHECK(test_array_2.Size() == 0);
    BOOST_CHECK(test_array_2.AllocatedSize() == 256);
}

BOOST_AUTO_TEST_CASE(one_item_default)
{
    TestArray test_array_1;
    TestStruct test_struct_1;
    int test_struct_1_index;

    test_struct_1.id = 1;

    test_struct_1_index = test_array_1.Add(&test_struct_1);
    BOOST_CHECK(test_array_1.Size() == 1);
    BOOST_CHECK(test_array_1.AllocatedSize() == 128);
    BOOST_CHECK(test_struct_1_index == 0);
    BOOST_CHECK(test_array_1[test_struct_1_index].id == test_struct_1.id);
}

BOOST_AUTO_TEST_CASE(one_item_allocated)
{
    TestArray test_array_2(256);
    TestStruct test_struct_2;
    int test_struct_2_index;

    test_struct_2.id = 2;
    test_struct_2_index = test_array_2.Add(&test_struct_2);
    BOOST_CHECK(test_array_2.Size() == 1);
    BOOST_CHECK(test_array_2.AllocatedSize() == 256);
    BOOST_CHECK(test_struct_2_index == 0);
    BOOST_CHECK(test_array_2[test_struct_2_index].id == test_struct_2.id);
}
