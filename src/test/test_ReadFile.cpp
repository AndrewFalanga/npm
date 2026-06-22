#include <cerrno>
#include <cstddef>
#include <gtest/gtest.h>

#include <ReadFile.h>

#include <cstdint>

/* This file is generated during the build */
#include <test_file.h>

TEST(ReadFile, TestParameters)
{
    uint32_t size = 0;
    int ret;
    const char *bogusFile = "this_file.does_not_exist";
    uint8_t *contents = nullptr;

    /* First, check that all parameters are tested for a null value */
    ret = ReadFile(nullptr, nullptr, nullptr);
    ASSERT_EQ(EINVAL, ret);

    ret = ReadFile(bogusFile, nullptr, nullptr);
    ASSERT_EQ(EINVAL, ret);

    ret = ReadFile(bogusFile, reinterpret_cast<void**>(&contents), nullptr);
    ASSERT_EQ(EINVAL, ret);

    /* Now, test that a pointer with real value is not permitted */
    contents = reinterpret_cast<uint8_t*>(&size);
    ret = ReadFile(bogusFile, reinterpret_cast<void**>(&contents), &size);
    ASSERT_EQ(EINVAL, ret);
}

TEST(ReadFile, TestFileHandling)
{
    const char *bogusFile = "this_file.does_not_exist";
    char *contents = nullptr;
    int ret;
    uint32_t size = 0;

    /* First check that a non-existent file return ENOENT */
    contents = nullptr;
    ret = ReadFile(bogusFile, reinterpret_cast<void**>(&contents), &size);
    ASSERT_EQ(ENOENT, ret);

    ret = ReadFile(testFile, reinterpret_cast<void**>(&contents), &size);
    ASSERT_EQ(0, ret);
    EXPECT_EQ(69, size);
    ASSERT_STREQ(fileContents, contents);
}
