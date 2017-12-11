#define BOOST_TEST_MODULE AppTrigger
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* APP_TRIGGER = 5 */
BOOST_AUTO_TEST_CASE(AppTrigger)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_AppTrigger.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::APP_TRIGGER);
    Vector::BLF::AppTrigger * obj = static_cast<Vector::BLF::AppTrigger *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::APP_TRIGGER);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* AppTrigger */
    BOOST_CHECK_EQUAL(obj->preTriggerTime, 0x1111111111111111);
    BOOST_CHECK_EQUAL(obj->postTriggerTime, 0x2222222222222222);
    BOOST_CHECK_EQUAL(obj->channel, 0x3333);
    BOOST_CHECK(obj->flags == Vector::BLF::AppTrigger::Flags::SingleTrigger);
    BOOST_CHECK_EQUAL(obj->appSpecific2, 0x44444444);

    delete obj;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::APP_TRIGGER);

    delete obj;

    file.close();
}
