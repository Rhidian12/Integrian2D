#include "NavGraphPolygon.h"
#include "../../Renderer/Renderer.h"

#include <algorithm>
#include <limits>
#include <set>

#undef min // THESE MACROS ARE THE WORST
#undef max // THESE MACROS ARE THE WORST

namespace Integrian2D
{
	NavGraphPolygon::NavGraphPolygon(const std::vector<Point2f>& vertices)
		: m_Vertices{ vertices }
		, m_ChildPolygons{}
		, m_IsTriangulated{}
	{}

	NavGraphPolygon::NavGraphPolygon(const std::vector<Point2f>& outerVertices, const std::vector<std::vector<Point2f>>& innerVertices)
		: m_Vertices{ outerVertices }
		, m_ChildPolygons{}
		, m_IsTriangulated{}
	{
		for (const std::vector<Point2f>& vector : innerVertices)
			AddChild(vector);
	}

	void NavGraphPolygon::Render() const noexcept
	{
		if (m_IsTriangulated)
		{
			for (const PTrianglef& triangle : m_Triangles)
				Renderer::GetInstance()->RenderTriangle(triangle);
		}

		for (size_t i{}; i < m_Vertices.size(); ++i)
		{
			if (i == m_Vertices.size() - 1)
				Renderer::GetInstance()->RenderLine(m_Vertices[i], m_Vertices[0], 3.f);
			else
				Renderer::GetInstance()->RenderLine(m_Vertices[i], m_Vertices[i + 1], 3.f);
		}
	}

	//void NavGraphPolygon::Triangulate() noexcept
	//{
	//	m_IsTriangulated = true;
	//	m_Triangles.clear();

	//	// Make a triangle that encompasses our entire polygon
	//	const float minX{ GetMinXVertex() };
	//	const float minY{ GetMinYVertex() };
	//	const float maxX{ GetMaxXVertex() };
	//	const float maxY{ GetMaxYVertex() };

	//	const float deltaX{ maxX - minX };
	//	const float deltaY{ maxY - minY };
	//	const float biggestDifference{ std::max(deltaX, deltaY) };

	//	const PTrianglef superTriangle{ Point2f{minX - biggestDifference, minY - biggestDifference},
	//		Point2f{GetCenterOfPolygon().x, maxY + biggestDifference},
	//		Point2f{maxX + biggestDifference, minY - biggestDifference} };

	//	m_Triangles.push_back(superTriangle);

	//	for (const Point2f& p : m_Vertices)
	//	{
	//		std::set<PTrianglef> badTriangles{};

	//		for (const PTrianglef& t : m_Triangles)
	//		{
	//			const float squaredDistance{ DistanceSquared(p, GetCenter(t)) };
	//			const float radiusSquared{ DistanceSquared(GetCenter(t), *t.begin()) };

	//			if (squaredDistance <= radiusSquared)
	//				badTriangles.insert(t);
	//		}

	//		std::vector<PLinef> polygon{};

	//		for (auto it{ badTriangles.begin() }; it != badTriangles.end(); ++it)
	//		{

	//		}

	//		for (size_t i{}; i < badTriangles.size(); ++i)
	//		{
	//			const PLinef edges[3]{ GetEdgeOne(badTriangles[i]), GetEdgeTwo(badTriangles[i]), GetEdgeThree(badTriangles[i]) };
	//			bool foundEdges[3]{};

	//			for (size_t j{}; j < badTriangles.size(); ++j)
	//			{
	//				if (i == j)
	//					continue;

	//				if (!foundEdges[0])
	//					if (edges[0] == GetEdgeOne(badTriangles[j]))
	//						foundEdges[0] = true;

	//				if (!foundEdges[1])
	//					if (edges[1] == GetEdgeTwo(badTriangles[j]))
	//						foundEdges[1] = true;

	//				if (!foundEdges[2])
	//					if (edges[2] == GetEdgeThree(badTriangles[j]))
	//						foundEdges[2] = true;
	//			}

	//			// Add edges to polygon if they werent found
	//			for (size_t j{}; j < 3; ++j)
	//				if (!foundEdges[j])
	//					polygon.push_back(edges[j]);
	//		}

	//		// create new triangles
	//		for (const PLinef& l : polygon)
	//			m_Triangles.push_back(PTrianglef{ l.begin, l.end, p });
	//	}

	//	// clean up
	//	m_Triangles.erase(std::remove_if(m_Triangles.begin(), m_Triangles.end(), [&superTriangle](const PTrianglef& t)->bool
	//		{
	//			for (int i{}; i < 3; ++i)
	//				if (*(superTriangle.begin() + i) == *(t.begin() + i))
	//					return true;

	//			return false;
	//		}), m_Triangles.end());
	//}

	//void NavGraphPolygon::Triangulate() noexcept
	//{
	//	m_IsTriangulated = true;
	//	m_Triangles.clear();

	//	// Make a triangle that encompasses our entire polygon
	//	const float minX{ GetMinXVertex() };
	//	const float minY{ GetMinYVertex() };
	//	const float maxX{ GetMaxXVertex() };
	//	const float maxY{ GetMaxYVertex() };

	//	const float deltaX{ maxX - minX };
	//	const float deltaY{ maxY - minY };
	//	const float biggestDifference{ std::max(deltaX, deltaY) };

	//	const PTrianglef superTriangle{ Point2f{minX - biggestDifference, minY - biggestDifference},
	//		Point2f{GetCenterOfPolygon().x, maxY + biggestDifference},
	//		Point2f{maxX + biggestDifference, minY - biggestDifference} };

	//	m_Triangles.push_back(superTriangle);

	//	for (const Point2f& p : m_Vertices)
	//	{
	//		std::vector<PLinef> polygon{};
	//		std::vector<PLinef> badPolygon{};
	//		std::vector<PTrianglef> badTriangles{};

	//		for (const PTrianglef& t : m_Triangles)
	//		{
	//			const float squaredDistance{ DistanceSquared(p, GetCenter(t)) };
	//			const float radiusSquared{ DistanceSquared(GetCenter(t), *t.begin()) };

	//			if (squaredDistance <= radiusSquared)
	//			{
	//				badTriangles.push_back(t);
	//				polygon.push_back(GetEdgeOne(t));
	//				polygon.push_back(GetEdgeTwo(t));
	//				polygon.push_back(GetEdgeThree(t));
	//			}
	//		}

	//		for (const PTrianglef& t : badTriangles)
	//			m_Triangles.erase(std::remove(m_Triangles.begin(), m_Triangles.end(), t), m_Triangles.end());

	//		for (size_t i{}; i < polygon.size(); ++i)
	//		{
	//			for (size_t j{ i + i }; j < polygon.size(); ++j)
	//			{
	//				if (polygon[i] == polygon[j])
	//				{
	//					badPolygon.push_back(polygon[i]);
	//					badPolygon.push_back(polygon[j]);
	//				}
	//			}
	//		}

	//		for (const PLinef& l : badPolygon)
	//			polygon.erase(std::remove(polygon.begin(), polygon.end(), l), polygon.end());

	//		for (const PLinef& l : polygon)
	//			m_Triangles.push_back(PTrianglef{ l.begin, l.end, p });
	//	}

	//	// clean up
	//	m_Triangles.erase(std::remove_if(m_Triangles.begin(), m_Triangles.end(), [&superTriangle](const PTrianglef& t)->bool
	//		{
	//			for (int i{}; i < 3; ++i)
	//				if (*(superTriangle.begin() + i) == *(t.begin() + i))
	//					return true;

	//			return false;
	//		}), m_Triangles.end());
	//}

	//void NavGraphPolygon::Triangulate() noexcept
	//{
	//	m_IsTriangulated = true;
	//	m_Triangles.clear();

	//	// Use a local copy of the vertices
	//	std::vector<Point2f> sortedVertices{ m_Vertices };

	//	// Select a starting point (I'll just take the first vertex in m_Vertices)
	//	const Point2f startVertex{ sortedVertices[0] };

	//	// Remove the start vertex from our vertices
	//	sortedVertices.erase(std::remove(sortedVertices.begin(), sortedVertices.end(), startVertex), sortedVertices.end());

	//	// Sort the vertices based on distance from the startVertex
	//	std::sort(sortedVertices.begin(), sortedVertices.end(), [&startVertex](const Point2f& a, const Point2f& b)->bool
	//		{
	//			return DistanceSquared(a, startVertex) <= DistanceSquared(b, startVertex);
	//		});

	//	// Find the closest point to the starting vertex, which SHOULD be the first element in the sorted vertices
	//	const Point2f vertexOne{ sortedVertices[0] };

	//	// Remove vertexOne from our vertices
	//	sortedVertices.erase(std::remove(sortedVertices.begin(), sortedVertices.end(), vertexOne), sortedVertices.end());

	//	// Find the point that creates the smallest circumcircle with the startVertex and vertexOne
	//	float smallestCircumCircle{ std::numeric_limits<float>::max() };
	//	Point2f vertexTwo{};
	//	Point2f centerOfCircumCircle{};

	//	for (const Point2f& p : sortedVertices)
	//	{
	//		PTrianglef triangle{ startVertex, vertexOne, p };

	//		const Point2f& center{ GetCenter(triangle) };
	//		const float distance{ DistanceSquared(center, p) };

	//		if (distance <= smallestCircumCircle)
	//		{
	//			smallestCircumCircle = distance;
	//			vertexTwo = p;
	//			centerOfCircumCircle = center;
	//		}
	//	}

	//	// Order these 3 points for a right handed system(???)

	//	// Remove vertexTwo from our vertices
	//	sortedVertices.erase(std::remove(sortedVertices.begin(), sortedVertices.end(), vertexTwo), sortedVertices.end());

	//	// now sort the remaining vertices based on the distance from the center of the circumcircle
	//	std::sort(sortedVertices.begin(), sortedVertices.end(), [&centerOfCircumCircle](const Point2f& a, const Point2f& b)->bool
	//		{
	//			return DistanceSquared(a, centerOfCircumCircle) <= DistanceSquared(b, centerOfCircumCircle);
	//		});

	//	// now start adding these points to the root triangle we made
	//	for (size_t i{}; i < sortedVertices.size(); ++i)
	//	{
	//		m_Triangles.push_back(PTrianglef{ sortedVertices[i], sortedVertices[i + 2], sortedVertices[i + 1] });

	//		if (i == sortedVertices.size() - 3) // final triangle
	//			break; // stop the loop
	//	}
	//}

	void NavGraphPolygon::Triangulate() noexcept
	{
		m_IsTriangulated = true;
		m_Triangles.clear();

		std::vector<Point2f> vertices{ m_Vertices };

		const Point2f& startVertex{ m_Vertices[0] };

		vertices.erase(std::remove(vertices.begin(), vertices.end(), startVertex), vertices.end());

		std::sort(vertices.begin(), vertices.end(), [&startVertex](const Point2f& a, const Point2f& b)->bool
			{
				return DistanceSquared(a, startVertex) <= DistanceSquared(b, startVertex);
			});

		for (size_t i{}; i < vertices.size(); ++i)
		{
			if (!Utils::AreEqual(startVertex.x, vertices[i].x) || !Utils::AreEqual(startVertex.x, vertices[i + 1].x))
			{
				if (!Utils::AreEqual(startVertex.y, vertices[i].y) || !Utils::AreEqual(startVertex.y, vertices[i + 1].y))
				{
					m_Triangles.push_back(PTrianglef{ startVertex, vertices[i], vertices[i + 1] });
					break;
				}
			}
		}

		for (size_t i{ 1 }; i < vertices.size(); ++i)
		{
			m_Triangles.push_back(PTrianglef{ vertices[i], vertices[i + 2], vertices[i + 1] });

			if (i == vertices.size() - 3) // final triangle
				break; // stop the loop
		}

		std::vector<PTrianglef> overlappingTriangles{};

		bool areThereNoOverlappingTriangles{ false };
		do
		{
			overlappingTriangles.clear();

			// Identify overlapping triangles
			for (size_t i{}; i < m_Triangles.size(); ++i)
			{
				for (size_t j{ i + 1 }; j < m_Triangles.size(); ++j)
				{
					for (int k{}; k < 3; ++k)
					{
						const Point2f& triangleOnePoint{ *(m_Triangles[i].begin() + k) };
						if (DoVectorsIntersect(m_Triangles[i].begin() + k, m_Triangles[j].begin() + k, GetEdgeOne(m_Triangles[j])))
						{
							if (std::find(overlappingTriangles.cbegin(), overlappingTriangles.cend(), m_Triangles[i]) == overlappingTriangles.cend())
								overlappingTriangles.push_back(m_Triangles[i]);
							if (std::find(overlappingTriangles.cbegin(), overlappingTriangles.cend(), m_Triangles[j]) == overlappingTriangles.cend())
								overlappingTriangles.push_back(m_Triangles[j]);
						}
					}
				}
			}

			// Make new non overlapping triangles
			std::vector<Point2f> unusedVertices{};
			for (const PTrianglef& t : overlappingTriangles)
			{
				m_Triangles.erase(std::remove(m_Triangles.begin(), m_Triangles.end(), t), m_Triangles.end());

				for (const Point2f& p : t)
					unusedVertices.push_back(p);
			}

			unusedVertices.erase(std::unique(unusedVertices.begin(), unusedVertices.end()), unusedVertices.end());

			for (size_t i{}; i < overlappingTriangles.size(); ++i)
			{
				if (unusedVertices.size() > 2)
				{
					int indexOne{ int(rand() % unusedVertices.size()) };
					int indexTwo{ int(rand() % unusedVertices.size()) };
					int indexThree{ int(rand() % unusedVertices.size()) };

					while (indexOne == indexTwo || indexOne == indexThree || indexTwo == indexThree)
					{
						indexTwo = int(rand() % unusedVertices.size());
						indexOne = int(rand() % unusedVertices.size());
						indexThree = int(rand() % unusedVertices.size());
					}

					m_Triangles.push_back(PTrianglef{ unusedVertices[indexOne], unusedVertices[indexTwo], unusedVertices[indexThree] });
				}
				else if (unusedVertices.size() == 2)
				{
					int indexOne{ int(rand() % unusedVertices.size()) };
					int indexTwo{ int(rand() % unusedVertices.size()) };

					while (indexOne == indexTwo)
					{
						indexOne = int(rand() % unusedVertices.size());
						indexTwo = int(rand() % unusedVertices.size());
					}

					float distance{ std::numeric_limits<float>::max() };
					const Point2f centerPoint{ (unusedVertices[indexOne] + unusedVertices[indexTwo]) / 2.f };
					Point2f thirdVertex{};
					do
					{
						thirdVertex = *std::find_if(m_Vertices.cbegin(), m_Vertices.cend(), [&distance, &centerPoint](const Point2f& a)->bool
							{
								const float newDistance{ DistanceSquared(a, centerPoint) };
								if (newDistance <= distance)
								{
									distance = newDistance;
									return true;
								}
								else
									return false;
							});
					} while (thirdVertex == unusedVertices[indexOne] || thirdVertex == unusedVertices[indexTwo]);

					m_Triangles.push_back(PTrianglef{ unusedVertices[indexOne], unusedVertices[indexTwo], thirdVertex });
				}
				else if (unusedVertices.size() == 1)
				{
					int indexOne{ int(rand() % unusedVertices.size()) };
					Point2f closestVertices[2]{ Point2f{}, Point2f{} };

					for (int j{}; j < 2; ++j)
					{
						float distance{ std::numeric_limits<float>::max() };
						Point2f newVertex{};
						do
						{
							newVertex = *std::find_if(m_Vertices.cbegin(), m_Vertices.cend(), [&distance, &unusedVertices, indexOne](const Point2f& a)->bool
								{
									const float newDistance{ DistanceSquared(a, unusedVertices[indexOne]) };
									if (newDistance <= distance)
									{
										distance = newDistance;
										return true;
									}
									else
										return false;
								});
						} while (newVertex == unusedVertices[indexOne] || newVertex == closestVertices[(j == 0 ? 1 : 0)]);
					}

					m_Triangles.push_back(PTrianglef{ unusedVertices[indexOne], closestVertices[0], closestVertices[1] });
				}
				else
					break;
			}

			areThereNoOverlappingTriangles = overlappingTriangles.empty();

		} while (!areThereNoOverlappingTriangles);
	}

	NavGraphPolygon* NavGraphPolygon::AddChild(const std::vector<Point2f> vertices) noexcept
	{
		m_ChildPolygons.push_back(NavGraphPolygon{ vertices });
		return &m_ChildPolygons.back();
	}

	void NavGraphPolygon::AddChild(const NavGraphPolygon child) noexcept
	{
		m_ChildPolygons.push_back(child);
	}

	void NavGraphPolygon::RemoveChild(const NavGraphPolygon& childToRemove) noexcept
	{
		m_ChildPolygons.erase(std::remove(m_ChildPolygons.begin(), m_ChildPolygons.end(), childToRemove), m_ChildPolygons.end());
	}

	Point2f NavGraphPolygon::GetCenterOfPolygon() const noexcept
	{
		Point2f average{};

		for (const Point2f& p : m_Vertices)
			average += p;

		return average / static_cast<float>(m_Vertices.size());
	}

	bool NavGraphPolygon::IsTriangulated() const noexcept
	{
		return m_IsTriangulated;
	}

	float NavGraphPolygon::GetMaxXVertex() const noexcept
	{
		float maxXPosition{ std::numeric_limits<float>::min() };

		for (const Point2f& position : m_Vertices)
			if (position.x > maxXPosition)
				maxXPosition = position.x;

		return maxXPosition;
	}

	float NavGraphPolygon::GetMaxYVertex() const noexcept
	{
		float maxYPosition{ std::numeric_limits<float>::min() };

		for (const Point2f& position : m_Vertices)
			if (position.y > maxYPosition)
				maxYPosition = position.y;

		return maxYPosition;
	}

	float NavGraphPolygon::GetMinXVertex() const noexcept
	{
		float minXPosition{ std::numeric_limits<float>::max() };

		for (const Point2f& position : m_Vertices)
			if (position.x < minXPosition)
				minXPosition = position.x;

		return minXPosition;
	}

	float NavGraphPolygon::GetMinYVertex() const noexcept
	{
		float minYPosition{ std::numeric_limits<float>::max() };

		for (const Point2f& position : m_Vertices)
			if (position.y < minYPosition)
				minYPosition = position.y;

		return minYPosition;
	}

	bool NavGraphPolygon::IsOverlapping(const NavGraphPolygon& p) const noexcept
	{
		// == Check if they CERTAINLY cannot overlap ==
		if (GetMinXVertex() > p.GetMaxXVertex() || GetMaxXVertex() < p.GetMinXVertex())
			return false;

		// == Check if they CERTAINLY cannot overlap ==
		if (GetMinYVertex() > p.GetMaxYVertex() || GetMaxYVertex() < p.GetMinYVertex())
			return false;

		// == The Expensive way to check if they overlap ==
		for (size_t i{}; i < m_Vertices.size(); ++i)
		{
			const Point2f& startVertex{ m_Vertices[i] };
			Point2f endVertex{ m_Vertices[i + 1] };

			if (i == m_Vertices.size() - 1)
				endVertex = m_Vertices[0];

			for (size_t j{}; j < p.m_Vertices.size(); ++j)
			{
				if (j == p.m_Vertices.size() - 1)
				{
					if (DoVectorsIntersect(startVertex, Vector2f{ startVertex,  endVertex }, p.m_Vertices[j], Vector2f{ p.m_Vertices[j], p.m_Vertices[0] }, nullptr))
						return true;
				}
				else
				{
					if (DoVectorsIntersect(startVertex, Vector2f{ startVertex,  endVertex }, p.m_Vertices[j], Vector2f{ p.m_Vertices[j], p.m_Vertices[j + 1] }, nullptr))
						return true;
				}
			}
		}

		return false;
	}

	const std::vector<Point2f>& NavGraphPolygon::GetVertices() const noexcept
	{
		return m_Vertices;
	}

	const std::vector<NavGraphPolygon>& NavGraphPolygon::GetChildren() const noexcept
	{
		return m_ChildPolygons;
	}
}