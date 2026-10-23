#include "viewmodels/graph_view_model.hpp"

#include <QtTest>

class GraphViewModelTest : public QObject {
    Q_OBJECT

private slots:
    void init() {
        viewModel_ = new GraphViewModel();
    }

    void cleanup() {
        delete viewModel_;
        viewModel_ = nullptr;
    }

    void addNode_incrementsNodeCount() {
        viewModel_->addNode("a");
        QCOMPARE(viewModel_->nodeCount(), 1u);
    }

    void addEdge_implicitlyAddsNodes() {
        viewModel_->addEdge("a", "b");
        QCOMPARE(viewModel_->nodeCount(), 2u);
        QVERIFY(viewModel_->graph().hasEdge("a", "b"));
    }

    void addNode_notifiesListener() {
        std::size_t notified = 0;
        viewModel_->setNodeCountListener([&notified](std::size_t count) { notified = count; });

        viewModel_->addNode("a");

        QCOMPARE(notified, 1u);
    }

private:
    GraphViewModel* viewModel_ = nullptr;
};

QTEST_GUILESS_MAIN(GraphViewModelTest)

#include "graph_view_model_test.moc"
