#include "stdafx.h"
#include "CMapTests.h"

using namespace std;

struct Map_
{

	Map_()
	{

	}
};

BOOST_FIXTURE_TEST_SUITE(Map, Map_)
////////////////////////////////////
	BOOST_AUTO_TEST_SUITE(Template)
		BOOST_AUTO_TEST_CASE(template_1)
		{

			BOOST_CHECK(true);

			BOOST_CHECK_EQUAL(1, 1);
		}

	BOOST_AUTO_TEST_SUITE_END()
////////////////////////////////////
	BOOST_AUTO_TEST_CASE(open_input_file)
	{
		CMap("map.txt");
	}
	BOOST_AUTO_TEST_CASE(correct_read_from_file)
	{
		CMap("map1.txt");
	}
BOOST_AUTO_TEST_SUITE_END()


	