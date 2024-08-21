#ifndef ECS_TESTS_H_
#define ECS_TESTS_H_

#include <gtest/gtest.h>

#include <scene/ecs/sparse_set.h>
#include <scene/ecs/ComponentPool.h>
#include <scene/ecs/ComponentPoolFactory.h>
#include <scene/ecs/registry.h>

using namespace rtl;
using namespace radium;
class Sprite2DMock
{
public:
    Sprite2DMock(const char* str) : m_name(str) {}
    void printName() { printf("%s\n", m_name.c_str()); }
    rtl::string m_name;

};

struct test
{
    int the_int;
    int the_short;
    int the_add() { return the_int + the_short; }

    test(int x, int y) : the_int(x), the_short(y) {}

    test(const test& o) : the_int(o.the_int), the_short(o.the_short) {}

};

TEST(ecs_tests, component_pool_test1)
{

    ComponentPool<test> test1;

    for (int i = 0; i < 10; i++)
    {
        test1.addComponent(i, i, i);
        EXPECT_TRUE(test1.exists(i));
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(test1.getComponent(i)->the_add() == i + i);
    }

    for (int i = 0; i < 10; i++)
    {
        test1.updateComponent(i, i * 2, i * 2);
        EXPECT_TRUE(test1.exists(i));
    }
    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(test1.getComponent(i)->the_add() == (i * 2) * 2);
    }

    auto* loc = test1.getComponent(1);
    test1.removeComponent(1);

    EXPECT_FALSE(test1.exists(1));

    auto* nloc = test1.addComponent(1, 1, 1);
    EXPECT_EQ(loc, nloc);
    
}

TEST(ecs_test, component_pool_factory_test)
{
    ComponentPoolFactory cpf;

    cpf.addNewPool<test>();

    
    EXPECT_TRUE(cpf.getIfExists<test>() != nullptr);
    EXPECT_TRUE(cpf.getIfExists<int>() == nullptr);

    auto* test2 = cpf.get<test>();
    EXPECT_NE(test2, nullptr);
    

    for (int i = 0; i < 10; i++)
    {
        test2->addComponent(i, i, i);
        EXPECT_TRUE(test2->exists(i));
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(test2->getComponent(i)->the_add() == i + i);
    }

    for (int i = 0; i < 10; i++)
    {
        test2->updateComponent(i, i * 2, i * 2);
        EXPECT_TRUE(test2->exists(i));
    }
    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(test2->getComponent(i)->the_add() == (i * 2) * 2);
    }

    
    cpf.addNewPool<Sprite2DMock>();
    EXPECT_TRUE(cpf.getIfExists<Sprite2DMock>() != nullptr);

    auto* sp = cpf.get<Sprite2DMock>();
    EXPECT_NE(sp, nullptr);

    cpf.get<Sprite2DMock>()->addComponent(1, "skamtebord");
    cpf.get<Sprite2DMock>()->addComponent(2, "lopster");

    EXPECT_STREQ(cpf.get<Sprite2DMock>()->getComponent(1)->m_name.c_str(), "skamtebord");
    EXPECT_STREQ(cpf.get<Sprite2DMock>()->getComponent(2)->m_name.c_str(), "lopster");

    auto* loc1 = sp->getComponent(1);

    cpf.removeAll(1);

    EXPECT_TRUE(sp->getComponent(1) == nullptr);
    EXPECT_TRUE(test2->getComponent(1) == nullptr);

    auto* loc2 = sp->addComponent(1, "skamtebord the scond");

    EXPECT_TRUE(loc1 == loc2);

}

TEST(ecs_test, registry_test)
{
    registry test2;

    entity_t bob = test2.create();

    entity_t alice = test2.create();

    entity_t oldbob = bob;

    test2.release(bob);

    entity_t newbob = test2.create();
    // test graveyard functions
    EXPECT_EQ(oldbob, newbob);


}
#endif // ECS_TESTS_H_