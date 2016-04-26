
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
    TestArray test_array_1;
    TestArray test_array_2(256);

    //Testing methods - checks empty size and allocated size
    //These are the only values to be changed by the constructor
    BOOST_CHECK(test_array_2.Size() == 0);
    BOOST_CHECK(test_array_2.AllocatedSize() == 256);
}

BOOST_AUTO_TEST_CASE(setup_default_constructor_dynamic)
{
    //Test Arrays - Automatic and Dynamically allocated
    TestArray* test_array_3 = new TestArray();

    //Testing methods - checks empty size and allocated size
    //These are the only values to be changed by the constructor
    BOOST_CHECK(test_array_3->Size() == 0);
    BOOST_CHECK(test_array_3->AllocatedSize() == 128);

    delete test_array_3;
}

BOOST_AUTO_TEST_CASE(setup_allocated_constructor_dynamic)
{
    //Test Arrays - Automatic and Dynamically allocated
    TestArray* test_array_4 = new TestArray(256);

    //Testing methods - checks empty size and allocated size
    //These are the only values to be changed by the constructor
    BOOST_CHECK(test_array_4->Size() == 0);
    BOOST_CHECK(test_array_4->AllocatedSize() == 256);

    delete test_array_4;
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

BOOST_AUTO_TEST_CASE(one_item_default_dynamic)
{
    TestArray* test_array_3 = new TestArray();
    TestStruct* test_struct_3 = new TestStruct();
    int test_struct_3_index;

    test_struct_3->id = 3;
    test_struct_3_index = test_array_3->Add(test_struct_3);
    BOOST_CHECK(test_array_3->Size() == 1);
    BOOST_CHECK(test_array_3->AllocatedSize() == 128);
    BOOST_CHECK(test_struct_3_index == 0);
    BOOST_CHECK((*test_array_3)[test_struct_3_index].id == test_struct_3->id);

    delete test_array_3;
    delete test_struct_3;
}

BOOST_AUTO_TEST_CASE(one_item_allocated_dynamic)
{
    TestArray* test_array_4 = new TestArray(256);
    TestStruct* test_struct_4 = new TestStruct();
    int test_struct_4_index;

    test_struct_4->id = 4;
    test_struct_4_index = test_array_4->Add(test_struct_4);
    BOOST_CHECK(test_array_4->Size() == 1);
    BOOST_CHECK(test_array_4->AllocatedSize() == 256);
    BOOST_CHECK(test_struct_4_index == 0);
    BOOST_CHECK((*test_array_4)[test_struct_4_index].id == test_struct_4->id);

    delete test_array_4;
    delete test_struct_4;
}
