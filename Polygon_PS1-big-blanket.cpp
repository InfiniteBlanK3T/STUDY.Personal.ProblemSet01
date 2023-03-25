#include "Polygon.h"

float Polygon::getSignedArea() const noexcept
{
	float Result = 0.0f, addUp = 0.0f;

	for (int i = 1; i < fNumberOfVertices; i++)
	{
		addUp += (fVertices[i - 1].y() + fVertices[i].y()) * (fVertices[i - 1].x() - fVertices[i].x());
	}

	addUp += (fVertices[fNumberOfVertices - 1].y() + fVertices[0].y()) * (fVertices[fNumberOfVertices - 1].x() - fVertices[0].x());

	Result = addUp / 2;
	
	return Result;
}

Polygon Polygon::transform(const Matrix3x3& aMatrix) const noexcept
{
	Polygon transform = *this;
	for (int i = 0; i < fNumberOfVertices; i++)
	{
		 transform.fVertices[i] = aMatrix * Vector3D(fVertices[i]);
	}
	return transform;
}