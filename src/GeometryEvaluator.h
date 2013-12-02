#ifndef GEOMETRYEVALUATOR_H_
#define GEOMETRYEVALUATOR_H_

#include "visitor.h"
#include "enums.h"
#include "memory.h"
#include "Geometry.h"

#include <utility>
#include <list>
#include <vector>
#include <map>

class GeometryEvaluator : public Visitor
{
public:
	GeometryEvaluator(const class Tree &tree);
	virtual ~GeometryEvaluator() {}

	shared_ptr<const Geometry> getGeometry(const AbstractNode &node, bool cache);
	shared_ptr<const Geometry> evaluateGeometry(const AbstractNode &node, bool allownef);

	virtual Response visit(State &state, const AbstractNode &node);
	virtual Response visit(State &state, const AbstractPolyNode &node);
	virtual Response visit(State &state, const LinearExtrudeNode &node);
	virtual Response visit(State &state, const RotateExtrudeNode &node);
	virtual Response visit(State &state, const LeafNode &node);
	virtual Response visit(State &state, const TransformNode &node);
	virtual Response visit(State &state, const CsgNode &node);
	virtual Response visit(State &state, const CgaladvNode &node);
	virtual Response visit(State &state, const RenderNode &node);
	virtual Response visit(State &state, const ProjectionNode &node);

	const Tree &getTree() const { return this->tree; }

private:
	bool isCached(const AbstractNode &node) const;
	void smartCache(const AbstractNode &node, const shared_ptr<const Geometry> &geom);
	std::vector<const class Polygon2d *> collectChildren2D(const AbstractNode &node);
	Geometry::ChildList collectChildren3D(const AbstractNode &node);
	Polygon2d *applyMinkowski2D(const AbstractNode &node);
	Polygon2d *applyHull2D(const AbstractNode &node);
	Geometry *applyHull3D(const AbstractNode &node);
	Polygon2d *applyToChildren2D(const AbstractNode &node, OpenSCADOperator op);
	Geometry *applyToChildren3D(const AbstractNode &node, OpenSCADOperator op);
	Geometry *applyToChildren(const AbstractNode &node, OpenSCADOperator op);
	void addToParent(const State &state, const AbstractNode &node, const shared_ptr<const Geometry> &geom);

	std::map<int, Geometry::ChildList> visitedchildren;
	const Tree &tree;
	shared_ptr<const Geometry> root;

public:
// FIXME: Deal with visibility
	class CGALEvaluator *cgalevaluator;
};


#endif
