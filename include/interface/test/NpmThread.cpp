
#include <cerrno>
#include <gtest/gtest.h>

#include <interface/NpmThread.h>
#include <errno.h>

extern NpmThread* ti;

static int StartNpmThread(NpmThread* th);
static int StopNpmThread(NpmThread* th);
static uint32_t GetNpmThreadId(NpmThread* th);
static int IsNpmThreadRunning(NpmThread* th);

/*
 * This provides a suite of tests which will work with an NpmThread object.
 * Since the interface does not include a definition of a constructor, this
 * module must be compiled and linked with a real implementation. However, this
 * suite of tests should provide confidence that it is working as intended.
 */
TEST(NpmThread, TestStartAndStop)
{
    int err;
    uint8_t *signature;

    /* First, test function parameter handling */
    err = StartNpmThread(nullptr);
    ASSERT_EQ(err, EINVAL);
    err = StartNpmThread(ti);
    ASSERT_EQ(err, 0);

    /* It would be nicer to test Stop() separately. However, from the spirit of
     * this testing exercise, that would require stopping the thread for this
     * test with something other than the API. That can't be done without
     * assuming everyone implements threading with the same underlying thread
     * model.
     */
    err = StopNpmThread(nullptr);
    ASSERT_EQ(err, EINVAL);
    err = StopNpmThread(ti);
    ASSERT_EQ(err, 0);
}

TEST(NpmThread, TestThreadId)
{
    int id;

    id = GetNpmThreadId(nullptr);
    ASSERT_EQ(id, -EINVAL);

    id = GetNpmThreadId(ti);
    ASSERT_NE(id, 0);
}

TEST(NpmThread, TestIsThreadRunning)
{
    int isRunning;

    isRunning = IsNpmThreadRunning(nullptr);
    ASSERT_EQ(isRunning, 0);

    isRunning = IsNpmThreadRunning(ti);
    ASSERT_EQ(isRunning, 0);

    int err = StartNpmThread(ti);
    EXPECT_EQ(err, 0);

    isRunning = IsNpmThreadRunning(ti);
    ASSERT_EQ(isRunning, 1);

    err = StopNpmThread(ti);
    EXPECT_EQ(err, 0);

    err = IsNpmThreadRunning(ti);
    ASSERT_EQ(err, 0);
}
