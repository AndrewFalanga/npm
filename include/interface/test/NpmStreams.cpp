#include <gtest/gtest.h>

#include <interface/NpmStream.h>
#include <errno.h>

extern NpmStream* si;

/*
 * There isn't an easy way, given the overall design for how this testing would
 *  send anything, have it flushed in the stream and then receive data. This
 *  test design expects that the implementation provided by the 3rd party will
 *  act as a loop for the test.
 */
TEST(NpmStreams, TestSendRecv)
{
    int err;
    char dataToSend[] = "This string will be sent across the stream and read back";
    uint8_t *pData = (uint8_t*)dataToSend;
    uint32_t dataLength = sizeof(dataToSend);
    uint32_t dataRecvLength = 0;
    uint8_t recvData[256] = {0}; // purposefully, to catch if "more" came
    uint32_t recvLength = 0;
    int i;

    /* First, test function parameter handling */
    err = NpmSend(nullptr, nullptr, 0);
    ASSERT_EQ(err, EINVAL);
    err = NpmSend(si, nullptr, 0);
    ASSERT_EQ(err, EINVAL);
    err = NpmSend(si, pData, 0);
    ASSERT_EQ(err, EINVAL);

    err = NpmRecv(nullptr, nullptr, nullptr);
    ASSERT_EQ(err, EINVAL);
    err = NpmRecv(si, nullptr, nullptr);
    ASSERT_EQ(err, EINVAL);
    err = NpmRecv(si, pData, nullptr);
    ASSERT_EQ(err, EINVAL);

    /* Now, test that data is sent and then received */
    err = NpmSend(si, pData, dataLength);
    ASSERT_EQ(err, 0);

    err = NpmRecv(si, recvData, &recvLength);
    ASSERT_EQ(err, 0);
    ASSERT_EQ(recvLength, dataLength);
    for (i = 0; i < dataLength; i++)
        ASSERT_EQ(pData[i], recvData[i]);
}
