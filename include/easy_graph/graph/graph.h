#ifndef H813EC8C1_3850_4320_8AC0_CE071C89B871
#define H813EC8C1_3850_4320_8AC0_CE071C89B871

#include "easy_graph/graph/node.h"
#include "easy_graph/graph/edge.h"
#include <string>
#include <set>
#include <map>

EG_NS_BEGIN

struct GraphVisitor;
struct LayoutOption;
enum class Status;

struct Graph
{
	explicit Graph(const std::string& name);

	__DECL_EQUALS(Graph);

	std::string getName() const;

	template<typename NODE>
	Node* addNode(NODE && node) {
		auto result = nodes.emplace(node.getId(), std::forward<NODE>(node));
		return &(result.first->second);
	}

	template<typename EDGE>
	Edge* addEdge(EDGE && edge) {
		auto result = edges.emplace(std::forward<EDGE>(edge));
		if (!result.second) return nullptr;
		return &(const_cast<Edge&>(*(result.first)));
	}

	Node* findNode(const NodeId&);
	const Node* findNode(const NodeId&) const;

	std::pair<const Node*, const Node*> findNodePair(const Edge&) const;
	std::pair<Node*, Node*> findNodePair(const Edge&);

	bool hasEdge(const Edge&) const;

	void remove(const NodeId&);
	void remove(const Edge&);

	void accept(GraphVisitor&) const;

	Status layout(const LayoutOption* option = nullptr) const;

private:
	std::string name;
	std::map<NodeId, Node> nodes;
	std::set<Edge> edges;
};

EG_NS_END

#endif
