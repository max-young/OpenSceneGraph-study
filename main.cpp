#define GL_SILENCE_DEPRECATION

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Node>

#include <iostream>

using std::cout;
using std::endl;

// override默认NodeVisitor的遍历函数, 将其cout
class InfoVisitor : public osg::NodeVisitor
{
public:
  InfoVisitor() : osg::NodeVisitor(TRAVERSE_ALL_CHILDREN), _indent(0) {}

  virtual void apply(osg::Node &node)
  {
    for (int i = 0; i < _indent; ++i)
      cout << " ";
    cout << "[" << _indent + 1 << "]" << node.libraryName() << "::" << node.className() << endl;
    _indent++;
    traverse(node);
    _indent--;
  }

  // node叶子结点
  virtual void apply(osg::Geode &node)
  {
    for (int i = 0; i < _indent; ++i)
      cout << " ";
    cout << "[" << _indent + 1 << "]" << node.libraryName() << "::" << node.className() << endl;
    for (unsigned int n = 0; n < node.getNumDrawables(); ++n)
    {
      osg::Drawable *drawable = node.getDrawable(n);
      if (!drawable)
        continue;
      for (int i = 0; i <= _indent; ++i)
        cout << " ";
      cout << drawable->libraryName() << "::" << drawable->className() << endl;
    }
    _indent++;
    traverse(node);
    _indent--;
  }

protected:
  int _indent;
};

int main(int argc, char** argv)
{
  osg::ArgumentParser arguments(&argc, argv);
  osg::Node *root = osgDB::readNodeFiles(arguments);
  if (!root) root = osgDB::readNodeFile("axes.osgt");

  InfoVisitor infoVisitor;
  if (root) root->accept(infoVisitor);

  return 0;
}