#include <gtest/gtest.h>

#include <interface/NpmCrypto.h>
#include <errno.h>

extern NpmCrypto* ci;

/*
 * This provides a suite of tests which will work with an NpmCrypto object.
 * Since the interface does not include a definition of a constructor, this
 * module must be compiled and linked with a real implementation. However, this
 * suite of tests should provide confidence that it is working as intended.
 */
TEST(NpmCrypto, TestSign)
{
    int err;

    err = NpmSign(nullptr, nullptr, 0, nullptr);
    ASSERT_EQ(err, EINVAL);
    err = NpmSign(nullptr, nullptr, 0, nullptr);
    ASSERT_EQ(err, EINVAL);
    err = NpmSign(nullptr, nullptr, 0, nullptr);
    ASSERT_EQ(err, EINVAL);
    err = NpmSign(nullptr, nullptr, 0, nullptr);
    ASSERT_EQ(err, EINVAL);
}
