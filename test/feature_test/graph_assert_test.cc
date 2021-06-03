#include <cctest/cctest.h>
#include "easy_graph/builder/graph_dsl.h"
#include "easy_graph/graph/graph_visitor.h"
#include "easy_graph/infra/log.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <map>

USING_EG_NS

namespace {
	struct GraphAssertVisitor: GraphVisitor {
		using Nodes = std::vector<NodeId>;

		const Graph& operator* () const{
			return *graph;
		}

		const Graph* operator-> () const {
			return graph;
		}

		size_t getNodeCount() const {
			return nodeEdges.size();
		}

		size_t getEdgeCount() const {
			size_t count = 0;
			for (auto& item : nodeEdges) {
				count += item.second.size();
			}
			return count;
		}

		Nodes getNextNodesOf(const NodeId& id) const {
			return getNextNodeIn(nodeEdges, id, [](const auto& e) {return e->getDstNodeId();});
		}

		Nodes getPrevNodesOf(const NodeId& id) const {
			return getNextNodeIn(reverseNodeEdges, id, [](const auto& e) {return e->getSrcNodeId();});
		}

	private:
		using Edges = std::vector<const Edge*>;

		Status visit(const Graph& graph) override {
			this->graph = &graph;
			return EG_SUCCESS;
		}

		Status visit(const Node& node) override {
			setupNodeEdges(nodeEdges, node.getId());
			setupNodeEdges(reverseNodeEdges, node.getId());
			return EG_SUCCESS;
		}

		Status visit(const Edge& edge) override {
			classifyNodeEdge(nodeEdges, edge.getSrcNodeId(), edge);
			classifyNodeEdge(reverseNodeEdges, edge.getDstNodeId(), edge);
			return EG_SUCCESS;
		}

	private:
		void dumpNodeEdges() const {
			for (auto& item : nodeEdges) {
				std::cout << item.first << ": { ";
				for (auto e : item.second) {
					std::cout << e->getDstNodeId() << "(" << e->getSrcPortId() << "," <<  e->getDstPortId() << ") ";
				}
				std::cout << "}" << std::endl;
			}
		}

		static void setupNodeEdges(std::map<NodeId, Edges>& nodeEdges, const NodeId& id) {
			if (nodeEdges.find(id) == nodeEdges.end()) {
				nodeEdges[id] = Edges{};
			}
		}

		static void classifyNodeEdge(std::map<NodeId, Edges>& nodeEdges, const NodeId& id, const Edge& edge) {
			auto item = nodeEdges.find(id);
			if(item != nodeEdges.end()) {
				nodeEdges[id].push_back(&edge);
			}
		}

		template<typename GET_NODE_ID>
		static Nodes getNextNodeIn(const std::map<NodeId, Edges>& nodeEdges, const NodeId& id, GET_NODE_ID getNodeId) {
			Nodes nodes;

			auto item = nodeEdges.find(id);
			if (item == nodeEdges.end()) {
				return nodes;
			}

			for(auto& e : item->second) {
				nodes.push_back(getNodeId(e));
			}
			return std::move(nodes);
		}

	private:
		const Graph* graph{nullptr};
		std::map<NodeId, Edges> nodeEdges;
		std::map<NodeId, Edges> reverseNodeEdges;
	};
}

FIXTURE(GraphAssertTest) {
	TEST("should build graph success") {

		GRAPH(g1) {
			CHAIN(Node("a") -> Node("b") -> Node("c") -> Node("d") -> Node("e"));
		});

		GraphAssertVisitor visitor;
		g1.accept(visitor);

		ASSERT_EQ(std::string("g1"), visitor->getName());

		ASSERT_EQ(5, visitor.getNodeCount());
		ASSERT_EQ(4, visitor.getEdgeCount());

		ASSERT_TRUE(visitor->findNode("a"));
		ASSERT_TRUE(visitor->findNode("b"));
		ASSERT_TRUE(visitor->findNode("c"));
		ASSERT_TRUE(visitor->findNode("d"));
		ASSERT_TRUE(visitor->findNode("e"));

		ASSERT_FALSE(visitor->findNode("f"));

		{
			auto nodes = visitor.getNextNodesOf("a");
			ASSERT_EQ(1, nodes.size());
			ASSERT_EQ(std::string("b"), nodes[0]);
		}

		{
			auto nodes = visitor.getNextNodesOf("e");
			ASSERT_EQ(0, nodes.size());
		}

		{
			auto nodes = visitor.getPrevNodesOf("a");
			ASSERT_EQ(0, nodes.size());
		}

		{
			auto nodes = visitor.getPrevNodesOf("d");
			ASSERT_EQ(1, nodes.size());
			ASSERT_EQ(std::string("c"), nodes[0]);
		}
	}
};
