#include "main.cpp"
#include <gtest/gtest.h>


class GraphTest : public testing::Test{
public:
    Graph *g, *g2;
    GraphTest(){ g = new Graph; }
};

TEST_F(GraphTest, GraphEmpty){ //facut sa testez si stilul asta 
    EXPECT_EQ(0, g->get_adj().size());
    EXPECT_EQ(0, g->getNodes().size());
}

TEST(constructorParam, GraphWithElements){
    unordered_map<int, unordered_set<int>> adj = {{1,{2,3}},{2,{1}},{3,{1}}};
    Graph g(adj);
    Graph g2(g);
    EXPECT_EQ(adj, g.get_adj());
    EXPECT_EQ(g.get_adj(), g2.get_adj());
    EXPECT_EQ(3, g.getNodes().size());
}

TEST_F(GraphTest, inserturiStergeri){
    g->insertNode();
    EXPECT_EQ(1, g->get_adj().size());
    EXPECT_EQ(INT_MAX-1, g->get_x());
    EXPECT_EQ(1, g->get_adj().find(INT_MAX) != g->get_adj().end());
    EXPECT_EQ(1, g->getNodes().size());
    g->insertNode(1);
    EXPECT_EQ(2, g->get_adj().size());
    EXPECT_EQ(2, g->getNodes().size());
    g->insertNode(1);
    EXPECT_EQ(2, g->get_adj().size());
    g->deleteNode(1);
    EXPECT_EQ(1, g->get_adj().size());
    g->deleteNode(1);
    EXPECT_EQ(1, g->get_adj().size());
    g->insertNode(1);
    EXPECT_EQ(2, g->get_adj().size());
    /*------------graful 2-----------------*/
    unordered_map<int, unordered_set<int>> adj = {{1,{2,3}},{2,{1}},{3,{1}}}; // il folosesc pentru teste
    Graph g2(adj);
    EXPECT_EQ(3, g2.get_adj().size());
    EXPECT_TRUE(g2.checkAdj(1,2));
    g2.deleteNode(2);
    EXPECT_EQ(2, g2.get_adj().size());
    EXPECT_FALSE(g2.checkAdj(1,2));
    g2.insertNode(2);
    EXPECT_EQ(3, g2.get_adj().size());
    EXPECT_FALSE(g2.checkAdj(1,2));
    g2.deleteNode(3);
    EXPECT_FALSE(g2.checkAdj(1, 3));
}

TEST_F(GraphTest, adiacente){
    EXPECT_EQ(0, g->get_adj().size());
    g->insertNode(1);
    g->insertNode(2);
    g->insertNode(3);
    EXPECT_FALSE(g->checkAdj(1,2));
    EXPECT_FALSE(g->checkAdj(2,1));
    g->insertEdge(1,2);
    EXPECT_TRUE(g->checkAdj(1,2));
    g->insertEdge(1,2);
    EXPECT_TRUE(g->checkAdj(1,2));
    EXPECT_TRUE(g->checkAdj(2,1));
    g->insertEdge(2,1);
    g->deleteEdge(1,2);
    EXPECT_FALSE(g->checkAdj(1,2));
    g->deleteEdge(1,2);
    g->deleteEdge(2,1);
    EXPECT_FALSE(g->checkAdj(1,2));
    EXPECT_FALSE(g->checkAdj(2,1));
    EXPECT_FALSE(g->checkAdj(5,6));
}

// testare parametrizata
struct incercariAciclitate{
    unordered_map<int, unordered_set<int>> adj;
    bool aciclic;
};

struct aciclitateTeste : public GraphTest, public testing::WithParamInterface<incercariAciclitate>{
    aciclitateTeste(){
        g2 = new Graph(GetParam().adj);
    }
};

TEST_P(aciclitateTeste, verificaAciclitate){
    auto as = GetParam();
    bool aciclic = g2->acyclicity();
    EXPECT_EQ(as.aciclic, aciclic);
}

INSTANTIATE_TEST_SUITE_P(Default, aciclitateTeste,
    testing::Values(
        incercariAciclitate{ {{1,{2,3}}, {2,{1,3}} , {3,{1,2}} }   , false},
        incercariAciclitate{ {{1,{2,3}}, {2,{1}} , {3,{1}} }   , true},
        incercariAciclitate{ {{1,{2}}, {2,{1}} }  , true},
        incercariAciclitate{ {{1,{}} }  , true},
        incercariAciclitate{ {{1,{2}}, {2,{1,3,4}}, {3,{2,4}}, {4,{2,3}} }  , false}
    ));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
