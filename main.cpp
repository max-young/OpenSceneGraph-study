#define GL_SILENCE_DEPRECATION

#include <osg/ProxyNode>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main(int argc, char** argv)
{
  osg::ArgumentParser arguments(&argc, argv);
  osg::ref_ptr<osg::ProxyNode> root = new osg::ProxyNode;

  unsigned int childrenNo = 0;
  for (int i = 1; i < arguments.argc(); ++i)
  {
    if (arguments.isString(i))
      root->setFileName(childrenNo++, arguments[i]);
  }
  if (!root->getNumFileNames())
    root->setFileName(0, "cow.osgt");
  
  osgViewer::Viewer viewer;
  viewer.setSceneData(root.get());
  return viewer.run();
}