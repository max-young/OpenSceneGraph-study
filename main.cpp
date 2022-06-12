#define GL_SILENCE_DEPRECATION

#include <osg/io_utils>
#include <osg/TriangleFunctor>
#include <osg/Drawable>
#include <osgDB/ReadFile>
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class AttributePrinter: public osg::Drawable::AttributeFunctor
{
public:
  using AttributeType = osg::Drawable::AttributeType;
  inline const string getTypeName(AttributeType type)
  {
    static const string typeNames[] = {
      "Vertices", "Weights", "Normals", "colors", "Secondary Colors",
      "Fog Coordinates", "Attribute6", "Attribute7",
      "Texture Coords 0", "Texture Coords 1", "Texture Coords 2",
      "Texture Coords 3", "Texture Coords 4", "Texture Coords 5",
      "Texture Coords 6", "Texture Coords 7"
    };
    return typeNames[type];
  }

  template<typename T>
  void printInfo(AttributeType type, unsigned int size, T* front)
  {
    cout << "***" << getTypeName(type) << ": " << size << endl;
    for (unsigned int i = 0; i < size; ++i)
      cout << "(" << *(front+i) << ")";
    cout << endl << endl;
  }

  virtual void apply(AttributeType type, unsigned int size, float *front) {printInfo(type, size, front);}
  virtual void apply(AttributeType type, unsigned int size, osg::Vec2 *front) {printInfo(type, size, front);}
  virtual void apply(AttributeType type, unsigned int size, osg::Vec3 *front) {printInfo(type, size, front);}
  virtual void apply(AttributeType type, unsigned int size, osg::Vec4 *front) {printInfo(type, size, front);}
};

struct TrianglePrinter
{
  TrianglePrinter(){cout << "***Triangles***" << endl;}

  void operator()(const osg::Vec3 &v1, const osg::Vec3 &v2, const osg::Vec3 &v3) const
  {cout << "(" << v1 << ");(" << v2 << ");(" << v3 << ")" << endl;}
};

class FindGeometryVisitor: public osg::NodeVisitor
{
public:
  FindGeometryVisitor(): osg::NodeVisitor(TRAVERSE_ALL_CHILDREN) {}
    
  virtual void apply(osg::Node &node){traverse(node);}

  virtual void apply(osg::Geode &node)
  {
    for(unsigned int i = 0; i < node.getNumDrawables(); ++i)
    {
      osg::Drawable *drawable = node.getDrawable(i);
      if (!drawable) continue;
      cout << "[" << drawable->libraryName() << "::" << drawable->className() << "]" << endl;

      AttributePrinter attrPrinter;
      drawable->accept(attrPrinter);

      osg::TriangleFunctor<TrianglePrinter> triPrinter;
      drawable->accept(triPrinter);

      cout << endl;
    }
    traverse(node);
  }
};

int main(int argc, char** argv)
{
  osg::ArgumentParser arguments(&argc, argv);
  osg::Node *model = osgDB::readNodeFiles(arguments);
  if(!model) osgDB::readNodeFile("house.ive");

  FindGeometryVisitor fgv;
  if(model) model->accept(fgv);
  return 0;
}