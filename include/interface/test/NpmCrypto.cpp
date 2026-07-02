#include <gtest/gtest.h>

#include <interface/NpmCrypto.h>
#include <errno.h>

extern NpmCrypto* ci;
extern uint8_t *eccPrivate;
extern uint32_t eccPrivateSize;
extern uint8_t *eccPublic;
extern uint32_t eccPublicSize;

extern uint8_t *dataToSign;
extern uint32_t dataSize;

/* being outside of a function, this is initialized to NULL */
static uint8_t *priorSignature;

/*
 * This provides a suite of tests which will work with an NpmCrypto object.
 * Since the interface does not include a definition of a constructor, this
 * module must be compiled and linked with a real implementation. However, this
 * suite of tests should provide confidence that it is working as intended.
 */
TEST(NpmCrypto, TestSign)
{
    int err;
    uint8_t *signature;

    /* First, test function parameter handling */
    err = NpmSign(nullptr, nullptr, 0, nullptr);
    ASSERT_EQ(err, EINVAL);
    err = NpmSign(ci, nullptr, 0, nullptr);
    ASSERT_EQ(err, EINVAL);
    err = NpmSign(ci, dataToSign, 0, nullptr);
    ASSERT_EQ(err, EINVAL);
    err = NpmSign(ci, dataToSign, dataSize, nullptr);
    ASSERT_EQ(err, EINVAL);

    /* Second, test the signing function */
    err = NpmSign(ci, dataToSign, dataSize, &signature);
    ASSERT_EQ(err, 0);
    ASSERT_NE(signature, nullptr);
    ASSERT_EQ(signature[0], 0x30); // DER the signature is always a generated sequence

    /* the nature of Elliptic Curve signatures is that they vary and will not be
     * deterministic. Thus, there is no check for an expected signature.
     */
}

TEST(NpmCrypto, TestVerify)
{
    int err;

    ASSERT_NE(priorSignature, nullptr);
    /* First, test function parameter handling */
    err = NpmVerify(nullptr, nullptr, 0, nullptr);
    ASSERT_EQ(err, EINVAL);
    err = NpmVerify(ci, nullptr, 0, nullptr);
    ASSERT_EQ(err, EINVAL);
    err = NpmVerify(ci, dataToSign, 0, nullptr);
    ASSERT_EQ(err, EINVAL);
    err = NpmVerify(ci, dataToSign, dataSize, nullptr);
    ASSERT_EQ(err, EINVAL);

    /* Second, test the signing function */
    err = NpmVerify(ci, dataToSign, dataSize, priorSignature);
    ASSERT_EQ(err, 0);

}
