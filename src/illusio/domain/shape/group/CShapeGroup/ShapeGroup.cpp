#include "pch_illusio.h"

#include "ShapeGroup.h"

namespace illusio::domain::shape
{

IShapeGroupSharedPtr ShapeGroup::Create()
{
	return std::make_shared<ShapeGroup>(pass_key{});
}

using UuidGeneratorMT19937 = illusio::common::UuidGeneratorMT19937;

ShapeGroup::ShapeGroup()
	: m_uuid(UuidGeneratorMT19937()())
	, m_basePoint()
	, m_shapes()
	, m_outlineStyle()
{
}

ShapeGroup::ShapeGroup(pass_key)
	: m_uuid(UuidGeneratorMT19937()())
	, m_basePoint()
	, m_shapes()
	, m_outlineStyle()
{
}

using FrameD = ShapeGroup::FrameD;

FrameD ShapeGroup::GetFrame() const noexcept
{
	std::vector<FrameD> rects;
	rects.reserve(GetShapesCount());
	for (const auto& shape : m_shapes)
	{
		rects.push_back(shape->GetFrame());
	}

	return domain::common::axes::GetMaxFrame<double>(rects);
}

using PointD = ShapeGroup::PointD;

const PointD& ShapeGroup::GetBasePoint() const noexcept
{
	auto myFrame = GetFrame();
	auto x = myFrame.pLeftTop.x + myFrame.size.width / 2;
	auto y = myFrame.pLeftTop.y + myFrame.size.height / 2;
	m_basePoint = PointD(x, y);

	return m_basePoint;
}

using Style = ShapeGroup::Style;

const Style& ShapeGroup::GetOutlineStyle() const noexcept
{
	return *m_outlineStyle;
}

const ShapeGroup::Uuid& ShapeGroup::GetUuid() const noexcept
{
	return m_uuid;
}

void ShapeGroup::SetFrame(const FrameD& frame)
{
}

IShapeGroupSharedPtr ShapeGroup::GetShapeGroup()
{
	return shared_from_this();
}

IShapeGroupSharedConstPtr ShapeGroup::GetShapeGroup() const
{
	return shared_from_this();
}

size_t ShapeGroup::GetShapesCount() const noexcept
{
	return m_shapes.size();
}

IShapeSharedPtr ShapeGroup::GetShape(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Failed to get shape at" + std::to_string(index) + " index. Index is out of range");
	}

	auto it = m_shapes.begin();
	std::advance(it, index);

	return *it;
}

IShapeSharedConstPtr ShapeGroup::GetShape(size_t index) const
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Failed to get shape at " + std::to_string(index) + " index. Index is out of range");
	}

	auto it = m_shapes.begin();
	std::advance(it, index);

	return *it;
}

void ShapeGroup::InsertShape(const IShapeSharedPtr& shape, std::optional<size_t> index)
{
	if (std::addressof(*shape) == this)
	{
		return;
	}

	const auto insertIndex = (index.has_value())
		? std::min(*index, m_shapes.size())
		: m_shapes.size();

	auto it = m_shapes.begin();
	std::advance(it, insertIndex);

	m_shapes.insert(it, shape);
}

void ShapeGroup::RemoveShape(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Failed to remove shape at " + std::to_string(index) + " index. Index is out of range");
	}

	auto it = m_shapes.begin();
	std::advance(it, index);

	m_shapes.erase(it);
}

using Connection = ShapeGroup::Connection;

Connection ShapeGroup::DoOnFrameChange(const OnFrameChange&)
{
	return Connection();
}

} // namespace illusio::domain::shape
