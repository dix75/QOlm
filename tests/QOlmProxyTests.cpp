// Our test classes
#include <QOlm/QOlm.hpp>

// gtest framework
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Spy signal call without having a main loop
#include <QSignalSpy>

// stl headers
#include <queue>
#include <utility>

#include "Foo.hpp"
#include "FooTree.hpp"
#include "FooProxy.hpp"


class QOlmTestTreeFilledByHand : public ::testing::Test
{
protected:
    void SetUp() override {
      item1->append(item11);
      item1->append(item12);
      item1->append(item13);
      tree->append(item1);
      tree->append(item2);
      proxy->setSourceModel(tree);
    }
    void TearDown() override {}

    FooTree* tree = new FooTree(-1);
    FooTree* item1 = new FooTree(1, tree);
    FooTree* item2 = new FooTree(2, tree);

    FooTree* item11 = new FooTree(11, item1);
    FooTree* item12 = new FooTree(12, item1);
    FooTree* item13 = new FooTree(13, item1);

    FooProxy* proxy = new FooProxy();
};

class QOlmTestTreeFilledByAuto : public ::testing::Test
{
protected:
    void SetUp() override {
      proxy->setSourceModel(tree);
      item1->append(item11);
      item1->append(item12);
      item1->append(item13);
      tree->append(item1);
      tree->append(item2);
    }
    void TearDown() override {}

    FooTree* tree = new FooTree(-1);
    FooTree* item1 = new FooTree(1, tree);
    FooTree* item2 = new FooTree(2, tree);

    FooTree* item11 = new FooTree(11, item1);
    FooTree* item12 = new FooTree(12, item1);
    FooTree* item13 = new FooTree(13, item1);

    FooProxy* proxy = new FooProxy();
};

TEST_F(QOlmTestTreeFilledByHand, filterAcceptsRowByHand)
{
  auto const& root = tree->index(0,0, {});
  auto const& _1 = tree->index(0,0, root);
  auto const& _2 = tree->index(1,0, root);
  auto const& _11 = tree->index(0,0, _1);
  auto const& _12 = tree->index(1,0, _1);
  auto const& _13 = tree->index(2,0, _1);

  // ASSERT_EQ(proxy->filterAcceptsRow(0, root), true);
  // ASSERT_EQ(proxy->filterAcceptsRow(0, _1), true);
  // ASSERT_EQ(proxy->filterAcceptsRow(1, _2), false);
  // ASSERT_EQ(proxy->filterAcceptsRow(0, _11), false);
  // ASSERT_EQ(proxy->filterAcceptsRow(1, _12), false);
  // ASSERT_EQ(proxy->filterAcceptsRow(2, _13), false);

  ((FooProxy*)proxy)->setFilter(11);
  // ASSERT_EQ(proxy->filterAcceptsRow(0, _1), false);
  // ASSERT_EQ(proxy->filterAcceptsRow(1, _2), false);
  ASSERT_EQ(proxy->filterAcceptsRow(0, _11), true);
  // ASSERT_EQ(proxy->filterAcceptsRow(1, _12), false);
  // ASSERT_EQ(proxy->filterAcceptsRow(2, _13), false);
}

TEST_F(QOlmTestTreeFilledByAuto, filterAcceptsRowByAuto)
{
}
