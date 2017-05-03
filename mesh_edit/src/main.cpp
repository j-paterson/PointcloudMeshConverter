#include "CGL/CGL.h"

#include "collada.h"
#include "meshEdit.h" //contains octree.h
#include "bezierPatch.h"
#include "bezierCurve.h"
#include "mergeVertices.h"
#include "shaderUtils.h"
#include "pointcloud.h" //includes marchingcubes.h which includes octree.h :/

#include <iostream>

using namespace std;
using namespace CGL;

#define msg(s) cerr << "[Collada Viewer] " << s << endl;

PointCloud loadPointsAndNorms(FILE* file) {

  //should we negate the normals here?
  char* currString = "1";
  char* elString = "1";

  string holdString;
  string elHoldString;

  int numVertice = 0;
  CGL::Vector3D coordinatesHolder;
  CGL::Vector3D normalHolder;


  printf("%s\n", "inside load points and norms");

  /*
  while (currString != "end_header") {
    printf("%s\n", "hi");

    fscanf(file, "%c", currString);

    holdString = currString;

    printf("%s\n", "hi");

    if (holdString == "element") {

      fscanf(file, "%s", &elString);

      elHoldString = elString;

      if (elHoldString == "vertex") {
        fscanf(file, "%d", &numVertice);
      }

    }
  }
  */
  fscanf(file, "%d", &numVertice);


  PointCloud pc(numVertice);

  for (int i = 0; i < numVertice; i++) {
    fscanf(file, "%lf %lf %lf", &coordinatesHolder.x, &coordinatesHolder.y, &coordinatesHolder.z);
    fscanf(file, "%lf %lf %lf", &normalHolder.x, &normalHolder.y, &normalHolder.z);

    //cout << coordinatesHolder << endl;
    //cout << normalHolder << endl;

    pc.points.push_back(Point(coordinatesHolder, normalHolder));
  }

  return pc;
}

int loadFile(MeshEdit* collada_viewer, const char* path) {

  //made a MeshEdit local Octree var and in this function, set collada_viewer's Octree local var, then when we press V after the
  //file has been loaded, then we should see the Octree since the visualize function will
  //be able to work from within the


  Scene* scene = new Scene();

  std::string path_str = path;
  if (path_str.substr(path_str.length()-4, 4) == ".dae")
  {
    if (ColladaParser::load(path, scene) < 0) {
      delete scene;
      return -1;
    }
  }
  else if (path_str.substr(path_str.length()-4, 4) == ".bez")
  {
    Camera* cam = new Camera();
    cam->type = CAMERA;
    Node node;
    node.instance = cam;
    scene->nodes.push_back(node);
    Polymesh* mesh = new Polymesh();

    FILE* file = fopen(path, "r");
    int n = 0;
    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++)
    {
      BezierPatch patch;
      patch.loadControlPoints(file);
      patch.add2mesh(mesh);
      mergeVertices(mesh);
    }
    fclose(file);

    mesh->type = POLYMESH;
    node.instance = mesh;
    scene->nodes.push_back(node);
  }
  else if (path_str.substr(path_str.length()-4, 4) == ".NOtxt")
  {
    printf("%s\n", "reading txt");

    Camera* cam = new Camera();
    cam->type = CAMERA;
    Node node;
    node.instance = cam;
    scene->nodes.push_back(node);
    Polymesh* mesh = new Polymesh();

    FILE* file = fopen(path, "r");
    int n = 0;
    fscanf(file, "%d", &n);

    PointCloud pc(n);
    pc.loadPoints(file);
    pc.add2mesh(mesh);
    //mergeVertices(mesh);
    fclose(file);

    mesh->type = POLYMESH;
    node.instance = mesh;
    scene->nodes.push_back(node);
  }
  else if (path_str.substr(path_str.length()-4, 4) == ".rtf")
  {
    printf("%s\n", "reading rtf");
    \
    Camera* cam = new Camera();
    cam->type = CAMERA;
    Node node;
    node.instance = cam;
    scene->nodes.push_back(node);
    Polymesh* mesh = new Polymesh();

    FILE* file = fopen(path, "r");
    int n = 0;
    //fscanf(file, "%d", &n);

    //pass in a BBOX that is constructed based on the sphere being made
    BBox bb(Vector3D(-20, -20, -20), Vector3D(20, 20, 20)); //MAKE BBOX FOR SPHERE TEST
    OctreeNode oct(nullptr, 0, bb, 5); //CONSTRUCT FULL OCTREE
    collada_viewer->oNode = &oct;
    //maybe to test BBOX, don't run the marching cubes?

    PointCloud pc(10); //make pointcloud for mesh constructin
    Mesh* meshResult = new Mesh;
    marchingCubes(oct, IndicatorFunction, meshResult);
    pc.loadMesh(mesh, *meshResult);


    //mergeVertices(mesh);
    fclose(file);

    mesh->type = POLYMESH;
    node.instance = mesh;
    scene->nodes.push_back(node);
  } else if (path_str.substr(path_str.length()-4, 4) == ".txt") {

    printf("%s\n", "reading ply");
    Camera* cam = new Camera();
    cam->type = CAMERA;
    Node node;
    node.instance = cam;
    scene->nodes.push_back(node);
    Polymesh* mesh = new Polymesh();

    FILE* file = fopen(path, "r");
    int n = 0;
    //fscanf(file, "%d", &n);

    //make a function which takes the plyfile, parses it, and then constructs a point cloud which it returns;
    //this ply file will already have to normals generated from the normal generator exe
    PointCloud pc = loadPointsAndNorms(file);

    for (int i = 0; i < pc.points.size(); i++) {
      printf("%d\n", i);
    }

    BBox bb(Vector3D(-2.0, -2.0, -2.0), Vector3D(2.0, 2.0, 2.0));
    Mesh* meshResult = new Mesh;
    OctreeNode ocTest(nullptr, pc.points, 0, nullptr, bb, 12);
    marchingCubes(ocTest, IndicatorFunction, meshResult);
    pc.loadMesh(mesh, *meshResult);

    //mergeVertices(mesh);
    fclose(file);

    mesh->type = POLYMESH;
    node.instance = mesh;
    scene->nodes.push_back(node);
  }

  collada_viewer->load( scene );

  GLuint tex = makeTex("envmap/envmap.png");
  if(!tex) tex = makeTex("../envmap/envmap.png");
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, tex);
  glActiveTexture(GL_TEXTURE2);

  return 0;
}

int main( int argc, char** argv ) {

  const char* path = argv[1];
  std::string path_str = path;

  //////////////////////////////
  // Bezier curve viewer code //
  //////////////////////////////

  if (path_str.substr(path_str.length()-4, 4) == ".bzc")
  {
    // Each file contains a single Bezier curve's control points
    FILE* file = fopen(path, "r");

    int numControlPoints;
    fscanf(file, "%d", &numControlPoints);

    BezierCurve curve(numControlPoints);
    curve.loadControlPoints(file);
    fclose(file);

    // Create viewer
    Viewer viewer = Viewer();
    viewer.set_renderer(&curve);
    viewer.init();
    viewer.start();

    exit(EXIT_SUCCESS);

    return 0;
  }

  // create viewer
  Viewer viewer = Viewer();

  // create collada_viewer
  MeshEdit* collada_viewer = new MeshEdit();

  // set collada_viewer as renderer
  viewer.set_renderer(collada_viewer);

  // init viewer
  viewer.init();

  // load tests
  if( argc == 2 ) {
    if (loadFile(collada_viewer, argv[1]) < 0) exit(0);
  } else {
    msg("Usage: ./meshedit <path to scene file>"); exit(0);
  }

  // start viewer
  viewer.start();

  return 0;
}
