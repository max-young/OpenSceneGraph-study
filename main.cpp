#define GL_SILENCE_DEPRECATION

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main()
{
  osgViewer::Viewer viewer;
  viewer.setSceneData(osgDB::readNodeFile("cow.osg"));
  return viewer.run();
}