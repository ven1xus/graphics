#include "PerVertexOperations.h"

// static Pipeline transformation matrices
dmat4 PerVertex::modelingTransformation;
dmat4 PerVertex::viewingTransformation;
dmat4 PerVertex::projectionTransformation;
dmat4 PerVertex::viewportTransformation;
dvec3 PerVertex::eyePositionInWorldCoords;

bool PerVertex::perVertexLightingEnabled = true;
Render_Mode PerVertex::polygonRenderMode = FILL;

// static Nnrmalized device coordinate horizontal and vertical limits
const int PerVertex::xNdcMin = -1, PerVertex::yNdcMin = -1, PerVertex::xNdcMax = 1, PerVertex::yNdcMax = 1;

// static view port limits
double PerVertex::xViewportMin, PerVertex::yViewportMin, PerVertex::xViewportMax, PerVertex::yViewportMax;

// static planes describing the normalized device coordinates view volume
std::vector<ClippingPlane> PerVertex::ndcPlanes{ ClippingPlane(dvec3(0, 1, 0), dvec3(0, -1, 0)),
											   ClippingPlane(dvec3(1, 0, 0), dvec3(-1, 0, 0)),
											   ClippingPlane(dvec3(0, 0, 1), dvec3(0, 0, -1)),
											   ClippingPlane(dvec3(-1, 0, 0), dvec3(1, 0, 0)),
											   ClippingPlane(dvec3(0, -1, 0), dvec3(0, 1, 0)),
											   ClippingPlane(dvec3(0, 0, -1), dvec3(0, 0, 1)) };


//********************************** Vertex Shading *********************************

void PerVertex::applyLighting( std::vector<VertexData> & worldCoords )
{
    for (auto p : ndcPlanes) {

    }
    for(auto &wCoord : worldCoords) {
            
        double alpha = wCoord.material.diffuseColor.a;
        color totalLight = wCoord.material.emissiveColor;
        for(auto light : lights) {
            totalLight += light->illuminate(PerVertex::eyePositionInWorldCoords,
                                            wCoord.worldPosition,
                                            wCoord.worldNormal,
                                            wCoord.material);
        }
        wCoord.shadedColor = totalLight;
        wCoord.material.diffuseColor.a = alpha;
    }
} // end applyLighting


// Break general convex polygons into triangles.
std::vector<VertexData> PerVertex::triangulate(const std::vector<VertexData> & poly)
{
	std::vector<VertexData> triangles;
	triangles.push_back(poly[0]);
	triangles.push_back(poly[1]);
	triangles.push_back(poly[2]);

	for (unsigned int i = 2; i < poly.size() - 1; i++) {

		triangles.push_back(poly[0]);
		triangles.push_back(poly[i]);
		triangles.push_back(poly[i + 1]);
	}

	return triangles;

} // end triangulate

std::vector<VertexData> PerVertex::clipPolygon(const std::vector<VertexData> & clipCoords)
{
	std::vector<VertexData> ndcCoords;

	if (clipCoords.size()>2) {

		std::vector<VertexData> polygon;

		for (unsigned int i = 0; i<clipCoords.size() - 2; i += 3) {

			polygon.push_back(clipCoords[i]);
			polygon.push_back(clipCoords[i + 1]);
			polygon.push_back(clipCoords[i + 2]);

			for (ClippingPlane plane : ndcPlanes) {
				polygon = clipAgainstPlane(polygon, plane);
			}

			if (polygon.size() > 3) {
				polygon = triangulate(polygon);
			}

			for (VertexData v : polygon) {
				ndcCoords.push_back(v);
			}
			polygon.clear();
		}
	}

	return ndcCoords;

}

std::vector<VertexData> PerVertex::clipAgainstPlane(std::vector<VertexData> & verts, ClippingPlane & plane)
{
	std::vector<VertexData> output;

	if (verts.size() > 2) {

		verts.push_back(verts[0]);

		for (unsigned int i = 1; i < verts.size(); i++) {

			bool v0In = plane.insidePlane(verts[i - 1]);
			bool v1In = plane.insidePlane(verts[i]);

			if (v0In && v1In) {

				output.push_back(verts[i]);
			}
			else if (v0In || v1In) {

				VertexData I = plane.findIntersection(verts[i - 1], verts[i]);
				output.push_back(I);

				if (!v0In && v1In) {

					output.push_back(verts[i]);
				}
			}
		}
	}

	return output;

} // end clipAgainstPlane

//********************************** Vertex Transformation *********************************

// Applies a modeling transformation in the form of a matrix to a list of vertices. Transforms 
// the vertices and normals to World coordinates.
std::vector<VertexData> PerVertex::transformVerticesToWorldCoordinates( const dmat4 & modelMatrix, const std::vector<VertexData> & vertices )
{
	// Create 3 x 3 matrix for transforming normal vectors to world coordinates
	glm::dmat3 modelingTransfomationForNormals( modelMatrix );
	modelingTransfomationForNormals = glm::transpose( glm::inverse( modelingTransfomationForNormals ) );

	std::vector<VertexData> transformedVertices;

	for( VertexData v : vertices ) {

		// Copy the vertex data
		VertexData vt = v;

		// Transform the position and surface normal to world coordinates
		vt.position = modelMatrix * v.position;
		vt.worldPosition = vt.position;
		vt.worldNormal = modelingTransfomationForNormals * v.localNormal;

		transformedVertices.push_back( vt );
	}

	return transformedVertices;

} // end transformVertices


// Applies a transformation in the form of a matrix to a list of vertices.
std::vector<VertexData> PerVertex::transformVertices( const dmat4 & transMatrix, const std::vector<VertexData> & vertices )
{
	std::vector<VertexData> transformedVertices;

	for( VertexData v : vertices ) {

		// Copy the vertex data
		VertexData vt = v;

		// Transform the position
		vt.position = transMatrix * v.position;

		// Add the vertex for further processing by the pipeline
		transformedVertices.push_back( vt );
	}

	return transformedVertices;

} // end transformVertices

//********************************** Triangle Pipeline *********************************

// Tranforms triangle vertices from world to view port coordinate via eye, clip, and normalized device coordinates. 
// Vertices are clipped and backfaces are culled. Lighting calculations are performed in World coordinates.
void PerVertex::processTriangleVertices(const std::vector<VertexData> & objectCoords)
{
	// Modeling tranformation
	std::vector<VertexData> worldCoords = transformVerticesToWorldCoordinates(modelingTransformation, objectCoords);

	if (perVertexLightingEnabled == true) {
	
		// Perform lighting calculations in World coordinates
		applyLighting(worldCoords);
	}
  
	// Viewing Transformation
  	std::vector<VertexData> eyeCoords = transformVertices(viewingTransformation, worldCoords);
  
	// Projections Transformation
  	std::vector<VertexData> projCoords = transformVertices(projectionTransformation, eyeCoords);
  
  	std::vector<VertexData> clipCoords;
  
  	// Perspective division
  	for (VertexData v : projCoords) {
  
  		v.position = v.position / v.position.w;
  		clipCoords.push_back(v);
  	}
  
	// Backface Cullling
    clipCoords = removeBackwardFacingTriangles(clipCoords); 
  	// Clipping
	//TODO
	std::vector<VertexData> ndcCoords = clipCoords;
  
	// Window Transformation
  	std::vector<VertexData> windowCoords = transformVertices(viewportTransformation, ndcCoords);
  
	if (polygonRenderMode == FILL) {
	
		drawManyFilledTriangles(windowCoords);
	}
	else {

		drawManyWireFrameTriangles(windowCoords);
	}
  
} // end processTriangleVertices
  
//********************************** Line Segment Pipeline *********************************

 std::vector<VertexData> PerVertex::removeBackwardFacingTriangles(const std::vector<VertexData> & triangleVerts) {
    std::vector<VertexData> forwardFacingTriangles;
    
    const dvec3 viewDirection(0.0, 0.0, -1.0);
    
    for(unsigned int i = 0; i < triangleVerts.size() - 2; i += 3) {
       dvec3 normal = findUnitNormal(triangleVerts[i].position,
               triangleVerts[i+1].position, triangleVerts[i+2].position);
        if (glm::dot(viewDirection, normal) <= 0.0) {
            forwardFacingTriangles.push_back(triangleVerts[i]);
            forwardFacingTriangles.push_back(triangleVerts[i+1]);
            forwardFacingTriangles.push_back(triangleVerts[i+2]);
        }
    }


    return forwardFacingTriangles;
 }

// Tranforms line segments from world to view port coordinate via eye, clip, and normalized device coordinates. 
// Vertices are clipped . Lighting calculations are performed in World coordinates.
void PerVertex::processLineSegments(const std::vector<VertexData> & objectCoords)
{
	// Modeling Transformation
  	std::vector<VertexData> worldCoords = transformVerticesToWorldCoordinates(modelingTransformation,objectCoords);
  
	// Viewing Transformation
  	std::vector<VertexData> eyeCoords = transformVertices(viewingTransformation, worldCoords);
  
	// Projection Transformation
  	std::vector<VertexData> projCoords = transformVertices(projectionTransformation, eyeCoords);
  
  	std::vector<VertexData> clipCoords;
  
  	// Perspective division
  	for (VertexData v : projCoords) {
  
  		v.position = v.position / v.position.w;
  		clipCoords.push_back(v);
  	}
  
  	// Clipping
	//TODO
	std::vector<VertexData> ndcCoords = clipCoords;
  
	// Window Transformation
  	std::vector<VertexData> windowCoords = transformVertices(viewportTransformation, ndcCoords);
  
	drawManyLines( windowCoords );
  
} // end linePipeline
