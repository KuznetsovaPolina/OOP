#include <gtest/gtest.h>
#include "VectorMemoryResource.h"
#include "PmrQueue.h"
#include "SimpleStruct.h"

TEST(PmrQueueIntTest, PushPopIterate) {
    VectorMemoryResource mem;
    PmrQueue<int> q(&mem);

    EXPECT_TRUE(q.empty());
    q.push(1);
    q.push(2);
    q.push(3);
    EXPECT_EQ(q.size(), 3u);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 3);

    int sum = 0;
    for (int v : q) sum += v;
    EXPECT_EQ(sum, 1 + 2 + 3);

    q.pop();
    EXPECT_EQ(q.size(), 2u);
    EXPECT_EQ(q.front(), 2);
}

TEST(PmrQueuePersonTest, PushAndCompare) {
    VectorMemoryResource mem;
    PmrQueue<Person> q1(&mem);
    PmrQueue<Person> q2(&mem);

    Person a{"Alice", 30, 100000.0};
    Person b{"Bob", 25, 80000.0};

    q1.push(a);
    q1.push(b);

    q2.push(a);
    q2.push(b);

    EXPECT_TRUE(q1 == q2);

    q2.pop();
    EXPECT_TRUE(q1 != q2);
}
