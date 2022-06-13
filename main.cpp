#define GL_SILENCE_DEPRECATION

#include <osg/Group>
#include <osgDB/ReadFile>
#include <osgViewer/CompositeViewer>
#include <osgViewer/Viewer>

int main(int argc, char **argv)
{
  osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer;
  view1->setUpViewInWindow(0, 50, 320, 240);
  view1->setSceneData(osgDB::readNodeFile("cow.osg"));

  osg::ref_ptr<osgViewer::Viewer> view2 = new osgViewer::Viewer;
  view2->setUpViewInWindow(320, 50, 320, 240);
  view2->setSceneData(osgDB::readNodeFile("cessna.osg"));

  osg::ref_ptr<osgViewer::Viewer> view3 = new osgViewer::Viewer;
  view3->setUpViewInWindow(640, 50, 320, 240);
  view3->setSceneData(osgDB::readNodeFile("axes.osgt"));

  osgViewer::CompositeViewer compositeViewer;
  compositeViewer.addView(view1.get());
  compositeViewer.addView(view2.get());
  compositeViewer.addView(view3.get());
  return compositeViewer.run();
}