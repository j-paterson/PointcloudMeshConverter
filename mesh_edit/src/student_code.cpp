#include "student_code.h"
#include "mutablePriorityQueue.h"

using namespace std;

namespace CGL
{
    void BezierCurve::evaluateStep()
    {
        // TODO Part 1.
        // Perform one step of the Bezier curve's evaluation at t using de Casteljau's algorithm for subdivision.
        // Store all of the intermediate control points into the 2D vector evaluatedLevels.
        // back() returns last element in vector
        // push_back() adds an element to the end of vector
        std::vector<Vector2D> currentLevel = evaluatedLevels[evaluatedLevels.size() - 1];
        std::vector<Vector2D> nextLevel;

        // evaluateStep should return immediately if the Bezier curve has already been completely evaluated at t
        if(currentLevel.size() == 1){
          std::cout << "Bezier Curve is complete evaluated";
          return;
        }

        // Want to sort through all sets of points in currentLevel and interpolate to create nextLevel.
        for(int i=0; i<(currentLevel.size()-1);i++){
          Vector2D p1 = currentLevel[i];
          Vector2D p2 = currentLevel[i+1];
          Vector2D p3 = ((1-t)*p1)+(t*p2);
          nextLevel.push_back(p3);
        }

        evaluatedLevels.push_back(nextLevel);
    }


    Vector3D BezierPatch::evaluate(double u, double v) const
    {
        // TODO Part 2.
        // Evaluate the Bezier surface at parameters (u, v) through 2D de Casteljau subdivision.
        // (i.e. Unlike Part 1 where we performed one subdivision level per call to evaluateStep, this function
        // should apply de Casteljau's algorithm until it computes the final, evaluated point on the surface)

        //controlPoints is holding 4 arrays of 4 points.

        std::vector<Vector3D> controlCurves;

        for(int i=0; i<4; i++){
            //cout << "Control curve #";
            //cout << controlCurves.size() <<endl;
            std::vector<Vector3D> nextRow;
            for(int j=0; j<4; j++){
                nextRow.push_back(controlPoints[i][j]);
                //cout << "Accessing controlPoints"<<endl;
            }
            //cout << "Sending nextRow to be evaluated"<<endl;
            controlCurves.push_back(evaluate1D(nextRow, u));
        }
        return evaluate1D(controlCurves, v);
    }

    Vector3D BezierPatch::evaluate1D(std::vector<Vector3D> points, double t) const
    {
        // TODO Part 2.
        // Optional helper function that you might find useful to implement as an abstraction when implementing BezierPatch::evaluate.
        // Given an array of 4 points that lie on a single curve, evaluates the Bezier curve at parameter t using 1D de Casteljau subdivision.
        //cout << "Analyzing1:";

        std::vector< std::vector<Vector3D> > previousLevels;
        previousLevels.push_back(points);

        while(previousLevels[previousLevels.size()-1].size()>1){
            //cout << "Analyzing2:";
            //cout << previousLevels.size() <<endl;
            std::vector<Vector3D> nextLevel;
            std::vector<Vector3D> currentCurve = previousLevels[previousLevels.size() - 1];
            for(int i=0; i<(currentCurve.size()-1);i++){
                Vector3D p1 = currentCurve[i];
                Vector3D p2 = currentCurve[i+1];
                Vector3D p3 = ((1-t)*p1)+(t*p2);
                nextLevel.push_back(p3);
            }
            previousLevels.push_back(nextLevel);
        }

        return previousLevels.back()[0];
    }



    Vector3D Vertex::normal( void ) const
    {
        // TODO Part 3.
        // Returns an approximate unit normal at this vertex, computed by
        // taking the area-weighted average of the normals of neighboring
        // triangles, then normalizing.

        // if we delete a mesh element, we must be certain that no existing elements
        // still point to it; the halfedge data structure does not take care of these
        // relationships for you automatically.
        Vector3D n = Vector3D(0,0,0);

        HalfedgeCIter h = this->halfedge();// get one of the outgoing halfedges of the vertex
        int neighboringFaces=0;
        do{
            h = h->twin();
            //Get the vertex at the source of the twin for the outgoing halfedge
            VertexCIter vertex1 = h->vertex();
            //subtract vertex position from original vertex position to get Vector3D
            Vector3D pos1 = (this->position)-(vertex1->position);
//            cout << vertex1->position <<endl;

            //next and then check ahead to the twin to get it's source vertex

            h = h->next();
            HalfedgeCIter h_twin = h->twin();

            VertexCIter vertex2 = h_twin->vertex();
            //subtract vertex position from original vertex position to get Vector3D
            Vector3D pos2 = (this->position)-(vertex2->position);
//            cout << vertex2->position <<endl;

            //add cross product to n
            n += cross(pos1, pos2);
            neighboringFaces+=1;

//            cout << "the positions have been crossed: ";
//            cout << cross(pos1, pos2) <<endl;
//            cout << "N is: ";
//            cout << n <<endl;
        }while(h != this->halfedge());

        return n/neighboringFaces;
    }

    EdgeIter HalfedgeMesh::flipEdge( EdgeIter e0 )
    {
        // TODO Part 4.
        // TODO This method should flip the given edge and return an iterator to the flipped edge.

        // Never flip boundary edges (just return immediately if either neighboring face is a boundary loop).
        if(e0->halfedge()->face()->isBoundary()){
            cout << "That got registered as a boundary edge!";
            return e0;
        }
        if(e0->halfedge()->twin()->face()->isBoundary()){
            cout << "That got registered as a boundary edge!";
            return e0;
        }

        //Edges before flip
        HalfedgeIter h0 = e0->halfedge();
        HalfedgeIter h1 = h0->next();
        HalfedgeIter h2 = h1->next();
        HalfedgeIter h3 = h0->twin();
        HalfedgeIter h4 = h3->next();
        HalfedgeIter h5 = h4->next();
        HalfedgeIter h6 = h2->twin();
        HalfedgeIter h7 = h1->twin();
        HalfedgeIter h8 = h5->twin();
        HalfedgeIter h9 = h4->twin();
        //Vertices before flip
        VertexIter v0 = h3->vertex();
        VertexIter v1 = h0->vertex();
        VertexIter v2 = h2->vertex();
        VertexIter v3 = h5->vertex();
        //Edges before flip
        EdgeIter e1 = h2->edge();
        EdgeIter e2 = h1->edge();
        EdgeIter e3 = h5->edge();
        EdgeIter e4 = h4->edge();
        //Faces before flip
        FaceIter f0 = h0->face();
        FaceIter f1 = h3->face();

//        cout << "Made it through assigning before flip!";

        //FLIP
        //Edges after flip
        //void setNeighbors(next, twin, vertex, edge, face)
        h0->setNeighbors(h1, h3, v3, e0, f0);
        h1->setNeighbors(h2, h6, v2, e1, f0);
        h2->setNeighbors(h0, h9, v1, e4, f0);
        h3->setNeighbors(h4, h0, v2, e0, f1);
        h4->setNeighbors(h5, h8, v3, e3, f1);
        h5->setNeighbors(h3, h7, v0, e2, f1);
        //outer edges
        h6->twin()= h1;
        h7->twin()= h5;
        h8->twin()= h4;
        h9->twin()= h2;

//        cout << "Made it through flipping edges!";
        //Vertices after flip
        v0->halfedge() = h5;
        v1->halfedge() = h2;
        v2->halfedge() = h1;
        v3->halfedge() = h4;
        //Edges after flip
        e0->halfedge() = h0;
        e1->halfedge() = h1;
        e2->halfedge() = h5;
        e3->halfedge() = h4;
        e4->halfedge() = h2;
        //Faces after flip
        f0->halfedge() = h0;
        f1->halfedge() = h3;
//        cout << "Done!";
        return e0;
    }

    VertexIter HalfedgeMesh::splitEdge( EdgeIter e0 )
    {
        // TODO Part 5.
        // TODO This method should split the given edge and return an iterator to the newly inserted vertex.
        // TODO The halfedge of this vertex should point along the edge that was split, rather than the new edges.
        // Never split boundary edges (just return immediately if either neighboring face is a boundary loop).
        if(e0->halfedge()->face()->isBoundary()){
            cout << "That got registered as a boundary edge!";
            return e0->halfedge()->vertex();
        }
        if(e0->halfedge()->twin()->face()->isBoundary()){
            cout << "That got registered as a boundary edge!";
            return e0->halfedge()->vertex();
        }

        //Edges before flip
        HalfedgeIter h0 = e0->halfedge();
        HalfedgeIter h1 = h0->next();
        HalfedgeIter h2 = h1->next();
        HalfedgeIter h3 = h0->twin();
        HalfedgeIter h4 = h3->next();
        HalfedgeIter h5 = h4->next();
        HalfedgeIter h6 = h2->twin();
        HalfedgeIter h7 = h1->twin();
        HalfedgeIter h8 = h5->twin();
        HalfedgeIter h9 = h4->twin();
        //Vertices before flip
        VertexIter v0 = h3->vertex();
        VertexIter v1 = h0->vertex();
        VertexIter v2 = h2->vertex();
        VertexIter v3 = h5->vertex();
        //Edges before flip
        EdgeIter e1 = h2->edge();
        EdgeIter e2 = h1->edge();
        EdgeIter e3 = h5->edge();
        EdgeIter e4 = h4->edge();
        //Faces before flip
        FaceIter f0 = h0->face();
        FaceIter f1 = h3->face();

        //SPLIT: NEW OBJECTS

        //New Vertex
        VertexIter m = this->newVertex();

        //Assign proper position to new vertex
        Vector3D pos1 = e0->halfedge()->vertex()->position;
        Vector3D pos2 = e0->halfedge()->twin()->vertex()->position;
        Vector3D pos3 = (pos1+pos2)/2;
        m->position = pos3;

        //New Halfedges
        HalfedgeIter h10 = this->newHalfedge();
        HalfedgeIter h11 = this->newHalfedge();
        HalfedgeIter h12 = this->newHalfedge();
        HalfedgeIter h13 = this->newHalfedge();
        HalfedgeIter h14 = this->newHalfedge();
        HalfedgeIter h15 = this->newHalfedge();

        //New Edges
        EdgeIter e5 = this->newEdge();
//        e5->isNew =false;
        EdgeIter e6 = this->newEdge();
//        e6->isNew =true;
        EdgeIter e7 = this->newEdge();
//        e7->isNew =true;

        //New Faces
        FaceIter f2 = this->newFace();
        FaceIter f3 = this->newFace();

        //SPLIT: POINTER REASSIGNMENT

        //Halfedges after flip
        //void setNeighbors(next, twin, vertex, edge, face)
        h0->setNeighbors(h15, h3, v1, e0, f0);
        h1->setNeighbors(h14, h7, v0, e2, f2);
        h2->setNeighbors(h0, h6, v2, e1, f0);
        h3->setNeighbors(h4, h0, m, e0, f1);
        h4->setNeighbors(h13, h9, v1, e4, f1);
        h5->setNeighbors(h11, h8, v3, e3, f3);

        h10->setNeighbors(h1, h11, m, e5, f2);
        h11->setNeighbors(h12, h10, v0, e5, f3);
        h12->setNeighbors(h5, h13, m, e6, f3);
        h13->setNeighbors(h3, h12, v3, e6, f1);
        h14->setNeighbors(h10, h15, v2, e7, f2);
        h15->setNeighbors(h2, h14, m, e7, f0);

        //Vertices after flip
        v0->halfedge() = h11;
        v1->halfedge() = h0;
        v2->halfedge() = h14;
        v3->halfedge() = h13;
        m->halfedge() = h3;

        //Edges after flip
        e0->halfedge() = h3;
        e1->halfedge() = h2;
        e2->halfedge() = h1;
        e3->halfedge() = h5;
        e4->halfedge() = h4;
        e5->halfedge() = h10;
        e6->halfedge() = h12;
        e7->halfedge() = h15;

        //Faces after flip
        f0->halfedge() = h0;
        f1->halfedge() = h3;
        f2->halfedge() = h10;
        f3->halfedge() = h11;

        e0->isNew=false;
        e5->isNew=false;
        e6->isNew=true;
        e7->isNew=true;

        return e0->halfedge()->vertex();
    }



    void MeshResampler::upsample( HalfedgeMesh& mesh )
    {
        // TODO Part 6.
        // This routine should increase the number of triangles in the mesh using Loop subdivision.
        // Each vertex and edge of the original surface can be associated with a vertex in the new (subdivided) surface.
        // Therefore, our strategy for computing the subdivided vertex locations is to *first* compute the new positions
        // using the connectity of the original (coarse) mesh; navigating this mesh will be much easier than navigating
        // the new subdivided (fine) mesh, which has more elements to traverse. We will then assign vertex positions in
        // the new mesh based on the values we computed for the original mesh.

        // #1: Compute new positions for all the vertices in the input mesh, using the Loop subdivision rule,

        for(VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); v++) {
          //compute new position for vertex using loop subdivision rule
          //(1 - n*u) * original_position + u * neighbor_position_sum

            double n = 0;
            double u;
            HalfedgeIter h = v->halfedge();
            HalfedgeIter h_orig = v->halfedge();
            Vector3D sum = Vector3D();

            // mark each vertex as being a vertex of the original mesh.
            v->isNew=false;

            //calculating the number of edges connected to this vertex
            do
            {
               // don't count boundary loops
               if(!h->face()->isBoundary() )
               {
                  n++; // increment degree
                  sum += h->twin()->vertex()->position;
//                  cout<<h->twin()->vertex()->position<<endl;
               }

               // move to the next halfedge around the vertex
               h = h->twin()->next();
            }
            while( h != h_orig ); // done iterating over halfedges

            //u=3/16 if n=3, else u=3/(8)n
            if(n==3){
                u=3.0/16.0;
            } else {
                u=3.0/(8.0*n);
            }
            //Calculate position
            Vector3D newpos = ((1-n*u)*v->position)+(u*sum);

            // Store them in Vertex::newPosition.
            v->newPosition=newpos;
//            cout<<"Old Pos:";
//            cout<<v->position<<endl;
//            cout<<"New Pos:";
//            cout<<newpos<<endl;

//            cout<<"n:";
//            cout<<n<<endl;
//            cout<<"u:";
//            cout<<u<<endl;
        }

        // #2: Compute the updated midpoint vertex positions associated with edges, and store it in Edge::newPosition.
        for(EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); e++) {
            Vector3D A = e->halfedge()->vertex()->position;
//            cout<<"A:";
//            cout<<A<<endl;
            Vector3D B = e->halfedge()->twin()->vertex()->position;
//            cout<<"B:";
//            cout<<B<<endl;
            Vector3D C = e->halfedge()->next()->next()->vertex()->position;
//            cout<<"C:";
//            cout<<C<<endl;
            Vector3D D = e->halfedge()->twin()->next()->next()->vertex()->position;
//            cout<<"D:";
//            cout<<D<<endl;
            e->isNew=false;
            e->newPosition = (0.375*(A+B))+(0.125*(C+D));
//            cout<<"New midpoint pos: ";
//            cout<<e->newPosition<<endl;
        }

//        cout<<"Successfully updated midpoint vertex positions associated with edges and stored them in Edge:newPosition"<<endl;


        // #3: Split every edge in the mesh, in any order.  For future reference, we're also going
        // to store some information about which subdivided edges come from splitting an edge in the
        // original mesh, and which edges are new, by setting the flat Edge::isNew.  Note that in this
        // loop, we only want to iterate over edges of the original mesh---otherwise, we'll end up splitting
        // edges that we just split (and the loop will never end!)

        for(EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); e++) {
            if(!e->isNew){
                if(e->halfedge()->vertex()->isNew==false){
                    if(e->halfedge()->twin()->vertex()->isNew==false){
                        //this returns the midpoint on where the edge is split
                        VertexIter midpoint=mesh.splitEdge(e);
                        midpoint->isNew=true;
                        midpoint->newPosition=e->newPosition;
                    }
                }
            }
        }

//        cout<<"Successfully split every edge in the mesh"<<endl;

         // #4 Now flip any new edge that connects an old and new vertex.
        for(EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); e++) {
            if(e->isNew){
                if(e->halfedge()->vertex()->isNew!=e->halfedge()->twin()->vertex()->isNew){
                    mesh.flipEdge(e);
                }
            }
        }

//        cout<<"Successfully flipped every edge that connected an old and new vertex"<<endl;

        // #5 Finally, copy the new vertex positions into final Vertex::position.
        for(VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); v++) {
            v->position=v->newPosition;
            //cout<<v->newPosition<<endl;
        }

//        cout<<"Successfully copied over all new vertex positions"<<endl;
    }

}
