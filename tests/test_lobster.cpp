//
// Created by Uncle Chu on 11/5/18.
//

#define BOOST_TEST_MODULE test_orderbook
#define BOOST_TEST_DYN_LINK

#include <string>
#include <boost/test/unit_test.hpp>
#include "../lobster/AddOrderMsg.hpp"
#include "../lobster/CancelOrderMsg.hpp"
#include "../lobster/MsgParser.h"
#include "../lobster/DeleteOrderMsg.hpp"
#include "../lobster/OrderExecutedMsg.hpp"

using namespace std;
using namespace lobster;

BOOST_AUTO_TEST_SUITE( test_lobster_suite )

    BOOST_AUTO_TEST_CASE( test_add_order )
    {
        auto parser = lobster::MsgParser();

        string data = "34200.18960767,1,11885113,21,2238100,1";
        
        auto msg = dynamic_pointer_cast<AddOrderMsg>(parser.parse_msg(data));
        BOOST_TEST( msg->m_timestamp.tv_sec == 34200);
        BOOST_TEST( msg->m_timestamp.tv_nsec == 18960767);
        BOOST_TEST( msg->m_msgtype == '1');
        BOOST_TEST( msg->m_orderId == 11885113);
        BOOST_TEST( msg->m_shares == 21);
        BOOST_TEST( msg->m_price == 2238100);
        BOOST_TEST( msg->m_side == 1);

    }

    BOOST_AUTO_TEST_CASE( test_cancel_order )
    {
        auto parser = lobster::MsgParser();

        string data = "34409.326018975,2,21866417,200,2239600,-1";

        auto msg = dynamic_pointer_cast<CancelOrderMsg>(parser.parse_msg(data));
        BOOST_TEST( msg->m_timestamp.tv_sec == 34409);
        BOOST_TEST( msg->m_timestamp.tv_nsec == 326018975);
        BOOST_TEST( msg->m_msgtype == '2');
        BOOST_TEST( msg->m_orderId == 21866417);
        BOOST_TEST( msg->m_shares == 200);
        BOOST_TEST( msg->m_price == 2239600);
        BOOST_TEST( msg->m_side == -1);

    }

    BOOST_AUTO_TEST_CASE( test_delete_order )
    {
        auto parser = lobster::MsgParser();

        string data = "34395.851552647,3,21138842,200,2239800,-1";

        auto msg = dynamic_pointer_cast<DeleteOrderMsg>(parser.parse_msg(data));
        BOOST_TEST( msg->m_timestamp.tv_sec == 34395);
        BOOST_TEST( msg->m_timestamp.tv_nsec == 851552647);
        BOOST_TEST( msg->m_msgtype == '3');
        BOOST_TEST( msg->m_orderId == 21138842);
        BOOST_TEST( msg->m_shares == 200);
        BOOST_TEST( msg->m_price == 2239800);
        BOOST_TEST( msg->m_side == -1);

    }

    BOOST_AUTO_TEST_CASE( test_order_executed )
    {
        auto parser = lobster::MsgParser();

        string data = "34414.765462735,4,21942984,100,2237600,1";

        auto msg = dynamic_pointer_cast<OrderExecutedMsg>(parser.parse_msg(data));
        BOOST_TEST( msg->m_timestamp.tv_sec == 34414);
        BOOST_TEST( msg->m_timestamp.tv_nsec == 765462735);
        BOOST_TEST( msg->m_msgtype == '4');
        BOOST_TEST( msg->m_orderId == 21942984);
        BOOST_TEST( msg->m_shares == 100);
        BOOST_TEST( msg->m_price == 2237600);
        BOOST_TEST( msg->m_side == 1);
        BOOST_TEST( msg->m_visible == true);


        string data2 = "34418.450176448,5,0,100,2238600,-1";
        auto msg2 = dynamic_pointer_cast<OrderExecutedMsg>(parser.parse_msg(data2));
        BOOST_TEST( msg2->m_timestamp.tv_sec == 34418);
        BOOST_TEST( msg2->m_timestamp.tv_nsec == 450176448);
        BOOST_TEST( msg2->m_msgtype == '5');
        BOOST_TEST( msg2->m_orderId == 0);
        BOOST_TEST( msg2->m_shares == 100);
        BOOST_TEST( msg2->m_price == 2238600);
        BOOST_TEST( msg2->m_side == -1);
        BOOST_TEST( msg2->m_visible == false);
    }

BOOST_AUTO_TEST_SUITE_END()